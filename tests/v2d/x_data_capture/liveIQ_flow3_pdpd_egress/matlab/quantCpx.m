function data = quantCpx(msb,lsb,data,disableErrorOnSat,simetricRange,quantEn)

if (nargin==6) && (~quantEn)
    return
end


if nargin<4
    disableErrorOnSat = 0;
    simetricRange     = 0;
elseif nargin<5
    simetricRange     = 0;
end

dataReal = real(data);
dataImag = imag(data);


if ~isempty(lsb) 
  dataReal = floor(dataReal./(2.^lsb) + .5).*(2.^lsb);
  dataImag = floor(dataImag./(2.^lsb) + .5).*(2.^lsb);
end

if ~isempty(msb)
  neg_sat = -2.^(msb+1);
  if isempty(lsb) || simetricRange
    pos_sat =  2.^(msb+1);
  else
    pos_sat =  2.^(msb+1) - 2.^lsb;
  end

  if any((dataReal > pos_sat) | ...
          (dataReal < neg_sat) | ...
          (dataImag > pos_sat) | ...
          (dataImag < neg_sat))

      dataReal(dataReal > pos_sat) = pos_sat;
      dataReal(dataReal < neg_sat) = neg_sat;
      
      dataImag(dataImag > pos_sat) = pos_sat;
      dataImag(dataImag < neg_sat) = neg_sat; 
      
      if ~disableErrorOnSat
        disp('saturation hit the fan')
        %keyboard
        %error('saturation hit the fan')
      end
      
  end  
end

data = dataReal + 1i*dataImag;
