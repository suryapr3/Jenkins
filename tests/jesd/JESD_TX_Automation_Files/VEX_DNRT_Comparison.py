#The below script is used for comparing VEX TX data to DNRT RX SPL

import difflib
import collections
import sys
import re
import os
from multiprocessing import Process

files = 16

# Parent Directory path
parent_directory = r"/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p8/abc_emul-srvrgen4/tests/jesd/xstep_files/savepayloads"
base_directory = r"/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p8/abc_emul-srvrgen4/tests/jesd"

# Path
path = os.path.join(parent_directory, "VEX_VS_SPL")
path_matched = os.path.join(parent_directory, "VEX_VS_SPL", "matched")
path_unmatched = os.path.join(parent_directory, "VEX_VS_SPL", "unmatched")

if not os.path.exists(path):
    os.mkdir(path)
    os.mkdir(path_matched)
    os.mkdir(path_unmatched)

def VEX_VS_SPL(rotation):
    
    os.chdir(parent_directory)
    filename_savepayload  = "savepayload"
    filename_payload = "payload"
    
    spl = open(str(filename_savepayload)+str(rotation)+".txt","r")
    pl = open(str(filename_payload)+str(rotation)+".txt","r")
    vex = pl.readlines()
    dnrt = spl.readlines()
    matched = 0
    unmatched = 0
    total = 0
    p = 0
    h = 0
    x = open(str(path_matched)+"/payload_"+str(rotation)+"_matched_with_savepayload_"+str(rotation)+".txt","w")
    y = open(str(path_unmatched)+"/payload_"+str(rotation)+"_unmatched_with_savepayload_"+str(rotation)+".txt","w")


    # splitting the dnrt save payloads into each cycle based on 0000 into ref_list
    mas_list = []
    ref_list = []
    for i in dnrt:
        if i != vex[0]:
            ref_list.append(i)
            continue
        # adding ref_list into mas_list i.e., all the cycles of data
        mas_list.append(ref_list)
        ref_list = [vex[0]]
    #print("mas_list", mas_list)
    count = 1
    #Comparing mas_list data (Save payloads) against vex data (payloads)
    for i in mas_list:
        if i == vex:
            x.write("matched element " + str(u) + " in cycle " + str(count) + "\n")
        else:
            #It will find the index of first matching element of mas_list (save payload) in vex (payload)
            index = vex.index(i[0])
            #If any mis-match found, it will search whether that element is present in the cycle at all
            for u in vex[index:]:
                if u in i:
                    x.write("matched element " + str(u) + " in cycle " + str(count) + "\n")
                else:
                    y.write("unmatched element " + str(u) + " in cycle " + str(count) + "\n")
        count = count + 1


    # x.write("\ntotal number of values in payload_"+str(rotation)+ ": " + str(total) + "\nnumber of matched values: " +str(matched))
    # y.write("\ntotal number of values in payload: "+str(rotation)+ ": " + str(total) + "\nnumber of unmatched values: " +str(unmatched))

    print("*******************finished VEX Vs DNRT_SPL comparison*******************")

def VEX_VS_SPL_calling():
    for i in range (0, files):
        VEX_VS_SPL(i)
    os.chdir(base_directory)
    
    
#Enable these 2 lines to perform comparison directly
# for i in range (0, files):
   # VEX_VS_SPL(i)

#Basic working with save payload as reference, failing for data skip
    # for m in range(0, len(dnrt)):
        # flag = 0
        # #if dnrt[m + 1] == vex[c + 1]:

        # for l in range(0, len(vex)):
            # if l < len(vex) - 4 and m < len(dnrt) - 4 and (
                    # dnrt[m] == vex[l] and (
                    # dnrt[m + 3] == vex[l + 3] and dnrt[m + 2] == vex[
                # l + 2] and dnrt[m + 1] == vex[l + 1])) or (
                    # dnrt[m] == vex[l] and (
                    # dnrt[m - 4] == vex[l - 4] and dnrt[m - 3] == vex[
                # l - 3] and dnrt[m - 2] == vex[l - 2] and dnrt[m - 1] == vex[
                        # l - 1])):

                # x.write("matched element " + str(dnrt[m]) + " in cycle " + str(p) + "\n")
                # h = h + 1
                # flag = 1
                # break
            # elif ((l >= len(vex) - 3 and l <= len(vex) - 1) or (
                    # m >= len(dnrt) - 3 and m <= len(dnrt) - 1)) and dnrt[m] == vex[l] and (
                    # dnrt[m - 2] == vex[l - 2] and dnrt[m - 1] == vex[l - 1]):
                # x.write("matched element " + str(dnrt[m]) + " in cycle " + str(p) + "\n")
                # h = h + 1
                # flag = 1
                # break



#Taking VEX Data as Reference

'''    for m in range(0, len(vex)):
        flag = 0
        #if vex[m + 1] == dnrt[c + 1]:

        for l in range(0, len(dnrt)):
            if l < len(dnrt) - 4 and m < len(vex) - 4 and (
                    vex[m] == dnrt[l] and (
                    vex[m + 3] == dnrt[l + 3] and vex[m + 2] == dnrt[
                l + 2] and vex[m + 1] == dnrt[l + 1])) or (
                    vex[m] == dnrt[l] and (
                    vex[m - 4] == dnrt[l - 4] and vex[m - 3] == dnrt[
                l - 3] and vex[m - 2] == dnrt[l - 2] and vex[m - 1] == dnrt[
                        l - 1])):

                x.write("matched element " + str(vex[m]) + " in cycle " + str(p) + "\n")
                h = h + 1
                flag = 1
                break
            elif ((l >= len(dnrt) - 3 and l <= len(dnrt) - 1) or (
                    m >= len(vex) - 3 and m <= len(vex) - 1)) and vex[m] == dnrt[l] and (
                    vex[m - 2] == dnrt[l - 2] and vex[m - 1] == dnrt[l - 1]):
                x.write("matched element " + str(vex[m]) + " in cycle " + str(p) + "\n")
                h = h + 1
                flag = 1
                break

            #c = l
                #print("not matched");
        if flag == 0:
            y.write("unmatched element " + str(dnrt[m]) + " in cycle " + str(p) + "\n")

        if h == len(vex):
            p = p + 1
            h = 0
            '''