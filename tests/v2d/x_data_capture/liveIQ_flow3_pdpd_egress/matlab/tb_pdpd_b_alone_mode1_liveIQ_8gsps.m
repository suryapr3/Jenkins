format longG

load testData_copy.mat
nTestPts=12288;

%% PLOT
plot_range_en = 1;
if(plot_range_en)
    temp1 = dlmread( 'liveIQ_ref_LUT12_64_i_8gsps.txt');
    temp2 = dlmread( 'liveIQ_ref_LUT12_64_q_8gsps.txt');
    temp3 = dlmread( 'liveIQ_ref_LUTall_64_i.txt');
    temp4 = dlmread( 'liveIQ_ref_LUTall_64_q.txt');
    temp5 = dlmread( 'liveIQ_FP_LUT12_64_i_8gsps.txt');
    temp6 = dlmread( 'liveIQ_FP_LUT12_64_q_8gsps.txt');
    temp7 = dlmread( 'liveIQ_FP_LUTall_64_i.txt');
    temp8 = dlmread( 'liveIQ_FP_LUTall_64_q.txt');
    
    size(1) = numel(temp1);
    size(2) = numel(temp2);
    size(3) = numel(temp3);
    size(4) = numel(temp4);
    size(5) = numel(temp5);
    size(6) = numel(temp6);
    size(7) = numel(temp7);
    size(8) = numel(temp8);
    array_size = max(size);
    M = zeros(array_size,8);
    M(1:size(1),1) = temp1;
    M(1:size(2),2) = temp2;
    M(1:size(3),3) = temp3;
    M(1:size(4),4) = temp4;
    M(1:size(5),5) = temp5;
    M(1:size(6),6) = temp6;
    M(1:size(7),7) = temp7;
    M(1:size(8),8) = temp8;
    for j = 100: nTestPts
        difference_i(j) = M(j,1)-M(j,5);
        difference_q(j) = M(j,2)-M(j,6);
    end 


    plot_range = (100:nTestPts);

    figure;
    plot(M(plot_range,1))
    hold on
    %figure

    plot(M(plot_range,5))
    hold off
    figure;
    plot(M(plot_range,2))
    hold on
    %figure

    plot(M(plot_range,6))
    hold off
    figure;
    plot(difference_i(plot_range));
    figure;
    plot(difference_q(plot_range));

end

%%


%fracOs = 1;
%nTestPts = floor(nTestPts/fracOs)*fracOs;

frac_os = 1;
nTestPts = floor(nTestPts/frac_os)*frac_os;
x = x(1:nTestPts);


% ----- Set up of configs corresponding to GMP_STATIC and DDR_STATIC

% Initialize term_types, which are the types of the terms described in the 
%  HAS section 12.5.1.2. 
term_types = zeros( 48, 1 );
%term_types(1:48) = 1;     % Value must be between and including 1 and 5
% Initialize q and m delays
q_dly = zeros( 48, 1 );
m_dly = zeros( 48, 1 );

%reading from version2 delivered by Ramon
ftermType = fopen("termType.txt","r");
fqdly = fopen("q_dly.txt","r");
fmdly = fopen("m_dly.txt","r");

            %term_types(termParams_index) = fscanf(ftermType, "%d");
            term_types = fscanf(ftermType, "%d");
            q_dly = fscanf(fqdly, "%d"); 
            m_dly = fscanf(fmdly, "%d"); 
fclose (ftermType);
fclose (fqdly);
fclose (fmdly);


% ----- Set up of configs corresponding to CONFIG register

% passthru_dly 
passthru_dly = 64;  %as suggested by Kannan changed to 64

% Non-linear magnitude mapping enable, NLMAG_ENABLE 
nlmag_en = 0;   % 0 is default

% Coefficient LUT Segments, CLUT_SEGMENTS 
clut_segments = 0;  % 1 corresponds to 32 entries per LUT
                    % 0 (default) corresponds to 64 entries per LUT

% ----- Passthru coefficients (PASSTHRU_C_LIVE)

