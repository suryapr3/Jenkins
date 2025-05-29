#!/usr/bin/sh

############################################################################
# 
# $0: this script name
# $1: HW_FLAG: 0: soc, 1: rcs
# $2: FW_ROOT, the root folder of ABC FW
#     example:"/nfs/site/disks/xne_abc_fe_002/users/yujing/arborcrest"
# $3: SUB_DIR: sub folder within FW ROOT where the script is launched.
#     This is also the workarea to cd to when CTH shell starts
#     exammple test_tgt/rtl
# $4: SCRIPT: the script to be launch in CTH shell
#     example: run_daily_rcs.py
# the full path of the script is then $FW_ROOT/$SUB_DIR/$SCRIPT
#
# Example: 
# 1. rcs (<path>/cron_simreg.sh 1 <path>run_daily_rcs.h) 
# /nfs/site/disks/xne_abc_fe_002/users/yujing/abc-cron/arborcrest/scripts/cron_simreg.sh 1 /nfs/site/disks/xne_abc_fe_002/users/yujing/abc-cron/arborcrest test_tgt/rtl/simreg run_daily_rcs.sh 
# 2. soc (<path>/cron_simreg.sh 1 <path>run_daily_rcs.h) 
# /nfs/site/disks/xne_abc_fe_002/users/yujing/abc-cron/arborcrest/scripts/cron_simregjob.sh 0 /nfs/site/disks/xne_abc_fe_002/users/yujing/abc-cron/arborcrest test_tgt/rtl/simreg run_daily_soc.sh 
#
# limitation:
# rcs and soc cannot be scheduled at the same time because they are working on
# the same repo and doing clean-build. RCS runs for about 30 min and SOC runs 
# for about 2 hours. 
# XXX SOC simreg will be scheduled 1 hour behind RCS XXX
############################################################################

#############################################################
# git pull the latest
#############################################################
cron_log () {
   echo "$1"
   echo $1 >> $SIMREG_CRON_LOG
}

#############################################################
# git pull the latest
#############################################################
cron_simreg_daily_update_repo_n_build () {

    FUNC_RET=0
    
    cron_log "#########################################"
    cron_log "updating repo $FW_ROOT"
    cron_log "#########################################"

    cd $FW_ROOT
    # update repo
    git pull --recurse-submodules=yes
    if [[ $? != 0 ]]; then
        cron_log "error, git pull failed"
        popd 
        FUNC_RET=1
        return
    fi

    cron_log "#########################################"
    cron_log "building elfs"
    cron_log "#########################################"
    source ./src.env
    make clean
    make
    if [[ $? != 0 ]]; then
        cron_log "error, make elfs failed"
        popd 
        FUNC_RET=1
        return
    fi

    cron_log "#########################################"
    cron_log "building SO"
    cron_log "#########################################"
    cd $RTL_DIR
    make clean
    make
    if [[ $? != 0 ]]; then
        cron_log "error, make SO failed"
        popd 
        FUNC_RET=1
        return
    fi
}

#############################################################
# cron job to do rcs daily run
#############################################################
cron_simreg_daily_run () {

    FUNC_RET=0

    cd $FW_ROOT
    source ./src.env

    cd $SIMREG_OUT_DIR
    # remove logs from prior run
    rm -f *##*$EZ_ZONE*vp*
    rm -rf $SIMREG_LOG_DIR
    rm -rf $SIMREG_LOG_DIR.*

    cron_log "####################################################"
    cron_log "submitting netbatch jobs under workarea: $WARD"
    cron_log "####################################################"

    # -f: force to CTH shell while it is already in it
    #CMD="/p/hdk/bin/cth_psetup -f -p abc -cfg HWCFE -read_only -cmd $CMD_RUN_JOB -logfile $LOG -ward $WARD"
    CMD="/p/hdk/bin/cth_psetup -f -p abc -cfg HWCFE -read_only -cmd $CMD_RUN_JOB -ward $WARD"
    cron_log "CMD=$CMD"
    eval $CMD

    if [[ $? != 0 ]]; then
        cron_log "error. not able to execute $CMD_RUN_JOB in CTH"
        FUNC_RET=1
        return
    fi

}

