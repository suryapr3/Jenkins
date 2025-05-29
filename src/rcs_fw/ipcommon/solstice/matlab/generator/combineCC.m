function [waveform,smpRate,params,f]=combineCC(ccs,params,digBO,fcenter,rast,spacing)
%combineCC combines multiple component carriers into a signle CA waveform
%%%%%%% INPUTS %%%%%%%%%%%
%ccs = a matrix of component carriers with each column being a new carrier, for lower sample-rate carriers leave zeros after the waveform
%params.rat = 'NR' or 'LTE'
%params.bw = bandwidth in Hz
%params.scs = subcarrier spacing in Hz (NR only)
%params.fr = 1 for fr1, 2 for fr2-1, 22 for fr2-2 (NR only)
%params.dir = 'UL' or 'DL' (LTE only)
%params.loop = indicates if interpolation should be done assuming a looping
%digBO = digital backoff for the CA waveform
%%%%%%% OPTIONAL INPUTS %%%%%%%%%%%%%%%
%fcenter = a vector of center frequencies for each component forb non-contiguous CA, they should be in order from lowest to highest.  For contiguous CA pass an empty array []
%rast = indicate the channel raster (Hz) [100E3,60E3,15E3], must be 100E3 for LTE
%spacing = indicate reduced spacing for contiguous CA as a positive int
%%%%%%% OUTPUTS %%%%%%%%%%%
%waveform = vector of output waveform samples
%smpRate = sample rate of output waveform in Hz
%params = updated parameters with unique seeds per CC
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
%check number of inputs and set defaults
if(nargin<6)
    spacing=0;
    if(nargin<5)
        rast=100E3;
        if(nargin<4)
            fcenter=[];
        end
    end
end

%save fixed point to the end
if(isfield(params,'format'))
    finalFixed=params(1).format;
else
    finalFixed=0;
end
numCar=length(params);
for cc=1:1:numCar
    params(cc).format=0;
end

%extract numerology
subCarriers=zeros(numCar,1);
GB=zeros(numCar,1);
mu_not=0;
time_adj=zeros(numCar,1);
for cc=1:1:numCar
    if(strcmp(params(cc).rat,'NR'))
        [fftSize,subCarriers(cc),shortCP,longCP,symLCP,evmWindow,GB(cc)]=numerologyNR(params(cc).bw, params(cc).scs, params(cc).fr);
    elseif(strcmp(params(cc).rat,'LTE'))
        [fftSize,subCarriers(cc),shortCP,longCP,symLCP,evmWindow,GB(cc)]=numerologyLTE(params(cc).bw, params(cc).dir);
        params(cc).scs=15E3;
        rast=100E3;
        GB(cc)=params(cc).bw*0.1*0.5;
    else
        error('Channel filtering is not supported for this RAT');
    end
    mu_not=max(mu_not,log2(params(cc).scs/15E3));
    singleRates(cc)=fftSize*params(cc).scs;
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
    f=f-(fullspan/2-params(1).bw/2);
    smpRate=2^ceil(log2(fullspan*1.2/7.68E6))*7.68E6;
else %non-contiguous CA case
    fullspan=2*max(abs(fcenter(end)+params(end).bw/2),abs(fcenter(1)-params(1).bw/2));
    smpRate=2^ceil(log2(fullspan*1.2/7.68E6))*7.68E6;
    f=fcenter; %user defined center frequencies for each component
end

for cc=1:1:numCar
    %if no seed is selected, use default
    if(~isfield(params(cc),'seed') || isempty(params(cc).seed))
        params(cc).seed=cc-1;
    end
    %ensure all defaults are met
    if(strcmp(params(cc).rat,'NR'))
        paramsd = defaultParamsNR(params(cc));
    elseif(strcmp(params(cc).rat,'LTE'))
        paramsd = defaultParamsLTE(params(cc));
    end
    if(isfield(params,'activeSym'))
        scaling=sqrt(paramsd.numRBs*paramsd.scs*sum(paramsd.activeSym));
    else
        scaling=sqrt(paramsd.numRBs*paramsd.scs);
    end
    component=ccs(:,cc);
    singleRate=singleRates(cc);
    %determine appropriate interpolation
    [up,down]=rat(smpRate/singleRate);
    %interpolate
    if(params(cc).loop)
        M=128;
        component=[component(end-M+1:end);component;component(1:M)];
        component=resample(component,up,down,40,10);
        M=round(M*up/down);
        component=component(1+M:end-M); %remove ends
    else
        component=resample(component,up,down,40,10);
    end

    %shift in frequency
    n=[0:1:length(component)-1].';
    component=component.*exp(1j*2*pi*f(cc)/smpRate*n);
    %scale based on RBs
    component=component./rms(component).*scaling.*sqrt(down/up);

    %add to combine
    if(cc==1)
        waveform=component;
    else
        if(length(waveform)>length(component))
            component=[component;zeros(length(waveform)-length(component),1)];
        elseif(length(waveform)<length(component))
            waveform=[waveform;zeros(length(component)-length(waveform),1)];
        end
        waveform=waveform+component;
    end
end

%normalize
waveform=waveform./rms(waveform);
%scale to backoff relative to 1
waveform=waveform.*10.^(digBO/20); % !!! yelled at me to turn ^ to .^


%quantize to requresetd format
if(finalFixed~=0) %fixed point
    bits=round(finalFixed);
    I=fi(real(waveform),1,bits,bits-1);
    Q=fi(imag(waveform),1,bits,bits-1);
    waveform=double(I)+1j.*double(Q);
end
