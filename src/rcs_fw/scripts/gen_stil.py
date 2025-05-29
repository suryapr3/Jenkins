#!/usr/bin/env python3
#
# INTEL CONFIDENTIAL
#
# Copyright 2022 Intel Corporation All Rights Reserved.
#
# The source code contained or described herein and all documents related
# to the source code ("Material") are owned by Intel Corporation or its
# suppliers or licensors. Title to the Material remains with Intel
# Corporation or its suppliers and licensors. The Material contains trade
# secrets and proprietary and confidential information of Intel or its
# suppliers and licensors. The Material is protected by worldwide copyright
# and trade secret laws and treaty provisions. No part of the Material
# may be used, copied, reproduced, modified, published, uploaded, posted,
# transmitted, distributed, or disclosed in any way without Intel's prior
# express written permission.
#
# No license under any patent, copyright, trade secret or other
# intellectual property right is granted to or conferred upon you by
# disclosure or delivery of the Materials, either expressly, by
# implication, inducement, estoppel or otherwise. Any license under such
# intellectual property rights must be express and approved by Intel in
# writing.


import sys
import os
import argparse
import typing
import tarfile


class rcs_dmac_cfgreg_reg_t:
    DMAC_EN = int(0)
    INT_EN = int(0)
    RSVD_DMAC_CFGREG = int(0)
    value = int(0)

    def __init__(self, value=0):
        self.set(value)

    def get(self):
        res = 0
        res += self.DMAC_EN
        res += self.INT_EN << 1
        res += self.RSVD_DMAC_CFGREG << 2
        return res

    def set(self, value):
        self.DMAC_EN = value & 0x1
        self.INT_EN = (value >> 1) & 0x2
        self.RSVD_DMAC_CFGREG = (value >> 2) & 0xFFFFFFFFFFFFFFFC

    def addr(self):
        return 0x270010


class rcs_dmac_ch1_cfg_reg_t:
    SRC_MULTBLK_TYPE = int(0)
    DST_MULTBLK_TYPE = int(0)
    RSVD_DMAC_CHX_CFG_4TO17 = int(0)
    RD_UID = int(0)
    RSVD_DMAC_CHX_CFG_22TO24 = int(0)
    WR_UID = int(0)
    RSVD_DMAC_CHX_CFG_29TO31 = int(0)
    TT_FC = int(0)
    HS_SEL_SRC = int(0)
    HS_SEL_DST = int(0)
    SRC_HWHS_POL = int(0)
    DST_HWHS_POL = int(0)
    SRC_PER = int(0)
    RSVD_DMAC_CHX_CFG_42_39 = int(0)
    RSVD_DMAC_CHX_CFG_43 = int(0)
    DST_PER = int(0)
    RSVD_DMAC_CHX_CFG_47_44 = int(0)
    RSVD_DMAC_CHX_CFG_48 = int(0)
    CH_PRIOR = int(0)
    LOCK_CH = int(0)
    LOCK_CH_L = int(0)
    SRC_OSR_LMT = int(0)
    DST_OSR_LMT = int(0)
    RSVD_DMAC_CHX_CFG_63 = int(0)

    def __init__(self, value=0):
        self.set(value)

    def get(self):
        res = 0
        res += self.RSVD_DMAC_CHX_CFG_63 << 63
        res += self.DST_OSR_LMT << 59
        res += self.SRC_OSR_LMT << 55
        res += self.LOCK_CH_L << 53
        res += self.LOCK_CH << 52
        res += self.CH_PRIOR << 49
        res += self.RSVD_DMAC_CHX_CFG_48 << 48
        res += self.RSVD_DMAC_CHX_CFG_47_44 << 47
        res += self.DST_PER << 44
        res += self.RSVD_DMAC_CHX_CFG_43 << 43
        res += self.RSVD_DMAC_CHX_CFG_42_39 << 42
        res += self.SRC_PER << 39
        res += self.DST_HWHS_POL << 38
        res += self.SRC_HWHS_POL << 37
        res += self.HS_SEL_DST << 36
        res += self.HS_SEL_SRC << 35
        res += self.TT_FC << 32
        res += self.RSVD_DMAC_CHX_CFG_29TO31 << 29
        res += self.WR_UID << 25
        res += self.RSVD_DMAC_CHX_CFG_22TO24 << 22
        res += self.RD_UID << 18
        res += self.RSVD_DMAC_CHX_CFG_4TO17 << 4
        res += self.DST_MULTBLK_TYPE << 2
        res += self.SRC_MULTBLK_TYPE
        return res

    def set(self, value):
        self.RSVD_DMAC_CHX_CFG_63 = (value >> 63) & 0x1
        self.DST_OSR_LMT = (value >> 59) & 0xF
        self.SRC_OSR_LMT = (value >> 55) & 0xF
        self.LOCK_CH_L = (value >> 53) & 0x3
        self.LOCK_CH = (value >> 52) & 0x1
        self.CH_PRIOR = (value >> 49) & 0x7
        self.RSVD_DMAC_CHX_CFG_48 = (value >> 48) & 0x1
        self.RSVD_DMAC_CHX_CFG_47_44 = (value >> 47) & 0x1
        self.DST_PER = (value >> 44) & 0x7
        self.RSVD_DMAC_CHX_CFG_43 = (value >> 43) & 0x1
        self.RSVD_DMAC_CHX_CFG_42_39 = (value >> 42) & 0x1
        self.SRC_PER = (value >> 39) & 0x7
        self.DST_HWHS_POL = (value >> 38) & 0x1
        self.SRC_HWHS_POL = (value >> 37) & 0x1
        self.HS_SEL_DST = (value >> 36) & 0x1
        self.HS_SEL_SRC = (value >> 35) & 0x1
        self.TT_FC = (value >> 32) & 0x7
        self.RSVD_DMAC_CHX_CFG_29TO31 & 0x7
        self.WR_UID = (value >> 25) & 0xF
        self.RSVD_DMAC_CHX_CFG_22TO24 = (value >> 22) & 0x7
        self.RD_UID = (value >> 18) & 0xF
        self.RSVD_DMAC_CHX_CFG_4TO17 = (value >> 4) & 0x3FFF
        self.DST_MULTBLK_TYPE = (value >> 2) & 0x3
        self.SRC_MULTBLK_TYPE = value & 0x1

    def addr(self):
        return 0x270120


