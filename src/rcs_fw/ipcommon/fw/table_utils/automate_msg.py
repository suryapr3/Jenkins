#**************************************************************************
# INTEL CONFIDENTIAL
#
# Copyright 2024 Intel Corporation All Rights Reserved.
#
# The source code contained or described herein and all documents r
# to the source code ("Material") are owned by Intel Corporation or
# suppliers or licensors. Title to the Material remains with Intel
# Corporation or its suppliers and licensors. The Material contains
# secrets and proprietary and confidential information of Intel or
# suppliers and licensors. The Material is protected by worldwide c
# and trade secret laws and treaty provisions. No part of the Mater
# may be used, copied, reproduced, modified, published, uploaded, p
# transmitted, distributed, or disclosed in any way without Intel's
# express written permission.
#
# No license under any patent, copyright, trade secret or other
# intellectual property right is granted to or conferred upon you b
# disclosure or delivery of the Materials, either expressly, by
# implication, inducement, estoppel or otherwise. Any license under
# intellectual property rights must be express and approved by Inte
# writing.
#**************************************************************************

from os import listdir
import os
import json
import string
from time import strftime, localtime # for header copyright

def write_copyright(filename):
    """writes the copyright claim into the output file

    Parameters
    ----------
    filename: the outputfile for the copyright claim to be written in

    Returns
    ----------
    None
    """
    with open(filename, "w") as f:
        year = strftime("%Y", localtime())
        f.write("/**************************************************************************\n")
        f.write("** INTEL CONFIDENTIAL\n")
        f.write("** Copyright " + year + " Intel Corporation All Rights Reserved.\n")
        f.write("**\n")
        f.write("** The source code contained or described herein and all documents related to\n")
        f.write("** the source code (\"Material\") are owned by Intel Corporation or its\n")
        f.write("** suppliers or licensors. Title to the Material remains with\n")
        f.write("** Intel Corporation or its suppliers and licensors.\n")
        f.write("** The Material contains trade secrets and proprietary and confidential\n")
        f.write("** information of Intel or its suppliers and licensors. The Material is\n")
        f.write("** protected by worldwide copyright and trade secret laws and treaty\n")
        f.write("** provisions. No part of the Material may be used, copied, reproduced,\n")
        f.write("** modified, published, uploaded, posted, transmitted, distributed, or\n")
        f.write("** disclosed in any way without Intel's prior express written permission.\n")
        f.write("**\n")
        f.write("** No license under any patent, copyright, trade secret or other\n")
        f.write("** intellectual property right is granted to or conferred upon you by\n")
        f.write("** disclosure or delivery of the Materials, either expressly, by implication,\n")
        f.write("** inducement, estoppel or otherwise. Any license under such intellectual\n")
        f.write("** property rights must be express and approved by Intel in writing.\n")
        f.write("*************************************************************************/\n")

def write_headers(filename):
    """writes respective headers into the c and h outputfiles

    Parameters
    ----------
    filename: the outputfile for the headers to be written in

    Returns
    ----------
    None
    """

    write_copyright(filename)

    if (len(filename.split(".c")) > 1):
        with open(filename, "a") as f:
            f.write("#include <elf.h>\n")
            f.write("#include <stdbool.h>\n\n")
            f.write("#include \"srp.h\"\n")
            f.write("#include \"com_shared_memory_def.h\"\n")
            f.write("#include \"rcs_gpreg.h\"\n")
            f.write("#include \"srp_status.h\"\n\n")
            f.write("#include \"com_msg_def.h\"\n\n")
            f.write("#include \"srp_rcs_queue_if.h\"\n\n")
            f.write("#define SHARED_MEM_BASE 0x00200000\n\n")
            f.write("struct rcs_system_status_memory *p_system_data = (struct rcs_system_status_memory*) (SHARED_MEM_BASE);\n\n")
    elif(len(filename.split(".h")) > 1):
        with open(filename, "a") as f:
            f.write("\n/*! @file      srp_rcs_msg_if.h\n")
            f.write(" *  @brief     Radio Control Subsystem FW Message handlers\n")
            f.write(" *\n")
            f.write(" *  @addtogroup _rcs_ Radio Control Subsystem\n")
            f.write(" *\n")
            f.write(" *  @{\n")
            f.write(" */\n\n")
            f.write("#ifndef __SRP_RCS_MSG_IF_H__\n")
            f.write("#define __SRP_RCS_MSG_IF_H__\n\n")
            f.write("#include \"dl_req_msg.h\"\n")
            f.write("#include \"ul_req_msg.h\"\n")
            f.write("#include \"admin_msg.h\"\n")
            f.write("#include \"set_time_ref_msg.h\"\n")
            f.write("#include \"readback_msg.h\"\n")
            f.write("#include \"com_queue_def.h\"\n")
            f.write("#include \"srp_status.h\"\n")
            f.write("\n")


