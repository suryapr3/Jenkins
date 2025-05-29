function [pdpd_out_i, pdpd_out_q] = pdpd_wrap(term_types, q_dly, m_dly, passthru_dly, ...
         passthru_coeff_i, passthru_coeff_q, nlmag_en, lut_n, lut_c_i, lut_c_q, lut_s, ...
         data_in_i, data_in_q )

  format long
  format compact

  T = 48 ;       % number of terms
  N = 64 ;       % size of LUT
  enQuant = 1 ;  % enable quantization

  termParams = zeros( 48, 3 );
  termParams(1:48, 1) = term_types;
  % Input term types can't be 0; change 0's to 1's
  for i=1:48  
    if termParams(i,1) == 0
      termParams(i,1) = 1;
    end
  end 

  % passthru_dly is no longer used here
  %termParams(1:48, 2) = q_dly(1:48) - passthru_dly;
  %termParams(1:48, 3) = m_dly(1:48) - passthru_dly;
  termParams(1:48, 2) = q_dly(1:48);
  termParams(1:48, 3) = m_dly(1:48);

  termParams

  r = (passthru_coeff_i + 1i*passthru_coeff_q) / 2^13;

  nlmag_en
  lut_n = lut_n / 2^13

  lut_c = (lut_c_i(1:48,1:65) + 1i*lut_c_q(1:48,1:65)) / 2^12;
 
  % Matlab code *multiplies* by 2^shift, so negative numbers correspond
  %  to right shift 
  lut_s = -lut_s
 
  input_data = (data_in_i + 1i*data_in_q) / 2^15;

  %y = hwDpdQuant_v2( termParams, T, N, r, lut_c, lut_s, input_data, enQuant );
  y = hwDpdQuant_v2_nlmag( termParams, T, N, r, nlmag_en, lut_n, lut_c, lut_s, input_data, enQuant );

  pdpd_out = 2^15 * y

  % Note that saturation is needed here to deal with the fact that the
  %  model of just the data path has output sc[16,14], and the actual
  %  output is sc[16,15]

  pdpd_out_i = min( max( real( pdpd_out ), -2^15 ), 2^15-1 );
  pdpd_out_q = min( max( imag( pdpd_out ), -2^15 ), 2^15-1 );

end