class rcs_dmac_chenreg_reg_t:
    CH1_EN = int(0)
    CH2_EN = int(0)
    RSVD_DMAC_CHENREG_CH_EN = int(0)
    CH1_EN_WE = int(0)
    CH2_EN_WE = int(0)
    RSVD_DMAC_CHENREG_CH_WE_EN = int(0)
    CH1_SUSP = int(0)
    CH2_SUSP = int(0)
    RSVD_DMAC_CHENREG_CH_SUSP = int(0)
    CH1_SUSP_WE = int(0)
    CH2_SUSP_WE = int(0)
    RSVD_DMAC_CHENREG_CH_SUSP_WE = int(0)
    CH1_ABORT = int(0)
    CH2_ABORT = int(0)
    RSVD_DMAC_CHENREG_CH_ABORT = int(0)
    CH1_ABORT_WE = int(0)
    CH2_ABORT_WE = int(0)
    RSVD_DMAC_CHENREG_CH_ABORT_WE = int(0)
    RSVD_DMAC_CHENREG = int(0)

    def __init__(self, value=0):
        self.set(value)

    def get(self):
        res = 0
        res += self.CH1_EN
        res += self.CH2_EN << 1
        res += self.RSVD_DMAC_CHENREG_CH_EN << 2
        res += self.CH1_EN_WE << 8
        res += self.CH2_EN_WE << 9
        res += self.RSVD_DMAC_CHENREG_CH_WE_EN << 10
        res += self.CH1_SUSP << 16
        res += self.CH2_SUSP << 17
        res += self.RSVD_DMAC_CHENREG_CH_SUSP << 18
        res += self.CH1_SUSP_WE << 24
        res += self.CH2_SUSP_WE << 25
        res += self.RSVD_DMAC_CHENREG_CH_SUSP_WE << 26
        res += self.CH1_ABORT << 32
        res += self.CH2_ABORT << 33
        res += self.RSVD_DMAC_CHENREG_CH_ABORT << 34
        res += self.CH1_ABORT_WE << 40
        res += self.CH2_ABORT_WE << 41
        res += self.RSVD_DMAC_CHENREG_CH_ABORT_WE << 42
        res += self.RSVD_DMAC_CHENREG_CH_ABORT_WE << 48
        return res

    def set(self, value):
        self.CH1_EN = (value) & 0x1
        self.CH2_EN = (value >> 1) & 0x1
        self.RSVD_DMAC_CHENREG_CH_EN2 = (value >> 2) & 0x3F
        self.CH1_EN_WE = (value >> 8) & 0x1
        self.CH2_EN_WE = (value >> 9) & 0x1
        self.RSVD_DMAC_CHENREG_CH_WE_EN = (value >> 10) & 0x3F
        self.CH1_SUSP = (value >> 16) & 0x1
        self.CH2_SUSP = (value >> 17) & 0x1
        self.RSVD_DMAC_CHENREG_CH_SUSP = (value >> 18) & 0x3F
        self.CH1_SUSP_WE = (value >> 24) & 0x1
        self.CH2_SUSP_WE = (value >> 25) & 0x1
        self.RSVD_DMAC_CHENREG_CH_SUSP_WE = (value >> 26) & 0x3F
        self.CH1_ABORT = (value >> 32) & 0x1
        self.CH2_ABORT = (value >> 33) & 0x1
        self.RSVD_DMAC_CHENREG_CH_ABORT = (value >> 34) & 0x3F
        self.CH1_ABORT_WE = (value >> 40) & 0x1
        self.CH2_ABORT_WE = (value >> 41) & 0x1
        self.RSVD_DMAC_CHENREG_CH_ABORT_WE = (value >> 42) & 0x3F
        self.RSVD_DMAC_CHENREG = (value >> 48) & 0xFFFF

    def addr(self):
        return 0x270018


