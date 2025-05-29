% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Project     : ABC
% Author      : Hari (haridas.p@intel.com)
% Date        : 20 Mar 2024
% Brief       : This program is to generate input and output sample files for VHA
%               dual band modulation testing at 1.5Gsps
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc;
clear;
close all;

num_vectors = 24;
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

for i = 1:num_samples
    band0_input_iq(i) = i;        % ramp
end
fs = num_samples;
dt = 1/fs;
st = 1;
t = 0:dt:st-dt;
band1_input_iq1 = 50 * (1 + sin(2 * pi * t));
band1_input_iq = int32(band1_input_iq1);

figure('Name', 'Modulation');
n1 = 1:1:num_samples;
subplot(5, 2, 1); grid on; hold on;
stem(n1, band0_input_iq, 'green'); title("Band0 Input IQ samples @1.5G");
subplot(5, 2, 2); grid on; hold on;
stem(n1, band1_input_iq, 'green'); title("Band1 Input IQ samples @1.5G");

% write this into a file which can be sourced while running on FRIO
fileId = fopen("input_samples/modulation/band0_dual_band_modulation_1p5.txt", "w");
fprintf(fileId, "%08x\n", bitshift(band0_input_iq, 16));
fclose(fileId);
fileId = fopen("input_samples/modulation/band1_dual_band_modulation_1p5.txt", "w");
fprintf(fileId, "%08x\n", bitshift(band1_input_iq, 16));
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
band0_input_iq_to_duc = (band0_input_iq * scale_factor);
band1_input_iq_to_duc = (band1_input_iq1 * scale_factor);

% enable w1
config.vha_hbf_stages = [1 0 0 0];

% now do an interpolation
band0_output_iq_from_duc = vha_interpolate(band0_input_iq_to_duc, config);
band1_output_iq_from_duc = vha_interpolate(band1_input_iq_to_duc, config);

% now scale the samples up
scale_factor = 2^15;
n2 = 1:1:(numel(band0_output_iq_from_duc));
subplot(5, 2, 3); grid on; hold on;
stem(n2, (real(band0_output_iq_from_duc * scale_factor)), 'red'); title("DUC band0 Output 3Gsps");
stem(n2, (imag(band0_output_iq_from_duc * scale_factor)), 'blue');
n2 = 1:1:(numel(band1_output_iq_from_duc));
subplot(5, 2, 4); grid on; hold on;
stem(n2, (real(band1_output_iq_from_duc * scale_factor)), 'red'); title("DUC band1 Output 3Gsps");
stem(n2, (imag(band1_output_iq_from_duc * scale_factor)), 'blue');

% generate cw0 and cw1 for the modulation
Fclk = 1474000;
Fs   = 1474000 * 2;
fout0 = (Fclk / 2);
fprintf("3GSPS Modulation\n");
fprintf("fout0 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout0, Fs, Fclk);
cw0 = nco_pp(fout0, Fs, Fclk, length(band0_output_iq_from_duc), 0);   % 0 clk cycle delay
fout1 = (Fclk / 4);
fprintf("fout1 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout1, Fs, Fclk);
cw1 = nco_pp(fout1, Fs, Fclk, length(band1_output_iq_from_duc), 0);   % 0 clk cycles delay
subplot(5, 2, 5); grid on; hold on;
n3 = 1:1:(length(cw0));
stem(n3, real(cw0), 'red'); title("CW0");
stem(n3, imag(cw0), 'blue');
stem(n3, real(cw1), 'black');
stem(n3, imag(cw1), 'green');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 3;
cw0 = transpose(cw0);
cw1 = transpose(cw1);
[mod_output_3g, dummy] = vha_combine(band0_output_iq_from_duc, band1_output_iq_from_duc, cw0, cw1, config);
mod_output_3g = mod_output_3g * scale_factor;    % scale up the final output

n2 = 1:1:length(mod_output_3g);
subplot(5, 2, 6); grid on; hold on;
stem(n2, real(mod_output_3g), 'red'); title ("Output - 3Gsps Modulation");
stem(n2, imag(mod_output_3g), 'blue');
mod_output_3g_real = dec2hex(real(mod_output_3g), 4);
mod_output_3g_imag = dec2hex(imag(mod_output_3g), 4);
output_3g = strcat(mod_output_3g_real, mod_output_3g_imag);
fileId = fopen("output_samples/modulation/1p5/dual_band_modulation_3.txt", "w");
for i = 1:length(output_3g)
   nbytes = fprintf(fileId,'%8s\n',output_3g(i,:));
end
fclose(fileId);

% enable w1, w2
config.vha_hbf_stages = [1 1 0 0];

% now do an interpolation
band0_output_iq_from_duc = vha_interpolate(band0_input_iq_to_duc, config);
band1_output_iq_from_duc = vha_interpolate(band1_input_iq_to_duc, config);

% now scale the samples up
n2 = 1:1:(numel(band0_output_iq_from_duc));
subplot(5, 2, 7); grid on; hold on;
stem(n2, (real(band0_output_iq_from_duc * scale_factor)), 'red'); title("DUC band0 Output 6Gsps");
stem(n2, (imag(band0_output_iq_from_duc * scale_factor)), 'blue');
n2 = 1:1:(numel(band1_output_iq_from_duc));
subplot(5, 2, 8); grid on; hold on;
stem(n2, (real(band1_output_iq_from_duc * scale_factor)), 'red'); title("DUC band1 Output 6Gsps");
stem(n2, (imag(band1_output_iq_from_duc * scale_factor)), 'blue');

% generate cw0 for the modulation freq = 750Mhz, Fs = 6Ghz, Fclk = 1.5Ghz
Fs   = 1474000 * 4;
fprintf("6GSPS Modulation\n");
fprintf("fout0 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout0, Fs, Fclk);
cw0 = nco_pp(fout0, Fs, Fclk, length(band0_output_iq_from_duc), 1);   % 1 clk cycle delay
fout1 = fout0;
fprintf("fout1 = %d KHz, Fs = %d KHz, Fclk = %d KHz\n", fout1, Fs, Fclk);
cw1 = nco_pp(fout1, Fs, Fclk, length(band1_output_iq_from_duc), 3);   % 3 clk cycles delay
n3 = 1:1:(length(cw0));
subplot(5, 2, 9); grid on; hold on;
stem(n3, real(cw0), 'red'); title("CW0, CW1 @4Gsps");
stem(n3, imag(cw0), 'blue');
stem(n3, real(cw1), 'black');
stem(n3, imag(cw1), 'green');

% now do the modulation and combining
config.vha_bypass = [0 0];
config.vha_conj = [0, 0];
config.active_band = 3;
cw0 = transpose(cw0);
cw1 = transpose(cw1);
[mod_output_6g, dummy] = vha_combine(band0_output_iq_from_duc, band1_output_iq_from_duc, cw0, cw1, config);
mod_output_6g = mod_output_6g * scale_factor;    % scale up the final output

n2 = 1:1:length(mod_output_6g);
subplot(5, 2, 10); grid on; hold on;
stem(n2, real(mod_output_6g), 'red'); title ("Output - 6Gsps Modulation");
stem(n2, imag(mod_output_6g), 'blue');
mod_output_6g_real = dec2hex(real(mod_output_6g), 4);
mod_output_6g_imag = dec2hex(imag(mod_output_6g), 4);
output_6g = strcat(mod_output_6g_real, mod_output_6g_imag);
fileId = fopen("output_samples/modulation/1p5/dual_band_modulation_6.txt", "w");
for i = 1:length(output_6g)
   nbytes = fprintf(fileId,'%8s\n',output_6g(i,:));
end
fclose(fileId);

