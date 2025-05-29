% This program is to generate an input and output sample file for VHA
% single band demodulation testing at 4Gsps
clc;
clear;
close all;

% First generate an upconverted modulated output (4gsps), which can later be
% given as the input to the uplink path
num_vectors = 4;                       % say p25
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

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

% generate cw0 for the modulation freq = (Fs / 2), Fs = 4Ghz, Fclk = 1Ghz
Fclk = 983040;
Fs   = 983040 * 4;
freq = (Fs / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 1);   % 1 clk cycles delay

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_4g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
scale_factor = 2^15;
mod_output_4g = mod_output_4g * scale_factor;    % scale up the final output

% use this modulated upconverted signal as the input to the uplink path.
% first demodulate this input with a carrier wave and then downconvert to
% the required output rate
input_iq = mod_output_4g;
num_vectors = 64;                      % 4Gsps
num_samples_per_vector = 32;
num_samples = (num_vectors * num_samples_per_vector);

n1 = 1:1:num_samples;
subplot(4, 3, 2); grid on; hold on;
stem(n1, real(input_iq), 'green'); title("Input IQ samples @4g");
stem(n1, imag(input_iq), 'blue');

% write this into a file which can be sourced while running on FRIO
input_real = dec2hex(real(input_iq), 4);
input_imag = dec2hex(imag(input_iq), 4);
input_4g = strcat(input_real, input_imag);
fileId = fopen("input_samples/demodulation/single_band_demodulation_4.txt", "w");
for i = 1:length(input_4g)
    nbytes = fprintf(fileId, '%8s\n', input_4g(i,:));
end
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_for_model = (input_iq * scale_factor);

% now generate the CW for demodulation
% Fclk = 1GHz, Fs = 4Gsps, freq = (Fs / 2)
Fclk = 983040;
Fs   = (983040 * 4);
freq = (Fs / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw2 = nco_pp(freq, Fs, Fclk, length(input_iq), 1);
subplot(4, 3, 5); grid on; hold on;
n2 = 1:1:length(cw2);
stem(n2, real(cw2), 'red'); title("CW2");
stem(n2, imag(cw2), 'blue');

% now do the demodulation and band splitting
config.vha_bypass = [0 0];
config.vha_conj = [0 0];
cw2 = transpose(cw2);
demod_output_4g = vha_split(input_iq_for_model, cw2, config);
n3 = 1:1:length(demod_output_4g);
subplot(4, 3, 8); grid on; hold on;
stem(n3, real(demod_output_4g), 'red'); title("Output - 4gsps Demodulation");
stem(n3, imag(demod_output_4g), 'blue');

% now do the downconversion to p25
config.vha_hbf_stages = [1 1 1 1];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p25 = vha_decimate(demod_output_4g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p25 = (ddc_output_p25 * scale_factor);
n4 = 1:1:length(ddc_output_p25);
subplot(4, 3, 10); grid on; hold on;
title("Output - demodulated, down converted samples to p25-gsps");
stem(n4, real(ddc_output_p25), 'red');
stem(n4, imag(ddc_output_p25), 'blue');

% now write this to a file
ddc_output_p25_real = dec2hex(real(ddc_output_p25), 4);
ddc_output_p25_imag = dec2hex(imag(ddc_output_p25), 4);
output_p25 = strcat(ddc_output_p25_real, ddc_output_p25_imag);
fileId = fopen("output_samples/demodulation/4g/single_band_demodulation_p25.txt", "w");
for i = 1:length(output_p25)
    nbytes = fprintf(fileId, '%8s\n', output_p25(i,:));
end
fclose(fileId);

% now do the downconversion to p5
config.vha_hbf_stages = [1 1 1 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_p5 = vha_decimate(demod_output_4g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_p5 = (ddc_output_p5 * scale_factor);
n4 = 1:1:length(ddc_output_p5);
subplot(4, 3, 11); grid on; hold on;
title("Output - demodulated, down converted samples to p5-gsps");
stem(n4, real(ddc_output_p5), 'red');
stem(n4, imag(ddc_output_p5), 'blue');

% now write this to a file
ddc_output_p5_real = dec2hex(real(ddc_output_p5), 4);
ddc_output_p5_imag = dec2hex(imag(ddc_output_p5), 4);
output_p5 = strcat(ddc_output_p5_real, ddc_output_p5_imag);
fileId = fopen("output_samples/demodulation/4g/single_band_demodulation_p5.txt", "w");
for i = 1:length(output_p5)
    nbytes = fprintf(fileId, '%8s\n', output_p5(i,:));
end
fclose(fileId);

% now do the downconversion to 1
config.vha_hbf_stages = [1 1 0 0];
config.vha_agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;
ddc_output_1 = vha_decimate(demod_output_4g, config);

% now scale the samples up
scale_factor = 2^15;
ddc_output_1 = (ddc_output_1 * scale_factor);
n4 = 1:1:length(ddc_output_1);
subplot(4, 3, 12); grid on; hold on;
title("Output - demodulated, down converted samples to 1-gsps");
stem(n4, real(ddc_output_1), 'red');
stem(n4, imag(ddc_output_1), 'blue');

% now write this to a file
ddc_output_1_real = dec2hex(real(ddc_output_1), 4);
ddc_output_1_imag = dec2hex(imag(ddc_output_1), 4);
output_1 = strcat(ddc_output_1_real, ddc_output_1_imag);
fileId = fopen("output_samples/demodulation/4g/single_band_demodulation_1.txt", "w");
for i = 1:length(output_1)
    nbytes = fprintf(fileId, '%8s\n', output_1(i,:));
end
fclose(fileId);


% end of file