class rcs_dmac_ch1_ctl_reg_t:
    SMS = int(0)
    DMS = int(0)
    SINC = int(0)
    DINC = int(0)
    SRC_TR_WIDTH = int(0)
    DST_TR_WIDTH = int(0)
    SRC_MSIZE = int(0)
    DST_MSIZE = int(0)
    AR_CACHE = int(0)
    AW_CACHE = int(0)
    NONPOSTED_LASTWRITE_EN = int(0)
    AR_PROT = int(0)
    AW_PROT = int(0)
    ARLEN_EN = int(0)
    ARLEN = int(0)
    AWLEN_EN = int(0)
    AWLEN = int(0)
    SRC_STAT_EN = int(0)
    DST_STAT_EN = int(0)
    IOC_BLKTFR = int(0)
    SHADOWREG_OR_LLI_LAST = int(0)
    SHADOWREG_OR_LLI_VALID = int(0)

    def __init__(self, value=0):
        self.set(value)

    def get(self):
        res = 0
        res += self.SHADOWREG_OR_LLI_VALID << 63
        res += self.SHADOWREG_OR_LLI_LAST << 62
        res += self.IOC_BLKTFR << 58
        res += self.DST_STAT_EN << 57
        res += self.SRC_STAT_EN << 56
        res += self.AWLEN << 48
        res += self.AWLEN_EN << 47
        res += self.ARLEN << 39
        res += self.ARLEN_EN << 38
        res += self.AW_PROT << 35
        res += self.AR_PROT << 32
        res += self.NONPOSTED_LASTWRITE_EN << 30
        res += self.AW_CACHE << 26
        res += self.AR_CACHE << 22
        res += self.DST_MSIZE << 18
        res += self.SRC_MSIZE << 14
        res += self.DST_TR_WIDTH << 11
        res += self.SRC_TR_WIDTH << 8
        res += self.DINC << 6
        res += self.SINC << 4
        res += self.DMS << 2
        res += self.SMS
        return res

    def set(self, value):
        self.SHADOWREG_OR_LLI_VALID = (value >> 63) & 0x1
        self.SHADOWREG_OR_LLI_LAST = (value >> 62) & 0x1
        self.IOC_BLKTFR = (value >> 58) & 0x1
        self.DST_STAT_EN = (value >> 57) & 0x1
        self.SRC_STAT_EN = (value >> 56) & 0x1
        self.AWLEN = (value >> 48) & 0xFF
        self.AWLEN_EN = (value >> 47) & 0x1
        self.ARLEN = (value >> 39) & 0xFF
        self.ARLEN_EN = (value >> 38) & 0x1
        self.AW_PROT = (value >> 35) & 0x3
        self.AR_PROT = (value >> 32) & 0x3
        self.NONPOSTED_LASTWRITE_EN = (value >> 30) & 0x1
        self.AW_CACHE = (value >> 26) & 0xF
        self.AR_CACHE = (value >> 22) & 0xF
        self.DST_MSIZE = (value >> 18) & 0xF
        self.SRC_MSIZE = (value >> 14) & 0xF
        self.DST_TR_WIDTH = (value >> 11) & 0x3
        self.SRC_TR_WIDTH = (value >> 8) & 0x3
        self.DINC = (value >> 6) & 0x1
        self.SINC = (value >> 4) & 0x1
        self.DMS = (value >> 2) & 0x1
        self.SMS = value & 0x1

        def addr(self):
            return 0x270118


class rcs_dmac_ch1_llp_reg_t:
    LMS = int(0)
    RSVD_DMAC_CHX_LLP_1TO5 = int(0)
    LOC = int(0)

    def __init__(self, value=0):
        self.set(value)

    def get(self):
        res = 0
        res += self.LOC << 6
        res += self.RSVD_DMAC_CHX_LLP_1TO5 << 1
        res += self.LMS
        return res

    def set(self, value):
        self.LOC = (value >> 6) & 0x1FFFFFFFFFFFFFFF
        self.RSVD_DMAC_CHX_LLP_1TO5 = (value >> 1) & 0x3F
        self.LMS = value & 0x1

    def addr(self):
        return 0x270128


class rcs_gpreg_core3_ctrl_reg_t:
    CORE_RUNSTALL = int(0)
    CORE_STATVECTORSEC = int(0)
    OCDHALTONRESET = int(0)

    def __init__(self, value=0x11):
        self.set(value)

    def get(self):
        res = 0
        res += self.CORE_RUNSTALL << 0
        res += self.CORE_STATVECTORSEC << 4
        res += self.OCDHALTONRESET << 8
        return res

    def set(self, value):
        self.CORE_RUNSTALL = value & 0x1
        self.CORE_STATVECTORSEC = (value >> 4) & 0x1
        self.OCDHALTONRESET = (value >> 8) & 0x1

    def addr(self):
        return 0x26C014


class ant_csr_adc_cpu_ctrl_reg_t:
    RUN_STALL = int(0)
    STATVECTORSEL = int(0)

    def __init__(self, value=0x1):
        self.set(value)

    def get(self):
        res = 0
        res += self.RUN_STALL << 0
        res += self.STATVECTORSEL << 1
        return res

    def set(self, value):
        self.RUN_STALL = value & 0x1
        self.STATVECTORSEL = (value >> 1) & 0x1

    def addr(self):
        return 0x49F308C


class gpdma_desc:
    source = int(0)
    dst = int(0)
    block_ts = int(0)
    llp = int(0)
    ctl = rcs_dmac_ch1_ctl_reg_t(0)
    sstat = int(0)
    dstat = int(0)
    llp_status = int(0)
    reserved = int(0)

    def __init__(self, value=0):
        self.ctl = rcs_dmac_ch1_ctl_reg_t(0)

    def print_desc(self, file_obj: "typing.TextIO", output_format: "str"):
        print(output_format.format(self.source), file=file_obj)
        print(output_format.format(self.dst), file=file_obj)
        print(output_format.format(self.block_ts), file=file_obj)
        print(output_format.format(self.llp), file=file_obj)
        print(output_format.format(self.ctl.get()), file=file_obj)
        temp = 0
        temp = self.dstat << 32
        temp += self.sstat
        print(output_format.format(temp), file=file_obj)
        print(output_format.format(self.llp_status), file=file_obj)
        print(output_format.format(self.reserved), file=file_obj)

    def get_desc_size(self):
        size = 0
        size += self.source.nbytes
        size += self.dst.nbytes
        size += self.block_ts.nbytes
        size += self.llp.nbytes
        size += self.ctl.nbytes
        size += self.sstat.nbytes
        size += self.dstat.nbytes
        size += self.llp_status.nbytes
        size += self.reserved.nbytes
        return size


