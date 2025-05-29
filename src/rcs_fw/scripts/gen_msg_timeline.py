#!/usr/bin/env python3
 #
 # INTEL CONFIDENTIAL
 #
 # Copyright 2024 Intel Corporation All Rights Reserved.
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
 #
 #****************************************************************************/
import UsrIntel.R1
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
import pandas as pd
import plotly.express as px
import argparse 
import os
import plotly.graph_objs as go
from plotly.offline import iplot, init_notebook_mode

def time_scale(tim):
    return (tim)/983 

class ProcessingInterval():
    def __init__(self, id, recs_start, recs_end, rec_func, level):
        self.id = id   # Name of the node, duc
        self.record_list_start = [time_scale(recs_start)]
        self.record_list_end = [time_scale(recs_end)]
        self.record_list_func = [rec_func]
        self.record_list_level = [level]

    def add_record( self, func, start, end, level):
        self.record_list_start.append(time_scale(start))
        self.record_list_end.append(time_scale(end))
        self.record_list_func.append(func)
        self.record_list_level.append(level)

def add_record( records, func, start, end, level):
    for rec in records:
        if int(rec.id) == func:
            rec.add_record( func, start, end, level)
            return
    records.append( ProcessingInterval(str(func), start, end, func, level))

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Parse trace into data structure to be graphed 
# cpu_levels: dictionary that holds {   AX: [endtime1, endtime2, ...]
#                                       TX: [endtime1, ...] }
cpu_levels = {}
y_list = []
records = []
start_time = []
end_time = [] 
func = []
timestamps = {}
ts_flag = False 

# Parsing Arguments
parser = argparse.ArgumentParser()
parser = argparse.ArgumentParser(description='Generate a message timeline graph from a fw_funcs.log file.')
parser.add_argument("--t", dest='trace_log', required = True, help = 'trace log file to be parsed' )
args = parser.parse_args()
trace_log = args.trace_log

if not os.path.isfile(trace_log):
    print( "!!!" )
    print( "!!! log file not found: " + trace_log )
    print( "!!!" )
else: 
    with open(trace_log, 'r') as file:
        os.system("egrep 'DBG_DATA|FUNC|TIMESTAMP' %s | sed -e 's/.*: //' > temp.out" %(trace_log))

    # Parse Trace 
    with open('temp.out', 'r') as file:
        for line in file.readlines():
            strings = line.split()
            # 'Timestamp' lines
            if (strings[0] == "TIMESTAMP"): 
                ts_flag = True
                timestamp_id = strings[1]

            # Line after 'Timestamp' lines
            if ((len(strings) == 1) and (ts_flag == True)):
                time_val=int(strings[0],16)
                timestamps[round(time_scale(time_val), 1)] = timestamp_id
                ts_flag = False

            if len(strings) != 4:
                continue

            # 'Start' lines
            if (strings[0] == "START" ): 
                func.append(strings[2])
                start_time.append(strings[3][1:])
                cpu_id_scheme = {0x20: 'tx', 0x40: 'rx', 0x60: 'ax', 0x80: 'ax'}
                for i in range(len(func)):
                    if (int(func[i]) & 0xE0) in cpu_id_scheme:
                        this_cpu = cpu_id_scheme.get(int(func[i]) & 0xE0)
                    else:
                        this_cpu = 'other'

            # 'Stop' lines
            elif (strings[0] == "STOP" ):
                for i in range(len(func)):
                    if func[i] == strings[2]:
    
                        cpu_id_scheme = {0x20: 'tx', 0x40: 'rx', 0x60: 'ax', 0x80: 'ax'}
                        if (int(func[i]) & 0xE0) in cpu_id_scheme:
                            this_cpu = cpu_id_scheme.get(int(func[i]) & 0xE0)
                        else:
                            this_cpu = 'other'

                        found_cpu = False
                        # Record the cpu if hasn't been recorded yet
                        if this_cpu in cpu_levels.keys():
                            found_cpu = True
                        else: 
                            cpu_levels[this_cpu] = []
                        chosen_level = this_cpu
                
                        l_assigned = False
                        # If the current start time is greater than the lowest end time existing in the level, add it to that level
                        for l, l_element in enumerate(cpu_levels[this_cpu]):
                            if int(start_time[i]) > l_element:
                                cpu_levels[this_cpu][l] = int(strings[3][1:])
                                y_list.append(l)
                                chosen_level += str(l)
                                l_assigned = True
                                break

                        # ...otherwise, add the record to and create a new level 
                        if(l_assigned == False):
                            cpu_levels[this_cpu].append(int(strings[3][1:]))
                            y_list.append(len(cpu_levels[this_cpu]) - 1)
                            chosen_level += str(len(cpu_levels[this_cpu]) - 1)

                        add_record( records, int(func[i]), int(start_time[i]), int( strings[3][1:]), chosen_level)
                        del func[i]
                        del start_time[i]
                        break
    os.system("rm temp.out")
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
taskID_list = []
start_list = []
end_list = []
delta_list = []
y_list = []
title_list = []
id_scheme = {0x00: '',
             0x20: 'tx', 0x40: 'rx', 0x60: 'ax rx', 0x80: 'ax tx',
             0x08: ' spi', 0x10: ' dirq', 0x18: ' irq',
             0x01: ' on', 0x02: ' off', 0x03: ' config', 0x04: ' update control', 
             0x05: ' activate',0x06: ' rm'}
