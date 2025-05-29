from pprint import pprint

op_file_list = dict()
op_file_entry_count = dict()

def get_file_content(file_name):
    if op_file_list.get(file_name) is not None:
        op_file_entry_count[file_name] = op_file_entry_count[file_name]+1
        return op_file_list[file_name], op_file_entry_count[file_name]
    op_file_entry_count[file_name] = 0
    return [], 0

def set_file_content(file_name, content):
    op_file_list[file_name] = content
    #pprint(op_file_list)

def get_b2h_table_content(file_name, tableId):
    if "vha" in file_name:
        if tableId == 0:
            return 0x80000000, 0xFFFF
        if tableId == 1:
            return 0x80010000, 0x1FFFF

    if "v2d" in file_name:
        if tableId == 0:
            return 0x80000000, 0x1FFFF

    if "jesd" in file_name:
        if tableId == 0:
            return 0x80000000, 0xFFFF

    raise Exception(f"get_b2h_table_content, configure table for {file_name}, tableId {tableId}")

def print_config(register_file_name):
    with open(register_file_name, "w") as reg_seq_file:
        for file_name, content in op_file_list.items():
            create_config_file(file_name, content)
            reg_seq_file.write(f'#include "{file_name}"\n')


def extract_host_id(host_name):

    if "ve_" in host_name:
        dst_vexStr = host_name.replace("ve_", "").replace("_", "")
        dst_vexId = int(dst_vexStr, 8)

        if dst_vexId > 39:
            raise Exception("extract_host_id, invalid vexid host_name = " + host_name)

        return str(dst_vexId)
    elif "vha" in host_name:
        vha_host_map = {
        "vha_0_port_0": 0x44, "vha_0_port_1": 0x45,
        "vha_1_port_0": 0x4a, "vha_1_port_1": 0x4b,
        "vha_2_port_0": 0x50, "vha_2_port_1": 0x51,
        "vha_3_port_0": 0x56, "vha_3_port_1": 0x57,
        "vha_4_port_0": 0x5c, "vha_4_port_1": 0x5d,
        "vha_5_port_0": 0x62, "vha_5_port_1": 0x63,
        "vha_6_port_0": 0x68, "vha_6_port_1": 0x69,
        "vha_7_port_0": 0x6e, "vha_7_port_1": 0x6f}
        for key, value in vha_host_map.items():
            if host_name in key:
                return value

        raise Exception("extract_host_id, unknown host_name = " + host_name)
    elif "v2d" in host_name:
        v2d_host_map = {
        "v2d_0_port_0": 0x46, "v2d_0_port_1": 0x47, "v2d_0_port_2": 0x48, "v2d_0_port_3": 0x49,
        "v2d_1_port_0": 0x4C, "v2d_1_port_1": 0x4D, "v2d_1_port_2": 0x4E, "v2d_1_port_3": 0x4F,
        "v2d_2_port_0": 0x52, "v2d_2_port_1": 0x53, "v2d_2_port_2": 0x54, "v2d_2_port_3": 0x55,
        "v2d_3_port_0": 0x58, "v2d_3_port_1": 0x59, "v2d_3_port_2": 0x5A, "v2d_3_port_3": 0x5B,
        "v2d_4_port_0": 0x5E, "v2d_4_port_1": 0x5F, "v2d_4_port_2": 0x60, "v2d_4_port_3": 0x61,
        "v2d_5_port_0": 0x64, "v2d_5_port_1": 0x65, "v2d_5_port_2": 0x66, "v2d_5_port_3": 0x67,
        "v2d_6_port_0": 0x6A, "v2d_6_port_1": 0x6B, "v2d_6_port_2": 0x6C, "v2d_6_port_3": 0x6D,
        "v2d_7_port_0": 0x70, "v2d_7_port_1": 0x71, "v2d_7_port_2": 0x72, "v2d_7_port_3": 0x73}

        for key, value in v2d_host_map.items():
            if host_name in key:
                return value

        raise Exception("extract_host_id, unknown host_name = " + host_name)
    elif "jesd" in host_name:
        jesd_host_map = {
        "jesd_port_0": 0x40, "jesd_port_1": 0x41,
        "jesd_port_2": 0x42, "jesd_port_3": 0x43}

        for key, value in jesd_host_map.items():
            if host_name in key:
                return value
    else:
        raise Exception("extract_host_id, unknown host_name = " + host_name)
        return "haha"

def get_vha_nsip_hbi_md_control_tbl_value(entry, outrate):
    md_control_tbl = {'VHA_SYS_RATE_IQ_P125':3, 'VHA_SYS_RATE_IQ_P25':7, 'VHA_SYS_RATE_IQ_P5':15,
    'VHA_SYS_RATE_IQ_1':31, 'VHA_SYS_RATE_IQ_2':63, 'VHA_SYS_RATE_IQ_4':127}

    if "ve" in entry['dst']:
        #return md_control_tbl[outrate]
        return 7
    else:
        return (0x40000000 | 7)

def create_config_file(file_name, content):
    with open(file_name, "w") as file:
        for data in content:
            file.write('{{{addr}, {value}, 0xFFFFFFFF, "{name}"}},\n'.format(**data))

def create_node_config_file(file_name, content):
    with open(file_name, "w") as file:
        for param, value in content.items():
            #print(param, value)
            file.write(f'.{param} = {value},\n')

def get_nsip_host_base_addr(host_name):
    host_name = host_name.split("_")
    base_addr = ""
    
    #print(host_name)

    if "vha" in host_name[0]:
        base_addr = f"VHA{host_name[1]}_ANT{host_name[3]}_NSIP_HBI_CSR_BASE"
    if "jesd" in host_name[0]:
        base_addr = f"DLNK_JESD{host_name[2]}_NSIP_HBI_CSR_BASE"
    elif "v2d" in host_name[0]:
        if host_name[3] == "0":
            base_addr = f"V2D{host_name[1]}_AV2D_APB_0_NSIP_HBI_0_BASE"
        if host_name[3] == "1":
            base_addr = f"V2D{host_name[1]}_AV2D_APB_0_NSIP_HBI_1_BASE"
        if host_name[3] == "2":
            base_addr = f"V2D{host_name[1]}_AV2D_APB_1_NSIP_HBI_0_BASE"
        if host_name[3] == "3":
            base_addr = f"V2D{host_name[1]}_AV2D_APB_1_NSIP_HBI_1_BASE"

    if base_addr == "":
        raise Exception("generate_config_vex_to_hwa_dest, unknown host_name = " + host_name)

    return base_addr

#define VHA0_ANT0_NSIP_HBI_BASE          0x03c04000
#define VHA0_ANT1_NSIP_HBI_BASE          0x03c14000

#define V2D0_AV2D_APB_0_NSIP_HBI_BASE    0x03818000 0
#define V2D0_AV2D_APB_0_NSIP_HBI_1_BASE  0x03819000 1
#define V2D0_AV2D_APB_1_NSIP_HBI_0_BASE  0x03838000 2
#define V2D0_AV2D_APB_1_NSIP_HBI_BASE    0x03839000 3