def generate_descriptor_list(
    src_start_address: "list[int]",
    dest_start_address: "list[int]",
    desc_start_address: "int",
    image_size: "list[int]",
    program: "str",
) -> gpdma_desc:
    gpdma_list: "list[gpdma_desc]" = []
    # width = 18
    # print_format = "{0:#0" + str(width) + "x}"
    idx = 0
    block_size_16k = int(0x4000)
    partial_block_size = 0
    if program == "ana":
        num_cpu = 4
        memory_offset = int("0x200000", 16)
    else:
        num_cpu = 1
        memory_offset = 0
    for cpu_count in range(num_cpu):
        for loop_count in range(2):
            num_desc = int(image_size[loop_count] / block_size_16k)
            partial_load = image_size[loop_count] % block_size_16k and 1
            partial_block_size = int(
                int((image_size[loop_count] - num_desc * block_size_16k)) / 16
            )
            if partial_load:
                # print("partial block size = ", partial_block_size)
                if (
                    partial_block_size * 16
                    != image_size[loop_count] - num_desc * block_size_16k
                ):
                    print("source size if not a multiple of 16 bytes")
                    sys.exit()
                else:
                    partial_block_size -= 1
            src_address = src_start_address[loop_count]
            des_address = dest_start_address[loop_count]
            # print("num descriptors: ", num_desc)
            # print("partial load: ", partial_load)
            for i in range(idx, idx + num_desc):
                # print("src address: ", print_format.format(src_address))
                # print("des address: ", print_format.format(des_address))

                dma_desc = gpdma_desc()
                dma_desc.source = src_address
                dma_desc.dst = des_address
                dma_desc.block_ts = int(block_size_16k / 16) - 1

                dma_desc.ctl.DST_TR_WIDTH = 0x4
                dma_desc.ctl.SRC_TR_WIDTH = 0x4
                dma_desc.ctl.SRC_MSIZE = 0x2
                dma_desc.ctl.DST_MSIZE = 0x2
                dma_desc.ctl.SRC_STAT_EN = 0x1
                dma_desc.ctl.DST_STAT_EN = 0x1
                dma_desc.ctl.SHADOWREG_OR_LLI_VALID = 0x1
                dma_desc.ctl.SHADOWREG_OR_LLI_LAST = 0x0
                desc_start_address += 64
                dma_desc.llp = desc_start_address
                src_address += block_size_16k
                des_address += block_size_16k
                gpdma_list.append(dma_desc)
            idx += num_desc
            # print("idx: ", idx)
            if partial_load:
                dma_desc = gpdma_desc()
                dma_desc.source = src_address
                dma_desc.dst = des_address
                dma_desc.block_ts = partial_block_size
                dma_desc.ctl.DST_TR_WIDTH = 0x4
                dma_desc.ctl.SRC_TR_WIDTH = 0x4
                dma_desc.ctl.SRC_MSIZE = 0x2
                dma_desc.ctl.DST_MSIZE = 0x2
                dma_desc.ctl.SRC_STAT_EN = 0x1
                dma_desc.ctl.DST_STAT_EN = 0x1
                dma_desc.ctl.SHADOWREG_OR_LLI_VALID = 0x1
                dma_desc.ctl.SHADOWREG_OR_LLI_LAST = 0x0
                desc_start_address += 64
                dma_desc.llp = desc_start_address
                idx += 1
                gpdma_list.append(dma_desc)
        dest_start_address[0] += memory_offset
        dest_start_address[1] += memory_offset
    idx -= 1
    # print("idx_corrected: ", print_format.format(idx))
    # print("value before correction: ", print_format.format(gpdma_list[idx].ctl.get()))
    gpdma_list[idx].ctl.SHADOWREG_OR_LLI_LAST = 0x1
    gpdma_list[idx].llp = 0x0
    # print("value after correction: ", print_format.format(gpdma_list[idx].ctl.get()))
    return gpdma_list


def get_line_count_from_command(cmd: "str") -> "int":
    linecount = 0
    for line in os.popen(cmd).readlines():
        data = line.rstrip("\n")
        linecount += 1
        if data[0] == "@":
            linecount = int(data[1:], 16)
    return linecount


def get_iram_dram_line_count(
    iram_processor_start: "int",
    iram_size: "int",
    dram_processor_start: "int",
    dram_size: "int",
    tools_dir: "str",
    elf_file: "str",
) -> "list[int]":
    line_size = 128
    cmd = (
        tools_dir
        + "/bin/"
        + "xt-dumpelf --width="
        + str(line_size)
        + " "
        + "--little-endian  --no-bss  --base="
        + str(iram_processor_start)
        + " "
        + "--size="
        + str(iram_size)
        + " "
        + elf_file
    )
    iram_linecount = get_line_count_from_command(cmd)
    cmd = (
        tools_dir
        + "/bin/"
        + "xt-dumpelf --width="
        + str(line_size)
        + " "
        + "--little-endian  --no-bss  --base="
        + str(dram_processor_start)
        + " "
        + "--size="
        + str(dram_size)
        + " "
        + elf_file
    )
    dram_linecount = get_line_count_from_command(cmd)
    return [iram_linecount, dram_linecount]