% Set to half scale (0.5)
%passthru_coeff_i = 2^13;  % real part
%passthru_coeff_q = 0;  % imaginary part
% from testData.mat r= 0.9738-0.0027i
%r = (passthru_coeff_i + 1i*passthru_coeff_q) / 2^13;   977.37+ 22.11i
% passthru_coeff_i = 0.9738*2^13
% passthru_coeff_i = 0.0027*2^13
passthru_coeff_i = floor (real(r)* 2^13);
passthru_coeff_q = floor (imag(r)* 2^13); % imaginary part

% ----- Nonlinear Magnitude LUT Coefficient Register (NL_C_LIVE)

lut_n = zeros( 1, 65 );

% ----- Tap Coefficient Registers (GMP_C_LIVE and DDR_C_LIVE)
%reading from testData_copy.mat
lut_c_i = zeros( 48, 65 );  % real part
lut_c_q = zeros( 48, 65 );  % imaginary part

% Set two of the coefficients' real parts to be half scale (0.5)
%lut_c_i(1:2,1:65) = 2^10;
%lut_c_i(1:2,1:65) = 2^11;

%correctes for lutC Nan related issues by Ramon.
lutC(:,54:65) = lutC(:,53)*ones(1,65-53)

lut_c_i = floor( (real(lutC)* 2^12));% or convert to int?
lut_c_q =  floor( (imag(lutC)* 2^12) );
fileId = fopen("liveIQ_lut_c_i.txt","w");
fileId1 = fopen("liveIQ_lut_c_q.txt","w");

for j = 1: 48
    for  k= 1:65
        fprintf(fileId, "%d\n", lut_c_i(j,k));
        fprintf(fileId1, "%d\n", lut_c_q(j,k));
    end
end 
fclose(fileId);
fclose(fileId1);

% ----- Tap Coefficient Shift Value Registers (GMP_SHIFT_LIVE and DDR_SHIFT_LIVE)

lut_s = zeros( 1, 48 ); 
%reading from testData_copy.mat
lut_s = lutS;

% for liveIQ on emulation, this need to be negative(Ramon)
%Kannan: in HW it is always a right shift. i.e lut_s should be always
%positive which shift the coefts to right.
% not setting this to ngative such that the input shoft values to wrap
% fucntion is negative was causing the wrning saturation hit fan
lut_s = -lut_s 

fileId = fopen("liveIQ_lut_s.txt","w");

for j = 1: 48
    fprintf(fileId, "%d\n", lut_s(j));
end
fclose(fileId);

% ----- Input Data
%reading from testData_copy.mat
%data_in_i = zeros( 20480, 1);
%data_in_q = zeros( 20480, 1);
data_in_i = zeros( nTestPts, 1);
data_in_q = zeros( nTestPts, 1);

data_in_i =  floor(real(x)* 2^15);
data_in_q =  floor(imag(x)* 2^15);


fileId = fopen("liveIQ_data_in_i.txt","w");
fileId1 = fopen("liveIQ_data_in_q.txt","w");
for j = 1: nTestPts
        
       fprintf(fileId, "%d\n", data_in_i(j));
       fprintf(fileId1, "%d\n", data_in_q(j));

end
fclose(fileId);
fclose(fileId1);

% ----- Extra Terms

xtra_in_i = zeros(nTestPts, 1 );
xtra_in_q = zeros(nTestPts, 1 );

% ----- Extra terms delay

xtra_dly = 0;


% ----- Fractional oversampling
%  This is the factor of subsampling being configured. 
%  For example, if subsampling from 8Gsps to 1Gsps, frac_os=8.
%   If subsampling from 4Gsps to 2Gsps, frac_os=2.

%frac_os = 1;  already set inthe beginning

% ----- Postfilter coefficients

post_c = zeros( 17, 1 );
post_c(9) = 2047; % Set center tap to ~1 to get a virtual passthru

passthru_dly = 64 ; 

% selecting first 8GMP terms and first 4 DDR terms for 8GSPS and  then
% applying duplication  logic on the coefts.

