% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Project     : ABC
% Author      : Hari (haridas.p@intel.com)
% Date        : 20 Feb 2024
% Brief       : This program is to generate input and output sample files for VHA
%               dual band demodulation testing at 3Gsps
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc;
clear;
close all;

num_vectors = 3;
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

fs = num_samples;
dt = 1/fs;
st = 1;
t = 0:dt:st-dt;
band0_input_iq1 = 50 * (1 + cos(2 * pi * t));
band0_input_iq = int32(band0_input_iq1);
band1_input_iq1 = 50 * (1 + sin(2 * pi * t));
band1_input_iq = int32(band1_input_iq1);

figure('Name', 'Modulation');
n1 = 1:1:num_samples;
subplot(4, 2, 1); grid on; hold on;
stem(n1, band0_input_iq, 'green'); title("Band0 Input IQ samples @p187");
subplot(4, 2, 2); grid on; hold on;
stem(n1, band1_input_iq, 'blue');  title("Band1 Input IQ samples @p187");

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
%band0_input_iq_to_duc = (band0_input_iq * scale_factor);
band0_input_iq_to_duc = (band0_input_iq1 * scale_factor);
band1_input_iq_to_duc = (band1_input_iq1 * scale_factor);

% enable w1, w2, w3, w4
config.vha_hbf_stages = [1 1 1 1];

% now do an interpolation
band0_output_iq_from_duc = vha_interpolate(band0_input_iq_to_duc, config);
band1_output_iq_from_duc = vha_interpolate(band1_input_iq_to_duc, config);

% now scale the samples up
scale_factor = 2^15;
n2 = 1:1:(numel(band0_output_iq_from_duc));
subplot(4, 2, 3); grid on; hold on;
stem(n2, (real(band0_output_iq_from_duc * scale_factor)), 'red'); title("DUC band0 Output 3gsps");
stem(n2, (imag(band0_output_iq_from_duc * scale_factor)), 'blue');
n2 = 1:1:(numel(band1_output_iq_from_duc));
subplot(4, 2, 4); grid on; hold on;
stem(n2, (real(band1_output_iq_from_duc * scale_factor)), 'red'); title("DUC band1 Output 3gsps");
stem(n2, (imag(band1_output_iq_from_duc * scale_factor)), 'blue');