def output_factory_input_content(
    dump_output: "list[str]",
    linecount: "int",
    file_obj: "typing.TextIO",
    print_format: "str",
):
    for i in range(linecount):
        data = dump_output[i].rstrip("\n")
        print(print_format.format(int(data, 16)), file=file_obj)


def generate_factory_image_file(
    iram_processor_start: "int",
    iram_size: "int",
    dram_processor_start: "int",
    dram_size: "int",
    tools_dir: "str",
    line_count: "list[int]",
    elf_file: "str",
    file_obj: "typing.TextIO",
    print_format: "str",
):
    line_size = 128
    cmd = (
        tools_dir
        + "/bin/"
        + "xt-dumpelf --width="
        + str(line_size)
        + " "
        + "--little-endian  --no-bss  --full --base="
        + str(iram_processor_start)
        + " "
        + "--size="
        + str(iram_size)
        + " "
        + elf_file
    )
    lines = os.popen(cmd).readlines()
    output_factory_input_content(lines, line_count[0], file_obj, print_format)
    cmd = (
        tools_dir
        + "/bin/"
        + "xt-dumpelf --width="
        + str(line_size)
        + " "
        + "--little-endian  --no-bss  --full --base="
        + str(dram_processor_start)
        + " "
        + "--size="
        + str(dram_size)
        + " "
        + elf_file
    )
    lines = os.popen(cmd).readlines()
    output_factory_input_content(lines, line_count[1], file_obj, print_format)


def generate_descriptor_file(
    file_obj: "typing.TextIO", print_format: "str", desc_list: "list[gpdma_desc]"
):
    for x in desc_list:
        gpdma_desc.print_desc(x, file_obj, print_format)


def gen_gpdma_program_data_address_file(
    file_obj_addr: "typing.TextIO",
    file_obj_data: "typing.TextIO",
    llp_start_addr: "int",
    print_format: "str",
):
    cfgreg = rcs_dmac_cfgreg_reg_t(0)
    cfgreg.DMAC_EN = 1
    print(print_format.format(cfgreg.get()), file=file_obj_data)
    print(print_format.format(cfgreg.addr()), file=file_obj_addr)
    ch1_cfg_reg = rcs_dmac_ch1_cfg_reg_t(0)
    ch1_cfg_reg.TT_FC = 0
    ch1_cfg_reg.DST_MULTBLK_TYPE = 0x3
    ch1_cfg_reg.SRC_MULTBLK_TYPE = 0x3
    ch1_cfg_reg.DST_PER = 0x1
    ch1_cfg_reg.SRC_PER = 0x0
    ch1_cfg_reg.DST_OSR_LMT = 15
    ch1_cfg_reg.SRC_OSR_LMT = 15
    ch1_cfg_reg.HS_SEL_SRC = 1
    ch1_cfg_reg.HS_SEL_DST = 1
    print(print_format.format(ch1_cfg_reg.get()), file=file_obj_data)
    print(print_format.format(ch1_cfg_reg.addr()), file=file_obj_addr)
    llpreg = rcs_dmac_ch1_llp_reg_t(0)
    llpreg.set(llp_start_addr)
    print(print_format.format(llpreg.get()), file=file_obj_data)
    print(print_format.format(llpreg.addr()), file=file_obj_addr)
    chenreg = rcs_dmac_chenreg_reg_t(0)
    chenreg.CH1_EN_WE = 0x1
    chenreg.CH1_EN = 0x1
    print(print_format.format(chenreg.get()), file=file_obj_data)
    print(print_format.format(chenreg.addr()), file=file_obj_addr)


