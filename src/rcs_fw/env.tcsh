
# Environment setup for pre-sil/Cheetah environment.
# Since it's tcsh vs bash, can't be combined with w/src.env
setenv LM_LICENSE_FILE 18764@xtensa11p.elic.intel.com
if ( -d /nfs/site/disks/axx_0008/tools ) then
   echo "SC Zone 1"
   setenv TOOLS_BASE /nfs/site/disks/axx_0008/tools
endif
if ( -d /nfs/site/disks/xne_abc_fe_002/fw_tools ) then
   echo "SC Zone 14"
   setenv TOOLS_BASE /nfs/site/disks/xne_abc_fe_002/fw_tools
endif
if ( -d /nfs/site/disks/ncsg_0001/tools/xtensa ) then
   echo "AN EC"
   setenv TOOLS_BASE /nfs/an/disks/ncsg_0001/tools/xtensa
endif
if ( -d /workspace/hw/xne/tools ) then
   echo "AN Pocket"
   setenv TOOLS_BASE /workspace/hw/xne/tools
   setenv JAVA_HOME /tools/AGRtools/jdk-11.0.2
   setenv ANT_HOME /home/sys_swbuilds/ANT/apache-ant-1.7.1
   setenv PATH /v/share/conda/envs/dev/bin:${ANT_HOME}/bin:/usr/intel/bin:${PATH}
endif
setenv SWTOOLS_CTL $TOOLS_BASE/RJ-2023.2-linux/XtensaTools
setenv PRJDIR $PWD

setenv COV_TOOLS $TOOLS_BASE/cov-analysis-linux64-2022.3.1
