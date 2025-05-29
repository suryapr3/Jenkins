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

% passthru_dly is no longer used by the model
passthru_dly = 0;

% Non-magnitude mapping enable, NLMAG_ENABLE 
nlmag_en = 0;

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

data_in_i = zeros( 4096, 1);
data_in_q = zeros( 4096, 1);

%data_in_i(1:16384) = [0:4:65535];
%data_in_q(1:16384) = [2:4:65535];
output_index = 1;
global_input_index = 1;
i_add = 0x0000;
j_add = 0x0000;
fileId = fopen("ref_output_8gsps.txt","w");
fileId_in = fopen("input.txt","r");
temp_var_in = 0;
%temp_var_in = bitor(data_in_i(input_index),bitshift(data_in_q(input_index),16));
%added by Sai
for blc_cnt = 0  %max blocks
    i_add = i_add + 0x0011;
    j_add = j_add + 0x0014;
    %input_index = 1;
    %i_add = i_add + 0x03;
    %j_add = j_add + 0x01;
    for i = 0:127 % vectors per block
        for j = 0:31
            data_in_i(global_input_index) = (i*2*32+(j*2)) + i_add;
            data_in_q(global_input_index) = (i*32+(j*2)) + j_add;
            %temp_var_in = bitor(data_in_i(global_input_index),bitshift(data_in_q(global_input_index),16));
            %fscanf(fileId_in,"%x\n",temp_var_in);
            %temp_var_in = fscanf(fileId,"%d",1);
            %print ("%08X\n", temp_var_in);
            %data_in_i(global_input_index) = bitsrl(bitand(temp_var_in,0xFFFF0000),16);
            %data_in_q(global_input_index) = bitand(temp_var_in,0x0000FFFF);
            global_input_index = global_input_index + 1;
        end
    end
end
    [y_out_i, y_out_q] = pdpd_wrap( term_types, q_dly, m_dly, passthru_dly, ...
                         passthru_coeff_i, passthru_coeff_q, nlmag_en, lut_n, ...
                        lut_c_i, lut_c_q, lut_s, data_in_i, data_in_q );
for blc_cnt = 0
    %temp_index = 1;
    for i = 0:127
        for j = 0:31
            temp_var = bitor(y_out_q(output_index),bitshift(y_out_i(output_index),16));
            fprintf(fileId, "%08x\n", temp_var);
            output_index = output_index + 1;
        end
    end

end

% ----- Call the function

%[y_out_i, y_out_q] = pdpd_wrap( term_types, q_dly, m_dly, passthru_dly, ...
 %                        passthru_coeff_i, passthru_coeff_q, nlmag_en, lut_n, ...
%                         lut_c_i, lut_c_q, lut_s, data_in_i, data_in_q );
%input_index = 1;
%fileId = fopen ("output.txt","w");
%for i = 0:127
 %   for j = 0:31
  %      temp_var = bitor(y_out_i(input_index),bitshift(y_out_q(input_index),16));

   %     fprintf(fileId, "%08x\n", temp_var);
        
    %    input_index = input_index+1;
    %end
%end
fclose(fileId);
fclose(fileId_in);