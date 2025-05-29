% This program is to generate an input and output sample file for VHA
% single band demodulation testing at  3gsps
clc;
clear;
close all;

% First generate an upconverted modulated output (3gsps), which can later be
% given as the input to the uplink path
num_vectors = 3;
num_samples_per_vector = 32;
num_samples = (num_vectors * num_samples_per_vector);

for i = 1:num_samples
    input_iq (i) = i;        % ramp
end

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_to_duc = (input_iq * scale_factor);

% enable w1, w2, w3, w4
config.vha_hbf_stages = [1 1 1 1];

% now do an interpolation
output_iq_from_duc = vha_interpolate(input_iq_to_duc, config);

% generate cw0 for the modulation
% Fs = 2Ghz, Fclk = 1Ghz, freq = (Fs / 2)
Fclk = 1474000;
Fs   = 1474000 * 2;
freq = (Fs / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 0);   % 0 clk cycles delay

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_3g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
scale_factor = 2^15;
mod_output_3g = (mod_output_3g * scale_factor);    % scale up the final output

% use this modulated upconverted signal as the input to the uplink path.
% first demodulate this input with a carrier wave and then downconvert to
% the required output rate
input_iq = mod_output_3g;
num_vectors = 48;                      % 3gsps
num_samples_per_vector = 32;
num_samples = (num_vectors * num_samples_per_vector);

n1 = 1:1:num_samples;
subplot(4, 2, 1); grid on; hold on;
stem(n1, real(input_iq), 'green'); title("Input IQ samples @3g");
stem(n1, imag(input_iq), 'blue');

% write this into a file which can be sourced while running on FRIO
input_real = dec2hex(real(input_iq), 4);
input_imag = dec2hex(imag(input_iq), 4);
input_3g = strcat(input_real, input_imag);
fileId = fopen("input_samples/demodulation/single_band_demodulation_3.txt", "w");
for i = 1:length(input_3g)
    nbytes = fprintf(fileId, '%8s\n', input_3g(i,:));
end
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_for_model = (input_iq * scale_factor);

% now generate the CW for demodulation
% Fclk = 1GHz, Fs = 2Gsps, freq = (Fs / 2)
Fclk = 1474000;
Fs   = 1474000 * 2;
freq = (Fs / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw2 = nco_pp(freq, Fs, Fclk, length(input_iq), 0);
subplot(4, 2, 3); grid on; hold on;
n2 = 1:1:length(cw2);
stem(n2, real(cw2), 'red'); title("CW2");
stem(n2, imag(cw2), 'blue');

% now do the demodulation and band splitting
config.vha_bypass = [0 0];
config.vha_conj = [0 0];
cw2 = transpose(cw2);
demod_output_3g = vha_split(input_iq_for_model, cw2, config);
n3 = 1:1:length(demod_output_3g);
subplot(4, 2, 5); grid on; hold on;
stem(n3, real(demod_output_3g), 'red'); title("Output - 3gsps Demodulation");
stem(n3, imag(demod_output_3g), 'blue');

% now do the downconversion to p187
config.vha_hbf_stages = [1 1 1 1];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p187 = vha_decimate(demod_output_3g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p187 = (ddc_output_p187 * scale_factor);
n4 = 1:1:length(ddc_output_p187);
subplot(4, 2, 2); grid on; hold on;
title("Output - demodulated, down converted samples to p187-gsps");
stem(n4, real(ddc_output_p187), 'red');
stem(n4, imag(ddc_output_p187), 'blue');

% now write this to a file
ddc_output_p187_real = dec2hex(real(ddc_output_p187), 4);
ddc_output_p187_imag = dec2hex(imag(ddc_output_p187), 4);
output_p187 = strcat(ddc_output_p187_real, ddc_output_p187_imag);
fileId = fopen("output_samples/demodulation/3g/single_band_demodulation_p187.txt", "w");
for i = 1:length(output_p187)
    nbytes = fprintf(fileId, '%8s\n', output_p187(i,:));
end
fclose(fileId);

% now do the downconversion to p375
config.vha_hbf_stages = [1 1 1 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p375 = vha_decimate(demod_output_3g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p375 = (ddc_output_p375 * scale_factor);
n4 = 1:1:length(ddc_output_p375);
subplot(4, 2, 4); grid on; hold on;
title("Output - demodulated, down converted samples to p375-gsps");
stem(n4, real(ddc_output_p375), 'red');
stem(n4, imag(ddc_output_p375), 'blue');

% now write this to a file
ddc_output_p375_real = dec2hex(real(ddc_output_p375), 4);
ddc_output_p375_imag = dec2hex(imag(ddc_output_p375), 4);
output_p375 = strcat(ddc_output_p375_real, ddc_output_p375_imag);
fileId = fopen("output_samples/demodulation/3g/single_band_demodulation_p375.txt", "w");
for i = 1:length(output_p375)
    nbytes = fprintf(fileId, '%8s\n', output_p375(i,:));
end
fclose(fileId);

% now do the downconversion to p75
config.vha_hbf_stages = [1 1 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p75 = vha_decimate(demod_output_3g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p75 = (ddc_output_p75 * scale_factor);
n4 = 1:1:length(ddc_output_p75);
subplot(4, 2, 6); grid on; hold on;
title("Output - demodulated, down converted samples to p75-gsps");
stem(n4, real(ddc_output_p75), 'red');
stem(n4, imag(ddc_output_p75), 'blue');

% now write this to a file
ddc_output_p75_real = dec2hex(real(ddc_output_p75), 4);
ddc_output_p75_imag = dec2hex(imag(ddc_output_p75), 4);
output_p75 = strcat(ddc_output_p75_real, ddc_output_p75_imag);
fileId = fopen("output_samples/demodulation/3g/single_band_demodulation_p75.txt", "w");
for i = 1:length(output_p75)
    nbytes = fprintf(fileId, '%8s\n', output_p75(i,:));
end
fclose(fileId);

% now do the downconversion to 1g
config.vha_hbf_stages = [1 0 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_1p5 = vha_decimate(demod_output_3g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_1p5 = (ddc_output_1p5 * scale_factor);
n4 = 1:1:length(ddc_output_1p5);
subplot(4, 2, 8); grid on; hold on;
title("Output - demodulated, down converted samples to 1-gsps");
stem(n4, real(ddc_output_1p5), 'red');
stem(n4, imag(ddc_output_1p5), 'blue');

% now write this to a file
ddc_output_1p5_real = dec2hex(real(ddc_output_1p5), 4);
ddc_output_1p5_imag = dec2hex(imag(ddc_output_1p5), 4);
output_1p5 = strcat(ddc_output_1p5_real, ddc_output_1p5_imag);
fileId = fopen("output_samples/demodulation/3g/single_band_demodulation_1p5.txt", "w");
for i = 1:length(output_1p5)
    nbytes = fprintf(fileId, '%8s\n', output_1p5(i,:));
end
fclose(fileId);


% end of file
