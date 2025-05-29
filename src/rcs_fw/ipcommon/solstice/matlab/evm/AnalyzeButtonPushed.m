% Button pushed function: AnalyzeButton
        function results = AnalyzeButtonPushed(input_params)
            %capture the waveform
            if(strcmp(input_params.source, 'Waveform File'))
                try
                    %get filename and load waveform
                    filename=input_params.filename;
                    %workspace=app.WorkspaceFolderEditFsigGenTMield.Value;
                    workspace = ".";
                    filepath=horzcat(workspace,'\',filename);
                    [waveform,params]=loadWaveDTP(filepath);
                    samp_rate=1966.08E6;
                    if(strcmp(input_params.duplex, 'TDD')) % why would it use values from a diff page? 
                        num_samp=ceil(0.020003108723958*samp_rate);
                    else
                        num_samp=ceil(0.010001554361979*samp_rate);
                    end
                    num_samp=min(length(waveform),num_samp); %don't exceed waveform
                    waveform=waveform(1:num_samp); %prevent EVM from going beyond waveform bounds
                    %run EVM analysis and display results
                    results = evm_analysis(params,waveform,samp_rate, input_params);
                catch err
                    disp(['error: ',err.message]);
                    fprintf('file: %s\nline: %d\n%s: %s\n',err.stack(1).file,err.stack(1).line,err.identifier,err.message);
                    return;
                end
            else %from test equipment
                % data=guidata(app.DoubletopPeakUIFigure); %read 
                if(isfield(data,'t') && contains(data.t.Running,'on'))
                    data.evm_meas=1; %schedule spectrum measurement 
                else
                    %app.analysis.Text='failed to analyze: waveform playback has not started';
                end
            end
        end
 
        function results = evm_analysis(params,waveform,samp_rate, input_params)
            try %try to measure EVM on waveform
                %generate the configuration parameters
                params.rat='NR';
                params.fr=1;
                [~,config,info] = sigGenTM(params,params.window,1,0);
                configca=config;
                params.numSlot=info.numSlot;
                paramsca=params;
                baseRate=info.SampleRate;
                for cc=2:1:params.numCar
                    [~,config,~] = sigGenTM(params,params.window,cc,1);
                    configca=[configca,config];
                    params.numSlot=info.numSlot;
                    paramsca=[paramsca,params];
                end
                %resample
                if(params.numCar>1)
                    ccs=splitCC(waveform,paramsca,samp_rate,params.fcenter,60E3);
                else
                    down=samp_rate/baseRate;
                    ccs=decimate(app,waveform,down);
                end

                %get EVM
                cfg = struct();
                cfg.Evm3GPP = true;
                cfg.TargetRNTIs = []; %default
                cfg.PlotEVM = 0;
                cfg.DisplayEVM = 0;
                cfg.Label = config.Label;
                cfg.TimeSyncEnable = true;
                cfg.UseWholeGrid = true; %use entire waveform for timing estimate
                cfg.CorrectCoarseFO = false;
                cfg.IQImbalance = false;
                if(strcmp(input_params.source,'Test Equipment') && input_params.correction)
                    cfg.CorrectFineFO = true;
                else
                    cfg.CorrectFineFO = false;
                end

                % Compute and display EVM measurements
                EVM_RMS=zeros(params.numCar,1);
                EVM_Peak=zeros(params.numCar,1);
                EVM_Worst_RB=zeros(params.numCar,1);
                EVM_Worst_Sy=zeros(params.numCar,1);
                EVM_Symbol=zeros(params.numCar,info.numSlot*14);
                flatness=zeros(params.numCar,1);
                allRB=0;
                RBindex=[];
                for cc=1:1:params.numCar
                    [evmInfo,eqSym,refSym,flat] = hNRDownlinkEVM(configca(cc),ccs(:,cc),cfg);
                    if(input_params.constellation) %plot constellation
                        fig=uifigure("Icon","intel_square_logo.png","Name","Constellation Diagram ");
                        ax = uiaxes(fig,'Position',[10 10 550 400]);
                        plot(ax,eqSym{1,1},'.'); 
                        hold(ax,'on');
                        plot(ax,refSym{1,1},'+');
                        hold(ax,"off");
                        xtreme=max([abs(ax.XLim),abs(ax.YLim)]);
                        ax.XLim=[-xtreme,xtreme];
                        ax.YLim=[-xtreme,xtreme];
                        title(ax,['CC',num2str(cc),' PDSCH Equalized Symbols Constellation']);
                    end
                    flatness(cc)=flat;
                    EVM_RMS(cc)=evmInfo.PDSCH.OverallEVM.RMS*100;
                    EVM_Peak(cc)=evmInfo.PDSCH.OverallEVM.Peak*100;
                    NRB=floor(length(evmInfo.PDSCH.SubcarrierRMS)/12);
                    n=1;
                    for rb=1:1:NRB
                        EVM_RB_RMS(rb+allRB)=rms(evmInfo.PDSCH.SubcarrierRMS(n:n+11));
                        EVM_RB_Peak(rb+allRB)=max(evmInfo.PDSCH.SubcarrierPeak(n:n+11));
                        n=n+12;
                    end
                    EVM_Worst_RB(cc)=max(EVM_RB_RMS(allRB+1:allRB+NRB));
                    EVM_Worst_Sy(cc)=max(evmInfo.PDSCH.SymbolRMS);
                    EVM_Symbol(cc,1:length(evmInfo.PDSCH.SymbolRMS))=evmInfo.PDSCH.SymbolRMS;
                    RBindex=[RBindex,[1:1:NRB]+allRB];
                    allRB=allRB+NRB;
                end

                %get spec limits
                if(contains(params.nrtm,'TM1')) %QPSK
                    %EVM_limit=-15.14;
                    EVM_limit=17.5;
                elseif(contains(params.nrtm,'a')) %256QAM
                    %EVM_limit=-29.12;
                    EVM_limit=3.5;
                elseif(contains(params.nrtm,'b')) %1024QAM
                    %EVM_limit=-32.04;
                    EVM_limit=2.5;
                else %64QAM
                    %EVM_limit=-21.94;
                    EVM_limit=8;
                end

                %percent or dB
                if(strcmp(input_params.units,'dB'))
                    EVM_Worst_RB=20*log10(EVM_Worst_RB/100);
                    EVM_Worst_Sy=20*log10(EVM_Worst_Sy/100);
                    EVM_RMS=20*log10(EVM_RMS/100);
                    EVM_Peak=20*log10(EVM_Peak/100);
                    EVM_RB_RMS=20*log10(EVM_RB_RMS/100);
                    EVM_RB_Peak=20*log10(EVM_RB_Peak/100);
                    EVM_Symbol=20*log10(EVM_Symbol/100);
                    EVM_limit=20*log10(EVM_limit/100);
                    names={'Overall RMS (dB)','Overall Peak (dB)','Worst RB RMS (dB)','Worst Symbol RMS (dB)','Equalizer Flatness (dB)'};
                else
                    names={'Overall RMS (%)','Overall Peak (%)','Worst RB RMS (%)','Worst Symbol RMS (%)','Equalizer Flatness (dB)'};
                end

                %setup parameters table
                evm_table=cell(5,params.numCar+1);
                evm_table(:,1)=names;
                column_names=cell(1,params.numCar+1);
                column_names(1,1)={'EVM'};
                for cc=1:1:params.numCar
                    results.(horzcat('CC',num2str(cc), '_tableInfo')) = {num2str(EVM_RMS(cc),3), num2str(EVM_Peak(cc),3), num2str(EVM_Worst_RB(cc),3), num2str(EVM_Worst_Sy(cc),3), num2str(flatness(cc),3)};
                    evm_table(:,cc+1)={num2str(EVM_RMS(cc),3),num2str(EVM_Peak(cc),3),num2str(EVM_Worst_RB(cc),3),num2str(EVM_Worst_Sy(cc),3),num2str(flatness(cc),3)};
                    column_names(cc+1)={horzcat('CC',num2str(cc))};
                end

                %EVM vs RB plot
                if(contains(params.nrtm,'TM2'))
                    results.rb_x = RBindex;
                    results.rb_y_b = EVM_RB_RMS;
                    results.rb_y_r = EVM_RB_Peak;
                else
                    results.rb_x = 0;
                    results.rb_y_b = EVM_RB_RMS;
                    results.rb_x = 0;
                    results.rb_y_r = EVM_RB_Peak;
                end
                results.xlim = [1,allRB];
                results.line_y= [1,1]*EVM_limit;

                %EVM vs Symbol
                results.symbol = EVM_Symbol;
                results.symbol_xlim = [1,length(EVM_Symbol(1,:))];
                results.symbol_y = [1,1]*EVM_limit;
                CCs={'CC1','CC2','CC3','CC4','CC5','CC6','CC7','CC8'};
                entries={CCs{1:params.numCar},'3GPP Limit'};
                %legend(app.UIAxes2_2,entries,'Location','best');
            catch err
                disp(['error: ',err.message]);  
            end
        end