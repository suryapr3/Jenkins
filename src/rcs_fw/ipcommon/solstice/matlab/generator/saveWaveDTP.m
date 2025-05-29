function []=saveWaveDTP(filename,s,params)
%This function saves waveform data to a binary or csv file
%%% INPUTS
%filename=name of file to save waveform in (*.bin)
%s=complex array containing waveform
%params=waveform parameters
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

%rotate if necessary
[r,c]=size(s);
if(c>r)
    s=s.';
end

%saturate and round
%round to nearest integer
s=round(s.*2^(bits-1));
I=real(s);
Q=imag(s);
%saturate clipping
maxLevel=2^(bits-1);
I(find(I>=maxLevel))=maxLevel-1;
Q(find(Q>=maxLevel))=maxLevel-1;
I(find(I<-maxLevel))=-maxLevel;
Q(find(Q<-maxLevel))=-maxLevel;

%binary or csv save
filename = strjoin(filename);
filename = strrep(filename, ' ', '');
filename = strrep(filename, '\', '/');
filename = strrep(filename, '/', '');
if(contains(filename(end),'.bin')) %bin file % !!! changed to contains
    fid=fopen(filename,'w'); %open file for writing
    if(fid==-1) %failed to open file
        error('failed to open waveform file');
    end
    
    %put I and Q into a vector
    szI=size(I);
    szQ=size(Q);
    if(szI(1)<szI(2))
        %flip row vector
        I=I.';
    end
    if(szQ(1)<szQ(2))
        %flip row vector
        Q=Q.';
    end
    data=[I;Q];

    %save header data to file
    if(contains(params.nrtm,'TM1.1'))
        fwrite(fid,1,'int8');
    elseif(contains(params.nrtm,'TM2a'))
        fwrite(fid,3,'int8');
    elseif(contains(params.nrtm,'TM2'))
        fwrite(fid,2,'int8');
    elseif(contains(params.nrtm,'TM3.1a'))
        fwrite(fid,5,'int8');
    elseif(contains(params.nrtm,'TM3.1'))
        fwrite(fid,4,'int8');
    elseif(contains(params.nrtm,'cw'))
        fwrite(fid,6,'int8');
    else
        error('Invalid TM waveform type');
    end
    if(contains(params.duplex,'TDD'))
        fwrite(fid,1,'int8');
    else %FDD
        fwrite(fid,2,'int8');
    end
    fwrite(fid,params.bw/1E6,'int8'); %bandwidth in MHz
    fwrite(fid,params.scs/1E3,'int8'); %subcarrier spacing in kHz
    fwrite(fid,round(params.cfrThresh*2^15),'int16'); %CFR threshold 99.99% in linear absolute terms
    if(isempty(params.window))
        fwrite(fid,2^15-1,'int16');
    else
        fwrite(fid,round(params.window*2^9),'int16'); %windowing percent
    end
    fwrite(fid,params.numCar,'int8'); %number of component carriers
    for i=1:1:params.numCar
        fwrite(fid,params.fcenter(i),'int32');
    end

%     %save BFF (only 65 length is allowed)
%     for i=1:1:65
%         fwrite(fid,bff(i)*2^31,'int32');
%     end

    %save IQ data to file
    fwrite(fid,data,precision);
    
    %close file
    fclose(fid);
else
    error('bad filename extension');
end
