#!/bin/bash

argv=("$@")
stage=${argv[0]}
outdir=${argv[1]}
add_delay=${argv[2]}
gating=${argv[3]}
cmd=${@:5}

if [ ! -f "${outdir}/.flowMgr/initiateIflow.touch" ]; then
	touch ${outdir}/.flowMgr/initiateIflow.touch
fi

touch ${outdir}/.flowMgr/.${stage}.touch_start
date +%s > ${outdir}/.flowMgr/.${stage}.start_time

if [ ${add_delay} != 0 ]; then
	sleep ${add_delay}
fi
eval ${cmd}
rc=$?

if [ $rc == 0 ]; then
	if [ -f ${outdir}/.flowMgr/${stage}.fail ]; then
		rm -rf ${outdir}/.flowMgr/${stage}.fail
	fi
	touch ${outdir}/.flowMgr/${stage}.touch
	date +%s > ${outdir}/.flowMgr/.${stage}.end_time
	exit ${rc}

else
	if [ $gating == 0 ]; then
		touch ${outdir}/.flowMgr/${stage}.fail
	fi
	printf "Job ${stage} failed. Check log in output directory (<outdir>/logs)";
	date +%s > ${outdir}/.flowMgr/.${stage}.end_time
	/bin/false
fi
if [ $gating == 0 ]; then
	touch ${outdir}/.flowMgr/${stage}.touch
	exit 0
fi
exit ${rc}