parser = argparse.ArgumentParser(
    description="Extract memory contents from elf file for factory file generation."
)
parser.add_argument("elf", metavar="file.elf", help="ELF file to process")
# parser.add_argument(
#     "--iram_mem_size",
#     dest="iram_mem_size",
#     default="0",
#     help="max size of the iram image in bytes, hex format 0xN+.",
# )
# parser.add_argument(
#     "--iram_proc_start",
#     dest="iram_processor_start_address",
#     default="0x0",
#     help="start address of the iram image in the processor (Native) in bytes.",
# )
# parser.add_argument(
#     "--iram_axi_start",
#     dest="iram_axi_start_address",
#     default="0x0",
#     help="start address of the iram image in the processor (AXI) in bytes.",
# )
# parser.add_argument(
#     "--dram_mem_size",
#     dest="dram_mem_size",
#     default="0",
#     help="max size of the dram image in bytes, hex format 0xN+.",
# )
# parser.add_argument(
#     "--dram_axi_start",
#     dest="dram_axi_start_address",
#     default="0x0",
#     help="start address of the dram image in the processor (AXI) in bytes.",
# )
# parser.add_argument(
#     "--dram_proc_start",
#     dest="dram_processor_start_address",
#     default="0x0",
#     help="start address of the dram image in the processor (Native) in bytes.",
# )
parser.add_argument(
    "--tools", dest="tools_dir", default="", help="Xtensa Tools Directory"
)
# parser.add_argument(
#     "--offset", dest="offset_addr", default="0", help="Offset for start address"
# )
# parser.add_argument(
#     "--desc_start",
#     dest="desc_start",
#     default="0x0",
#     help="start address (AXI)in shared memory where the descriptors will be stored in bytes.",
# )
# parser.add_argument(
#     "--image_start",
#     dest="image_factory_load_start",
#     default="0x0",
#     help="start address (AXI) in shared memory where the factory image will be loaded in  bytes.",
# )
# parser.add_argument(
#     "--output_base_file_name",
#     dest="output_base_name",
#     default="kp1_desc",
#     help="Base name of the output files",
# )
# parser.add_argument(
#     "--output_dir_name",
#     dest="output_dir_name",
#     default="",
#     help="directory where the output files will be put",
# )
# parser.add_argument(
#     "--output_line_count",
#     dest="output_line_count",
#     action="store_true",
#     help="flag to indicate whether the line counts will be printed in the stdout or not",
# )
# parser.add_argument(
#     "--output_presil",
#     dest="output_file_presil",
#     action="store_true",
#     help="Flag to indicate whether to generate the iram and dram file for presil testing",
# )
parser.add_argument(
    "--program",
    dest="program",
    default="cal",
    help="core for which the factory file is generated",
)  # parser.add_argument("--factorydesc_file_name",dest="desc_file_name",default="",help="Name of the file containing the descriptors")
parser.add_argument(
    "--target",
    dest="target",
    default="sim",
    help="target for which this factory tar file is created",
)  # parser.add_argument("--factorydesc_file_name",dest="desc_file_name",default="",help="Name of the file containing the descriptors")
mem_consts = {
    "factory_iram_mem_size": 0x00040000,
    "factory_iram_proc_start": 0x10000000,
    "factory_iram_axi_start": 0x00180000,
    "factory_dram_mem_size": 0x00040000,
    "factory_dram_proc_start": 0x10040000,
    "factory_dram_axi_start": 0x001C0000,
    "factory_desc_start": 0x80000,
    "factory_image_factory_load_start": 0x0,
    "factory_output_base_file_name": "kp1",
    "ana_iram_mem_size": 0x10000,
    "ana_iram_proc_start": 0x20000,
    "ana_iram_axi_start": 0x49B0000,
    "ana_dram_mem_size": 0x10000,
    "ana_dram_proc_start": 0x10000,
    "ana_dram_axi_start": 0x49A0000,
    "ana_desc_start": 0xA0800,
    "ana_image_factory_load_start": 0x80800,
    "ana_output_base_file_name": "ana",
}
mem_consts_presil_specific = {
    "factory_presil_image_factory_load_start": 0x220000,
    "factory_presil_desc_start": 0x23F400,
    "ana_presil_image_factory_load_start": 0x200000,
    "ana_presil_desc_start": 0x21F400,
}

line_size_in_bytes = 16
args = parser.parse_args()
presil_env = True
output_dir_name = os.path.split(args.elf)[0] + "/factory/"
output_base_name = output_dir_name + args.program+"_"+args.target
desc_file_name = output_base_name + "_desc_output.txt"
gpdma_regs_data_file_name = output_base_name + "_gpdmaregs_data.txt"
gpdma_regs_addr_file_name = output_base_name + "_gpdmaregs_addr.txt"
desc_start_addr_file_name = output_base_name + "_desc_start_addr.txt"
factory_file_name = output_base_name + "_image.txt"
image_start_addr_file_name = output_base_name + "_image_start_addr.txt"
stall_remove_reg_addr_file_name = output_base_name + "_stallreg_addr.txt"
stall_remove_reg_data_file_name = output_base_name + "_stallreg_data.txt"
tar_file_name = output_base_name + ".tar"
if presil_env:
    temp = os.path.splitext(desc_file_name)
    presil_desc_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(gpdma_regs_data_file_name)
    presil_gpdma_regs_data_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(gpdma_regs_addr_file_name)
    presil_gpdma_regs_addr_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(desc_start_addr_file_name)
    presil_desc_start_addr_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(factory_file_name)
    presil_factory_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(image_start_addr_file_name)
    presil_image_start_addr_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(tar_file_name)
    presil_tar_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(stall_remove_reg_addr_file_name)
    presil_stall_remove_reg_addr_file_name = temp[0] + "_presil" + temp[1]
    temp = os.path.splitext(stall_remove_reg_data_file_name)
    presil_stall_remove_reg_data_file_name = temp[0] + "_presil" + temp[1]
    line_count_file_name = output_base_name + "_line_count.txt"
    temp = os.path.splitext(line_count_file_name)
    presil_line_count_file_name = temp[0] + "_presil" + temp[1]
else:
    presil_desc_file_name = ""
    presil_gpdma_regs_data_file_name = ""
    presil_gpdma_regs_addr_file_name = ""
    presil_desc_start_addr_file_name = ""
    presil_factory_file_name = ""
    presil_image_start_addr_file_name = ""
    presil_line_count_file_name = ""
    presil_stall_remove_reg_addr_file_name = ""
    presil_stall_remove_reg_data_file_name = ""

if args.program == "ana":
    stall_remove_file_handle_data = open(stall_remove_reg_data_file_name, "w")
    stall_remove_file_handle_addr = open(stall_remove_reg_addr_file_name, "w")
    ana_control = ant_csr_adc_cpu_ctrl_reg_t()
    ana_control.RUN_STALL = 0
    ana_control_value = ana_control.get()
    ant_cpu_stall_register_addr = ana_control.addr()
    ant_cpu_stall_register_address_offset = 0x200000
    for i in range(4):
        print("{0:#034b}".format(ana_control_value), file=stall_remove_file_handle_data)
        print(
            "{0:#034b}".format(ant_cpu_stall_register_addr),
            file=stall_remove_file_handle_addr,
        )
        ant_cpu_stall_register_addr += ant_cpu_stall_register_address_offset
    stall_remove_file_handle_data.close()
    stall_remove_file_handle_addr.close()
    if presil_env:
        presil_stall_remove_file_handle_data = open(
            presil_stall_remove_reg_data_file_name, "w"
        )
        presil_stall_remove_file_handle_addr = open(
            presil_stall_remove_reg_addr_file_name, "w"
        )
        ant_cpu_stall_register_addr = ana_control.addr()
        for i in range(4):
            print(
                "{0:#010x}".format(ana_control_value),
                file=presil_stall_remove_file_handle_data,
            )

            print(
                "{0:#010x}".format(ant_cpu_stall_register_addr),
                file=presil_stall_remove_file_handle_addr,
            )
            ant_cpu_stall_register_addr += ant_cpu_stall_register_address_offset

        presil_stall_remove_file_handle_data.close()
        presil_stall_remove_file_handle_addr.close()