#############################################################
# wait for run to be done
#############################################################
cron_simreg_daily_wait () {

    FUNC_RET=0

    cd $SIMREG_OUT_DIR

    cron_log "waiting for job to start..."
    # wait for SIMREG_LOG_DIR to be created 
    log_dir_created=0
    for n in {0..100}
    do
        if [[ -d $SIMREG_LOG_DIR ]]; then
            log_dir_created=1
            # i.e. cd rcsabc
            cd $SIMREG_LOG_DIR
            break
        fi
        sleep 5
    done

    if [[ $log_dir_created == 0 ]]; then
        cron_log "job failed to start"
        FUNC_RET=1
        return
    fi

    # wait for ifeed_is_running to be created
    job_running=0
    for n in {0..100}
    do
        if [[ -f .ifeed_is_running ]]; then
            job_running=1
            break
        fi
        sleep 5
    done

    if [[ $job_running == 1 ]]; then
        cron_log "job is running..."
    else
        cron_log "job failed to start"
        FUNC_RET=1
        return
    fi
    
    cron_log "waiting up to 5 hour(s) for job to finish."

    # wait for 1 hour 
    job_done=0
    for n in {0..300}
    do
        if [[ ! -f .ifeed_is_running ]]; then
            job_done=1
            cron_log "job done in $n min"
            break
        fi
        sleep 60
    done

    if [[ $job_done == 0 ]]; then
        cron_log "job is not done"
        FUNC_RET=1
    fi
}

#############################################################
# check test results
#############################################################
cron_simreg_daily_check_result () {
    cron_log "checking results from rpt"
    # cd here so this func can be tested standalone
    cd "$SIMREG_OUT_DIR/$SIMREG_LOG_DIR"

    # get and save two most important lines. 
    # for simreg, one for each test in the rcs_dail.list
    TEST_RESULT=$(grep "DIR TAG\|TEST RESULT" *.rpt)
    cron_log "$TEST_RESULT"
    STATUS_LINE=$(grep "TEST STATUS" *.rpt) 
    cron_log "$STATUS_LINE"

    # look for this line in .rpt
    #     TEST STATUS: FAIL
    echo $STATUS_LINE | grep FAIL
    test_status=$?
    if [[ $test_status == 0 ]]; then
        FUNC_RET=1
    fi
}

#############################################################
# cron_simreg_daily_backup_logs
#############################################################
cron_simreg_daily_backup_logs () {
    # back to simreg output folder and make a save folder
    cd $SIMREG_OUT_DIR
    if [[ ! -d $SAVED_LOGS_DIR ]]; then
        mkdir $SAVED_LOGS_DIR
    fi

    # last weeks log dir
    logs_dir="$SAVED_LOGS_DIR/$SIMREG_SAVED_LOG_DIR"
    # remove the saved log folder from last week
    # i.e. rm -rf rcs_daily.list.Tue
    rm -rf $logs_dir
    # save today's, i.e. mv rcs_daily.list rcs_daily.list.Tue
    mv $SIMREG_LOG_DIR $logs_dir
}

#############################################################
# cron_simreg_daily_send_email
#############################################################
cron_simreg_daily_send_email () {

    mail_list="xne.rf.fw@intel.com"
    #debug, TODO: comment out for production 
    #mail_list="jing.h.yu@intel.com"

    # get git commit
    commit_id=$(git log  --pretty=oneline | grep HEAD)
    cron_log "commit id: $commit_id"

    # include commit id and logs locations in email 
    body="logs: $SIMREG_OUT_DIR/$SAVED_LOGS_DIR/$SIMREG_SAVED_LOG_DIR\n$TEST_RESULT\ncommit: $commit_id"

    subj="[cron simreg ${HW_FLAG} daily] test status:"
    if [[ $FUNC_RET == 0 ]]; then
        subj="$subj PASS"
    else
        subj="$subj FAIL"
    fi

    # use -e to treat \n as <cr>
    echo -e "$body" | mailx -s "$subj" $mail_list
}

