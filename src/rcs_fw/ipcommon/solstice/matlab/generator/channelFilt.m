function [r,delay] = channelFilt(s,params)
%CHANFILT simulates the channel filter in VEX
%the coefficients are calculated based on Paolo's Tx Criteria
%INPUTS
%s= complex input vector
%params.rat = 'NR' or 'LTE' or 'NBIOT'
%params.bw = bandwidth in Hz
%params.scs = subcarrier spacing in Hz (NR only)
%params.fr = 1 for fr1, 2 for fr2-1, 22 for fr2-2 (NR only)
%params.dir = 'UL' or 'DL' (LTE only)
%params.bstype = 'macro' or 'mmimo' (default)
%params.loop = 1 to wrap from start to end, 0 for no wrap (default)
%params.fftSize = indicates the fftSize to use for NBIOT only
%OUTPUTS
%r = complex output vector
%delay = the delay introduced by the filter in samples
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
%get numerology to determine occupied BW
if(strcmp(params.rat,'NR'))
    %design parameters
    ripple=0.1; %pass-band ripple in dB
    reject=30; %stop band rejection in positive
    [params.fftSize,subCarriers,~]=numerologyNR(params.bw, params.scs, params.fr);
    obw=subCarriers*params.scs;
    guard=params.bw-obw;
    Fs=params.fftSize*params.scs;
    if(isfield(params,'bstype') && strcmp(params.bstype,'macro'))
        guard_ratio=0.5+0.005*params.bw/guard;
    else
        guard_ratio=1; %defines how far the stop band is relative to the guard-band
    end
elseif(strcmp(params.rat,'LTE'))
    %design parameters
    ripple=(0.3-params.bw/100E6)*2; %pass-band ripple in dB
    reject=10+params.bw/1E6; %stop band rejection in positive
    guard_ratio=1.2-params.bw/100E6; %defines how far the stop band is relative to the guard-band
    [params.fftSize,subCarriers,~]=numerologyLTE(params.bw, params.dir);
    params.scs=15E3;
    obw=subCarriers*params.scs;
    guard=params.bw-obw;
    Fs=params.fftSize*params.scs;
elseif(strcmp(params.rat,'NBIOT'))
    %design parameters
    ripple=0.1; %pass-band ripple in dB
    reject=15; %stop band rejection in positive
    guard_ratio=8; %defines how far the stop band is relative to the guard-band
    subCarriers=12;
    params.scs=15E3;
    params.bw=200E3;
    obw=subCarriers*params.scs;
    guard=params.bw-obw;
    Fs=params.fftSize*params.scs;
else
    error('Channel filtering is not supported for this RAT');
end

d=designfilt('lowpassfir','PassbandFrequency',obw/2, ...
    'StopbandFrequency',(obw/2+guard*guard_ratio),'PassbandRipple',ripple, ...
    'StopbandAttenuation',reject,'DesignMethod','equiripple','SampleRate',Fs);

coeff=d.Coefficients;
delay=(length(coeff)-1)/2;
%apply filtering
if(isfield(params,'loop') && params.loop) %filter for looping
    s_ext=[s(end-ceil(delay)+1:end);s;s(1:ceil(delay))];
    s_ext=conv(coeff,s_ext);
    r=s_ext(1+ceil(delay)+floor(delay):end-2*ceil(delay));
    delay=delay-floor(delay);
else %filter normal mode
    r=conv(coeff,s);
end

end

