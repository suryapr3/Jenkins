% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Project     : ABC
% Author      : Hari (haridas.p@intel.com)
% Date        : 20 Feb 2024
% Brief       : This program is to generate input and output sample files for VHA
%               dual band demodulation testing at 2Gsps
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc;
clear;
close all;

num_vectors = 2;
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
stem(n1, band0_input_iq, 'green'); title("Band0 Input IQ samples @p125");
subplot(4, 2, 2); grid on; hold on;
stem(n1, band1_input_iq, 'blue');  title("Band1 Input IQ samples @p125");

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
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
stem(n2, (real(band0_output_iq_from_duc * scale_factor)), 'red'); title("DUC band0 Output 2Gsps");
stem(n2, (imag(band0_output_iq_from_duc * scale_factor)), 'blue');
n2 = 1:1:(numel(band1_output_iq_from_duc));
subplot(4, 2, 4); grid on; hold on;
stem(n2, (real(band1_output_iq_from_duc * scale_factor)), 'red'); title("DUC band1 Output 2Gsps");
stem(n2, (imag(band1_output_iq_from_duc * scale_factor)), 'blue');

% generate cw0 for the modulation Fs = 2Gsps, Fclk = 1Ghz
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
stem(n3, real(cw0), 'red'); title("CW0 @2Gsps");
stem(n3, imag(cw0), 'blue');
subplot(4, 2, 6); grid on; hold on;
stem(n3, real(cw1), 'blue'); title("CW1 @2Gsps");
stem(n3, imag(cw1), 'red');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 3;
cw0 = transpose(cw0);
cw1 = transpose(cw1);
[mod_output_2g, dummy] = vha_combine(band0_output_iq_from_duc, band1_output_iq_from_duc, cw0, cw1, config);
mod_output_2g = mod_output_2g * scale_factor;    % scale up the final output
n2 = 1:1:length(mod_output_2g);
subplot(4, 2, 7); grid on; hold on;
stem(n2, real(mod_output_2g), 'red'); title ("Output - 2Gsps Modulation");
stem(n2, imag(mod_output_2g), 'blue');

% use this modulated upconverted signal as the input to the uplink path.
% first demodulate this input with a carrier wave and then downconvert to
% the required output rate
input_iq = mod_output_2g;
num_vectors = 32;
num_samples_per_vector = 32;
num_samples = (num_vectors * num_samples_per_vector);

n1 = 1:1:num_samples;
figure('Name', 'Demodulation');
subplot(7, 2, 1); grid on; hold on;
stem(n1, real(input_iq), 'green'); title("Input IQ samples @2Gsps");
stem(n1, imag(input_iq), 'blue');

% write this into a file which can be sourced while running on FRIO
input_real = dec2hex(real(input_iq), 4);
input_imag = dec2hex(imag(input_iq), 4);
input_2g = strcat(input_real, input_imag);
fileId = fopen("input_samples/demodulation/dual_band_demodulation_2.txt", "w");
for i = 1:length(input_2g)
    nbytes = fprintf(fileId, '%8s\n', input_2g(i,:));
end
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_for_model = (input_iq * scale_factor);

