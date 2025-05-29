function [r] = vha_interpolate(s,config)
%VHA_INTERPOLATE simulates interpolation stages W4 through W1 in the digital RF
%INPUTS
%s=I+jQ complex input vector sc16.15
%config.vha_hbf_stages=boolean vector indicates which stages are active [w1,w2,w3,w4]
%OUTPUTS
%r=I+jQ complex output vector sc16.15

% Sunitha Kopparthi: Updated the filter coefficients

%filter coefficients
HB1 = [-4, 0, 20, 0, -56, 0, 128, 0, -257, 0, 468, 0, -800, 0, 1292, 0, -2006, 0, 3018, 0, -4448, 0, 6510, 0, -9640, 0, 14984, 0, -26760, 0, 83088, 131072, 83088, 0, -26760, 0, 14984, 0, -9640, 0, 6510, 0, -4448, 0, 3018, 0, -2006, 0, 1292, 0, -800, 0, 468, 0, -257, 0, 128, 0, -56, 0, 20, 0, -4];
HB2 = [192, 0, -1438, 0, 6016, 0, -19488, 0, 80256, 131072, 80256, 0, -19488, 0, 6016, 0, -1438, 0, 192];
HB3 = [1760, 0, -13440, 0, 77216, 131072, 77216, 0, -13440, 0, 1760];
HB4 = [-8320, 0, 73856, 131072, 73856, 0, -8320];
scale_hbf=2^-17; %bit-shift only

%simulation each stage of decimation
q=fi(s,1,16,15);
for i=1:1:4
    if(config.vha_hbf_stages(i))
        switch(i)
            case 4
                b=HB4;
            case 3
                b=HB3;
            case 2
                b=HB2;
            case 1
                b=HB1;
            otherwise
                break; %bypass if no stages chosen
        end
        coeffw=fi(b*scale_hbf,1,19,17); %add one more integer bit for passthrough coefficient
        q=filter(coeffw,1,upsample(q,2,0));
        q=fi(q,1,16,15); %round and saturate between stages
    end
end

%set final output
r=q;

end
