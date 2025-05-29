#!/bin/bash -e

# /p/hdk/bin/cth_psetup -p ncsg -cfg HWCFE -read_only
# cd <some writeable space>

#NB_WASH_GROUPS=hawkcrest,eaglecrest,n5,n5p,user,soc,ncsg76
#NB_WASH_ENABLED=
#BINDIR=/nfs/site/disks/ncsg_00320/users/bhrichar/arborcrest/out/bin
#IP_MODELS=/nfs/site/disks/ncsg_ipm_0000


FASTLOAD=1
RUN_TIME=500
NO_RX=0
NO_CAL=0
DPI=0
FW_BUILD=hw
VERSION=hwc_rcs-srvrgen4-latest
MSSG_CPU=tx

if [ ! -d "$IP_MODELS/hwc_rcs/$VERSION" ] ; then
    VERSION=`ls -1tr $IP_MODELS/hwc_rcs | tail -1`
fi

while [[ $# -gt 0 ]] ; do
    case $1 in
        -h|--help|--h)
           echo $0 [-v rcs] [-f] [-b hw\|sim] [fw_dir] [-args [args]]
           echo "      -args [*]:   specify arguments to DPI based C test, required to trigger DPI run."
           echo "      -b fw:       specify sim or hw build to run, default hw."
           echo "      -f:          Front-door pre-load (slow loading via AXI transactions)."
           echo "      -ocal:       Omit the cal CPU (KP1) from being loaded."
           echo "      -orx:        Omit the RX CPU (LX7_1) from being loaded."
           echo "      -p cpu:      CPU to monitor for print messages: tx rx cal."
           echo "      -u subdir:   hw unit test directory, all cores binaries needed.."
           echo "      -utx subdir: hw unit test directory, tx/LX0 only."
           echo "      -v rcs:      specify RCS version, i.e. 22ww38c"
           echo "                   will attempt to determine latest if omitted."
           echo "      fw_dir:      point to directory containing ELF images, uses \$PRJDIR base if defined."
           exit 2
           ;;
	-run)
	   RUN_TIME=$2
	   shift
	   shift
	   ;;
	-orx)
	   NO_RX=1
	   shift
	   ;;
        -ocal)
	   NO_CAL=1
	   shift
	   ;;
	-utx)
	   NO_RX=1
	   NO_CAL=1
	   U_SUBDIR=$2
	   shift
	   shift
	   ;;
	-u|--u)
	   U_SUBDIR=$2
	   shift
	   shift
	   ;;
        -v|--v)
           VERSION=hwc_rcs-srvrgen4-$2
           shift
           shift
           ;;
        -f|--f)
           FASTLOAD=0
           shift
           ;;
	-p|--p)
	   MSSG_CPU=$2
	   shift
	   shift
	   ;;
        -args|--args)
           C_SWCH=+RCS_RPC_C_TEST
           shift
           ARG_SWCH=+start_c_code_str="\"$*\""
           DPI=1
           break
           ;;
        -b|--b)
           FW_BUILD=$2
          shift
          shift
          ;;
    -kp1_test)
        KP1_TEST_TRUE=1
        shift
        ;;    
	*)
          BINDIR=$(realpath $1)
          shift
          ;;
              
    esac
done

if [ ! -d "$IP_MODELS/hwc_rcs/$VERSION" ] ; then
    echo "Unable to find RCS model: $IP_MODELS/hwc_rcs/$VERSION"
    exit 1
fi
VERSION_DIR=$IP_MODELS/hwc_rcs/$VERSION


if [ ! -d "$BINDIR" ]; then
    if [ "$PRJDIR" != "" ];  then
        BINDIR=$PRJDIR/out/bin
    else
        echo "FW Binary Directory not specified."
        exit 1
    fi
fi



if [ "$DPI" == "1" ]; then
        SO_DIR=$BINDIR/../../test_tgt/rtl
    if [ ! -f $SO_DIR/fw_sim.so ] ; then
        echo "RTL C DPI SO module not found: $SO_DIR/fw_sim.so"
        exit 1
   fi
   DPI_BUILD="-fwso $SO_DIR fw_sim"
   DPI_PARMS="$DPI_BUILD -simv_args $ARG_SWCH -simv_args-"
