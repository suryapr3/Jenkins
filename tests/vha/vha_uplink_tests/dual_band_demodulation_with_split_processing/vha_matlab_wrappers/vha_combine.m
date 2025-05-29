function [r0,r1] = vha_combine(s0,s1,cw0,cw1,config)
%VEXHW_COMBINE upconverts two baseband signals and combines them
%INPUTS
%s0=I+jQ complex input vector of first band cs16.15
%s1=I+jQ complex input vector of second band cs16.15
%cw0=complex CW tone from NCO for first band cs16.15
%cw1=complex CW tone from NCO for second band cs16.15
%config.vha_bypass=boolean vector [byp_band0,byp_band1]
%config.vha_conj=boolean vector [cw0_conj,cw1_conj]
%convfig.active_band=0->none active, 1->s0 active, 2->s1 active, 3-> both active
%OUTPUTS
%r0=real output vector of first stream cs16.15
%r1=real output vector of second stream cs16.15

%quantize
q0=fi(s0,1,16,15);
q1=fi(s1,1,16,15);

%ensure quantization for tones
cw0=fi(cw0,1,16,15);
cw1=fi(cw1,1,16,15);

%conjugation
if(config.vha_conj(1))
    cw0=conj(cw0);
end
if(config.vha_conj(2))
    cw1=conj(cw1);
end

%apply modulation
q0=q0.*cw0;
q1=q1.*cw1;

%dual-band combining
%round
q0=fi(q0,1,18,15);
q1=fi(q1,1,18,15);

%single/dual band mode select
if(config.active_band==3)
    %add bands together
    q0=q0+q1;
    q1=0;
elseif(config.active_band==1)
    q1=0;
elseif(config.active_band==2)
    q0=0;
else
    q0=0;
    q1=0;
end

%saturate
q0=fi(q0,1,16,15);
q1=fi(q1,1,16,15);

%process bypass modes and set output
if(config.vha_bypass(1))
    r0=fi(s0,1,16,15);
else
    r0=q0;
end
if(config.vha_bypass(2))
    r1=fi(s1,1,16,15);
else
    r1=q1;
end

end

