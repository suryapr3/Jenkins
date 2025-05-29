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

from pathlib import Path # for file name/path
from .util import p_green2

def build_html_output(file_name, tbl_dic, table_dim_dic, html_dir, do_msg):
    """converting table info defined in workbook into HTML format

    the generated HTML file is mainly for review purpose

    Parameters
    ----------
    file_name : str
        name of the output HTML file
    tbl_dic : dict
        a dictionary: tbl_name as key, tup (tbl_des, bf_blks, sub_tbl_dic, tbl_bitwidth_tup, align) as value
        tbl_des: table description
        bf_blks: bit-field block list, each bit-field block is a list of info for a specific bit-field
        sub_tbl_dic: a dictionary with info about a subtable
        tbl_bitwidth_tup: a tup with bitwidth info for each table
        align: specifying the alignment attribute of this table
    table_dim_dic : dict
        a dimision dictionary with tbl_name as key, tup (sub_tbl_num_max, sub_tbl_entry_num_max) as value
        sub_tbl_num_max: constant, subtable first dimision
        sub_tbl_entry_num_max: constant, subtable second dimision
	html_dir : str
        specifying the folder to hold the generated HTML files
    do_msg : str
        name for message header, when not None, indicating doing message table process

    Returns
    ----------
    None
    """

    col_color = ('C0C0F0', 'C0F0C0', 'F0C0C0', 'C0C0C0')
    label_name = ('Name', 'Description', 'Unit', 'Granularity', 'Min', 'Max', 'Sign', 'Bit width')

    path = Path(html_dir)
    path.mkdir(parents=True, exist_ok=True)
    with open(html_dir + '/' + file_name + '.html', "w") as of:
        # header
        of.write('<!DOCTYPE html>\n<html>\n<head>\n<style type=\"text/css\">\n\tbody {font-family:\"Segoe UI\", \"Segoe\",Tahoma,Verdana,Helvetica,Arial,sans-serif; background-color=#FFFFFF;}\n')
        of.write('\ttable, th, td {\n\t\tborder: 1px solid black;\n\t\tborder-collapse: collapse;\n\t}\n</style>\n</head>\n<body>')

        #of.write('<span id="SUP_' + file_name + '">\n')
        if do_msg == None:
            of.write('<h2>Tables layout and size:</h2>\n')
            of.write('<table style=\"width:40%\">\n')
            of.write('<tr><th bgcolor=\"E0C0C0\">Name and layout</th><th bgcolor=\"E0C0C0\">Size</th>\n')
            for tbl_name, dim_info in table_dim_dic.items():
                of.write('<tr><td align=\"center\"><a href=\"#REF_' + tbl_name + '\">' + '<span style=\"color:blue;font-weight:bold\">' + tbl_name + '</span></a></td>\n')
                of.write('<td align=\"center\"><span style=\"color:green;font-weight:bold\">' + str(dim_info[0]) + 'x' + str(dim_info[1]) + '</span></td></tr>\n')
            of.write('<table><br>\n')
            of.write('<h2>Tables details:</h2>\n')
            for tbl_name, dim_info in table_dim_dic.items():
                tbl_des = tbl_dic[tbl_name][0]
                tbl_alignment = str(tbl_dic[tbl_name][4])
                tbl_struct_blk_num = tbl_dic[tbl_name][3][2]
                type_bitwidth = tbl_dic[tbl_name][3][1]
                tbl_bitwidth = tbl_dic[tbl_name][3][0]
                of.write('<span id=\"REF_' + tbl_name + '\">\n')
                of.write('<h3>Table: ' + tbl_name + ' [' + '<span style=\"color:green;font-weight:bold\">' + str(dim_info[0]) + 'x' + str(dim_info[1]) + '</span>]</h3>\n')
                of.write('<p><span style=\"font-weight:bold\">Description:</span> ' + tbl_des + '</p>\n')
                of.write('<p><span style=\"font-weight:bold\">Alignment:</span> ' + tbl_alignment + '</p>\n')
                of.write('<p><span style=\"font-weight:bold\">Single entry size:</span> ' + str(tbl_bitwidth) + '-bits' + '</p>\n')
                of.write('<table style=\"width:90%\">\n')
                for blk_num in range(tbl_struct_blk_num):
                    of.write('<tr><td align=\"right\">Bit position</td>')
                    for b in range((blk_num + 1) * type_bitwidth - 1, blk_num * type_bitwidth - 1, -1):
                        of.write('<td colspan=\"1\" align=\"center\" bgcolor=\"EEEEEE\"><span style=\"color:green;font-weight:bold\">' + str(b) + '</span></td>')
                    of.write('</tr>')
                    bf_blk = tbl_dic[tbl_name][1][blk_num]
                    for r in range(8): # TODO: 8: bf_info_depth = table_pos_info[4]
                        of.write('<tr>' + '<td align=\"right\">' + label_name[r] + '</td>')
                        for f in range(len(bf_blk)-1, -1, -1):
                            if r==0 or r==7:
                                of.write('<td colspan=\"' + str(bf_blk[f][7]) +  '\" align=\"center\" bgcolor=\"' + col_color[f % 4] + '\">' + '<span style=\"color:blue;font-weight:bold\">' + str(bf_blk[f][r]) + '</span></td>')
                            elif r==6:
                                of.write('<td colspan=\"' + str(bf_blk[f][7]) +  '\" align=\"center\" bgcolor=\"' + col_color[f % 4] + '\">' + '<span style=\"font-weight:bold\">' + str(bf_blk[f][r]) + '</span></td>')
                            else:
                                of.write('<td colspan=\"' + str(bf_blk[f][7]) +  '\" align=\"center\" bgcolor=\"' + col_color[f % 4] + '\">' + str(bf_blk[f][r]) + '</td>')
                        of.write('</tr>\n')
                of.write('</table></span><br>\n')
        else:
            of.write('<h2>Tables:</h2>\n')
            of.write('<table style=\"width:40%\">\n')
            of.write('<tr><th bgcolor=\"E0C0C0\">Names</th>\n')
            for tbl_name in tbl_dic.keys():
                of.write('<tr><td align=\"center\"><a href=\"#REF_' + tbl_name + '\">' + '<span style=\"color:blue;font-weight:bold\">' + tbl_name + '</span></a></td>\n')
            of.write('<table><br>\n')
            of.write('<h2>Tables details:</h2>\n')
            for tbl_name in tbl_dic.keys():
                tbl_des = tbl_dic[tbl_name][0]
                tbl_alignment = str(tbl_dic[tbl_name][4])
                tbl_struct_blk_num = tbl_dic[tbl_name][3][2]
                type_bitwidth = tbl_dic[tbl_name][3][1]
                tbl_bitwidth = tbl_dic[tbl_name][3][0]
                of.write('<span id=\"REF_' + tbl_name + '\">\n')
                of.write('<h3>Table: ' + tbl_name + '</h3>\n')
                of.write('<p><span style=\"font-weight:bold\">Description:</span> ' + tbl_des + '</p>\n')
                of.write('<p><span style=\"font-weight:bold\">Alignment:</span> ' + tbl_alignment + '</p>\n')
                of.write('<p><span style=\"font-weight:bold\">Single entry size:</span> ' + str(tbl_bitwidth) + '-bits' + '</p>\n')
                of.write('<table style=\"width:90%\">\n')
                for blk_num in range(tbl_struct_blk_num):
                    of.write('<tr><td align=\"right\">Bit position</td>')
                    for b in range((blk_num + 1) * type_bitwidth - 1, blk_num * type_bitwidth - 1, -1):
                        of.write('<td colspan=\"1\" align=\"center\" bgcolor=\"EEEEEE\"><span style=\"color:green;font-weight:bold\">' + str(b) + '</span></td>')
                    of.write('</tr>')
                    bf_blk = tbl_dic[tbl_name][1][blk_num]
                    for r in range(8): # TODO: 8: bf_info_depth = table_pos_info[4]
                        of.write('<tr>' + '<td align=\"right\">' + label_name[r] + '</td>')
                        for f in range(len(bf_blk)-1, -1, -1):
                            if r==0 or r==7:
                                of.write('<td colspan=\"' + str(bf_blk[f][7]) +  '\" align=\"center\" bgcolor=\"' + col_color[f % 4] + '\">' + '<span style=\"color:blue;font-weight:bold\">' + str(bf_blk[f][r]) + '</span></td>')
                            elif r==6:
                                of.write('<td colspan=\"' + str(bf_blk[f][7]) +  '\" align=\"center\" bgcolor=\"' + col_color[f % 4] + '\">' + '<span style=\"font-weight:bold\">' + str(bf_blk[f][r]) + '</span></td>')
                            else:
                                of.write('<td colspan=\"' + str(bf_blk[f][7]) +  '\" align=\"center\" bgcolor=\"' + col_color[f % 4] + '\">' + str(bf_blk[f][r]) + '</td>')
                        of.write('</tr>\n')
                of.write('</table></span><br>\n')
        # footer
        of.write('</body>\n</html>')
    p_green2("\nGenerated HTML file", html_dir + '/' + file_name + '.html')