fi
if [ "$U_SUBDIR" != "" ]; then
    BINDIR_OLD=$BINDIR
    BINDIR=$BINDIR/$U_SUBDIR
    if [ "$FASTLOAD" == "0" ]; then
        echo "Must use fast load w/HW unit test."
        exit 1
    fi
    if [ $KP1_TEST_TRUE == "1" ]; then
        if [ ! -f "$BINDIR_OLD/tx_${FW_BUILD}.elf" ]; then
            echo "Tx firmware must be available to run any KP1 test"
            exit 1
        else
            cp  "$BINDIR_OLD/tx_${FW_BUILD}.elf" $BINDIR 
            cp  "$BINDIR_OLD/rx_${FW_BUILD}.elf" $BINDIR 
            cp  "$BINDIR_OLD/sram/tx_${FW_BUILD}_rom.data" $BINDIR/sram 
        fi
    fi                
fi

echo "bindir:$BINDIR"
ROMFILE=$BINDIR/sram/tx_${FW_BUILD}_rom.data

if [ "$FASTLOAD" == "0" ]; then
    IRAMFILE0=$BINDIR/sram//tx_${FW_BUILD}_iram.data
    DRAMFILE0=$BINDIR/sram/tx_${FW_BUILD}_dram.data
    IRAMLINES0=`tail -1 $IRAMFILE0`
    DRAMLINES0=`tail -1 $DRAMFILE0`
    IRAMFILE1=$BINDIR/sram/rx_${FW_BUILD}_iram.data
    DRAMFILE1=$BINDIR/sram/rx_${FW_BUILD}_dram.data
    IRAMLINES1=`tail -1 $IRAMFILE1`
    DRAMLINES1=`tail -1 $DRAMFILE1`
    IRAMFILE2=$BINDIR/sram/cal_${FW_BUILD}_iram.data
    DRAMFILE2=$BINDIR/sram/cal_${FW_BUILD}_dram.data
    IRAMLINES2=`tail -1 $IRAMFILE2`
    DRAMLINES2=`tail -1 $DRAMFILE2`

    if [ ! -f $IRAMFILE0 ] ; then
        echo "IRAM0 not found: $IRAMFILE0"

        exit 3
    fi
    if [ ! -f $DRAMFILE0 ] ; then
        echo "DRAM0 not found: $DRAMFILE0"
        exit 4
    fi
fi

# ROM and CPU 0 are required.
if [ ! -f $ROMFILE ]; then
    echo "ROM not found: $ROMFILE"
    exit 2
fi

if [ ! -f $BINDIR/tx_${FW_BUILD}.elf ]; then
    echo "Boot (TX) elf file not found: $BINDIR/tx_${FW_BUILD}.elf"
    exit 2
fi

if [ "$FASTLOAD" == "1" ]; then
    echo "Executing FASTLOAD $FW_BUILD FW from: $BINDIR"
else
    echo "Executing $FW_BUILD FW from: $BINDIR"
fi

MSSG_TRACE=
if [ $FW_BUILD == "sim" ]; then
    MSSG_FILE=$BINDIR/info/${MSSG_CPU}_sim_mssg.txt

    case $MSSG_CPU in
       tx) TRACE_LO=23FF00
           TRACE_HI=23FF3F
           ;;
       rx) TRACE_LO=23FF40
           TRACE_HI=23FF7F
           ;;
       cal) TRACE_LO=23FF80
            TRACE_HI=23FFBF
            ;;
    esac

    if [ -f $MSSG_FILE ]; then
        MSSG_TRACE="+DVTraceAddr_lo=$TRACE_LO +DVTraceAddr_hi=$TRACE_HI +FWMsgTable_pathfn=$MSSG_FILE"
    fi
fi


# Preload SRAM from KP1 binary, if needed.
SRAM_PRELOAD_FILE=$BINDIR/sram/cal_${FW_BUILD}_sram.data
if [ `grep -v 00000000000000000000000000000000 $SRAM_PRELOAD_FILE | wc -l` -gt 2 ]; then
    SRAM_PRELOAD="+RCS_RSM_PRELOAD_SRAM +RCS_RSM0_SRAM_FILE=$SRAM_PRELOAD_FILE"
fi