#############################################################
# main
#############################################################
if [[ $# < 4 ]]; then
    echo "usage: cron_job.sh n script-sub-dir script"
    echo "       n: 0=soc; 1=rcs"
fi

# always 1 for now
export WARD_FLAG=1
export HW_RUN=$1
export FW_ROOT=$2
SUB_DIR=$3
SCRIPT=$4

# cheetah -ward value
if [[ $WARD_FLAG == 0 ]]; then 
    export WARD=$FW_ROOT
else
    export WARD=$FW_ROOT/$SUB_DIR
fi

# day-of-the-week
dow=$(date "+%a")
# run-time
ts=$(date "+%y_%m_%d-%H_%m_%s")

# dirs in abc repo
export RTL_DIR="$FW_ROOT/test_tgt/rtl"
export SIMREG_DIR="$RTL_DIR/simreg"
export CMD_RUN_JOB="$SIMREG_DIR/$SCRIPT"
export SAVED_LOGS_DIR="saved_logs"

# decide which simreg model and lists to use
if [[ $HW_RUN == 1 ]]; then
    # RCS
    export HW_FLAG="rcs"
    export SIM_MODEL="rcsabc"
else
    # SOC
    export HW_FLAG="soc"
    export SIM_MODEL="abc4016_unvex"
fi

# output of the simreg run
export SIMREG_OUT_DIR="$SIMREG_DIR/${SIM_MODEL}"
# the list to use
export SIMREG_LOG_DIR="${HW_FLAG}_daily.list"
# the name of the rpt, which has the same name as the list
# it will be moved to saved folder.
export SIMREG_REPORT="${HW_FLAG}_daily.rpt"

# logs are postfixed with day-of-the-week
export SIMREG_SAVED_LOG_DIR="$SIMREG_LOG_DIR.$dow"
export SIMREG_CRON_LOG="$SIMREG_OUT_DIR/cron_simreg_${HW_FLAG}_daily_log_$dow.log"

# init the run log
echo "test starts..." > $SIMREG_CRON_LOG

cron_log ""
cron_log "$ts"
cron_log ""
cron_log "CTH WARD=$WARD"
cron_log "CTH command=$CMD_RUN_JOB"
cron_log ""

# system shell vars used in cron. (cron has no env by default)
export PYTHONSTARTUP="/etc/pythonstart"
export PYTHONDEBUG=1
export PATH="/usr/intel/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/bin/X11:/usr/lib/mit/bin:/usr/lib/mit/sbin:/usr/local/bin:."

cron_log $PATH

#  CTH shell vars
export EC_SITE=sc
export EC_ZONE=sc14

export FUNC_RET=0

# will be updated in cron_dail_wait
export STATUS_LINE="fail to run"
export TEST_RESULT="NOT RUN"

#######################################################
# the test
#######################################################
cron_simreg_daily_update_repo_n_build

if [[ $FUNC_RET == 0 ]]; then
    cron_log "cron_simreg_daily_run"
    cron_simreg_daily_run
fi

if [[ $FUNC_RET == 0 ]]; then
    cron_log "cron_simreg_daily_wait"
    cron_simreg_daily_wait
fi

if [[ $FUNC_RET == 0 ]]; then
    cron_log "cron_simreg_daily_check_result"
    cron_simreg_daily_check_result
fi

cron_log "cron_simreg_daily_backup_logs"
cron_simreg_daily_backup_logs

cron_log "rc=$FUNC_RET"
cron_log "cron_simreg_daily_send_email"
cron_simreg_daily_send_email

cron_log "test ends"
