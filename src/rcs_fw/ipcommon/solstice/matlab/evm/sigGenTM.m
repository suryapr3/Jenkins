function [waveform,config,info] = sigGenTM(params,window,seed,configOnly)
%Generates 5G NR waveforms using the Matlab 5G Toolbox
%%%%% INPUTS %%%%%
%params.nrtm = string containing NR-TM name
%params.bw = integer bandwidth in Hz
%params.scs = integer subcarrier spacing in Hz
%params.duplex = string duplexing mode ("TDD" or "FDD")
%window = percent of CP for windowing (max 50), or leave blank [] for automatic
%seed sets the cellID and random seed for data (set to a small positive integer)
%%%%% OPTIONAL INPUTS
%configOnly = boolean indicating if only the config parameters are needed (default is false)
%%%%% OUTPUTS %%%%%
%waveform = column vector of I+jQ samples
%
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
%% Generate TM waveform
% The channel bandwidth and subcarrier spacing combination have to be a valid
% pair from the associated FR bandwidth configuration table. The standard defines
% FR2 NR-TM for TDD only but this example also allows FDD waveforms to be created
% as well. PT-RS are specified for FR2 NR-TM but these are not present in the
% generated waveforms.
%

%% Release 15 NR-TM test models for FR1 and FR2
% fr1testmodels = hNRReferenceWaveformGenerator.FR1TestModels;
% fr2testmodels = hNRReferenceWaveformGenerator.FR2TestModels;
% allNRTM = [fr1testmodels fr2testmodels];

%   The RC identifier should be a char vector or string from the set of 
%   FR1 NR-TM  ('NR-FR1-TM1.1','NR-FR1-TM1.2','NR-FR1-TM2','NR-FR1-TM2a',
%               'NR-FR1-TM3.1','NR-FR1-TM3.1a','NR-FR1-TM3.2','NR-FR1-TM3.3')
%   FR2 NR-TM  ('NR-FR2-TM1.1','NR-FR2-TM2','NR-FR2-TM3.1')
%   FR1 DL FRC ('DL-FRC-FR1-QPSK','DL-FRC-FR1-64QAM',DL-FRC-FR1-256QAM')
%   FR2 DL FRC ('DL-FRC-FR2-QPSK','DL-FRC-FR2-16QAM',DL-FRC-FR2-64QAM')
%   FR1 UL FRC ('G-FR1-Ax-y', where x and y values come from TS 38.104 Annex A)
%   FR2 UL FRC ('G-FR2-Ax-y', where x and y values come from TS 38.104 Annex A)

%add the waveform generator path
%addpath('MatlabWaveGen');

% Create generator object for the above NR-TM
bw=horzcat(num2str(params.bw/1E6),'MHz');
scs=horzcat(num2str(params.scs/1E3),'kHz');
%addpath('../')
tmwavegen = hNRReferenceWaveformGenerator(params.nrtm,bw,scs,params.duplex);
%addpath('evm/')
tmwavegen = makeConfigWritable(tmwavegen);
%setup windowing
tmwavegen.Config.WindowingPercent = window; %set for automatic window control
tmwavegen.Config.NCellID=seed;
for i=1:1:length(tmwavegen.Config.PDSCH)
    tmwavegen.Config.PDSCH{i}.DataSource={'PN23',seed};
end
for i=1:1:length(tmwavegen.Config.PDSCH)
    tmwavegen.Config.PDCCH{1}.DataSource={'PN23',seed};
end

if(nargin<4 || ~configOnly)
    % Generate waveform
    [waveform,tmwaveinfo,resourcesinfo] = generateWaveform(tmwavegen,tmwavegen.Config.NumSubframes);
    info.numSlot=tmwaveinfo.Info.SlotsPerSubframe*tmwavegen.Config.NumSubframes;
    info.SampleRate=tmwaveinfo.Info.SampleRate;
else
    waveform=[];
    info=[];
end

%set config structure
config=tmwavegen.Config;
end