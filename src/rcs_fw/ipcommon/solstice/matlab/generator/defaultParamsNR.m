function [params] = defaultParamsNR(params)
%DEFAULTPARAMS takes a set of waveform parameters and generates the
%necessary default parameters that were not specified
%if no seed is selected, use default
%%%%_INPUTS_%%%%
%params.rat = 'NR'
%params.scs = subcarrier spacing in Hz
%params.bw = bandwidth in Hz
%params.fr = 1 for fr1, 2 for fr2-1, 22 for fr2-2
%params.numSlot = number of slots in waveform (14 symbols per slot)
%%%% OPTIONAL INPUTS %%%%%%%%%%%%%%%%%
%params.phy = 'DFTSOFDM' or 'CPOFDM'
%params.numRBs = number of resource blocks allocated
%params.rbOff = resource block offset
%params.iqMod = constellation size 2,4,16,64,256,1024
%params.payload = payload size for coding
%params.codeRate = coding rate 0<R<=1 (default 1)
%params.seed = seed for random number generation (int)
%params.config = DMRS params.configuration type 1 or 2
%params.cdm = CDM group 0, 1, or 2 (defaults to 0)
%params.map = DMRS params.mapping type 1=B, 2=A2, 3=A3
%params.add = DMRS params.additional symbols 0-3
%params.dbl = DMRS double symbol 1, single symbol 0
%params.cellID = indicates the cell ID for this cc
%params.txwola = boolean indicating that Tx WOLA is used (default to 1 if not indicated)
%params.rxwinlen = Rx side window length (0 for none), defaults to EVM window length
%params.preemph = pre-emphasis vector with length equal to full subcarriers
%params.postemph = post-emphasis vector with length equal to full subcarriers
%params.activeSym = a vector of boolean values indicating which symbols are allocated (1) or blank (0)
%params.rbmask = a mask for resource blocks included in the EVM analysis 1->inluded, 0-> excluded
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

%demand that the minimum set of non-optional parameters are specified
if(~isfield(params,'bw') || ~isfield(params,'scs') || ~isfield(params,'fr') || ~isfield(params,'numSlot'))
    error('The minimum set of non-optional parameters has not been specified!');
end

%set RAT to NR
if(isfield(params,'rat') && ~strcmp(params.rat,'NR'))
    error('A non-NR parameter set was passed in');
end
params.rat='NR';

%get fft size and total subcarriers
[fftSize,subcarriersPerCC,shortCP,longCP,symLCP,evmWindow]=numerologyNR(params.bw,params.scs,params.fr);

%%%%%%%%% SET DEFAULTS %%%%%%%%%%%%%
if(~isfield(params,'phy') || strcmp(params.phy,'DFTSOFDM'))
    params.phy='CPOFDM'; %CP-OFDM
end
if(~isfield(params,'numRBs'))
    params.numRBs=subcarriersPerCC/12; %max RBs
end
if(~isfield(params,'rbOff'))
    params.rbOff=0;
end
if(~isfield(params,'iqMod'))
    params.iqMod=4;
end

if(~isfield(params,'codeRate'))
    params.codeRate=1; %transportation block size doesn't matter for this setting
end

if(~isfield(params,'seed') && ~isfield(params,'cellID'))
    params.seed=0;
elseif(~isfield(params,'seed'))
    params.seed=params.cellID+1; %ensure seed is different for different cell IDs
end

%seed random number generation
rng(params.seed)

if(~isfield(params,'cellID'))
    params.cellID=3*(ceil(rand()*168)-1) + ceil(rand()*3)-1; %cell ID randomized
end

%set default DMRS config
if(~isfield(params,'config'))
    params.config=1;
end
if(~isfield(params,'cdm'))
    params.cdm=0;
end
if(~isfield(params,'map'))
    params.map=2;
end
if(~isfield(params,'add'))
    params.add=0;
end
if(~isfield(params,'dbl'))
    params.dbl=0;
end

%blank symbols
if(~isfield(params,'activeSym'))
    params.activeSym=ones(params.numSlot*14,1); %all active by default
end

%RB masking
if(~isfield(params,'rbmask'))
    params.rbmask=ones(subcarriersPerCC/12,1);
end

%pre-emphasis
if(~isfield(params,'preemph') || length(params.preemph)~=subcarriersPerCC)
    params.preemph=ones(subcarriersPerCC,1);
end
[row,col]=size(params.preemph);
if(col>row)
    params.preemph=params.preemph.';
end

%post-emphasis
if(~isfield(params,'postemph') || length(params.postemph)~=subcarriersPerCC)
    params.postemph=ones(subcarriersPerCC,1);
end
[row,col]=size(params.postemph);
if(col>row)
    params.postemph=params.postemph.';
end

%windowing
if(~isfield(params,'txwola'))
    params.txwola=1;
end
if(~isfield(params,'rxwinlen'))
    params.rxwinlen=evmWindow;
end

%digital backoff
if(~isfield(params,'digBO'))
    params.digBO=-20;
end

%format/number of bits
if(~isfield(params,'format'))
    params.format=0; %floating point
end

end

