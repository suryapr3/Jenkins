function [r] = nco_pp(freq,Fs,Fclk,samples,delay)
%NCO Simulates the polyphase NCO by combining multiple NCOs with different
%starting phases
%INPUTS
%freq=desired frequency in Hz
%Fs=sampling rate (Hz), should be a multiple of the clock rate
%Fclk=clock rate (Hz), must be 983.04MHz or 1474.56MHz
%samples=the number of samples in the output vector
%OPTIONAL INPUTS
%=integer clock-cycle delay for time-alignment (default to 0)
%OUTPUTS
%r=complex valued CW tone cs16.15

%defaults
if(nargin<5)
    delay=0;
end

%get number of active polyphase paths
pp=Fs/Fclk;
if(mod(pp,1)~=0)
    error('The indicated sampling rate is not supported for the polyphase NCO');
end

fprintf("pp = %d\n", pp);

%calculate frequency control word and check if valid
if(freq>(Fs/2) || freq<0)
    error('The indicated modulation frequency cannot be generated');
end
incr=2^38*freq/(Fs/pp); %check this for fractional precision
rem=mod(incr,1);
if(~(rem==0))
    %try using dual-increment mode
    [num,den]=rat(rem,1E-4);
    if(num>255 || den>255)
        error('The indicated modulation frequency cannot be generated');
    else
        config.incr_val=[floor(incr),floor(incr)+1];
        config.incr_count=[den-num,num];
        %config.incr_val=[floor(incr),0];
        %config.incr_count=[1,0];
    end
else
    config.incr_val=[incr,0];
    config.incr_count=[1,0];
end

%only allow numbers of samples that are integer multiples of the polyphases
if(~(mod(samples,pp)==0))
    error('The total samples requested from the NCO is not an integer multiple of the polyphases');
end

%%generate tone
dphase=incr/pp; %could be fractional!
phase=[0:dphase:(pp-1)*dphase];
r=zeros(samples,1);
for p=1:1:pp
    config.init_val=round(phase(p));
    q=nco_mex(config,samples/pp+delay);
    r(p:pp:samples)=q(1+delay:end);
end
end
