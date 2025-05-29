function [s,params]=loadWaveDTP(filename)
%This function loads a waveform from a binary
%%% INPUTS
%filename=name of file to load waveform from (*.bin)
%%% OUTPUTS
%s=complex vector containing waveform
%params = waveform parameters
%/*********************************************************************************************
%  *                                                                                         *
%  * INTEL CONFIDENTIAL                                                                      *
%  *                                                                                         *
%  * Copyright (C) 2023 Intel Corporation                                                    *
%  *                                                                                         *
%  * This software and the related documents ("Material") are  Intel copyrighted materials,  *
%  * and your use of them is governed by the express license under which they were provided  *
%  * to you ("License"). Unless the License provides otherwise, you may not use, modify,     *
%  * copy, publish, distribute, disclose or transmit this software or the related documents  *
%  * without Intel's prior written permission.                                               *
%  * This software and the related documents are provided as is, with no express or implied  *
%  * warranties, other than those that are expressly stated in the License.                  *
%  * No license under any patent, copyright, trade secret or other intellectual property     *
%  * right is granted to or conferred upon you by disclosure or delivery of the Materials,   *
%  * either expressly, by implication, inducement, estoppel or otherwise. Any license under  *
%  * such intellectual property rights must be express and approved by Intel in writing.     *
%  *                                                                                         *
%  ******************************************************************************************/

%bits is always 16 for DTP waveforms
bits=16;
precision='int16';

filename = strcat(filename{:});
%binary save
if(contains(filename,'.bin')) %bin file
    fid=fopen(filename,'r'); %open file for reading
    if(fid==-1) %failed to open file
        error('failed to open waveform file');
    end

    %load header data
    tmindex=fread(fid,1,'int8');
    switch tmindex
        case 1
            params.nrtm='NR-FR1-TM1.1';
        case 2
            params.nrtm='NR-FR1-TM2';
        case 3
            params.nrtm='NR-FR1-TM2a';
        case 4
            params.nrtm='NR-FR1-TM3.1';
        case 5
            params.nrtm='NR-FR1-TM3.1a';
        case 6
            params.nrtm='cw';
        otherwise
            error('Invalid TM waveform type');
    end
    if(fread(fid,1,'int8')==1)
        params.duplex='TDD';
    else %FDD
        params.duplex='FDD';
    end
    params.bw=fread(fid,1,'int8')*1E6; %bandwidth in MHz
    params.scs=fread(fid,1,'int8')*1E3; %subcarrier spacing in kHz
    params.cfrThresh=fread(fid,1,'int16')*2^-15; %CFR threshold 99.99% in linear absolute terms
    params.window=fread(fid,1,'int16'); 
    if(params.window==2^15-1)
        params.window=[];
    else
        params.window=params.window*2^-9;%windowing percent
    end
    params.numCar=fread(fid,1,'int8'); %number of component carriers
    for i=1:1:params.numCar
        params.fcenter(i)=fread(fid,1,'int32');
    end

%     %load BFF (only 65 length is allowed)
%     for i=1:1:65
%         bff(i)=fread(fid,1,'int32')*2^-31;
%     end

    %load data from file
    data=fread(fid,precision);

    %get I and Q
    I=data(1:length(data)/2);
    Q=data(length(data)/2+1:end);
    s=I+1j*Q;

    %if fixed point format do scaling
    s=s./2^(bits-1);
    %close file
    fclose(fid);
else
    error('bad filename extension');
end
