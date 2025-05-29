function data = cmag(data_in)

% input:   sc[14.13]
% output:  ur[13.13]

iterations = 16;            % Number of CORDIC iterations
frac_width = 13;            % Bit width of fractional portion
extra_bits = 4;             % Affects accumulator width
drift_bits = 12;            % Number of bits to represent the offset factor applied
                            %  to handle gain due to CORDIC drift

% scale determines the internal accumulator width
% e.g., if we're keeping 4 extra bits in the accumulators then scale is 16.0 
scale      = 2^extra_bits;

data_in_i = real(data_in) * 2^frac_width;
data_in_q = imag(data_in) * 2^frac_width;

accum_i = abs(data_in_i) * scale;  % Must be in quadrant 1 or 4
accum_q = data_in_q * scale;

s = 0;
k = 0;
gain = 1;

while k < 16
  s = -1;
  if accum_q < 0
    s = 1;
  end
  % accum_i = accum_i +/- (accum_q >> k)
  new_accum_i = floor( accum_i - (s * (accum_q * (2^(-k)))) + 0.5 );
  % accum_q = +/- (accum_i >> k) + accum_q
  new_accum_q = floor( (s * (accum_i * (2^(-k)))) + accum_q + 0.5 );
  accum_i = new_accum_i;
  accum_q = new_accum_q;
  gain = gain * ( 1 + ((2^(-k))^2))^0.5;
  k = k + 1;
end

% Compute drift factor based on gain due to CORDIC drift
drift = floor( ((1/gain) * (2^drift_bits)) + 0.5) ;
drift_factor = drift / (2^drift_bits) ;

% Round
data = floor( accum_i * (drift_factor) / scale + 0.5 ) ;

% Saturate
if ( data > 2^frac_width-1 )
  data = 2^frac_width-1;
end

% Final scaling to fraction
data = data / (2^frac_width);

