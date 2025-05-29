function [pdpd_out_i, pdpd_out_q] = pdpd_wrap(term_types, q_dly, m_dly, passthru_dly, ...
         passthru_coeff_i, passthru_coeff_q, nlmag_en, clut_segments, lut_n, lut_c_i, lut_c_q, lut_s, ...
         data_in_i, data_in_q, xtra_in_i, xtra_in_q, xtra_dly, frac_os, post_c )

  format long
  format compact

  T = 48 ;       % number of terms
  N = 64 ;       % size of LUT
  if clut_segments==1
    N = 32;
  end
  enQuant = 1 ;  % enable quantization

  termParams = zeros( T, 3 );
  termParams(1:T, 1) = term_types;
  % Input term types can't be 0; change 0's to 1's
  for i=1:T  
    if termParams(i,1) == 0
      termParams(i,1) = 1;
    end
  end 

  %termParams(1:T, 2) = q_dly(1:T) - passthru_dly;
  %termParams(1:T, 3) = m_dly(1:T) - passthru_dly;
  termParams(1:T, 2) = q_dly(1:T);
  termParams(1:T, 3) = m_dly(1:T);

  termParams;

  r = (passthru_coeff_i + 1i*passthru_coeff_q) / 2^13;

  nlmag_en;
  lut_n = lut_n / 2^13;

  lut_c = (lut_c_i(1:T,1:N+1) + 1i*lut_c_q(1:T,1:N+1)) / 2^12;
  %lut_d = (lut_c_i(:,2:N+1) + 1i*lut_c_q(:,2:N+1)) / 2^12;
  lut_d = lut_c(1:T,2:N+1) - lut_c(1:T,1:N);
 
  % Matlab code *multiplies* by 2^shift, so negative numbers correspond
  %  to right shift 
  lut_s = -lut_s;
 
  input_data = (data_in_i + 1i*data_in_q) ;
  input_data = (data_in_i + 1i*data_in_q) / 2^15;
  % The following addresses indexing in Ramon's model and issues with
  %  aligning phases properly for decimation.
  if frac_os > 1 
    input_data = [ zeros((frac_os-1), 1); input_data ];
    input_data = input_data(1:length(input_data)-(frac_os-1));
    if (mod(passthru_dly,frac_os) ~= 0)
      pmod = mod(passthru_dly,frac_os);
      input_data = [ zeros((pmod), 1); input_data ];
      input_data = input_data(1:length(input_data)-(pmod));
    end
  end

  % Extra terms from VEX are sc[16,14], unlike the main data, which is
  %  sc[15,14].
  extra_data = (xtra_in_i + 1i*xtra_in_q);
  extra_data = (xtra_in_i + 1i*xtra_in_q) / 2^14;

  % extra_delay to model is adjusted by passthru_dly, as all delays in the
  %  model are relative to passthru delay. 

  extra_dly = xtra_dly - floor(passthru_dly/frac_os);

  % Postfilter coefficients
  hPF = post_c / 2^11 ;

  %y = hwDpdQuant_temp( termParams, T, N, r, lut_c(:,1:64), lut_d, lut_s, input_data, enQuant );
  %y = hwDpdQuant_nlmag( termParams, T, N, r, nlmag_en, lut_n, lut_c(:,1:64), lut_d, lut_s, input_data, enQuant );
  %y = hwDpdQuant_v2( termParams, T, N, r, lut_c, lut_s, input_data, enQuant );
  y = hwDpdQuant_v3_nlmag( termParams, T, N, r, nlmag_en, lut_n, lut_c, lut_s, input_data, extra_data, extra_dly, enQuant, frac_os, hPF );

  pdpd_out = 2^15 * y;

  % Note that saturation is needed here to deal with the fact that the
  %  model of just the data path has output sc[16,14], and the actual
  %  output is sc[16,15]

  pdpd_out_i = min( max( real( pdpd_out ), -2^15 ), 2^15-1 );
  pdpd_out_q = min( max( imag( pdpd_out ), -2^15 ), 2^15-1 );

end

