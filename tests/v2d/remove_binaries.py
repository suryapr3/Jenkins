#!/usr/bin/env python
import sys
import os
import shutil

path = os.getcwd()
print(path)
for root, dirs, files in os.walk(path):
    for dir_name in dirs:
        if ("sim_m64" in dir_name) or ("html" in dir_name) or ("hivecc_intermediates" in dir_name):
            try:
                print(os.path.join(root,dir_name))
                shutil.rmtree(os.path.join(root,dir_name))
            except OSError as error:
                print (error)

    for file_name in files:
        if (".xlsx" in file_name):
            try:
                print(os.path.join(root,file_name))
                os.remove(os.path.join(root,file_name))
            except OSError as error:
                print (error)

