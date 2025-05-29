function [r] = vha_split(s,cw,config)
%VEXHW_SPLIT splits into two bands and downconverts each to baseband
%INPUTS
%s=I+jQ complex input vector cs16.15
%config.vha_bypass=boolean 1=bypass, 0=no bypass
%config.vha_conj=boolean indicating if cw should be conjugated before multiplication with IQ
%OUTPUTS
%r=complex output vector cs16.15

%ensure proper input format
q=fi(s,1,16,15);
cw=fi(cw,1,16,15);

%conjugation
if(config.vha_conj)
    cw=conj(cw);
end

%apply modulation
q=q.*cw;

if(config.vha_bypass)
    r=fi(s,1,16,15);
else
    %round and saturate
    r=fi(q,1,16,15,'RoundingMethod','Nearest','OverflowAction','Saturate');
end
end
