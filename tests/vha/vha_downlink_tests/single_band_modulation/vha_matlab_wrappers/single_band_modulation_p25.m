% This program is to generate an input and output sample files for VHA
% single band Modulation testing at p25 gsps
clc;
clear;
close all;

num_vectors = 4;
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

for i = 1:num_samples
    input_iq (i) = i;        % ramp
end

n1 = 1:1:num_samples;
subplot(4, 3, 2); grid on; hold on;
stem(n1, input_iq, 'green'); title("Input IQ samples @p25");

% write this into a file which can be sourced while running on FRIO
fileId = fopen("input_samples/modulation/single_band_modulation_p25.txt", "w");
fprintf(fileId, "%08x\n", bitshift(input_iq, 16));
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_to_duc = (input_iq * scale_factor);

% enable w1, w2
config.vha_hbf_stages = [1 1 0 0];

% now do an interpolation
output_iq_from_duc = vha_interpolate(input_iq_to_duc, config);

% now scale the samples up
scale_factor = 2^15;
n2 = 1:1:(numel(output_iq_from_duc));
subplot(4, 3, 4); grid on; hold on;
stem(n2, (real(output_iq_from_duc * scale_factor)), 'red'); title("DUC output 1Gsps");
stem(n2, (imag(output_iq_from_duc * scale_factor)), 'blue'); title("DUC output 1Gsps");

% generate cw0 for the modulation freq = 500Mhz, Fs = 1Ghz, Fclk = 1Ghz, #sample = 512
Fclk = 983040;
Fs   = 983040;
freq = (Fclk / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 1);
subplot(4, 3, 7); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0 + 1");
stem(n3, imag(cw0), 'blue');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_1g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
mod_output_1g = mod_output_1g * scale_factor;    % scale up the final output

n2 = 1:1:length(mod_output_1g);
subplot(4, 3, 10); grid on; hold on;
stem(n2, real(mod_output_1g), 'red'); title ("Output - 1Gsps Modulation");
stem(n2, imag(mod_output_1g), 'blue');
mod_output_1g_real = dec2hex(real(mod_output_1g), 4);
mod_output_1g_imag = dec2hex(imag(mod_output_1g), 4);
output_1g = strcat(mod_output_1g_real, mod_output_1g_imag);
fileId = fopen("output_samples/modulation/p25/single_band_modulation_1.txt", "w");
for i = 1:length(output_1g)
   nbytes = fprintf(fileId,'%8s\n',output_1g(i,:));
end
fclose(fileId);

% enable w1, w2, w3
config.vha_hbf_stages = [1 1 1 0];

% now do an interpolation
output_iq_from_duc = vha_interpolate(input_iq_to_duc, config);

% now scale the samples up
n2 = 1:1:(numel(output_iq_from_duc));
subplot(4, 3, 5); grid on; hold on;
stem(n2, (real(output_iq_from_duc * scale_factor)), 'red'); title("DUC output 2Gsps");
stem(n2, (imag(output_iq_from_duc * scale_factor)), 'blue'); title("DUC output 2Gsps");

% generate cw0 for the modulation freq = 500Mhz, Fs = 2Ghz, Fclk = 1Ghz, #sample = 512
Fs   = 983040 * 2;
freq = (Fclk / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 0);
subplot(4, 3, 8); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0 + 0");
stem(n3, imag(cw0), 'blue');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_2g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
mod_output_2g = mod_output_2g * scale_factor;    % scale up the final output

n2 = 1:1:length(mod_output_2g);
subplot(4, 3, 11); grid on; hold on;
stem(n2, real(mod_output_2g), 'red'); title ("Output - 2gsps Modulation");
stem(n2, imag(mod_output_2g), 'blue');
mod_output_2g_real = dec2hex(real(mod_output_2g),4);
mod_output_2g_imag = dec2hex(imag(mod_output_2g),4);
output_2g = strcat(mod_output_2g_real, mod_output_2g_imag);
fileId = fopen("output_samples/modulation/p25/single_band_modulation_2.txt", "w");
for i = 1:length(output_2g)
   nbytes = fprintf(fileId,'%8s\n',output_2g(i,:));
end
fclose(fileId);

% enable w1, w2, w3, w4
config.vha_hbf_stages = [1 1 1 1];

% now do an interpolation
output_iq_from_duc = vha_interpolate(input_iq_to_duc, config);

% now scale the samples up
n2 = 1:1:(numel(output_iq_from_duc));
subplot(4, 3, 6); grid on; hold on;
stem(n2, (real(output_iq_from_duc * scale_factor)), 'red'); title("DUC output 4Gsps");
stem(n2, (imag(output_iq_from_duc * scale_factor)), 'blue'); title("DUC output 4Gsps");

% generate cw0 for the modulation freq = 500Mhz, Fs = 4Ghz, Fclk = 1Ghz, #sample = 512
Fs   = 983040 * 4;
freq = (Fclk / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 1);
subplot(4, 3, 9); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0 + 1");
stem(n3, imag(cw0), 'blue');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_4g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
mod_output_4g = mod_output_4g * scale_factor;

n2 = 1:1:length(mod_output_4g);
subplot(4, 3, 12); grid on; hold on;
stem(n2, real(mod_output_4g), 'red'); title("Output - 4gsps Modulation");
stem(n2, imag(mod_output_4g), 'blue');
mod_output_4g_real = dec2hex(real(mod_output_4g), 4);
mod_output_4g_imag = dec2hex(imag(mod_output_4g), 4);
output_4g = strcat(mod_output_4g_real, mod_output_4g_imag);
fileId = fopen("output_samples/modulation/p25/single_band_modulation_4.txt", "w");
for i = 1:length(output_4g)
   nbytes = fprintf(fileId,'%8s\n',output_4g(i,:));
end
fclose(fileId);
