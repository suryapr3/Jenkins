from csv import reader
from pprint import pprint
from parser_support import *
from global_config import *
import os
import pdb

scenario_sequence = []
vha_config = {'vha_num':0, 'ant_num':0, 'in_rate':0, 'out_rate':0, 'mode':"AUTO"}
v2d_config = {'v2d_num':0,'apb_num':0, 'test_config':0,'in_rate':0, 'out_rate':0,'drf_clock':0, 'pdpd_enable':0}
v2d_config['pdpd_enable']=PDPD_ENABLE

def parse_scenario():
    with open('scenario.txt') as in_file:
        csv_reader = reader(in_file)
        headers = [x.strip() for x in next(csv_reader)]

        for line in csv_reader:
            if line:
                d = dict(zip(headers, map(str.strip, line)))

                # ignore comments marked by #
                if "#" not in d['src']:
                    scenario_sequence.append(d)

# generates cio2strm config for vex
def generate_cio2strm_config(entry):
    
    stream=[{"low":"0x0", "high":"0x1ffff"},
    {"low":"0x20000", "high":"0x3ffff"},
    {"low":"0x40000", "high":"0x5ffff"},
    {"low":"0x60000", "high":"0x7ffff"},
    {"low":"0x80000", "high":"0x9ffff"},
    {"low":"0xA0000", "high":"0xBffff"},
    {"low":"0xC0000", "high":"0xDffff"},
    {"low":"0xE0000", "high":"0xFffff"}, 
    ]
    
    file_name = entry['src'] + "_cio2strm_config.h"
    cio2strm_list, tableId = get_file_content(file_name)

    vexId = extract_host_id(entry['src'])
    base_addr = f"VEXABC{vexId}_C2S_CIO2STRM_BASE"
    
    cio2strm_list.append({f'addr':f"CIO2STRM_INT_EN_ADR({base_addr})",'value':"0x3F",'name':"CIO2STRM_INT_EN"})
    cio2strm_list.append({f'addr':f"CIO2STRM_FIFO_STAT_CTL_ADR({base_addr})",'value':"0x1",'name':"CIO2STRM_FIFO_STAT_CTL"})
    cio2strm_list.append({f'addr':f"CIO2STRM_WORD_CNT_CTL_ADR({base_addr})",'value':"0x1",'name':"CIO2STRM_WORD_CNT_CTL"})
    #pdb.set_trace()
    if "jesd"  in entry["dst"]:   #if jesd in destination
        num_streams = entry["numStream"]
        range_en = pow(2, int(num_streams)) -1
        cio2strm_list.append({f'addr':f"CIO2STRM_RANGE_EN_ADR({base_addr})",'value':hex(range_en),'name':"CIO2STRM_RANGE_EN"})
        for x in range(int(num_streams)):
            cio2strm_list.append({f'addr':f"CIO2STRM_MEM_ADDR_LOW{x}_ADR({base_addr})",'value':stream[x]['low'],'name':f"CIO2STRM_MEM_ADDR_LOW{x}"})
            cio2strm_list.append({f'addr':f"CIO2STRM_MEM_ADDR_HIGH{x}_ADR({base_addr})",'value':stream[x]['high'],'name':f"CIO2STRM_MEM_ADDR_HIGH{x}"})
            cio2strm_list.append({f'addr':f"CIO2STRM_MEM_OFFSET{x}_ADR({base_addr})",'value':"0x00000000",'name':f"CIO2STRM_MEM_OFFSET{x}"})
            cio2strm_list.append({f'addr':f"CIO2STRM_STRM_DEST{x}_ADR({base_addr})",'value':hex(extract_host_id(entry['dst'])),'name':f"CIO2STRM_STRM_DEST{x}"})

    else:    #(not jesd)
        # LSB 26 bit reserved for address, MSB 6 bits can be used to store vexId to make addresses unique across all vexes
        addr_low = int(vexId) << 26
        addr_high = (int(vexId) << 26 ) | ((1 << 26) - 1)

        cio2strm_list.append({f'addr':f"CIO2STRM_RANGE_EN_ADR({base_addr})",'value':"0x00000001",'name':"CIO2STRM_RANGE_EN"})

        # MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
        # calculate low and high in smart way. 26 LSB reserved for addr. 6 bit msb to make vex id unique
        cio2strm_list.append({f'addr':f"CIO2STRM_MEM_ADDR_LOW0_ADR({base_addr})",'value':hex(addr_low),'name':"CIO2STRM_MEM_ADDR_LOW0"})
        cio2strm_list.append({f'addr':f"CIO2STRM_MEM_ADDR_HIGH0_ADR({base_addr})",'value':hex(addr_high),'name':"CIO2STRM_MEM_ADDR_HIGH0"})

        # MEM_OFFSET[0]- is in words
        cio2strm_list.append({f'addr':f"CIO2STRM_MEM_OFFSET0_ADR({base_addr})",'value':"0x00000000",'name':"CIO2STRM_MEM_OFFSET0"})
        cio2strm_list.append({f'addr':f"CIO2STRM_STRM_DEST0_ADR({base_addr})",'value':extract_host_id(entry['dst']),'name':"CIO2STRM_STRM_DEST0"})

    set_file_content(file_name, cio2strm_list)