% generate cw0 for the modulation Fs = 3gsps, Fclk = 1.5Ghz
Fclk = 983040;
Fs   = (983040 * 2);
fout0 = (Fclk / 2);
fprintf("fout0 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout0, Fs, Fclk);
cw0 = nco_pp(fout0, Fs, Fclk, length(band0_output_iq_from_duc), 1);   % 1 clk cycles delay
fout1 = (Fclk / 4);
fprintf("fout1 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout1, Fs, Fclk);
cw1 = nco_pp(fout1, Fs, Fclk, length(band1_output_iq_from_duc), 3);   % 3 clk cycles delay
subplot(4, 2, 5); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0 @3gsps");
stem(n3, imag(cw0), 'blue');
subplot(4, 2, 6); grid on; hold on;
stem(n3, real(cw1), 'blue'); title("CW1 @3gsps");
stem(n3, imag(cw1), 'red');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 3;
cw0 = transpose(cw0);
cw1 = transpose(cw1);
[mod_output_3g, dummy] = vha_combine(band0_output_iq_from_duc, band1_output_iq_from_duc, cw0, cw1, config);
mod_output_3g = mod_output_3g * scale_factor;    % scale up the final output
n2 = 1:1:length(mod_output_3g);
subplot(4, 2, 7); grid on; hold on;
stem(n2, real(mod_output_3g), 'red'); title ("Output - 3gsps Modulation");
stem(n2, imag(mod_output_3g), 'blue');

% use this modulated upconverted signal as the input to the uplink path.
% first demodulate this input with a carrier wave and then downconvert to
% the required output rate
input_iq = mod_output_3g;
num_vectors = 48;
num_samples_per_vector = 32;
num_samples = (num_vectors * num_samples_per_vector);

n1 = 1:1:num_samples;
figure('Name', 'Demodulation');
subplot(7, 2, 1); grid on; hold on;
stem(n1, real(input_iq), 'green'); title("Input IQ samples @3g");
stem(n1, imag(input_iq), 'blue');

% write this into a file which can be sourced while running on FRIO
input_real = dec2hex(real(input_iq), 4);
input_imag = dec2hex(imag(input_iq), 4);
input_3g = strcat(input_real, input_imag);
fileId = fopen("input_samples/demodulation/dual_band_demodulation_3.txt", "w");
for i = 1:length(input_3g)
    nbytes = fprintf(fileId, '%8s\n', input_3g(i,:));
end
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_for_model = (input_iq * scale_factor);

% now generate the CW for demodulation
% Fclk = 1.5GHz, Fs = 3gsps
fprintf("fout0 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout0, Fs, Fclk);
cw0 = nco_pp(fout0, Fs, Fclk, length(input_iq), 0);
subplot(7, 2, 3); grid on; hold on;
n2 = 1:1:length(cw0);
stem(n2, real(cw0), 'red'); title("CW0 @3gsps");
stem(n2, imag(cw0), 'blue');
fprintf("fout1 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout1, Fs, Fclk);
cw1 = nco_pp(fout1, Fs, Fclk, length(input_iq), 2);
subplot(7, 2, 4); grid on; hold on;
n2 = 1:1:length(cw1);
stem(n2, real(cw1), 'red'); title("CW1 @3gsps");
stem(n2, imag(cw1), 'blue');

% now do the demodulation and band splitting
config.vha_bypass = [0 0];
config.vha_conj = [0 0];
% Band0 demodulation and splitting
cw0 = transpose(cw0);
demod_output_3g_band0 = vha_split(input_iq_for_model, cw0, config);
n3 = 1:1:length(demod_output_3g_band0);
subplot(7, 2, 5); grid on; hold on;
stem(n3, real(demod_output_3g_band0), 'red'); title("Band0 Output - 3gsps Demodulation");
stem(n3, imag(demod_output_3g_band0), 'blue');

% Band1 demodulation and splitting
cw1 = transpose(cw1);
demod_output_3g_band1 = vha_split(input_iq_for_model, cw1, config);
n3 = 1:1:length(demod_output_3g_band1);
subplot(7, 2, 6); grid on; hold on;
stem(n3, real(demod_output_3g_band1), 'red'); title("Band1 Output - 3gsps Demodulation");
stem(n3, imag(demod_output_3g_band1), 'blue');

% now do the downconversion to p187
config.vha_hbf_stages = [1 1 1 1];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p187_band0 = vha_decimate(demod_output_3g_band0, config);
ddc_output_p187_band1 = vha_decimate(demod_output_3g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p187_band0 = (ddc_output_p187_band0 * scale_factor);
n4 = 1:1:length(ddc_output_p187_band0);
subplot(7, 2, 7); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to p187-gsps");
stem(n4, real(ddc_output_p187_band0), 'red');
stem(n4, imag(ddc_output_p187_band0), 'blue');

ddc_output_p187_band1 = (ddc_output_p187_band1 * scale_factor);
n4 = 1:1:length(ddc_output_p187_band1);
subplot(7, 2, 8); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to p187-gsps");
stem(n4, real(ddc_output_p187_band1), 'red');
stem(n4, imag(ddc_output_p187_band1), 'blue');

% now write this to a file
ddc_output_p187_real_band0 = dec2hex(real(ddc_output_p187_band0), 4);
ddc_output_p187_imag_band0 = dec2hex(imag(ddc_output_p187_band0), 4);
band0_output_p187 = strcat(ddc_output_p187_real_band0, ddc_output_p187_imag_band0);
fileId = fopen("output_samples/demodulation/3g/band0_dual_band_demodulation_p187.txt", "w");
for i = 1:length(band0_output_p187)
    nbytes = fprintf(fileId, '%8s\n', band0_output_p187(i,:));
end
fclose(fileId);

ddc_output_p187_real_band1 = dec2hex(real(ddc_output_p187_band1), 4);
ddc_output_p187_imag_band1 = dec2hex(imag(ddc_output_p187_band1), 4);
band1_output_p187 = strcat(ddc_output_p187_real_band1, ddc_output_p187_imag_band1);
fileId = fopen("output_samples/demodulation/3g/band1_dual_band_demodulation_p187.txt", "w");
for i = 1:length(band1_output_p187)
    nbytes = fprintf(fileId, '%8s\n', band1_output_p187(i,:));
end
fclose(fileId);

% now do the downconversion to p375
config.vha_hbf_stages = [1 1 1 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p375_band0 = vha_decimate(demod_output_3g_band0, config);
ddc_output_p375_band1 = vha_decimate(demod_output_3g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p375_band0 = (ddc_output_p375_band0 * scale_factor);
n4 = 1:1:length(ddc_output_p375_band0);
subplot(7, 2, 9); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to p375-gsps");
stem(n4, real(ddc_output_p375_band0), 'red');
stem(n4, imag(ddc_output_p375_band0), 'blue');

ddc_output_p375_band1 = (ddc_output_p375_band1 * scale_factor);
n4 = 1:1:length(ddc_output_p375_band1);
subplot(7, 2, 10); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to p375-gsps");
stem(n4, real(ddc_output_p375_band1), 'red');
stem(n4, imag(ddc_output_p375_band1), 'blue');

% now write this to a file
ddc_output_p375_real_band0 = dec2hex(real(ddc_output_p375_band0), 4);
ddc_output_p375_imag_band0 = dec2hex(imag(ddc_output_p375_band0), 4);
band0_output_p375 = strcat(ddc_output_p375_real_band0, ddc_output_p375_imag_band0);
fileId = fopen("output_samples/demodulation/3g/band0_dual_band_demodulation_p375.txt", "w");
for i = 1:length(band0_output_p375)
    nbytes = fprintf(fileId, '%8s\n', band0_output_p375(i,:));
end
fclose(fileId);

ddc_output_p375_real_band1 = dec2hex(real(ddc_output_p375_band1), 4);
ddc_output_p375_imag_band1 = dec2hex(imag(ddc_output_p375_band1), 4);
band1_output_p375 = strcat(ddc_output_p375_real_band1, ddc_output_p375_imag_band1);
fileId = fopen("output_samples/demodulation/3g/band1_dual_band_demodulation_p375.txt", "w");
for i = 1:length(band1_output_p375)
    nbytes = fprintf(fileId, '%8s\n', band1_output_p375(i,:));
end
fclose(fileId);

% now do the downconversion to p75
config.vha_hbf_stages = [1 1 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p75_band0 = vha_decimate(demod_output_3g_band0, config);
ddc_output_p75_band1 = vha_decimate(demod_output_3g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p75_band0 = (ddc_output_p75_band0 * scale_factor);
n4 = 1:1:length(ddc_output_p75_band0);
subplot(7, 2, 11); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to p75-gsps");
stem(n4, real(ddc_output_p75_band0), 'red');
stem(n4, imag(ddc_output_p75_band0), 'blue');

ddc_output_p75_band1 = (ddc_output_p75_band1 * scale_factor);
n4 = 1:1:length(ddc_output_p75_band1);
subplot(7, 2, 12); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to p75-gsps");
stem(n4, real(ddc_output_p75_band1), 'red');
stem(n4, imag(ddc_output_p75_band1), 'blue');

% now write this to a file
ddc_output_p75_real_band0 = dec2hex(real(ddc_output_p75_band0), 4);
ddc_output_p75_imag_band0 = dec2hex(imag(ddc_output_p75_band0), 4);
band0_output_p75 = strcat(ddc_output_p75_real_band0, ddc_output_p75_imag_band0);
fileId = fopen("output_samples/demodulation/3g/band0_dual_band_demodulation_p75.txt", "w");
for i = 1:length(band0_output_p75)
    nbytes = fprintf(fileId, '%8s\n', band0_output_p75(i,:));
end
fclose(fileId);

ddc_output_p75_real_band1 = dec2hex(real(ddc_output_p75_band1), 4);
ddc_output_p75_imag_band1 = dec2hex(imag(ddc_output_p75_band1), 4);
band1_output_p75 = strcat(ddc_output_p75_real_band1, ddc_output_p75_imag_band1);
fileId = fopen("output_samples/demodulation/3g/band1_dual_band_demodulation_p75.txt", "w");
for i = 1:length(band1_output_p75)
    nbytes = fprintf(fileId, '%8s\n', band1_output_p75(i,:));
end
fclose(fileId);


% now do the downconversion to 1.5G
config.vha_hbf_stages = [1 0 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_1p5_band0 = vha_decimate(demod_output_3g_band0, config);
ddc_output_1p5_band1 = vha_decimate(demod_output_3g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_1p5_band0 = (ddc_output_1p5_band0 * scale_factor);
n4 = 1:1:length(ddc_output_1p5_band0);
subplot(7, 2, 13); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to 1.5Gsps");
stem(n4, real(ddc_output_1p5_band0), 'red');
stem(n4, imag(ddc_output_1p5_band0), 'blue');

ddc_output_1p5_band1 = (ddc_output_1p5_band1 * scale_factor);
n4 = 1:1:length(ddc_output_1p5_band1);
subplot(7, 2, 14); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to 1.5Gsps");
stem(n4, real(ddc_output_1p5_band1), 'red');
stem(n4, imag(ddc_output_1p5_band1), 'blue');

% now write this to a file
ddc_output_1p5_real_band0 = dec2hex(real(ddc_output_1p5_band0), 4);
ddc_output_1p5_imag_band0 = dec2hex(imag(ddc_output_1p5_band0), 4);
band0_output_1p5 = strcat(ddc_output_1p5_real_band0, ddc_output_1p5_imag_band0);
fileId = fopen("output_samples/demodulation/3g/band0_dual_band_demodulation_1p5.txt", "w");
for i = 1:length(band0_output_1p5)
    nbytes = fprintf(fileId, '%8s\n', band0_output_1p5(i,:));
end
fclose(fileId);

ddc_output_1p5_real_band1 = dec2hex(real(ddc_output_1p5_band1), 4);
ddc_output_1p5_imag_band1 = dec2hex(imag(ddc_output_1p5_band1), 4);
band1_output_1p5 = strcat(ddc_output_1p5_real_band1, ddc_output_1p5_imag_band1);
fileId = fopen("output_samples/demodulation/3g/band1_dual_band_demodulation_1p5.txt", "w");
for i = 1:length(band1_output_1p5)
    nbytes = fprintf(fileId, '%8s\n', band1_output_1p5(i,:));
end
fclose(fileId);
