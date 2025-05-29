% This program is to generate an input and output sample file for VHA DUC
% testing at 1.5 gsps
clc;
clear;
close all;

num_vectors = 24;
num_samples_per_vector = 32;
num_samples = num_vectors * num_samples_per_vector;

for i = 1:num_samples
    input_iq (i) = i;        % ramp
end

n1 = 1:1:num_samples;
subplot(6,1,1); grid on;
stem(n1, input_iq); title("Input IQ samples @1.5G");

% write this into a file which can be sourced while running on FRIO
fileId = fopen("input_samples/upconversion/single_band_upconversion_1p5.txt", "w");
fprintf(fileId, "%08x\n", input_iq);
fclose(fileId);

% input_iq should be scaled down before giving as input to the matlab model
scale_factor = 2^-15;
input_iq_for_model = (input_iq * scale_factor);

% no filters enabled
config.vha_hbf_stages = [0 0 0 0];

% now do an interpolation
output_iq_from_model_1p5 = vha_interpolate(input_iq_for_model, config);

% now scale the samples up
scale_factor = 2^15;
output_iq_1p5 = (output_iq_from_model_1p5 * scale_factor);

n2 = 1:1:length(output_iq_1p5);
subplot(6, 1, 2); grid on;
stem(n2, output_iq_1p5);  title ("Output - No filters enabled");

% write this output to another file
fileId = fopen("output_samples/upconversion/1g/single_band_upconversion_1p5.txt", "w");
fprintf(fileId, "%08x\n", output_iq_1p5);
fclose(fileId);

% enable w1
config.vha_hbf_stages = [1 0 0 0];

% now do an interpolation
output_iq_from_model_3 = vha_interpolate(input_iq_for_model, config);

% now scale the samples up
output_iq_3 = (output_iq_from_model_3 * scale_factor);

n2 = 1:1:length(output_iq_3);
subplot(6, 1, 3); grid on;
stem(n2, output_iq_3); title ("Output - W1 enabled");
fileId = fopen("output_samples/upconversion/1g/single_band_upconversion_3.txt", "w");
fprintf(fileId, "%08x\n", output_iq_3);
fclose(fileId);

% enable w1, w2
config.vha_hbf_stages = [1 1 0 0];

% now do an interpolation
output_iq_from_model_6 = vha_interpolate(input_iq_for_model, config);

% now scale the samples up
output_iq_6 = (output_iq_from_model_6 * scale_factor);

n2 = 1:1:length(output_iq_6);
subplot(6, 1, 4); grid on;
stem(n2, output_iq_6);title ("Output - W1, W2 enabled");
fileId = fopen("output_samples/upconversion/1g/single_band_upconversion_6.txt", "w");
fprintf(fileId, "%08x\n", output_iq_6);
fclose(fileId);

clear;