elif args.program == "factory":
    stall_remove_file_handle_data = open(stall_remove_reg_data_file_name, "w")
    stall_remove_file_handle_addr = open(stall_remove_reg_addr_file_name, "w")
    kp1_control = rcs_gpreg_core3_ctrl_reg_t()
    kp1_control.CORE_RUNSTALL = 0
    print("{0:#034b}".format(kp1_control.get()), file=stall_remove_file_handle_data)
    print("{0:#034b}".format(kp1_control.addr()), file=stall_remove_file_handle_addr)
    stall_remove_file_handle_data.close()
    stall_remove_file_handle_addr.close()
    if presil_env:
        presil_stall_remove_file_handle_data = open(
            presil_stall_remove_reg_data_file_name, "w"
        )
        presil_stall_remove_file_handle_addr = open(
            presil_stall_remove_reg_addr_file_name, "w"
        )
        print(
            "{0:#010x}".format(kp1_control.get()),
            file=presil_stall_remove_file_handle_data,
        )
        print(
            "{0:#010x}".format(kp1_control.addr()),
            file=presil_stall_remove_file_handle_addr,
        )
        presil_stall_remove_file_handle_data.close()
        presil_stall_remove_file_handle_addr.close()
else:
    print("program must be either 'factory' or 'ana'")
    sys.exit()

start_address_des = [
    mem_consts[args.program + "_iram_axi_start"],
    mem_consts[args.program + "_dram_axi_start"],
]
iram_processor_start_address = mem_consts[args.program + "_iram_proc_start"]
iram_mem_size = mem_consts[args.program + "_iram_mem_size"]
dram_processor_start_address = mem_consts[args.program + "_dram_proc_start"]
dram_mem_size = mem_consts[args.program + "_dram_mem_size"]
line_count = get_iram_dram_line_count(
    iram_processor_start_address,
    iram_mem_size,
    dram_processor_start_address,
    dram_mem_size,
    args.tools_dir,
    args.elf,
)
print("IRAM line count = {0:#018x}".format(line_count[0]))
print("DRAM line count = {0:#018x}".format(line_count[1]))
if presil_env:
    file_line_count = open(presil_line_count_file_name, "w")
    print("{0:#018x}".format(line_count[0]), file=file_line_count)
    print("{0:#018x}".format(line_count[1]), file=file_line_count)
    file_line_count.close()

image_size: "list[2]" = [
    line_count[0] * line_size_in_bytes,
    line_count[1] * line_size_in_bytes,
]
start_address_src: "list[2]" = [0, 0]
start_address_src[0] = mem_consts[args.program + "_image_factory_load_start"]
start_address_src[1] = start_address_src[0] + line_count[0] * line_size_in_bytes
desc_address = mem_consts[args.program + "_desc_start"]
my_desc_list: "list[gpdma_desc]" = generate_descriptor_list(
    start_address_src, start_address_des, desc_address, image_size, args.program
)
# write the descriptors to file
desc_file_handle_data = open(desc_file_name, "w")
print_format_bin = "{0:#066b}"
generate_descriptor_file(desc_file_handle_data, print_format_bin, my_desc_list)
desc_file_handle_data.close()
if presil_env:
    start_address_src[0] = mem_consts_presil_specific[
        args.program + "_presil_image_factory_load_start"
    ]
    start_address_src[1] = start_address_src[0] + line_count[0] * line_size_in_bytes
    desc_address = mem_consts_presil_specific[args.program + "_presil_desc_start"]
    desc_file_handle_data = open(presil_desc_file_name, "w")
    my_desc_list: "list[gpdma_desc]" = generate_descriptor_list(
        start_address_src, start_address_des, desc_address, image_size, args.program
    )
    print_format_hex = "{0:#018x}"
    generate_descriptor_file(desc_file_handle_data, print_format_hex, my_desc_list)
    desc_file_handle_data.close()


# write image to file
iram_processor_start_address = mem_consts[args.program + "_iram_proc_start"]
iram_mem_size = mem_consts[args.program + "_iram_mem_size"]
dram_processor_start_address = mem_consts[args.program + "_dram_proc_start"]
dram_mem_size = mem_consts[args.program + "_dram_mem_size"]
print_format = "{0:#0130b}"
image_file_handle = open(factory_file_name, "w")
generate_factory_image_file(
    iram_processor_start_address,
    iram_mem_size,
    dram_processor_start_address,
    dram_mem_size,
    args.tools_dir,
    line_count,
    args.elf,
    image_file_handle,
    print_format,
)
image_file_handle.close()
if presil_env:
    print_format = "{0:032x}"
    image_file_handle = open(presil_factory_file_name, "w")
    print("@00000000", file=image_file_handle)
    generate_factory_image_file(
        iram_processor_start_address,
        iram_mem_size,
        dram_processor_start_address,
        dram_mem_size,
        args.tools_dir,
        line_count,
        args.elf,
        image_file_handle,
        print_format,
    )
    image_file_handle.close()