def generate_func_body(msg_title, field_dic):
    """generates a string with the function's body

    Parameters
    ----------
    msg_title: the title of the message starting with ul/dl and then the task (on, off, config...)

    Returns
    ----------
    a string with the function's body
    """
    # creates a string with the information in the function bodys
    func_body = "    msg_t msg;\n"
    func_body += "    srp_uint32_t msg_len = LEN_IN_WORD(sizeof(" + msg_title + "_bf_t));\n"
    func_body += "    msg." + msg_title + "  = *" + msg_title + "_msg;\n"
    func_body += generate_range_checking(field_dic, msg_title)
    func_body += "    fw_msg_queue_insert (srp, p_msg_queue, &msg, msg_len);\n"
    if msg_title.startswith('ul_'):
        func_body += "srp_rcs_set_rx_mailbox_interrupt(srp);\n"
    elif msg_title.startswith('dl_'):
        func_body += "srp_rcs_set_tx_mailbox_interrupt(srp);\n"
    else:
        func_body += "srp_rcs_set_admin_mailbox_interrupt(srp);\n"
    func_body += "    return SRP_ST_SUCCESS;\n"
    func_body = "{\n" + func_body + "}"

    return func_body

def generate_range_checking(field_dic, msg_title):
    """generates a string with the range checking conditionals

    Parameters
    ----------
    field_dic: a dictionary containing the fields within the message

    Returns
    ----------
    a string with the range checking conditionals
    """
    rc_string = ""

    for field in field_dic:
        if ((field_dic[field]["max"] != 0) or (field_dic[field]["min"] != 0)):
            error_msg = "SRP_ST_RCS_INVALID"
            # removing digits from end of message title
            error_field = field.rstrip(string.digits)
            error_msg = error_msg + "_" + error_field.upper()
            rc_string += generate_range_check(field, field_dic, msg_title, error_msg)

    return rc_string

def generate_range_check(field, field_dic, msg_title, return_t):
    """generates a string with 1 range checking conditional given a specific field

    Parameters
    ----------
    field: a string with the name of the field to range check for
    detail_dic: a dictionary with the details about the field (min, max, etc.)
    field_dic: a dictionary containing the fields within the message and their details

    Returns
    ----------
    a string with 1 specific range checking conditional
    """
    detail_dic = field_dic[field]
    rc_string = ""
    rc_string = "    if ((msg." + msg_title + "." + field + " > " + str(detail_dic["max"]) + ") "
    rc_string += "|| (msg." + msg_title + "." + field + " < " + str(detail_dic["min"]) + ")){return " + return_t + ";}\n"
    return rc_string

def generate_func_definition(msg_title):
    """generates a string with the function definition based off the message title

    Parameters
    ----------
    msg_title: the title of the message starting with ul/dl and then the task (on, off, config...)

    Returns
    ----------
    a string with the function definition
    """
    # creating the function definition
    func_name = "srp_st_t" + " " + "srp_rcs_send_" + msg_title + "_msg"
    func_params ="void *srp"+ ", " + "msg_queue_t *p_msg_queue" + ", "
    func_params += msg_title + "_bf_t" + " " + "*" + msg_title + "_msg"
    func_definition = func_name + " " + "(" + func_params + ")"

    return func_definition

def write_functions(directory_name,outputfile, rc_dic):
    """writes the functions name, parameters, and bodies for the messages in a specified directory into the output file

    Parameters
    ----------
    directory_name: the directory containing the message csv files
    outputfile: the file to write the functions within

    Returns
    ----------
    None
    """
    # creating function definitions for messags in the passed in directory name
    path = directory_name
    files = sorted(listdir(path))

    general_title = directory_name.split("/")[len(directory_name.split("/"))- 1]
    general_title = general_title.split("_")[0]

    # comment with what directory the messages are from
    with open(outputfile, "a") as f:
        f.write(r"//" + general_title + " functions\n")

    # creating the function names based off each file name
    for fn in files:
        #splitting the .csv off of the file names
        fn,ext = fn.split(".")

        if ( ext == "csv" ):
           # writing to the output file
           with open(outputfile, "a") as f:
               f.write(generate_func_definition(fn) + "\n")
               f.write(generate_func_body(fn, rc_dic[fn]))
               f.write("\n\n")


