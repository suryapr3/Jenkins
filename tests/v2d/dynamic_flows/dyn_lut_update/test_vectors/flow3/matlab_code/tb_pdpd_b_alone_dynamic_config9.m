format longG

% ----- Set up of configs corresponding to GMP_STATIC and DDR_STATIC

% Initialize term_types, which are the types of the terms described in the 
%  HAS section 12.5.1.2. 
term_types = zeros( 48, 1 );
term_types(1:48) = 1;     % Value must be between and including 1 and 5

% Initialize q and m delays
q_dly = zeros( 48, 1 );
m_dly = zeros( 48, 1 );

% ----- Set up of configs corresponding to CONFIG register

% passthru_dly 
passthru_dly = 10;

% Non-linear magnitude mapping enable, NLMAG_ENABLE 
nlmag_en = 0;   % 0 is default

% Coefficient LUT Segments, CLUT_SEGMENTS 
clut_segments = 0;  % 1 corresponds to 32 entries per LUT
                    % 0 (default) corresponds to 64 entries per LUT

% ----- Passthru coefficients (PASSTHRU_C_LIVE)

% Set to half scale (0.5)
passthru_coeff_i = 2^13;  % real part
passthru_coeff_q = 0;  % imaginary part

% ----- Nonlinear Magnitude LUT Coefficient Register (NL_C_LIVE)

lut_n = zeros( 1, 65 );

% ----- Tap Coefficient Registers (GMP_C_LIVE and DDR_C_LIVE)

lut_c_i = zeros( 48, 65 );  % real part
lut_c_q = zeros( 48, 65 );  % imaginary part

lut_c_i_value = [0x83, 0x5F, 0x11, 0x50];

% Set two of the coefficients' real parts to be half scale (0.5)
%lut_c_i(1:12,1:65) = 2^10;
lut_c_i(1:2,1:65) = 2^11;

% ----- Tap Coefficient Shift Value Registers (GMP_SHIFT_LIVE and DDR_SHIFT_LIVE)

lut_s = zeros( 1, 48 );

%Kannan: in HW it is always a right shift. i.e lut_s should be always
%positive which shift the coefts to right.
% not setting this to ngative such that the input shoft values to wrap
% fucntion is negative was causing the wrning saturation hit fan
%live IQ experiment
lut_s = -lut_s;

% ----- Input Data

data_in_i = zeros( 16384, 1);
data_in_q = zeros( 16384, 1);


% ----- Extra Terms

xtra_in_i = zeros(16384, 1 );
xtra_in_q = zeros(16384, 1 );

% ----- Extra terms delay

xtra_dly = 0;

output_index = 1;
global_input_index = 1;
output_file_index = 1;
extra_term_global_input_index = 1;

fileId = fopen("ref_output_config9.txt","w");
%fileId_input = fopen("input_iq.txt", "w");

% ----- Fractional oversampling
%  This is the factor of subsampling being configured. 
%  For example, if subsampling from 8Gsps to 1Gsps, frac_os=8.
%   If subsampling from 4Gsps to 2Gsps, frac_os=2.

frac_os = 4;

% ----- Postfilter coefficients

post_c = zeros( 17, 1 );
%post_c(1:17) = 100;
post_c(9) = 2047; % Set center tap to ~1 to get a virtual passthru


for tot_iter = 0:3
    global_input_index = 1;
    output_index = 1;
    %Modify the LUT for each run
    lut_c_i(1:8,1:65) = lut_c_i_value(tot_iter + 1);
    %lut_c_i(1:2,1:65) = 2^11 / 2^tot_iter;
    for input_blk_iter = 0:3
        for blc_cnt = 1:4
            input_index = 1;
            while input_index < 16385
                data_in_i(global_input_index) = input_index;
                data_in_q(global_input_index) = input_index + 2;
                xtra_in_i(global_input_index) = 0;
                xtra_in_q(global_input_index) = 0;
                %temp_var = bitor(data_in_q(global_input_index),bitshift(data_in_i(global_input_index),16));
                %fprintf(fileId_input, "%08x\n", temp_var);
                global_input_index = global_input_index + 1;
                input_index = input_index + 1;
            end
        end
    end

    % ----- Call the function

    [y_out_i, y_out_q] = pdpd_wrap( term_types, q_dly, m_dly, passthru_dly, ...
                             passthru_coeff_i, passthru_coeff_q, nlmag_en, ...
                             clut_segments, lut_n, ...
                             lut_c_i, lut_c_q, lut_s, data_in_i, data_in_q, ...
                             xtra_in_i, xtra_in_q, xtra_dly, frac_os, post_c );

    for i = 1:(passthru_dly / frac_os)
        fprintf(fileId, "%08x\n",0);
        output_file_index = output_file_index + 1;
    end

    while output_index < ((65537 - (passthru_dly / frac_os)))
      temp_var = bitor(y_out_q(output_index),bitshift(y_out_i(output_index),16));
      fprintf(fileId, "%08x\n", temp_var);
      output_index = output_index + 1;
      output_file_index = output_file_index + 1;
    end
end

fclose(fileId);
%fclose(fileId_input);
