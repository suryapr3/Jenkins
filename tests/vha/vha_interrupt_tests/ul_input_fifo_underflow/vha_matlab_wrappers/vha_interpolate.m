function [r] = vha_interpolate(s,config)
%VHA_INTERPOLATE simulates interpolation stages W4 through W1 in the digital RF
%INPUTS
%s=I+jQ complex input vector sc16.15
%config.vha_hbf_stages=boolean vector indicates which stages are active [w1,w2,w3,w4]
%OUTPUTS
%r=I+jQ complex output vector sc16.15

%filter coefficients
HB1 = [-6, 0, 24, 0, -63, 0, 138, 0, -270, 0, 487, 0, -821, 0, 1319, 0, -2035, 0, 3049, 0, -4480, 0, 6539, 0, -9666, 0, 15004, 0, -26773, 0, 83090, 131072, 83090, 0, -26773, 0, 15004, 0, -9666, 0, 6539, 0, -4480, 0, 3049, 0, -2035, 0, 1319, 0, -821, 0, 487, 0, -270, 0, 138, 0, -63, 0, 24, 0, -6];
HB2 = [175, 0, -1393, 0, 5956, 0, -19439, 0, 80237, 131072, 80237, 0, -19439, 0, 5956, 0, -1393, 0, 175];
HB3 = [1732, 0, -13363, 0, 77167, 131072, 77167, 0, -13363, 0, 1732];
HB4 = [-8351, 0, 73885, 131072, 73885, 0, -8351];
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