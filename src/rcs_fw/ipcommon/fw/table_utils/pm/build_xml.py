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

from .util import p_green2
from fractions import Fraction
#import pprint
#pp=pprint.PrettyPrinter(indent=4)

def build_xml_output(file_name, super_table_name, tbl_dic, table_dim_dic, addr_len_tup, xsd_file):
    """converting table info defined in workbook into XML format

    Parameters
    ----------
    file_name : str
        name of the output XML file
    xsd_file : str
        name of the .xsd file to be referenced by output XML file
    super_table_name : str
        table name which contains all the tables defined in this .xlsx file
    tbl_dic : dict
        a dictionary: tbl_name as key, tup (tbl_des, bf_blks, sub_tbl_dic, tbl_bitwidth_tup, align) as value
        tbl_des: table description
        bf_blks: bit-field block list, each bit-field block is a list of info for a specific bit-field
        sub_tbl_dic: a dictionary with info about a subtable
        tbl_bitwidth_tup: a tup with bitwidth info for each table
        align: specifying the alignment attribute of this table
    table_dim_dic : dict
        a dimision dictionary: tbl_name as key, tup (sub_tbl_num_max, sub_tbl_entry_num_max) as value
        sub_tbl_num_max: constant, subtable first dimision
        sub_tbl_entry_num_max: constant, subtable second dimision
    addr_len_tup : tup
        a tup of (table_address, table_length_in_bytes)

    Returns
    ----------
    None
    """
    xsd_file_content = """<?xml version="1.0" encoding="UTF-8"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
\t<xs:simpleType name="bitfield_type">
\t\t<xs:restriction base="xs:string">
\t\t\t<xs:enumeration value="signed"/>
\t\t\t<xs:enumeration value="unsigned"/>
\t\t\t<xs:enumeration value="float"/>
\t\t\t<xs:enumeration value="double"/>
\t\t</xs:restriction>
\t</xs:simpleType>
\t<xs:complexType name="field_info">
\t\t<xs:sequence>
\t\t\t<xs:element name="Name" type="xs:string"/>
\t\t\t<xs:element name="Description" type="xs:string"/>
\t\t\t<xs:element name="Unit" type="xs:string"/>
\t\t\t<xs:element name="Granularity" type="xs:decimal"/>
\t\t\t<xs:element name="Min" type="xs:decimal"/>
\t\t\t<xs:element name="Max" type="xs:decimal"/>
\t\t\t<xs:element name="Type" type="bitfield_type"/>
\t\t\t<xs:element name="Width" type="xs:integer"/>
\t\t\t<xs:element name="Val" type="xs:decimal"/>
\t\t</xs:sequence>
\t</xs:complexType>
\t<xs:complexType name="sub_table_entry_info">
\t\t<xs:sequence>
\t\t\t<xs:element name="Bitfield" minOccurs="1" maxOccurs="unbounded" type="field_info"/>
\t\t</xs:sequence>
\t</xs:complexType>
\t<xs:complexType name="sub_table_info">
\t\t<xs:sequence>
\t\t\t<xs:element name="Name" type="xs:string"/>
\t\t\t<xs:element name="Entry" minOccurs="1" maxOccurs="unbounded" type="sub_table_entry_info"/>
\t\t</xs:sequence>
\t</xs:complexType>
\t<xs:complexType name="table_info">
\t\t<xs:sequence>
\t\t\t<xs:element name="Name" type="xs:string"/>
\t\t\t<xs:element name="Description" type="xs:string"/>
\t\t\t<xs:element name="Single_entry_size" type="xs:string"/>
\t\t\t<xs:element name="Alignment" type="xs:string"/>
\t\t\t<xs:element name="Num_of_sub_table" type="xs:decimal"/>
\t\t\t<xs:element name="Num_of_entry_per_sub_table" type="xs:decimal"/>
\t\t\t<xs:element name="Sub_table" minOccurs="1" maxOccurs="unbounded" type="sub_table_info"/>
\t\t</xs:sequence>
\t</xs:complexType>
\t<xs:complexType name="super_table_info">
\t\t<xs:sequence>
\t\t\t<xs:element name="Name" type="xs:string"/>
\t\t\t<xs:element name="Address_or_section" type="xs:string"/>
\t\t\t<xs:element name="Length" type="xs:string"/>
\t\t\t<xs:element name="Table" minOccurs="1" maxOccurs="unbounded" type="table_info"/>
\t\t</xs:sequence>
\t</xs:complexType>
\t<xs:element name="Super_table" type="super_table_info"/>
</xs:schema>"""
    with open(xsd_file + ('.xsd', '')[xsd_file.endswith(".xsd")], "w") as out_f:
        out_f.write("{}".format(xsd_file_content))

    xml_header = '<?xml version="1.0" encoding="UTF-8"?>'
    xml_schema = 'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation='
    address_layout_info = ('Name', 'Address_or_section', 'Length')
    tbl_items = ('Name', 'Description', 'Single_entry_size', 'Alignment', 'Num_of_sub_table', 'Num_of_entry_per_sub_table')
    bf_items = ('Name', 'Description', 'Unit', 'Granularity', 'Min', 'Max', 'Type', 'Width', 'Val')

    with open(file_name + '.xml', "w") as of:
        k = 1
        of.write("{0}\n".format(xml_header))
        of.write("<{0} {1}\"{2}\">\n".format('Super_table', xml_schema, xsd_file + ('.xsd', '')[xsd_file.endswith(".xsd")]))
        of.write("{0}<{1}>{2}</{1}>\n".format('\t'*k, address_layout_info[0], super_table_name))
        of.write("{0}<{1}>{2}</{1}>\n".format('\t'*k, address_layout_info[1], super_table_name.upper() + '_START_ADDRESS'))
        of.write("{0}<{1}>{2}</{1}>\n".format('\t'*k, address_layout_info[2], addr_len_tup[1]))
        #pp.pprint(table_dim_dic)
        for tbl_name, dim_info in table_dim_dic.items():
            if tbl_name in tbl_dic.keys(): # only if it's been processed
                of.write("{0}<{1}>\n".format('\t'*k, 'Table'))
                of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+1), tbl_items[0], tbl_name))
                of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+1), tbl_items[1], tbl_dic[tbl_name][0]))
                of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+1), tbl_items[2], tbl_dic[tbl_name][3][0]))
                of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+1), tbl_items[3], str(tbl_dic[tbl_name][4])))

                sub_tbl_num_max = table_dim_dic[tbl_name][0] # A: num of sub tbl
                sub_tbl_entry_num_max = table_dim_dic[tbl_name][1] # B: num of entry for each sub tbl
                of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+1), tbl_items[4], sub_tbl_num_max))
                of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+1), tbl_items[5], sub_tbl_entry_num_max))

                sub_tbl_dic = tbl_dic[tbl_name][2] # {sub_tbl_name:(L, R, sub_tbl_hex, sub_tbl_bf_info), ...}}
                for sub_tbl_name in sub_tbl_dic.keys():
                    of.write("{0}<{1}>\n".format('\t'*(k+1), 'Sub_table'))
                    of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+2), 'Name', sub_tbl_name))
                    L = sub_tbl_dic[sub_tbl_name][0]
                    R = sub_tbl_dic[sub_tbl_name][1]
                    sub_tbl_max_valid_entry_cnt = (L, L*R)[L != 0]
                    sub_tbl_bf_info = sub_tbl_dic[sub_tbl_name][3]

                    total_blk_num = tbl_dic[tbl_name][3][2]
                    for e in range(sub_tbl_entry_num_max):
                        of.write("{0}<{1}>\n".format('\t'*(k+2), 'Entry'))
                        blk_ofs = 0
                        for blk_num in range(total_blk_num):
                            bf_blk = tbl_dic[tbl_name][1][blk_num]
                            for f in range(len(bf_blk)):
                                of.write("{0}<{1}>\n".format('\t'*(k+3), 'Bitfield'))
                                for r in range(9):
                                    if r == 1:
                                        bf = str(bf_blk[f][r]).replace('\n','')
                                    elif (r == 4 or r == 5 ) and (str(bf_blk[f][r]) == 'None'):
                                        bf = 0
                                    elif r == 3:
                                        bf = float(Fraction(str(bf_blk[f][r])))
                                    elif r == 8:
                                        if e < sub_tbl_max_valid_entry_cnt:
                                            bf = sub_tbl_bf_info[e][f+blk_ofs]
                                        else:
                                            bf = 0
                                    else:
                                        bf = str(bf_blk[f][r])
                                    of.write("{0}<{1}>{2}</{1}>\n".format('\t'*(k+4), bf_items[r], bf))
                                of.write("{0}</{1}>\n".format('\t'*(k+3), 'Bitfield'))
                            blk_ofs += len(bf_blk)
                        of.write("{0}</{1}>\n".format('\t'*(k+2), 'Entry'))
                    of.write("{0}</{1}>\n".format('\t'*(k+1), 'Sub_table'))
                of.write("{0}</{1}>\n".format('\t'*k, 'Table'))
        of.write("</{0}>\n".format('Super_table'))
    p_green2("\nGenerated XML file", file_name + '.xml')