# Parse information from records for the graph
for r, r_element in enumerate(records):
    for e, e_element in enumerate(records[r].record_list_end):
        msg_title = "other"
        taskID_list.append(records[r].id)
        start_list.append(records[r].record_list_start[e] * 4)

        if (int(records[r].id) & 0xE0) in id_scheme:
            msg_title = id_scheme.get(int(records[r].id) & 0xE0)
        if (int(records[r].id) & 0x18) in id_scheme:
            msg_title += id_scheme.get(int(records[r].id) & 0x18)
        if (int(records[r].id) & 0x07) in id_scheme:
            msg_title += id_scheme.get(int(records[r].id) & 0x07)
        
        title_list.append(msg_title)
        end_list.append(records[r].record_list_end[e] * 4)
        delta_list.append(records[r].record_list_end[e]-records[r].record_list_start[e])
        y_list.append(records[r].record_list_level[e])

# Dictionary of all elements that need to be shown on graph  
df_dict = { 
           'Id': taskID_list,
           'Title': title_list,
           'Start': start_list,
           'Finish': end_list,
           'Delta': delta_list,
           'YAxis': y_list,
          }
df = pd.DataFrame(df_dict)

# Details for the graph
color_map = {'Timestamps': 'black'}
fig = px.timeline(df, x_start="Start", x_end="Finish", y = "YAxis", color = "Title", color_discrete_map = color_map, hover_data = {'Id':True, 'Start': True, 'Finish':True, 'YAxis': False}, category_orders = {'Id': df['Id'].unique()}, template = "plotly_dark")
fig.layout.xaxis.type = 'linear'
for d in fig.data:
    filt = df['Title'] == d.name
    d.x = df[filt]['Delta'].tolist()

# Adding timestamps and their annotations
for t_element in timestamps:
    ts_title = 'other'
    if (int(int(timestamps.get(t_element)) & 0xE0)) in id_scheme:
        ts_title = id_scheme.get(int(int(timestamps.get(t_element)) & 0xE0))
    if (int(int(timestamps.get(t_element)) & 0x18)) in id_scheme:
        ts_title += id_scheme.get(int(int(timestamps.get(t_element)) & 0x18))
    if (int(int(timestamps.get(t_element)) & 0x07)) in id_scheme:
        ts_title += id_scheme.get(int(int(timestamps.get(t_element)) & 0x07))
    fig.add_vline(x=t_element, line_width=3, line_color="gray", annotation_text = str(round(t_element,2)) + '<br>' + ts_title, line_dash = 'dash')

# Axis Title, sort alphabetically, show legend, etc. 
fig.update_layout(yaxis_title="Task ID")
fig.update_layout(xaxis_title="Time (uSecs)")
fig.update_layout(xaxis = dict(dtick = 10))
fig.update_layout(title="Thread Timeline Per Task")
fig.update(layout_coloraxis_showscale=False)
fig.update_traces(showlegend = True)

# Write to html
fig.write_html("msg_timeline.html")
