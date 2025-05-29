#!/bin/bash
set -xe

print_vars()
{
    echo "INFO: Current values for env variables are:"
    echo "PUBLISH_DIR : $PUBLISH_DIR"
}

usage()
{
    echo "Error: The following environment variables need to be set for execution"
    echo "PUBLISH_DIR : directory to publish artifacts"
    print_vars
    exit 1
}


: ${DAILY_PUBLISH_TEMPLATE=abcfw_template.html}

ABCFW_DIR=$(dirname "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )")
VER_FILE=$ABCFW_DIR/out/gen/src/fw_ver.c

cd $ABCFW_DIR
ABCFW_COMMIT_ID=$(git rev-parse --verify --short HEAD)
ABCFW_BIN_PKG=$(ls -Art $ABCFW_DIR/images/abcfw_bin*.tar.gz)
ABCFW_DOC_PKG=$(ls -Art $ABCFW_DIR/images/abcfw_html*.tar.gz)
ABCFW_SRC_PKG=$(ls -Art $ABCFW_DIR/images/abcfw_source*.tar.gz)
ABCFW_BIN_PKG_NAME=$(basename $ABCFW_BIN_PKG)
ABCFW_DOC_PKG_NAME=$(basename $ABCFW_DOC_PKG)
ABCFW_SRC_PKG_NAME=$(basename $ABCFW_SRC_PKG)

VER_MAJOR=$( grep major $VER_FILE | cut -d: -f2 | xargs )
VER_MINOR=$( grep minor $VER_FILE | cut -d: -f2 | xargs )
CURR_YEAR=$( grep year $VER_FILE | cut -d: -f2 | xargs )
CURR_MONTH=$( grep month $VER_FILE | cut -d: -f2 | xargs )
CURR_DAY=$( grep day $VER_FILE | cut -d: -f2 | xargs )
FW_EB=$( grep eb $VER_FILE | cut -d: -f2 | xargs )
FW_ITER=$( grep iter $VER_FILE | cut -d: -f2 | xargs )
BIN_VER_INFO=${VER_MAJOR}_${VER_MINOR}_${CURR_YEAR}${CURR_MONTH}${CURR_DAY}_${FW_EB}_${FW_ITER}_${ABCFW_COMMIT_ID}

ABCFW_BIN_PKG_NAME_PUBLISH=abcfw_bin_${BIN_VER_INFO}.tar.gz
ABCFW_DOC_PKG_NAME_PUBLISH=abcfw_html_${BIN_VER_INFO}.tar.gz
ABCFW_SRC_PKG_NAME_PUBLISH=abcfw_source_${BIN_VER_INFO}.tar.gz
MD5_SUM_BIN=`md5sum $ABCFW_DIR/images/$ABCFW_BIN_PKG_NAME | awk '{print $1}'`
MD5_SUM_SRC=`md5sum $ABCFW_DIR/images/$ABCFW_SRC_PKG_NAME | awk '{print $1}'`
BIN_PKG_SIZE=`ls -l $ABCFW_DIR/images/$ABCFW_BIN_PKG_NAME | awk '{print $5}'`
DOC_PKG_SIZE=`ls -l $ABCFW_DIR/images/$ABCFW_DOC_PKG_NAME | awk '{print $5}'`
SRC_PKG_SIZE=`ls -l $ABCFW_DIR/images/$ABCFW_SRC_PKG_NAME | awk '{print $5}'`
MD5_BIN=md5sum_bin
MD5_SRC=md5sum_src
SOC_HW_TAG=$(cat $ABCFW_DIR/ipcommon/misc/rtl_ver.txt | grep soc | sed -e 's/soc.*srvrgen4-//')

#
# Publish the artifacts
#

CURRDATE=`date`
cp $ABCFW_DIR/bldtools/templates/$DAILY_PUBLISH_TEMPLATE $ABCFW_DIR/images/index.html

cat << EOF1 > sed.tmp
s|DATE_TIME|$CURRDATE|g
s|VERSIONSTRING|${BIN_VER_INFO}|g
s|REF_ABCFW_BIN_PKG|${ABCFW_BIN_PKG_NAME_PUBLISH}|g
s|VAL_ABCFW_BIN_PKG|${ABCFW_BIN_PKG_NAME_PUBLISH}|g
s|REF_ABCFW_DOC_PKG|${ABCFW_DOC_PKG_NAME_PUBLISH}|g
s|REF_ABCFW_SRC_PKG|${ABCFW_SRC_PKG_NAME_PUBLISH}|g
s|VAL_ABCFW_SRC_PKG|${ABCFW_SRC_PKG_NAME_PUBLISH}|g
s|REF_MD5SUM_BIN|${MD5_BIN}|g
s|VAL_MD5SUM_BIN|${MD5_BIN}|g
s|REF_MD5SUM_SRC|${MD5_SRC}|g
s|VAL_MD5SUM_SRC|${MD5_SRC}|g
s|REF_BIN_PKG_SIZE|${BIN_PKG_SIZE}|g
s|REF_DOC_PKG_SIZE|${DOC_PKG_SIZE}|g
s|REF_SRC_PKG_SIZE|${SRC_PKG_SIZE}|g
s|ABCHW_TAG|${SOC_HW_TAG}|g
EOF1

sed -i -f sed.tmp $ABCFW_DIR/images/index.html
rm sed.tmp

# copy the artifacts to publish dir
mkdir -p $PUBLISH_DIR/download_fw
echo -e $ABCFW_BIN_PKG_NAME_PUBLISH "\t" $MD5_SUM_BIN "\t" $ABCFW_BIN_PKG_NAME_PUBLISH > $PUBLISH_DIR/download_fw/md5sum_bin
echo -e $ABCFW_SRC_PKG_NAME_PUBLISH "\t" $MD5_SUM_SRC "\t" $ABCFW_SRC_PKG_NAME_PUBLISH > $PUBLISH_DIR/download_fw/md5sum_src
cp $ABCFW_DIR/images/* $PUBLISH_DIR/download_fw/
cd $PUBLISH_DIR/download_fw
mv $ABCFW_BIN_PKG_NAME $ABCFW_BIN_PKG_NAME_PUBLISH
mv $ABCFW_DOC_PKG_NAME $ABCFW_DOC_PKG_NAME_PUBLISH
mv $ABCFW_SRC_PKG_NAME $ABCFW_SRC_PKG_NAME_PUBLISH

mkdir -p $PUBLISH_DIR/download_fw/docs
cd $PUBLISH_DIR/download_fw/docs
tar xfz $ABCFW_DIR/images/$ABCFW_DOC_PKG_NAME

mkdir -p $PUBLISH_DIR/download_fw/docs/html
cp -r $ABCFW_DIR/ipcommon/html $PUBLISH_DIR/download_fw/docs/html/hw
