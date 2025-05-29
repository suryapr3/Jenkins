% This program is to generate an input and output sample files for VHA
 % single band Modulation testing at 1.5Gsps
clc;
clear;
close all;

num_vectors = 24;
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

for i = 1:num_samples
    input_iq (i) = 1;        % dc
end

n1 = 1:1:num_samples;
subplot(4, 2, 1); grid on; hold on;
stem(n1, input_iq, 'green'); title("Input IQ samples @1.5G");

% write this into a file which can be sourced while running on FRIO
fileId = fopen("input_samples/modulation/single_band_modulation_1p5.txt", "w");
fprintf(fileId, "%08x\n", bitshift(input_iq, 16));
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_to_duc = (input_iq * scale_factor);

% enable w1
config.vha_hbf_stages = [1 0 0 0];

% now do an interpolation
output_iq_from_duc = vha_interpolate(input_iq_to_duc, config);

% now scale the samples up
scale_factor = 2^15;
n2 = 1:1:(numel(output_iq_from_duc));
subplot(4, 2, 3); grid on; hold on;
stem(n2, (real(output_iq_from_duc * scale_factor)), 'red'); title("DUC output 3Gsps");
stem(n2, (imag(output_iq_from_duc * scale_factor)), 'blue');

% generate cw0 for the modulation freq = 750Mhz, Fs = 3Ghz, Fclk = 1.5Ghz
Fclk = 983040;
Fs   = 983040 * 2;
freq = (Fclk / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 0);
subplot(4, 2, 5); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0 + 0");
stem(n3, imag(cw0), 'blue');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_3g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
mod_output_3g = mod_output_3g * scale_factor;    % scale up the final output

n2 = 1:1:length(mod_output_3g);
subplot(4, 2, 7); grid on; hold on;
stem(n2, real(mod_output_3g), 'red'); title ("Output - 3Gsps Modulation");
stem(n2, imag(mod_output_3g), 'blue');
mod_output_3g_real = dec2hex(real(mod_output_3g),4);
mod_output_3g_imag = dec2hex(imag(mod_output_3g),4);
output_3g = strcat(mod_output_3g_real, mod_output_3g_imag);
fileId = fopen("output_samples/modulation/1p5/single_band_modulation_3.txt", "w");
for i = 1:length(output_3g)
   nbytes = fprintf(fileId,'%8s\n',output_3g(i,:));
end
fclose(fileId);

% enable w1, w2
config.vha_hbf_stages = [1 1 0 0];

% now do an interpolation
output_iq_from_duc = vha_interpolate(input_iq_to_duc, config);

% now scale the samples up
n2 = 1:1:(numel(output_iq_from_duc));
subplot(4, 2, 4); grid on; hold on;
stem(n2, (real(output_iq_from_duc * scale_factor)), 'red'); title("DUC output 6Gsps");
stem(n2, (imag(output_iq_from_duc * scale_factor)), 'blue'); title("DUC output 6Gsps");

% generate cw0 for the modulation freq = 750Mhz, Fs = 6Ghz, Fclk = 1.5Ghz, #sample = 512
Fs   = 983040 * 4;
freq = (Fclk / 2);
fprintf("freq = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", freq, Fs, Fclk);
cw0 = nco_pp(freq, Fs, Fclk, length(output_iq_from_duc), 1);
subplot(4, 2, 6); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0 + 1");
stem(n3, imag(cw0), 'blue');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 1;
cw0 = transpose(cw0);
[mod_output_6g, dummy] = vha_combine(output_iq_from_duc, 0, cw0, 0, config);
mod_output_6g = mod_output_6g * scale_factor;

n2 = 1:1:length(mod_output_6g);
subplot(4, 2, 8); grid on; hold on;
stem(n2, real(mod_output_6g), 'red'); title("Output - 6Gsps Modulation");
stem(n2, imag(mod_output_6g), 'blue');
mod_output_6g_real = dec2hex(real(mod_output_6g), 4);
mod_output_6g_imag = dec2hex(imag(mod_output_6g), 4);
output_6g = strcat(mod_output_6g_real, mod_output_6g_imag);
fileId = fopen("output_samples/modulation/1p5/single_band_modulation_6.txt", "w");
for i = 1:length(output_6g)
   nbytes = fprintf(fileId,'%8s\n',output_6g(i,:));
end
fclose(fileId);
