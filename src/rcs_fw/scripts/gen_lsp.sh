#!/usr/intel/bin/bash -e

KP1=HWC_RCS_KP1
LX7=HWC_RCS_LX7
ADC_LX7=hwc_adc_lx7

if [ ! -x $SWTOOLS_CTL/bin/xt-genldscripts ] ; then
    SWTOOLS_CTL=/nfs/site/disks/xne_abc_fe_002/fw_tools/RJ-2023.2-linux/XtensaTools
fi

# Aggressive 'garbage collection' in KP1 link stage may strip needed sections.
function keep_section {
    local section=$1
    local lnk_script=$2
    sed -i "s/*($section)/KEEP(*($section))/g" $lnk_script
}

function set_mpu_noncacheable {
    local tgt=$1

    for cpu in cal ax rx tx ana; do
        if ([ $cpu != cal ] || [ $tgt != iss ]); then
            sed -i '/_memmap_cacheattr_reset/s/_memmap_cacheattr_wb_trapnull/_memmap_cacheattr_bp_trapnull/g' scripts/lsp/$tgt/$cpu/ldscripts/elf32xtensa.x
        fi
    done
}

for target in sim hw iss ; do
    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$KP1 -v -b scripts/lsp/$target/cal
    keep_section .dram0.com_tables.data scripts/lsp/$target/cal/ldscripts/elf32xtensa.x
    keep_section .dram0.cal_tables.data scripts/lsp/$target/cal/ldscripts/elf32xtensa.x
    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$KP1 -v -b scripts/lsp/$target/factory
    keep_section .dram0.com_tables.data scripts/lsp/$target/factory/ldscripts/elf32xtensa.x
    keep_section .dram0.cal_tables.data scripts/lsp/$target/factory/ldscripts/elf32xtensa.x

    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$LX7 -v -b scripts/lsp/$target/tx
    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$LX7 -v -b scripts/lsp/$target/rx
    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$LX7 -v -b scripts/lsp/$target/ax
    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$ADC_LX7 -v -b scripts/lsp/$target/ana
    $SWTOOLS_CTL/bin/xt-genldscripts --xtensa-core=$LX7 -v -b scripts/lsp/$target/spl

    # as no cache used in ABC RCS CPUs, change default MPU setting to non-cacheable:
    set_mpu_noncacheable $target

    # Remove the compiled MPU artifacts.
    rm scripts/lsp/$target/*/libmpu.a
    rm scripts/lsp/$target/*/mpu_table.o
done