def generate_comments(msg_title):
    """generates the doxygen for a function given their message title (ul_on)

    Parameters
    ----------
    msg_title: the title of the message starting with ul/dl and then the task (on, off, config...)

    Returns
    ----------
    a string containing the doxygen for the message
    """
    # tx or rx correlates with ul or dl
    tx_rx = ""
    if (msg_title.split("_")[0] == "ul"):
        tx_rx = "RX"
    elif (msg_title.split("_")[0] == "dl"):
        tx_rx = "TX"

    # @fn
    comments = "/*! "
    comments += "@fn " + generate_func_definition(msg_title) +";\n"

    # @brief
    # cutting off dl/ul
    if (len(msg_title.split("_")) == 1):
        msg_task = msg_title
    else:
        msg_task = msg_title.split("%s_" %(msg_title.split("_")[0]))[1]

    # words between ul/dl and _msg
    task = ""
    for word in msg_task.split("_"):
        task += " %s"%(word)

    # if condition for the brief
    comments += "    @brief Send the " + tx_rx
    comments += task + " message\n"
    # @params
    comments += "    @param srp Incoming handle of the current RCS module instance\n"
    comments += "    @param p_msg_queue pointer to the message queue\n"


    # third @param
    comments +=  "    @param " + msg_title + "_msg " + tx_rx + task + " message structure\n"

    # closing the comments
    comments += "*/\n"

    return comments

def write_doxygen_functions(directory_name, output_path):
    """writes the function definitions and their doxygen in the header file

    Parameters
    ----------
    directory_name: the directory which contains the message .csv files
    outputfile: the file to write the doxygen functions within

    Returns
    ----------
    None
    """

    # creating function definitions for messags in rxv
    path = directory_name
    files = sorted(listdir(path))

    general_title = directory_name.split("/")[len(directory_name.split("/"))- 1]
    general_title = general_title.split("_")[0]

    # comment with what directory the messages are from
    with open(output_path, "a") as f:
        f.write(r"//" + general_title.upper() + " FUNCTIONS\n\n")

    # creating the function names based off each file name
    for csv_filename in files:
        #splitting the .csv off of the file names
        msg_title,ext = csv_filename.split(".")

        # writing to the output file
        if ( ext == "csv" ):
            with open(output_path, "a") as f:
                f.write(generate_comments(msg_title) + "\n")
                f.write(generate_func_definition(msg_title) + ";\n")
                f.write("\n\n")


def csv2api(source_dir, dest_dir, command, msg_dic_file):
    """writes the header and c files for a specified source directory with message csv files

    Parameters
    ----------
    source_dir: the name of the directory following the path /abc_fw/arborcrest/ipcommon/fw/msg/csv/ with the csv files
    dest_dir: the name of the directory for the autogenerated h and c files to reside in
    command:'w': write mode
            'a': append mode
            't': tail mode
    msg_dic_file: the file name contains msg related dictionary

    Returns
    ----------
    None
    """
    outputfile = "srp_rcs_msg_if.c"

    # read the range checking dictionary
    with open(msg_dic_file, "a") as f:
        f.write("")

    with open(msg_dic_file, "r+") as f:
        # range checking dictionary
        rc_dic = json.load(f)

    # creating directories if they do not already exist
    os.makedirs(dest_dir, exist_ok=True)

    # if received the write append 'w', then we are writing for the first time so headers are needed
    if command == "w":
        write_headers(dest_dir + "/src/" + outputfile)
        write_headers(dest_dir + "/inc/" + (outputfile).split(".")[0] + r".h")

    # always write the functions
    write_functions(source_dir, dest_dir + "/src/" + outputfile, rc_dic)
    write_doxygen_functions(source_dir, dest_dir + "/inc/" + outputfile.split(".")[0] + ".h")

    # if this function is the tail, needs to end with #endif at the end of the file
    if command == 't':
        with open(dest_dir + "/inc/" + outputfile.split(".")[0] + ".h", "a") as f:
            f.write("#endif\n")
        os.remove(msg_dic_file)



