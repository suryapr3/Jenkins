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
passthru_dly = 0;

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

% Set two of the coefficients' real parts to be half scale (0.5)
%lut_c_i(1,1:65) = 2^11;
%lut_c_i(2,1:65) = 2^11;

% ----- Tap Coefficient Shift Value Registers (GMP_SHIFT_LIVE and DDR_SHIFT_LIVE)

lut_s = zeros( 1, 48 ); 

% ----- Input Data

data_in_i = zeros( 12288, 1);
data_in_q = zeros( 12288, 1);


% ----- Extra Terms

xtra_in_i = zeros(12288, 1 );
xtra_in_q = zeros(12288, 1 );

% ----- Extra terms delay

xtra_dly = 0;

output_index = 1;
global_input_index = 1;
extra_term_global_input_index = 1;
i_add = 0x0000;
j_add = 0x0000;

fileId = fopen("ref_output_8gsps_b_alone_mode2.txt","w");
fileId1 = fopen("ref_output_8gsps.txt","w");

i_add = i_add + 0x0000;
j_add = j_add + 0x0000;

for i = 0:31
    %xtra_in_i(extra_term_global_input_index) = 0;
    %xtra_in_q(extra_term_global_input_index) = 0;
    %extra_term_global_input_index = extra_term_global_input_index + 1;
end

for blc_cnt = 0:2  %max blocks this value should be 32 , 16, 8, 4, 2 for p5, 1IQ, 2IQ, 4IQ and 8IQ rates
    i_add = i_add + 0x0000;
    j_add = j_add + 0x0000;
    for i = 0:127 % vectors per block this value should be 8, 16, 32, 64, 128 for p5, 1IQ, 2IQ, 4IQ and 8IQ rates
        for j = 0:31
            data_in_i(global_input_index) = (i*2*32+(j*2)) + i_add;
            data_in_q(global_input_index) = (i*32+(j*2)) + j_add;
            %xtra_in_i(extra_term_global_input_index) = (i*2*32+(j*2)) + i_add;
            %xtra_in_q(extra_term_global_input_index) = (i*32+(j*2)) + j_add;   
            %xtra_in_i(extra_term_global_input_index) = (i*32+(j)) + i_add;
            %xtra_in_q(extra_term_global_input_index) = (i*32+(j)) + j_add; 
            global_input_index = global_input_index + 1;
            extra_term_global_input_index = extra_term_global_input_index + 1;
        end
    end
    %j_add = j_add + 1;
end


% ----- Fractional oversampling
%  This is the factor of subsampling being configured. 
%  For example, if subsampling from 8Gsps to 1Gsps, frac_os=8.
%   If subsampling from 4Gsps to 2Gsps, frac_os=2.

frac_os = 1;

% ----- Postfilter coefficients

post_c = zeros( 17, 1 );
post_c(9) = 2047; % Set center tap to ~1 to get a virtual passthru


% ----- Call the function

[y_out_i, y_out_q] = pdpd_wrap( term_types, q_dly, m_dly, passthru_dly, ...
                         passthru_coeff_i, passthru_coeff_q, nlmag_en, ...
                         clut_segments, lut_n, ...
                         lut_c_i, lut_c_q, lut_s, data_in_i, data_in_q, ...
                         xtra_in_i, xtra_in_q, xtra_dly, frac_os, post_c );

for blc_cnt = 0:2  %max blocks this value should be 32 , 16, 8, 4, 2 for p5, 1IQ, 2IQ, 4IQ and 8IQ rates
    for i = 0:127    % vectors per block this value should be 8, 16, 32, 64, 128 for p5, 1IQ, 2IQ, 4IQ and 8IQ rates
        for j = 0:31
            temp_var = bitor(y_out_q(output_index),bitshift(y_out_i(output_index),16));
            fprintf(fileId, "%08x\n", temp_var);
            if blc_cnt == 1
                fprintf(fileId1, "%08x\n", temp_var);
            end
            output_index = output_index + 1;
        end
    end

end

fclose(fileId);
fclose(fileId1);