%gmp terms
gmp_index = 1;
i = 1 ;
term_types_8gsps = zeros(48,1);
q_dlys_8gsps = zeros(48,1);
m_dlys_8gsps = zeros(48,1);
lut_c_i_8gsps = zeros(48,65);
lut_c_q_8gsps = zeros(48,65);
lut_s_8gsps = zeros(48,1);
%M = zeros(array_size,8);
while  ( (gmp_index<=8) & (i<=48) )
    if  ( (term_types(i)==0) | (term_types(i)==1) |(term_types(i)==2) )
        term_types_8gsps(gmp_index) = term_types(i);
        q_dlys_8gsps(gmp_index) = q_dly(i);
        m_dlys_8gsps(gmp_index) = m_dly(i);
        lut_c_i_8gsps (gmp_index,1:65) = lut_c_i(i,1:65);
        lut_c_q_8gsps (gmp_index,1:65) = lut_c_q(i,1:65);
        lut_s_8gsps (gmp_index) = lut_s(i);
  
        gmp_index =  gmp_index + 1;

    end
    i = i+1 ;
end
ddr_index = 1;
i = 1;
while ( (ddr_index<=4)& (i<=48))
    if  ( (term_types(i)==3) | (term_types(i)==4) |(term_types(i)==5) )
        term_types_8gsps(ddr_index+8) = term_types(i);
        q_dlys_8gsps(ddr_index+8) = q_dly(i);
        m_dlys_8gsps(ddr_index+8) = m_dly(i);
        lut_c_i_8gsps ((ddr_index+8),1:65) = lut_c_i(i,1:65);
        lut_c_q_8gsps ((ddr_index+8), 1:65) = lut_c_q(i,1:65);
        lut_s_8gsps (ddr_index+8) = lut_s(i);

        ddr_index =  ddr_index + 1;
    end
    i = i+1 ;
end
% modified paramters copying bac bfore calling the wrapper

term_types = term_types_8gsps;
q_dly = q_dlys_8gsps;
m_dly = m_dlys_8gsps;
lut_c_i = lut_c_i_8gsps ;
lut_c_q = lut_c_q_8gsps;
lut_s = lut_s_8gsps;


fileId = fopen("liveIQ_lut_c_i_8gsps.txt","w");
fileId1 = fopen("liveIQ_lut_c_q_8gsps.txt","w");

for j = 1: 48
    for  k= 1:65
        fprintf(fileId, "%d\n", lut_c_i_8gsps(j,k));
        fprintf(fileId1, "%d\n", lut_c_q_8gsps(j,k));
    end
end 
fclose(fileId);
fclose(fileId1);

[y_out_i, y_out_q] = pdpd_wrap( term_types, q_dly, m_dly, passthru_dly, ...
                         passthru_coeff_i, passthru_coeff_q, nlmag_en, ...
                         clut_segments, lut_n, ...
                         lut_c_i, lut_c_q, lut_s, data_in_i, data_in_q, ...
                         xtra_in_i, xtra_in_q, xtra_dly, frac_os, post_c );


%adjustment to the output index w.r.t the non zero passthrough delay,
% Kannan clarified this the correct way
%
fileId = fopen("liveIQ_ref_LUT12_64_i_8gsps.txt","w");
fileId1 = fopen("liveIQ_ref_LUT12_64_q_8gsps.txt","w");
%fileId2 = fopen("liveIQ_ref_output_i_q.txt","w");
passthu_delay_shift = (floor(passthru_dly/frac_os));
for i = 1:passthu_delay_shift
    fprintf(fileId, "%x\n",0);
    fprintf(fileId1, "%x\n",0);
     %fprintf(fileId2, "%x\n",0);
end
for j = 1: nTestPts
    fprintf(fileId, "%d\n", floor(y_out_i(j)));
    fprintf(fileId1, "%d\n", floor(y_out_q(j)));
 %temp_var = bitor(y_out_q(j),bitshift(y_out_i(j),16));
     %fprintf(fileId2, "%x\n", temp_var);
end
fclose(fileId);
fclose(fileId1);


j = 1 ;




























