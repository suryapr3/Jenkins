% button pushed function: GenerateWaveformButton
function params = genButton(input_params)
    val = 0;
    try
        %get waveform parameters
        [params,ibw] = getWaveParams(input_params);

        %validate the center frequencies
        if(~isnumeric(params.fcenter) || isempty(params.fcenter))
            error('invalid CC center frequencies');
        end
        if(ibw>400E6)
            error('Integrated bandwidth must not exceed 400MHz');
        end
        if(sum((abs(params.fcenter)+params.bw/2)>200E6))
            error('CC edge frequency exceeds 200MHz from center');
        end
        if(params.numCar>length(params.fcenter))
            error('not enough center frequencies specified');
        end

        %get filename
        filename=input_params.filename;
        %get windowing parameters
        if(input_params.windowing)
            if(input_params.auto_length)
                params.window=[]; %automatic
            else
                params.window=input_params.windowing_le;
            end
        else
            params.window=0; %no windowing applied
        end
        %generate the waveform
        ccs=[];
        paramsca=[];
        for cc=1:1:params.numCar
            [waveform,config,info] = sigGenTM(params,params.window,cc);
            if(strcmp(input_params.duplex_mode,'TDD') && (isempty(params.window) || params.window~=0)) %slightly shift waveform to prevent end burst from windowing
                N=round(length(waveform)*(1-0.0321));
                N=find(waveform(N+1:end)~=0,1)+N;
                waveform=[waveform(N:end);waveform(1:N-1)];
            end
            if(input_params.channel_filter)
                waveform=channelFilt(waveform,params);
            end
            ccs=[ccs,waveform];
            params.numSlot=info.numSlot;
            paramsca=[paramsca,params];
        end
        %%%%%% ADJUSTMENT FOR TDD DUTY CYCLE %%%%%%%%%%%
        if(strcmp(input_params.duplex_mode,'TDD'))
            adjV=sqrt(0.742857142857143);
            adjdB=20*log10(adjV);
            duty_cycle='74.3%';
        else
            adjV=1;
            adjdB=0;
            duty_cycle='100%';
        end

        if(params.numCar>1)
            %combine CCs
            digBO=params.digBO;
            [waveform,smpRate,paramsca,params.fcenter]=combineCC(ccs,paramsca,digBO+adjdB,params.fcenter,60E3);
        else
            params.fcenter=[0];
            smpRate=info.SampleRate;
            waveform=waveform./rms(waveform).*adjV.*10^(params.digBO/20); %scale to desired level
        end

        %CFR application
        if(input_params.apply_CFR) % !!! broken
            %scale to optimal
            scale=(2^15-1)/max(abs(waveform))*10^(-1/20);
            waveformQ=round(waveform*scale);
            %waveformQ=round(waveform*2^15);
            peak_limit=round(params.cfrThresh*scale);
                % if(contains(input_params.specification,'Relative'))
                %     PAR=input_params.target_PAPR;
                %     peak_limit=round(rms(waveformQ)*10^(PAR/20)/adjV);
                % else
                %     abs_limit=10^(input_params.threshold_BFS/20);
                %     peak_limit=round(abs_limit*scale);
                % end
            if(max(abs(waveformQ))>peak_limit) %only run if clipping occurs
                waveformQ=apply_cfr(waveformQ,peak_limit,params.numCar,params.bw,smpRate,params.fcenter,params.loop); %this function transposes the waveform
                %waveform=waveformQ./2^15; %scale back
                waveform=waveformQ/scale;
            end
        end
        %resample to 1966.08MHz
        up=1966.08E6/smpRate;
        waveform=interpolate(waveform,up,params.loop);
        smpRate=1966.08E6;

        %set level and quantize to 16 bits
        [fftSize,subCarriers,shortCP,longCP,symLCP,evmWindow,minGB]=numerologyNR(params.bw,params.scs,1);
        fullRB=subCarriers/12;
        if(contains(params.nrtm,'2') && input_params.level_scaled_to_allocated_RBs)
            scaleRB=sqrt((1+2/14)/fullRB); %1RB plus some addition for the PDCCH
        else
            scaleRB=1;
        end
        waveform=waveform./rms(waveform).*adjV.*10^(input_params.signal_level/20).*scaleRB;
        I=max(-1,min(1-2^-15,round(real(waveform)*2^15)*2^-15));
        Q=max(-1,min(1-2^-15,round(imag(waveform)*2^15)*2^-15));
        s=I+1j*Q;
        %s=double(fi(waveform,1,16,15));
        level=round(20*log10(rms(s)./adjV),2);

        %save to file
        %workspace=app.WorkspaceFolderEditField.Value; 
        workspace = "";
        filepath=horzcat(workspace,'\',filename);
        saveWaveDTP(filepath,s,params);
    catch err
       disp(['error: ',err.message]);
       val = 1;

       return;
    end
    % 
     %spectrum plot
     df=smpRate/length(s);
     fvec=-smpRate/2:df:smpRate/2-df;
     pspec=20*log10(abs(fftshift(fft(s)/sqrt(length(s)))));
     params.spectrum_x = fvec/1E6;
     params.spectrum_x = params.spectrum_x(1:100:end);
     params.spectrum_y = transpose(pspec);
     params.spectrum_y = params.spectrum_y(1:100:end);
     params.spectrum_xlim = [-smpRate/2,smpRate/2]./1E6;
     params.spectrum_ylim = [-100,max(0,ceil(max(pspec)/10)*10)];
     
     %time plot
     dt=1/smpRate;
     time=0:dt:dt*(length(s)-1);
     env=abs(s);
     params.time_x = time/1E-3;
     params.time_x = params.time_x(1:100:end);
     params.time_y = transpose(env);
     params.time_y = params.time_y(1:100:end);
     %CCDF
     dist=sort(abs(s));
     totalSamples=length(dist);
        
     ind999=totalSamples-round(totalSamples*0.001);
     ind9999=totalSamples-round(totalSamples*0.0001);
     
     papr100=20*log10(dist(end)/rms(dist)*adjV);
     papr999=20*log10(dist(ind999)/rms(dist(1:ind999))*adjV);
     papr9999=20*log10(dist(ind9999)/rms(dist(1:ind9999))*adjV);
     params.papr100 = papr100;
     params.papr999 = papr999;
     params.papr9999 = papr9999;
     params.dutyCycle = duty_cycle;
     params.level = level;
end

function [params,ibw] = getWaveParams(input_params)
    % default fixed parameters
    params.rat='NR';
    params.fr=1;
    params.dir='DL';

    % duplex mode
    params.dm = input_params.duplex_mode;
    params.duplex = input_params.duplex_mode;

    % waveform type
    if(input_params.NRWF == "gen_NRWf_TM11_rb")
        params.nrtm='NR-FR1-TM1.1';
    elseif(input_params.NRWF == "gen_NRWf_TM2_rb")
        params.nrtm='NR-FR1-TM2';
    elseif(input_params.NRWF == "gen_NRWf_TM2a_rb")
        params.nrtm='NR-FR1-TM2a';
    elseif(input_params.NRWF == "gen_NRWf_TM31_rb")
        params.nrtm='NR-FR1-TM3.1';
    elseif(input_params.NRWF == "gen_NRWf_TM31a_rb")
        params.nrtm='NR-FR1-TM3.1a';
    end

    % cfr threshold
    rmsLevel=input_params.signal_level;
    if(input_params.apply_CFR)
        if(input_params.specification == "Relative")
            clipLevel=input_params.target_PAPR;
            params.cfrThresh=10^((rmsLevel+clipLevel)/20);
        else
            params.cfrThresh=10^(input_params.threshold_BFS/20);
        end
    else
        params.cfrThresh=10^((rmsLevel+9.675)/20); %statistics for a waveform with no CFR
    end

    % bandwidth
    if(input_params.BW == "gen_BW_20_rb") %20MHz
        params.bw=20E6;
    elseif(input_params.BW == "gen_BW_50_rb")%50MHz
        params.bw=50E6;
    elseif(input_params.BW == "gen_BW_100_rb")%100MHz
        params.bw=100E6;
    end

    % subcarrier spacing
    if(input_params.SCS == "gen_SCS_15_rb") %15kHz
        params.scs=15E3;
    elseif(input_params.SCS == "gen_SCS_30_rb")%30kHz
        params.scs=30E3;
    elseif(input_params.SCS == "gen_SCS_60_rb")%60kHz
        params.scs=60E3;
    end

    %looping for channel filter
    if(input_params.filter_style == "Loop")
        params.loop=1;
    else
        params.loop=0;
    end

    % digital level
    if(input_params.level_scaled_to_allocated_RBs)
        [fftSize,subCarriers,shortCP,longCP,symLCP,evmWindow,minGB]=numerologyNR(params.bw, params.scs, params.fr);
        if(contains(params.nrtm,'TM2'))
            numSubc=12; %may need adjustment for PDCCH
        else
            numSubc=subCarriers;
        end
        params.digBO=input_params.full_RB_level+10*log10(numSubc/subCarriers);
    else
        params.digBO = input_params.signal_level;
    end

    %number of component carriers
    if(input_params.NoC == "gen_NoC_1_rb")
        params.numCar=1;
    elseif(input_params.NoC == "gen_NoC_2_rb")
        params.numCar=2;
    elseif(input_params.NoC == "gen_NoC_3_rb")
        params.numCar=3;
    elseif(input_params.NoC == "gen_NoC_4_rb")
        params.numCar=4;
    elseif(input_params.NoC == "gen_NoC_5_rb")
        params.numCar=5;
    elseif(input_params.NoC == "gen_NoC_6_rb")
        params.numCar=6;
    elseif(input_params.NoC == "gen_NoC_7_rb")
        params.numCar=7;
    elseif(input_params.NoC == "gen_NoC_8_rb")
        params.numCar=8;
    end

    % CA configuration
    if(params.numCar==1)
        params.fcenter=[0];
    else
        if(input_params.contiguous)

            paramsca=[];
            for cc=1:1:params.numCar
                paramsca=[paramsca,params];
            end
            [params.fcenter,~]=getFcenter(paramsca,60E3,0);
        else
            params.fcenter=sort(str2num(input_params.center_freq));
        end
    end
    ibw=max(params.fcenter)-min(params.fcenter)+params.bw;
end

function r = interpolate(s,n,loop)
    %use these filters to match CFR
    N=[100,32,22,16,10,10];
    w1 = firhalfband(N(1),0.8138/2)*2;
    w2 = firhalfband(N(2),0.8138/4)*2;
    w3 = firhalfband(N(3),0.8138/8)*2;
    w4 = firhalfband(N(4),0.8138/16)*2;
    w5 = firhalfband(N(5),0.8138/32)*2;
    w6 = firhalfband(N(6),0.8138/64)*2;

    %extend for looping
    if(loop)
        O=length(s)*n;
        M=512;
        r=[s(end-M+1:end);s;s(1:M)];
    else
        r=s;
    end
    %interpolate
    for i=1:log2(n)
        switch(i)
            case 6
                coeff=w6;
            case 5
                coeff=w5;
            case 4
                coeff=w4;
            case 3
                coeff=w3;
            case 2
                coeff=w2;
            case 1
                coeff=w1;
        end
        r=conv(coeff,upsample(r,2,0));
    end

    %trim
    if(loop)
        M=(length(r)-O)/2;
        r=r(M+1:end-M);
    end
end