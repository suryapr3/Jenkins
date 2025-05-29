function [ccs]=splitCC(waveform,params,smpRate,fcenter,rast,spacing)
%generate a multi-component carrier waveform
%%%%%%% INPUTS %%%%%%%%%%%
%waveform = vector of IQ samples
%params.rat = 'NR' or 'LTE'
%params.bw = bandwidth in Hz
%params.scs = subcarrier spacing in Hz (NR only)
%params.fr = 1 for fr1, 2 for fr2-1, 22 for fr2-2 (NR only)
%params.dir = 'UL' or 'DL' (LTE only)
%smpRate = sample rate of input waveform (Hz)
%%OPTIONAL INPUTS %%%%%%%
%fcenter = a vector of center frequencies for each component for
%non-contiguous CA, they should be in order from lowest to highest.  For
%contiguous CA pass an empty array []
%rast = indicate the channel raster (Hz) [100E3,60E3,15E3], must be 100E3 for LTE
%spacing = indicate reduced spacing for contiguous CA as a positive int
%%%% OUTPUTS %%%%
%ccs = a matrix of component carriers with each column being a new carrier,
%for lower sample-rate carriers zeros are placed after the waveform
%powers = a vector of power levels for each CC (dBm)
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
%set defaults
if(nargin<6)
    spacing=0;
    if(nargin<5)
        rast=100E3;
        if(nargin<4)
            fcenter=[];
        end
    end
end

%extract numerology
numCar=length(params);
subCarriers=zeros(numCar,1);
GB=zeros(numCar,1);
singleRate=zeros(numCar,1);
mu_not=0;
for cc=1:1:numCar
    if(strcmp(params(cc).rat,'NR'))
        [fftSize,subCarriers(cc),shortCP,longCP,symLCP,evmWindow,GB(cc)]=numerologyNR(params(cc).bw, params(cc).scs, params(cc).fr);
    elseif(strcmp(params(cc).rat,'LTE'))
        [fftSize,subCarriers(cc),shortCP,longCP,symLCP,evmWindow,GB(cc)]=numerologyLTE(params(cc).bw, params(cc).dir);
        params(cc).scs=15E3;
        rast=100E3;
    else
        error('Channel filtering is not supported for this RAT');
    end
    singleRate(cc)=fftSize*params(cc).scs;
    mu_not=max(mu_not,log2(params(cc).scs/15E3));
end

%define spacing
if(isempty(fcenter))%contiguous CA case
    f=zeros(numCar,1);
    for cc=1:1:numCar-1
        %separation between component carriers in MHz
        if(rast==60E3)
            stepSize=60E3*2^(mu_not-2); %using 60kHz channel raster
        elseif(rast==15E3)
            stepSize=15E3*2^(mu_not); %using 15kHz channel raster
        elseif(rast==100E3)
            stepSize=300E3; %using 100kHz channel raster
        end
        sep=floor((params(cc).bw+params(cc+1).bw-2*abs(GB(cc)-GB(cc+1)))./(2*stepSize))*stepSize-stepSize*spacing;
        f(cc+1)=sep+f(cc);
    end
    %center the spectrum
    fullspan=f(end)+params(end).bw/2+params(1).bw/2;
    f=f-fullspan/2+params(1).bw/2;
    %f=f-floor((fullspan/2-params(1).bw/2)/stepSize)*stepSize;
else %non-contiguous CA case
    fullspan=2*max(abs(fcenter(end)+params(end).bw/2),abs(fcenter(1)-params(1).bw/2));
    f=fcenter; %user defined center frequencies for each component
end

maxLength=ceil(length(waveform)/smpRate*max(singleRate));
ccs=zeros(maxLength,numCar);
n=[0:1:length(waveform)-1].';
for cc=1:1:numCar
    %shift in frequency
    component=waveform.*exp(-1j*2*pi*f(cc)/smpRate*n);
    %determine appropriate interpolation
    [up,down]=rat(singleRate(cc)/smpRate);
    %decimate
    component=resample(component,up,down,40,10);

    %set output
    ccs(1:length(component),cc)=component;
end