if [ "$FASTLOAD" == "1" ]; then

    LX0_LOAD="-pre $VERSION_DIR/scripts/soc_go_wrap LX7 $BINDIR/tx_${FW_BUILD}.elf LX70_data -pre- 
              -simv_args +LX70_BACKDOOR_PRELOAD +LX70_PRELOAD_FILE_PATH=LX70_data/prog/tx_${FW_BUILD}.elf/dat_files -simv_args-"
   
    LX1_LOAD="-pre $VERSION_DIR/scripts/soc_go_wrap LX7 $BINDIR/rx_${FW_BUILD}.elf LX71_data -pre- 
              -simv_args +LX71_BACKDOOR_PRELOAD +LX71_PRELOAD_FILE_PATH=LX71_data/prog/rx_${FW_BUILD}.elf/dat_files -simv_args-"

    KP_LOAD="-pre $VERSION_DIR/scripts/soc_go_wrap KP1 $BINDIR/cal_${FW_BUILD}.elf KP1_data -pre-
              -simv_args +KP1_BACKDOOR_PRELOAD +KP1_PRELOAD_FILE_PATH=KP1_data/prog/cal_${FW_BUILD}.elf/dat_files $SRAM_PRELOAD -simv_args-"

    if [ "$NO_RX" == "1" ]; then
       LX1_LOAD=''
    fi
    if [ "$NO_CAL" == "1" ]; then
       KP_LOAD=''
    fi

else

    LX0_LOAD="-simv_args +RCS_RPC_LX7_0_IRAM_FILE=$IRAMFILE0 +RCS_RPC_LX7_0_IRAM_LINES=$IRAMLINES0 +RCS_RPC_LX7_0_DRAM_FILE=$DRAMFILE0 +RCS_RPC_LX7_0_DRAM_LINES=$DRAMLINES0 +RPC_FRONTDOOR_PRELOAD -simv_args-"
    LX1_LOAD="-simv_args +RCS_RPC_LX7_1_IRAM_FILE=$IRAMFILE1 +RCS_RPC_LX7_1_IRAM_LINES=$IRAMLINES1 +RCS_RPC_LX7_1_DRAM_FILE=$DRAMFILE1 +RCS_RPC_LX7_1_DRAM_LINES=$DRAMLINES1 -simv_args-"
    KP_LOAD="-simv_args +RCS_RPC_KP1_IRAM_FILE=$IRAMFILE2 +RCS_RPC_KP1_IRAM_LINES=$IRAMLINES2 +RCS_RPC_KP1_DRAM_FILE=$DRAMFILE2 +RCS_RPC_KP1_DRAM_LINES=$DRAMLINES2 $SRAM_PRELOAD -simv_args-"
    # per bank, or one large memory.
    # RSM_BANK_LOAD="-simv_args +RCS_RSM0_FILE=$RSMFILE0 +RCS_RSM0_LINES=$RSMLINES0 +RCS_RSM1_FILE=$RSMFILE1 +RCS_RSM1_LINES=$RSMLINES1 -simv_args-"
    # RSM_LOAD="-simv_args +RCS_RSM_FILE=$RSMFILE +RCS_RSM_LINES=$RSMLINES -simv_args-"

    if [ "$NO_RX" == "1" ]; then
       LX1_LOAD=''
    fi
    if [ "$NO_CAL" == "1" ]; then
       KP_LOAD=''
    fi
fi

echo "Running RCS model: $VERSION"
echo 
echo "For VERDE use: runverdi -d rcsabc -m rcs_rpc_tb -w $VERSION_DIR -ssf novas.vf &"
echo 
sleep 5

nbjob run --target zsc14_normal --qslot /xne/abc/rgr --class "SLES12SP5&&8G" trex rcs_rpc_lx7_0_boot -dut rcsabc -model rcs_rpc_tb -ms -test_name_plusarg UVM_TESTNAME -test_name_plusarg UVM_TESTNAME -ms- -noexist \
-pre /bin/ln -s $ROMFILE asdvds0g4l1p16384x32m16b8c1p1d0r0rm4rw00zh0h0ms0mg1_img0.hex -pre- \
-post $VERSION_DIR/scripts/xt_rtldis -post- \
$LX0_LOAD $LX1_LOAD $KP_LOAD \
-seed 1371932087 -simv_args +UVM_TIMEOUT=15000000000 +RCS_RPC_EN $C_SWCH +CTECH_LIB_META_OFF $MSSG_TRACE \
+RCS_RPC_RUN_CORE0_N_US=$RUN_TIME +fsdb_all -cm_dir . -simv_args- \
$DPI_PARMS -ver $VERSION_DIR