# write the desc start address to file
file = open(desc_start_addr_file_name, "w")
print_format = "{0:#066b}"

desc_address = mem_consts[args.program + "_desc_start"]
print(print_format.format(desc_address), file=file)
file.close()
file = open(image_start_addr_file_name, "w")
start_address_src = mem_consts[args.program + "_image_factory_load_start"]
print(print_format.format(start_address_src), file=file)
file.close()
if presil_env:
    print_format = "{0:#018x}"
    desc_address = mem_consts_presil_specific[args.program + "_presil_desc_start"]
    file = open(presil_desc_start_addr_file_name, "w")
    print(print_format.format(desc_address), file=file)
    file.close()
    file = open(presil_image_start_addr_file_name, "w")
    start_address_src = mem_consts_presil_specific[
        args.program + "_presil_image_factory_load_start"
    ]
    print(print_format.format(start_address_src), file=file)
    file.close()

# write the GPDMA programming sequence to file
print_format = "{0:#066b}"
gpdma_file_handle_addr = open(gpdma_regs_addr_file_name, "w")
gpdma_file_handle_data = open(gpdma_regs_data_file_name, "w")
desc_address = mem_consts[args.program + "_desc_start"]
print_format = "{0:#066b}"
print_format_bin
gen_gpdma_program_data_address_file(
    gpdma_file_handle_addr, gpdma_file_handle_data, desc_address, print_format
)
gpdma_file_handle_addr.close()
gpdma_file_handle_data.close()
if presil_env:
    print_format = "{0:#018x}"
    gpdma_file_handle_addr = open(presil_gpdma_regs_addr_file_name, "w")
    gpdma_file_handle_data = open(presil_gpdma_regs_data_file_name, "w")
    desc_address = mem_consts_presil_specific[args.program + "_presil_desc_start"]
    gen_gpdma_program_data_address_file(
        gpdma_file_handle_addr, gpdma_file_handle_data, desc_address, print_format
    )
    gpdma_file_handle_addr.close()
    gpdma_file_handle_data.close()


factory_tar = tarfile.open(tar_file_name, "w")
factory_tar.add(desc_file_name, arcname=os.path.split(desc_file_name)[1])
factory_tar.add(
    gpdma_regs_data_file_name, arcname=os.path.split(gpdma_regs_data_file_name)[1]
)
factory_tar.add(
    gpdma_regs_addr_file_name, arcname=os.path.split(gpdma_regs_addr_file_name)[1]
)
factory_tar.add(
    desc_start_addr_file_name, arcname=os.path.split(desc_start_addr_file_name)[1]
)
factory_tar.add(factory_file_name, arcname=os.path.split(factory_file_name)[1])
factory_tar.add(
    image_start_addr_file_name, arcname=os.path.split(image_start_addr_file_name)[1]
)
factory_tar.add(
    stall_remove_reg_data_file_name,
    arcname=os.path.split(stall_remove_reg_data_file_name)[1],
)
factory_tar.add(
    stall_remove_reg_addr_file_name,
    arcname=os.path.split(stall_remove_reg_addr_file_name)[1],
)
factory_tar.close()
os.remove(desc_file_name)
os.remove(gpdma_regs_data_file_name)
os.remove(gpdma_regs_addr_file_name)
os.remove(desc_start_addr_file_name)
os.remove(factory_file_name)
os.remove(image_start_addr_file_name)
os.remove(stall_remove_reg_data_file_name)
os.remove(stall_remove_reg_addr_file_name)
if presil_env:
    factory_tar = tarfile.open(presil_tar_file_name, "w")
    factory_tar.add(
        presil_desc_file_name, arcname=os.path.split(presil_desc_file_name)[1]
    )
    factory_tar.add(
        presil_gpdma_regs_data_file_name,
        arcname=os.path.split(presil_gpdma_regs_data_file_name)[1],
    )
    factory_tar.add(
        presil_gpdma_regs_addr_file_name,
        arcname=os.path.split(presil_gpdma_regs_addr_file_name)[1],
    )
    factory_tar.add(
        presil_desc_start_addr_file_name,
        arcname=os.path.split(presil_desc_start_addr_file_name)[1],
    )
    factory_tar.add(
        presil_factory_file_name, arcname=os.path.split(presil_factory_file_name)[1]
    )
    factory_tar.add(
        presil_image_start_addr_file_name,
        arcname=os.path.split(presil_image_start_addr_file_name)[1],
    )
    factory_tar.add(
        presil_stall_remove_reg_data_file_name,
        arcname=os.path.split(presil_stall_remove_reg_data_file_name)[1],
    )
    factory_tar.add(
        presil_stall_remove_reg_addr_file_name,
        arcname=os.path.split(presil_stall_remove_reg_addr_file_name)[1],
    )
    factory_tar.add(
        presil_line_count_file_name,
        arcname=os.path.split(presil_line_count_file_name)[1],
    )
    os.remove(presil_desc_file_name)
    os.remove(presil_gpdma_regs_data_file_name)
    os.remove(presil_gpdma_regs_addr_file_name)
    os.remove(presil_desc_start_addr_file_name)
    os.remove(presil_factory_file_name)
    os.remove(presil_image_start_addr_file_name)
    os.remove(presil_stall_remove_reg_data_file_name)
    os.remove(presil_stall_remove_reg_addr_file_name)
    os.remove(presil_line_count_file_name)
    factory_tar.close()