# generates strm2cio config for vex
def generate_strm2cio_config(entry):
    file_name = entry['dst'] + "_strm2cio_config.h"
    strm2cio_list, tableId = get_file_content(file_name)

    dst_vexId = extract_host_id(entry['dst'])
    base_addr = f"VEXABC{dst_vexId}_S2C_STRM2CIO_BASE"

    strm2cio_list.append({'addr':f"STRM2CIO_INT_EN_ADR({base_addr})",'value':"0xF",'name':"STRM2CIO_INT_EN"})
    strm2cio_list.append({'addr':f"STRM2CIO_FIFO_STAT_CTL_ADR({base_addr})",'value':"0x1",'name':"STRM2CIO_FIFO_STAT_CTL"})
    strm2cio_list.append({'addr':f"STRM2CIO_WORD_CNT_CTL_ADR({base_addr})",'value':"0x1",'name':"STRM2CIO_WORD_CNT_CTL"})

    set_file_content(file_name, strm2cio_list)

# generates b2h config for hwa
def generate_b2h_config(entry):
    file_name = entry['dst'] + "_b2h_config.h"
    address=["0x80000000","0x80020000","0x80040000","0x80060000","0x80080000","0x800A0000","0x800C0000","0x800E0000"]
    
    nsiphbi_b2h_list, tableId = get_file_content(file_name)

    base_addr = get_nsip_host_base_addr(entry['dst'])

    tableAddr, tableMask = get_b2h_table_content(file_name, tableId)

    if "vha" in entry['dst']:
        #based on VHA mapping
        if tableId == 1:
            tableId = 2
    elif "v2d" in entry['dst']:
        #do nothing for now
        tableId = tableId
    elif "jesd" in entry['dst']:
        #do nothing for now
        tableId = tableId
    else:
        raise Exception("generate_b2h_config, unknown host_name = " + entry['src'])

    # enable interrupts
    # avoid duplicate entries for same hwa
    if len(nsiphbi_b2h_list) == 0:
        nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_INTR_INT_HIGH_EN_ADR({base_addr})",'value':"0xFFFFF",'name':"CM_0_INT_HIGH_EN"})
        nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_INTR_INT_LOW_EN_ADR({base_addr})",'value':"0xFFFFF",'name':"CM_0_INT_LOW_EN"})

        nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_B2H_FF_FIFO_CTRL_ADR({base_addr})",'value':"0x184",'name':"B2H_FIFO_CONTROL"})
        #nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_B2H_CSR_CREDIT_CS_ADR({base_addr})",'value':"0x8",'name':"B2H_CREDIT_CS"})
        #nsiphbi_b2h_list.append({'addr':f"({base_addr})",'value':"MISC_CTRL_VALUE",'name':"B2H_MISC_CTRL"})

    
    # These are for Buffer A0
    nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_B2H_CSR_ADDR_TBL{tableId}_ADR({base_addr})",'value':f"{hex(tableAddr)}",'name':f"B2H_ADDR_MAP_TBL{tableId}"})

    # Mask was set for total 2K flits in words
    nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_B2H_CSR_ADDR_MASK_TBL{tableId}_ADR({base_addr})",'value':f"{hex(tableMask)}",'name':f"B2H_ADDR_MASK_TBL{tableId}"})

    if "jesd" in entry["dst"]:
        num_streams = entry["numStream"]
        #range_en = pow(2, int(num_streams)) -1
        #cio2strm_list.append({f'addr':f"CIO2STRM_RANGE_EN_ADR({base_addr})",'value':hex(range_en),'name':"CIO2STRM_RANGE_EN"})
        for x in range(1,int(num_streams)):
            nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_B2H_CSR_ADDR_TBL{x}_ADR({base_addr})",'value':address[x],'name':f"B2H_ADDR_MAP_TBL{x}"})
            nsiphbi_b2h_list.append({'addr':f"NSIP_HBI_B2H_CSR_ADDR_MASK_TBL{x}_ADR({base_addr})",'value':f"{hex(tableMask)}",'name':f"B2H_ADDR_MASK_TBL{x}"})
            #cio2strm_list.append({f'addr':f"CIO2STRM_MEM_ADDR_LOW{x}_ADR({base_addr})",'value':stream[x]['low'],'name':"CIO2STRM_MEM_ADDR_LOW0"})

    set_file_content(file_name, nsiphbi_b2h_list)

