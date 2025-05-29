function [fcenter,smpRate]=getFcenter(params,rast,spacing)
%getFcenter finds the proper center spacing for contiguous CA scenarios
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
if(nargin<3)
    spacing=0;
    if(nargin<2)
        rast=100E3;
    end
end

numCar=length(params);

%extract numerology
subCarriers=zeros(numCar,1);
GB=zeros(numCar,1);
signelRates=zeros(numCar,1);
mu_not=0;
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
%contiguous CA case
f=zeros(1,numCar);
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
fcenter=f-(fullspan/2-params(1).bw/2);
smpRate=2^ceil(log2(fullspan*1.2/7.68E6))*7.68E6;


