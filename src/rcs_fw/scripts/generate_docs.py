#!/usr/bin/env python3

import os, sys
import shutil
import logging


def delete_dir(rootdir):
    del_dir_name = rootdir+'/out/'+'doxy_doc'
    print(del_dir_name)
    try:
        shutil.rmtree(del_dir_name)
    except OSError as e:
            print("Error: %s : %s" % (del_dir_name, e.strerror))


def list_dirs(rootdir, out_dir, inp_dir_name, exclude):
    for dir_name in os.listdir(rootdir):
        d = os.path.join(rootdir, dir_name)
        if os.path.isdir(d) and dir_name not in exclude:
            if (d.find(inp_dir_name) != -1):   
                print(d)
                out_dir.append(d)
            list_dirs(d,out_dir,inp_dir_name,exclude)


def doxygen_gen(curr_dir, rootdir):
    print("curr_dir")
    os.chdir(curr_dir) #change directory to the current directory
    rootdir2 = os.getcwd() #rootdir2 = path to the current directory 
    print(rootdir2) #Print the path to the current directory 
    os.system('mkdir -p ./doc') #Will create new directory named doc in current directory
    doxy_command = 'doxygen'+ ' ' +rootdir + '/scripts/doxy_config_file'
    os.system(doxy_command) #runs doxygen (creates documentation) for root directpry
    dest_dir = rootdir2.replace(rootdir, rootdir+'/out/doxy_doc') #Replace path to root dir w paths to rootdir/output/doxydoc
    print("out_dir: "+ dest_dir) #print out_dir + path to roodir/output/doxydoc
    src_dir = os.getcwd() +'/doc/'  #src_dir is path to current directory/doc
    files = os.listdir(src_dir)  #files are all the files in the src_dir
    for f in files: 
        shutil.move(src_dir + f, dest_dir) #moves every file in the src to rootdir/output/doxydoc
    shutil.rmtree(src_dir) #Delete the src directoty


def generate_doxy_index(inc_dir_list, out_dir_list, rootdir):

    parent_index_path = os.path.join(rootdir, 'out', 'doxy_doc', 'index.html')
    with open(parent_index_path, 'w') as index_file:
        index_file.write("<html><head><title>Arbor Crest Firmware Documentation Index</title></head><body>")
        index_file.write("<h1>RCS Documentation Index</h1><ul>")      
    total_dir =  inc_dir_list + out_dir_list
    for dir in total_dir:
        dest_dir = dir.replace(rootdir + '/', '')
        final_link = os.path.join(dest_dir, "index.html")
        with open(parent_index_path, 'a') as index_file:
            index_file.write(f'<li><a href="{final_link}">{dest_dir}</a></li>') 
    with open(parent_index_path, 'a') as index_file:
        index_file.write("</ul></body></html>")


def combine_table_html( title, table_dir, outfile_name):
    html_files = sorted(os.listdir(table_dir))
    references = []
    body = ""
    for f in html_files:
        with open( os.path.join(table_dir,f), "r") as infile:
            filebody = False
            fileend = False
            while( not fileend ):
                line = infile.readline()
                if ( "#REF" in line ):
                    references.append( line )
                if ( "</body>" in line) : fileend = True
                if filebody:
                    body = body + "\n" + line
                if ( "Tables details:" in line ): filebody = True
    with open( outfile_name, "w") as outfile:
        header="""
                <!DOCTYPE html>
                <html>
                <head>
                <style type="text/css">
                        body {font-family:"Segoe UI", "Segoe",Tahoma,Verdana,Helvetica,Arial,sans-serif; background-color=#FFFFFF;}
                        table, th, td {
                            border: 1px solid black;
                            border-collapse: collapse;
                        }
                </style>
                </head>
                <body><h2>%s:</h2>
                <table style="width:40%%">
                <tr><th bgcolor="E0C0C0">Names</th>"""
        outfile.write(header % (title))
        outfile.write( '\n'.join(sorted(references)) )
        outfile.write( "</table><br>")
        outfile.write( body )
        outfile.write( "</body></html>")


print("Generating Doxygen documentation...")
rootdir = os.getcwd()
print(rootdir)
out_dir_list = []
inc_dir_list = []

# remove old doc files
delete_dir(rootdir)

list_dirs(rootdir,inc_dir_list, 'inc', ['rtl','rte','scripts','out', 'hw_inc'])
list_dirs(rootdir,out_dir_list, 'src', ['rtl','rte','scripts','out', 'hw_inc'])
print("inc dir list...")
print(inc_dir_list)
print("src dir list...")
print(out_dir_list)

for i in inc_dir_list:
    doxygen_gen(i,rootdir) #For each inc file, generate documentation
#    
for i in out_dir_list:
    doxygen_gen(i,rootdir) #For each src file, generate documentatiom

generate_doxy_index(inc_dir_list, out_dir_list, rootdir)

combine_table_html( "RCS FW Tables", rootdir + "/ipcommon/fw/tables/html", rootdir + "/out/doxy_doc/tables.html")
combine_table_html( "RCS FW Messages", rootdir + "/ipcommon/fw/msg/html", rootdir + "/out/doxy_doc/messages.html")
 
print("Done")
sys.exit(0)   #SUCCESS
