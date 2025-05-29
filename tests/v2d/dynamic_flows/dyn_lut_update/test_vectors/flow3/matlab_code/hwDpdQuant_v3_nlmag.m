function z = hwDpdQuant_v3_nlmag(termParams, T, N, r, nlmag_en, lutN, lutC, lutS, x, xtra, xtra_dly, enQuant, fracOs, hPF)

% termParams: Parameters defining each dpd term. First column is the type
% or term, second and third are the q and m delays
% T: Number of active terms (max is 48)
% N: Number of entries of each LUT
% lutC: LUT containing the C component of the nonlinearity (nonlinearity function)
% lutD LUT containing the D componentn of the nonlinearity (difference between
% adjacent inputs of C, to facilitate the interpolation
% shift value (power of 2 gain) of the C and D LUTs
% x: intpu data

if (log2(N) - round(log2(N)))~=0
    error('N must be a power of 2')
end

if enQuant

    %% Quantized
    
    
    % default quantization params
    % ---------------------------------------------------------------------
    
    enQ = 1;
    
    Q.x      = struct('signed',1, 'nBits',16, 'msb',-1, 'lsb',-15, 'disErr',0, 'sim',0, 'enable',enQ);    
    Q.lutC   = struct('signed',1, 'nBits',13, 'msb',-1, 'lsb',-12, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.r      = struct('signed',1, 'nBits',15, 'msb', 0, 'lsb',-13, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.lutS   = struct('signed',1, 'nBits', 4, 'msb', 3, 'lsb',  0, 'disErr',0, 'sim',0, 'enable',enQ);

    Q.x1     = struct('signed',1, 'nBits',11, 'msb',-1, 'lsb',-10, 'disErr',0, 'sim',0, 'enable',enQ);    
    Q.x2     = struct('signed',1, 'nBits',14, 'msb',-1, 'lsb',-13, 'disErr',0, 'sim',0, 'enable',enQ);    
    Q.a      = struct('signed',0, 'nBits',13, 'msb',-1, 'lsb',-13, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.a2     = struct('signed',0, 'nBits',10, 'msb',-1, 'lsb',-10, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.g1     = struct('signed',1, 'nBits',16, 'msb',-1, 'lsb',-15, 'disErr',0, 'sim',0, 'enable',enQ);
    
    Q.g21    = struct('signed',1, 'nBits',11, 'msb',-1, 'lsb',-10, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.g22    = struct('signed',0, 'nBits',10, 'msb',-1, 'lsb',-10, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.g      = struct('signed',1, 'nBits',14, 'msb',-1, 'lsb',-13, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.Na     = struct('signed',0, 'nBits',13, 'msb', 5, 'lsb', -7, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.i      = struct('signed',0, 'nBits',6,  'msb', 5, 'lsb',  0, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.f      = struct('signed',0, 'nBits',7,  'msb',-1, 'lsb', -7, 'disErr',0, 'sim',0, 'enable',enQ);
    % Added by mdell to handle clut_segments=1 cases (32 segments)
    if N == 32
      Q.Na     = struct('signed',0, 'nBits',13, 'msb', 4, 'lsb', -8, 'disErr',0, 'sim',0, 'enable',enQ);
      Q.i      = struct('signed',0, 'nBits',5,  'msb', 4, 'lsb',  0, 'disErr',0, 'sim',0, 'enable',enQ);
      Q.f      = struct('signed',0, 'nBits',8,  'msb',-1, 'lsb', -8, 'disErr',0, 'sim',0, 'enable',enQ);
    end
    % Non-Linear Magnitude Quantization ... mdell
    Q.NaNLM  = struct('signed',0, 'nBits',13, 'msb', 5, 'lsb', -7, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.iNLM   = struct('signed',0, 'nBits',6,  'msb', 5, 'lsb',  0, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.fNLM   = struct('signed',0, 'nBits',7,  'msb',-1, 'lsb', -7, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.b      = struct('signed',1, 'nBits',13, 'msb',-1, 'lsb',-12, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.gb     = struct('signed',1, 'nBits',15, 'msb',-1, 'lsb',-14, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.gbs    = struct('signed',1, 'nBits',18, 'msb',-1, 'lsb',-17, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.gbsAcc = struct('signed',1, 'nBits',24, 'msb', 5, 'lsb',-17, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.gbsAccQ= struct('signed',1, 'nBits',16, 'msb', 0, 'lsb',-14, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.rx     = struct('signed',1, 'nBits',16, 'msb', 0, 'lsb',-14, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.y      = struct('signed',1, 'nBits',16, 'msb', 0, 'lsb',-14, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.hPF    = struct('signed',1, 'nBits',12, 'msb', -1, 'lsb',-11, 'disErr',0, 'sim',0, 'enable',enQ);
    Q.z      = struct('signed',1, 'nBits',16, 'msb', -1, 'lsb',-15, 'disErr',0, 'sim',0, 'enable',enQ);
          
    % Quantize input data and signal
    Qu = Q.r; Qu.data = r;
    r = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
    Qu = Q.lutC; Qu.data = lutC;
    lutC = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
    Qu = Q.x; Qu.data = x;
    x = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
    Qu = Q.hPF; Qu.data = hPF;
    hPF = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);

    % Create output vector
    nX = length(x);
    y = zeros(length(x)/fracOs,1);
    z = zeros(length(x)/fracOs,1);

    % calculate points outside of calculation range
    hPFDel = length(hPF)-1;
    nStart = max(max([ termParams(:,2) termParams(:,2)+termParams(:,3) ]));
    nStart = max([nStart,xtra_dly*fracOs]); % mdell
    nStart = max([nStart,hPFDel*fracOs]); 
    nEnd = min(min([ termParams(:,2) termParams(:,2)+termParams(:,3) ]));
    nEnd = min([nEnd,xtra_dly*fracOs]); % mdell
    nStart = ceil((nStart+1)/fracOs)*fracOs-1;
    nEnd   = floor((nX+nEnd)/fracOs)*fracOs-nX;

    for n = nStart+1:fracOs:nX+nEnd
        
        gbsAcc = 0;
        for iTerm = 1: T
            
            t = termParams(iTerm,1);
            q = termParams(iTerm,2);
            m = termParams(iTerm,3);
            
            % Calculate signal part of the term
            if t==1
                % g = x(n-q);
                g = x(n-q);
                Qu = Q.g; Qu.data = g;
                g = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            elseif t==2
                % g = x(n-q-m);
                g = x(n-q-m);
                Qu = Q.g; Qu.data = g;
                g = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            elseif t==3
                % g = x(n-q).^2 .* conj(x(n-q-m));
                g1 = conj(x(n-q-m));
                Qu = Q.g1; Qu.data = g1;
                g1 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                x1 = x(n-q);
                Qu = Q.x1; Qu.data = x1;
                x1 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                g2 = x1.^2;
                Qu = Q.g21; Qu.data = g2;
                g2 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                g = g1.*g2;
                Qu = Q.g; Qu.data = g;
                g = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            elseif t==4
                %g = x(n-q) .* abs(x(n-q-m)).^2;
                g1 = x(n-q);
                Qu = Q.g1; Qu.data = g1;
                g1 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                x2 = x(n-q-m);
                Qu = Q.x2; Qu.data = x2;
                x2 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                %g2 =  abs(x2).^2;
                a = cmag(x2);
                Qu = Q.a; Qu.data = a;
                a = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                Qu = Q.a2; Qu.data = a;
                a2 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                g2 =  a2.^2;
                Qu = Q.g22; Qu.data = g2;
                g2 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                g = g1.*g2;
                Qu = Q.g; Qu.data = g;
                g = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            elseif t==5
                %g = x(n-q-m).^2 .* conj(x(n-q));
                g1 = conj(x(n-q));
                Qu = Q.g1; Qu.data = g1;
                g1 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                x1 = x(n-q-m);
                Qu = Q.x1; Qu.data = x1;
                x1 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                g2 = x1.^2;
                Qu = Q.g21; Qu.data = g2;
                g2 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
                g = g1.*g2;
                Qu = Q.g; Qu.data = g;
                g = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            end

            % lut intro (integern and decimal parts)
            x2 = x(n-q);
            Qu = Q.x2; Qu.data = x2;
            x2 = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            a = cmag(x2);
            Qu = Q.a; Qu.data = a;
            a = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);

            % NL_MAG LUT  ---------------------- added by mdell

            if nlmag_en == 1
              %Na = N * a;  
              Na = 64 * a;  % N is always 64 here ... mdell 
              Qu = Q.NaNLM; Qu.data = Na;
              Na = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);

              % lut pointer (integer) and interpolation weight (deco,añ)
              i = floor(Na);
              Qu = Q.iNLM; Qu.data = i;
              i = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
              f = Na-i;
              Qu = Q.fNLM; Qu.data = f;
              Qu.disErr =1;
              f = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);

              % read lut (already quantized)
              c = lutN(i+1);
              d = lutN(i+2) - lutN(i+1);

              % Interpolate to get interpolated lut output
              df = d * f;
              % Note that there is no quantization or saturation in this step.
              %  This offset is implemented as full multiplier.
              %Qu = Q.df; Qu.data = df;
              %df = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable)
              a = c + df;
              Qu = Q.a; Qu.data = a;
              a = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            end

            % Coefficient LUT  ----------------------

            Na = N * a;
            Qu = Q.Na; Qu.data = Na;
            Na = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            
            % lut pointer (integer) and interpolation weight (deco,añ)
            i = floor(Na);
            Qu = Q.i; Qu.data = i;
            i = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            f = Na-i;
            Qu = Q.f; Qu.data = f;
            Qu.disErr =1;
            f = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            
            % read luts (already quantized)
            c  = lutC(iTerm,i+1);
            c1 = lutC(iTerm,i+1+1);
            d  = c1-c;
            
            % Interpolate to get interpolated lut output
            df = d * f;   
            b = c + df;
            Qu = Q.b; Qu.data = b;
            b = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            
            % Multiply lut coefficient by signal part of the term
            gb      = b * g ;
            Qu = Q.gb; Qu.data = gb;
            gb = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            
            % Shift to de-normalize (undo lut content normalization)
            gbs = gb * 2^(lutS(iTerm));
            Qu = Q.gbs; Qu.data = gbs;
            gbs = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            
            % Accumulate terms
            gbsAcc = gbsAcc +  gbs;
            Qu = Q.gbsAcc; Qu.data = gbsAcc;
            gbsAcc = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
            
        end
        
        % Quantize accumulator before combining with r*x(n)  
        gbsAccQ = gbsAcc;
        Qu = Q.gbsAccQ; Qu.data = gbsAccQ;
        gbsAccQ = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
        
        % Rotate input (mean value of original static term LUT)
        rx = r*x(n);
        Qu = Q.rx; Qu.data = rx;
        rx = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
        
        % Convine to get output
        % mdell ... added extra terms
        %y(n/fracOs) = rx + gbsAccQ;
        y(n/fracOs) = rx + gbsAccQ + xtra(n/fracOs-xtra_dly);
        Qu = Q.y; Qu.data = y(n/fracOs);
        y(n/fracOs) = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);

        % DPD Post Filter (PF)
        z_ = 0;
        for iPF = 0:hPFDel
            z_ = z_ + y(n/fracOs-iPF)*hPF(iPF+1);
        end
        Qu = Q.z; Qu.data = z_;
        z_ = quantCpx(Qu.msb,Qu.lsb,Qu.data,Qu.disErr,Qu.sim,Qu.enable);
        z(n/fracOs)  = z_;

    end
    
else

    %% Not quantized
    
    nX = length(x);
    y = zeros(length(x)/fracOs,1);
    z = zeros(length(x)/fracOs,1);
    
    hPFDel = length(hPF)-1;
    nStart = max(max([ termParams(:,2) termParams(:,2)+termParams(:,3)]));
    nStart = max([nStart,hPFDel*fracOs]);
    nEnd   = min(min([ termParams(:,2) termParams(:,2)+termParams(:,3)]));
    nStart = ceil((nStart+1)/fracOs)*fracOs-1;
    nEnd   = floor((nX+nEnd)/fracOs)*fracOs-nX;
    
    for n = nStart+1: fracOs: nX+nEnd
        
        gbsAcc = 0;
        for iTerm = 1: T
            
            t = termParams(iTerm,1);
            q = termParams(iTerm,2);
            m = termParams(iTerm,3);
            
            if t==1
                g = x(n-q);
            elseif t==2
                g = x(n-q-m);
            elseif t==3
                g = x(n-q).^2 .* conj(x(n-q-m));
            elseif t==4
                g = x(n-q) .* abs(x(n-q-m)).^2;
            elseif t==5
                g = x(n-q-m).^2 .* conj(x(n-q));
            end
            
            a = abs(x(n-q));
            Na = N * a;
            i  = floor(Na);
            f  = Na-i;
            c  = lutC(iTerm,i+1);
            c1 = lutC(iTerm,i+1+1);
            d  = c1-c;
            
            df = d * f;
            b = c + df;
            
            gb      = g * b ;
            s = 2^(lutS(iTerm));
            gbs = gb * s;
            gbsAcc = gbsAcc +  gbs;
            
        end
        
        gbsAccQ = gbsAcc;
        rx = r*x(n);
        y(n/fracOs) = rx + gbsAccQ ;

        % DPD Post Filter (PF)
        z_ = 0;
        for iPF = 0:hPFDel
            z_ = z_ + y(n/fracOs-iPF)*hPF(iPF+1);
        end
        z(n/fracOs) = z_;
        
    end
    
end
