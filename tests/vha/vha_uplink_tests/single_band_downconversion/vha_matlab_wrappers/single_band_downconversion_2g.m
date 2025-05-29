% This program is to generate an input and output sample file for VHA DDC
% testing at 2gsps

clc;
clear;
close all;

num_vectors = 32;
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

for i = 1:num_samples
    input_iq (i) = i;        % ramp
end

n1 = 1:1:num_samples;
subplot(6,1,1); grid on;
stem(n1, input_iq); title("Input IQ samples @2G");

% write this into a file which can be sourced while running on FRIO
fileId = fopen("input_samples/downconversion/single_band_downconversion_2.txt", "w");
fprintf(fileId, "%08x\n", input_iq);
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_for_model = (input_iq * scale_factor);

% no filters enabled
config.vha_hbf_stages = [0 0 0 0];
config.agc_bit = 0;
config.format = 0;
config.fine_delay = 0;
config.coarse_delay = 0;

% now do an decimation
output_iq_from_model_2 = vha_decimate(input_iq_for_model, config);

% now scale the samples up
scale_factor = 2^15;
output_iq_2 = (output_iq_from_model_2 * scale_factor);

n2 = 1:1:length(output_iq_2);
subplot(6, 1, 2); grid on;
stem(n2, output_iq_2);  title ("Output - No filters enabled");

% write this output to another file
fileId = fopen("output_samples/downconversion/2g/single_band_downconversion_2.txt", "w");
fprintf(fileId, "%08x\n", output_iq_2);
fclose(fileId);

% enable w1
config.vha_hbf_stages = [1 0 0 0];

% now do an decimation
output_iq_from_model_1 = vha_decimate(input_iq_for_model, config);

% now scale the samples up
output_iq_1 = (output_iq_from_model_1 * scale_factor);

n2 = 1:1:length(output_iq_1);
subplot(6, 1, 3); grid on;
stem(n2, output_iq_1); title ("Output - W1 enabled");
fileId = fopen("output_samples/downconversion/2g/single_band_downconversion_1.txt", "w");
fprintf(fileId, "%08x\n", output_iq_1);
fclose(fileId);

% enable w1, w2
config.vha_hbf_stages = [1 1 0 0];

% now do an decimation
output_iq_from_model_p5 = vha_decimate(input_iq_for_model, config);

% now scale the samples up
output_iq_p5 = (output_iq_from_model_p5 * scale_factor);

n2 = 1:1:length(output_iq_p5);
subplot(6, 1, 4); grid on;
stem(n2, output_iq_p5);title ("Output - W1, W2 enabled");
fileId = fopen("output_samples/downconversion/2g/single_band_downconversion_p5.txt", "w");
fprintf(fileId, "%08x\n", output_iq_p5);
fclose(fileId);

% enable w1, w2, w3
config.vha_hbf_stages = [1 1 1 0];

% now do an decimation
output_iq_from_model_p25 = vha_decimate(input_iq_for_model, config);

% now scale the samples up
output_iq_p25 = (output_iq_from_model_p25 * scale_factor);

n2 = 1:1:length(output_iq_p25);
subplot(6, 1, 5); grid on;
stem(n2, output_iq_p25);title ("Output - W1, W2, W3 enabled");
fileId = fopen("output_samples/downconversion/2g/single_band_downconversion_p25.txt", "w");
fprintf(fileId, "%08x\n", output_iq_p25);
fclose(fileId);

% enable w1, w2, w3, w4
config.vha_hbf_stages = [1 1 1 1];

% now do an decimation
output_iq_from_model_p125 = vha_decimate(input_iq_for_model, config);

% now scale the samples up
output_iq_p125 = (output_iq_from_model_p125 * scale_factor);

n2 = 1:1:length(output_iq_p125);
subplot(6, 1, 6); grid on;
stem(n2, output_iq_p125);title ("Output - W1, W2, W3, W4 enabled");
fileId = fopen("output_samples/downconversion/2g/single_band_downconversion_p125.txt", "w");
for i = 1 : length(output_iq_p125)
    output_iq_p125_hex = dec2hex(output_iq_p125(i), 4);
    fprintf(fileId, "0000%s\n", output_iq_p125_hex);
end
fclose(fileId);

clear;