# generates h2b config for hwa
def generate_h2b_config(entry):
    dstHostId = extract_host_id(entry['dst'])
    base_addr = get_nsip_host_base_addr(entry['src'])
    tableAddr = 0x80004000

    file_name = entry['src'] + "_h2b_config.h"
    nsiphbi_h2b_list, tableId = get_file_content(file_name)


    if "vha" in entry['src']:
        #based on VHA mapping
        if tableId == 1:
            tableId = 4
    elif "v2d" in entry['src']:
        if "vha" in entry['dst']:
            tableAddr = 0x80010000
    elif "jesd" in entry['src']:
        #do nothing for now
        tableId = tableId
    else:
        raise Exception("generate_h2b_config, unknown host_name = " + entry['src'])

    if len(nsiphbi_h2b_list) == 0:
        # enable interrupts
        nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_INTR_INT_HIGH_EN_ADR({base_addr})",'value':"0xFFFFF",'name':"CM_0_INT_HIGH_EN"})
        nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_INTR_INT_LOW_EN_ADR({base_addr})",'value':"0xFFFFF",'name':"CM_0_INT_LOW_EN"})

        # H2B registers
        nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_FF_FIFO_CTRL_ADR({base_addr})",'value':"0x184",'name':"H2B_FIFO_CONTROL"})
        #nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_CREDIT_READY_CS_ADR({base_addr})",'value':"0x4",'name':"H2B_CREDIT_READY_CS"})
        #nsiphbi_h2b_list.append({'addr':"",'value':"MISC_CTRL_VALUE",'name':"H2B_BUF_FC_EN"})


    # 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_BUF_SZ_HW_TBL{tableId}_ADR({base_addr})",'value':"0x3F",'name':f"H2B_BUF_SZ_HW_TBL{tableId}"})

    # Token will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_TK_ADDR_LKUP_TBL{tableId}_ADR({base_addr})",'value':"0x18080",'name':f"H2B_TK_ADDR_LKUP_TBL{tableId}"})
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_MD_ADDR_LKUP_TBL{tableId}_ADR({base_addr})",'value':"0x18000",'name':f"H2B_MD_ADDR_LKUP_TBL{tableId}"})

    # Data will be written to VEX location 0x1000 * 4 = 0x4000
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_ADDR_LKUP_TBL{tableId}_ADR({base_addr})",'value':f"{hex(tableAddr)}",'name':f"H2B_ADDR_LKUP_TBL{tableId}"})

    #fill below 3 entries with receiver vex id
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL{tableId}_ADR({base_addr})",'value':dstHostId,'name':f"H2B_TK_ROUTE_LKUP_TBL{tableId}"})
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL{tableId}_ADR({base_addr})",'value':dstHostId,'name':f"H2B_MD_ROUTE_LKUP_TBL{tableId}"})
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_ROUTE_LKUP_TBL{tableId}_ADR({base_addr})",'value':dstHostId,'name':f"H2B_ROUTE_LKUP_TBL{tableId}"})

    # Vijay: Check if we can make it simple.. should be able to get it from out rate
    # These last 1 entries orders shouldn't be altered as they will be modified based on the runtime parameter for vex number
    nsiphbi_h2b_list.append({'addr':f"NSIP_HBI_H2B_MD_CTRL_TBL{tableId}_ADR({base_addr})",'value':hex(get_vha_nsip_hbi_md_control_tbl_value(entry, vha_config['out_rate'])),'name':f"H2B_MD_CTRL_TBL{tableId}"})

    set_file_content(file_name, nsiphbi_h2b_list)