% now generate the CW for demodulation
% Fclk = 1GHz, Fs = 2Gsps
fprintf("fout0 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout0, Fs, Fclk);
cw0 = nco_pp(fout0, Fs, Fclk, length(input_iq), 0);
subplot(7, 2, 3); grid on; hold on;
n2 = 1:1:length(cw0);
stem(n2, real(cw0), 'red'); title("CW0 @2Gsps");
stem(n2, imag(cw0), 'blue');
fprintf("fout1 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout1, Fs, Fclk);
cw1 = nco_pp(fout1, Fs, Fclk, length(input_iq), 2);
subplot(7, 2, 4); grid on; hold on;
n2 = 1:1:length(cw1);
stem(n2, real(cw1), 'red'); title("CW1 @2Gsps");
stem(n2, imag(cw1), 'blue');

% now do the demodulation and band splitting
config.vha_bypass = [0 0];
config.vha_conj = [0 0];
% Band0 demodulation and splitting
cw0 = transpose(cw0);
demod_output_2g_band0 = vha_split(input_iq_for_model, cw0, config);
n3 = 1:1:length(demod_output_2g_band0);
subplot(7, 2, 5); grid on; hold on;
stem(n3, real(demod_output_2g_band0), 'red'); title("Band0 Output - 2Gsps Demodulation");
stem(n3, imag(demod_output_2g_band0), 'blue');

% Band1 demodulation and splitting
cw1 = transpose(cw1);
demod_output_2g_band1 = vha_split(input_iq_for_model, cw1, config);
n3 = 1:1:length(demod_output_2g_band1);
subplot(7, 2, 6); grid on; hold on;
stem(n3, real(demod_output_2g_band1), 'red'); title("Band1 Output - 2Gsps Demodulation");
stem(n3, imag(demod_output_2g_band1), 'blue');

% now do the downconversion to p125
config.vha_hbf_stages = [1 1 1 1];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p125_band0 = vha_decimate(demod_output_2g_band0, config);
ddc_output_p125_band1 = vha_decimate(demod_output_2g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p125_band0 = (ddc_output_p125_band0 * scale_factor);
n4 = 1:1:length(ddc_output_p125_band0);
subplot(7, 2, 7); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to p125-gsps");
stem(n4, real(ddc_output_p125_band0), 'red');
stem(n4, imag(ddc_output_p125_band0), 'blue');

ddc_output_p125_band1 = (ddc_output_p125_band1 * scale_factor);
n4 = 1:1:length(ddc_output_p125_band1);
subplot(7, 2, 8); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to p125-gsps");
stem(n4, real(ddc_output_p125_band1), 'red');
stem(n4, imag(ddc_output_p125_band1), 'blue');

% now write this to a file
ddc_output_p125_real_band0 = dec2hex(real(ddc_output_p125_band0), 4);
ddc_output_p125_imag_band0 = dec2hex(imag(ddc_output_p125_band0), 4);
band0_output_p125 = strcat(ddc_output_p125_real_band0, ddc_output_p125_imag_band0);
fileId = fopen("output_samples/demodulation/2g/band0_dual_band_demodulation_p125.txt", "w");
for i = 1:length(band0_output_p125)
    nbytes = fprintf(fileId, '%8s\n', band0_output_p125(i,:));
end
fclose(fileId);

ddc_output_p125_real_band1 = dec2hex(real(ddc_output_p125_band1), 4);
ddc_output_p125_imag_band1 = dec2hex(imag(ddc_output_p125_band1), 4);
band1_output_p125 = strcat(ddc_output_p125_real_band1, ddc_output_p125_imag_band1);
fileId = fopen("output_samples/demodulation/2g/band1_dual_band_demodulation_p125.txt", "w");
for i = 1:length(band1_output_p125)
    nbytes = fprintf(fileId, '%8s\n', band1_output_p125(i,:));
end
fclose(fileId);

% now do the downconversion to p25
config.vha_hbf_stages = [1 1 1 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p25_band0 = vha_decimate(demod_output_2g_band0, config);
ddc_output_p25_band1 = vha_decimate(demod_output_2g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p25_band0 = (ddc_output_p25_band0 * scale_factor);
n4 = 1:1:length(ddc_output_p25_band0);
subplot(7, 2, 9); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to p25-gsps");
stem(n4, real(ddc_output_p25_band0), 'red');
stem(n4, imag(ddc_output_p25_band0), 'blue');

ddc_output_p25_band1 = (ddc_output_p25_band1 * scale_factor);
n4 = 1:1:length(ddc_output_p25_band1);
subplot(7, 2, 10); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to p25-gsps");
stem(n4, real(ddc_output_p25_band1), 'red');
stem(n4, imag(ddc_output_p25_band1), 'blue');

% now write this to a file
ddc_output_p25_real_band0 = dec2hex(real(ddc_output_p25_band0), 4);
ddc_output_p25_imag_band0 = dec2hex(imag(ddc_output_p25_band0), 4);
band0_output_p25 = strcat(ddc_output_p25_real_band0, ddc_output_p25_imag_band0);
fileId = fopen("output_samples/demodulation/2g/band0_dual_band_demodulation_p25.txt", "w");
for i = 1:length(band0_output_p25)
    nbytes = fprintf(fileId, '%8s\n', band0_output_p25(i,:));
end
fclose(fileId);

ddc_output_p25_real_band1 = dec2hex(real(ddc_output_p25_band1), 4);
ddc_output_p25_imag_band1 = dec2hex(imag(ddc_output_p25_band1), 4);
band1_output_p25 = strcat(ddc_output_p25_real_band1, ddc_output_p25_imag_band1);
fileId = fopen("output_samples/demodulation/2g/band1_dual_band_demodulation_p25.txt", "w");
for i = 1:length(band1_output_p25)
    nbytes = fprintf(fileId, '%8s\n', band1_output_p25(i,:));
end
fclose(fileId);

% now do the downconversion to p5
config.vha_hbf_stages = [1 1 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p5_band0 = vha_decimate(demod_output_2g_band0, config);
ddc_output_p5_band1 = vha_decimate(demod_output_2g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p5_band0 = (ddc_output_p5_band0 * scale_factor);
n4 = 1:1:length(ddc_output_p5_band0);
subplot(7, 2, 11); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to p5-gsps");
stem(n4, real(ddc_output_p5_band0), 'red');
stem(n4, imag(ddc_output_p5_band0), 'blue');

ddc_output_p5_band1 = (ddc_output_p5_band1 * scale_factor);
n4 = 1:1:length(ddc_output_p5_band1);
subplot(7, 2, 12); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to p5-gsps");
stem(n4, real(ddc_output_p5_band1), 'red');
stem(n4, imag(ddc_output_p5_band1), 'blue');

% now write this to a file
ddc_output_p5_real_band0 = dec2hex(real(ddc_output_p5_band0), 4);
ddc_output_p5_imag_band0 = dec2hex(imag(ddc_output_p5_band0), 4);
band0_output_p5 = strcat(ddc_output_p5_real_band0, ddc_output_p5_imag_band0);
fileId = fopen("output_samples/demodulation/2g/band0_dual_band_demodulation_p5.txt", "w");
for i = 1:length(band0_output_p5)
    nbytes = fprintf(fileId, '%8s\n', band0_output_p5(i,:));
end
fclose(fileId);

ddc_output_p5_real_band1 = dec2hex(real(ddc_output_p5_band1), 4);
ddc_output_p5_imag_band1 = dec2hex(imag(ddc_output_p5_band1), 4);
band1_output_p5 = strcat(ddc_output_p5_real_band1, ddc_output_p5_imag_band1);
fileId = fopen("output_samples/demodulation/2g/band1_dual_band_demodulation_p5.txt", "w");
for i = 1:length(band1_output_p5)
    nbytes = fprintf(fileId, '%8s\n', band1_output_p5(i,:));
end
fclose(fileId);


% now do the downconversion to 1g
config.vha_hbf_stages = [1 0 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_1g_band0 = vha_decimate(demod_output_2g_band0, config);
ddc_output_1g_band1 = vha_decimate(demod_output_2g_band1, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_1g_band0 = (ddc_output_1g_band0 * scale_factor);
n4 = 1:1:length(ddc_output_1g_band0);
subplot(7, 2, 13); grid on; hold on;
title("Band0 Output - demodulated, down converted samples to 1gsps");
stem(n4, real(ddc_output_1g_band0), 'red');
stem(n4, imag(ddc_output_1g_band0), 'blue');

ddc_output_1g_band1 = (ddc_output_1g_band1 * scale_factor);
n4 = 1:1:length(ddc_output_1g_band1);
subplot(7, 2, 14); grid on; hold on;
title("Band1 Output - demodulated, down converted samples to 1gsps");
stem(n4, real(ddc_output_1g_band1), 'red');
stem(n4, imag(ddc_output_1g_band1), 'blue');

% now write this to a file
ddc_output_1g_real_band0 = dec2hex(real(ddc_output_1g_band0), 4);
ddc_output_1g_imag_band0 = dec2hex(imag(ddc_output_1g_band0), 4);
band0_output_1g = strcat(ddc_output_1g_real_band0, ddc_output_1g_imag_band0);
fileId = fopen("output_samples/demodulation/2g/band0_dual_band_demodulation_1.txt", "w");
for i = 1:length(band0_output_1g)
    nbytes = fprintf(fileId, '%8s\n', band0_output_1g(i,:));
end
fclose(fileId);

ddc_output_1g_real_band1 = dec2hex(real(ddc_output_1g_band1), 4);
ddc_output_1g_imag_band1 = dec2hex(imag(ddc_output_1g_band1), 4);
band1_output_1g = strcat(ddc_output_1g_real_band1, ddc_output_1g_imag_band1);
fileId = fopen("output_samples/demodulation/2g/band1_dual_band_demodulation_1.txt", "w");
for i = 1:length(band1_output_1g)
    nbytes = fprintf(fileId, '%8s\n', band1_output_1g(i,:));
end
fclose(fileId);