# handling of 4 possible configurations
def generate_config_vex_to_hwa_dest(entry):
    generate_cio2strm_config(entry)
    generate_b2h_config(entry)
    #print("generate_config_vex_to_hwa_dest")

def generate_config_hwa_to_vex_dest(entry):
    generate_strm2cio_config(entry)
    generate_h2b_config(entry)
    #print("generate_config_hwa_to_vex_dest")

def generate_config_vex_to_vex_dest(entry):
    generate_cio2strm_config(entry)
    generate_strm2cio_config(entry)
    #print("generate_config_vex_to_vex_dest")

def generate_config_hwa_to_hwa_dest(entry):
    generate_h2b_config(entry)
    generate_b2h_config(entry)
    #print("generate_config_hwa_to_hwa_dest")


def generate_config_per_entry(entry):
    if "ve_" in entry['src']:
        if "ve_" in entry['dst']:
            generate_config_vex_to_vex_dest(entry)
        else:
            generate_config_vex_to_hwa_dest(entry)

    if "ve_" not in entry['src']:
        if "ve_" in entry['dst']:
            generate_config_hwa_to_vex_dest(entry)
        else:
            generate_config_hwa_to_hwa_dest(entry)

def generate_vha_config(vha_entries):
    vha_node_list = []
    #print(vha_entries)
    # this logic is faulty, dont think we need rx and tx vex as part vha config
    for entry in vha_entries:
        word = (entry['datarate'].split('_'))[1:]
        word='VHA_'+"_".join(word[:])
        if "vha" in entry['dst'] and vha_config['in_rate']==0:
            vha_config['in_rate'] = word
            #vha_config['tx_vex'] = extract_host_id(entry['src'])

        if "vha" in entry['src'] and vha_config['out_rate']==0:
            vha_config['out_rate'] = word
            #vha_config['rx_vex'] = extract_host_id(entry['dst'])

    vha_config['vha_num'], vha_config['ant_num'] = vha_entries[0]['dst'][4], vha_entries[0]['dst'][11]

    create_node_config_file(vha_entries[0]['dst'] + "_node_config.h", vha_config)

    print(vha_config)

def generate_v2d_config(v2d_entries):
    v2d_node_list = []
    for entry in v2d_entries:
        if v2d_config['pdpd_enable'] == 0:
            word = (entry['datarate'].split('_'))[1:]
            word='V2D_'+"_".join(word[:])
        else:
            word = (entry['datarate'].split('_'))[2:]
            word='PDPD_'+"_".join(word[:])

        if "v2d" in entry['dst']:
            v2d_config['in_rate'] = word
            #vha_config['tx_vex'] = extract_host_id(entry['src'])

        if "v2d" in entry['src']:
            v2d_config['out_rate'] = word
            #vha_config['rx_vex'] = extract_host_id(entry['dst'])
    
    if v2d_config['pdpd_enable']==1:
        v2d_config['v2d_num'], v2d_config['apb_num'] = v2d_entries[0]['dst'][4], 0
    else:
        v2d_config['v2d_num'], v2d_config['apb_num'] = v2d_entries[0]['dst'][4], v2d_entries[0]['dst'][11]
        
    create_node_config_file(v2d_entries[0]['dst'] + "_node_config.h", v2d_config)

    print(v2d_config)

def generate_hwa_config():
    #pdb.set_trace()
    vha_exist =0
    v2d_exist =0
    vha_entries = []
    v2d_entries = []
    for entry in scenario_sequence:
        if "vha" in entry['src'] or "vha" in entry['dst']:
            vha_entries.append(entry)
            vha_exist =1
        if  "v2d" in entry['src'] or "v2d" in entry['dst']:
            v2d_entries.append(entry)
            v2d_exist =1
    if vha_exist:
        generate_vha_config(vha_entries)
    if v2d_exist:
        generate_v2d_config(v2d_entries)

def generate_config():
    #pdb.set_trace()
    for entry in scenario_sequence:
        generate_config_per_entry(entry)
    print_config("register_sequence.h")

os.system("rm -rf *.h")
#os.system("del *.h")
# parser starts here

parse_scenario()
#pprint(scenario_sequence)
generate_hwa_config()
#pprint(scenario_sequence)
generate_config()
