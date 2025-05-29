function [fftSize,subCarriers,shortCP,longCP,symLCP,evmWindow,minGB]=numerologyNR(bw, scs, fr)
%calculate the NR numerology related to the given parameters
%bw = bandwidth of component carrier in Hz
%scs = subcarrier spacing in Hz
%fr = 1 for fr1, 2 for fr2-1, and 22 for fr2-2
%/*********************************************************************************************
%  *                                                                                         *
%  * INTEL CONFIDENTIAL                                                                      *
%  *                                                                                         *
%  * Copyright (C) 2023 Intel Corporation                                                    *
%  *                                                                                         *
%  * This software and the related documents ("Material") are  Intel copyrighted materials,  *
%  * and your use of them is governed by the express license under which they were provided  *
%  * to you ("License"). Unless the License provides otherwise, you may not use, modify,     *
%  * copy, publish, distribute, disclose or transmit this software or the related documents  *
%  * without Intel's prior written permission.                                               *
%  * This software and the related documents are provided as is, with no express or implied  *
%  * warranties, other than those that are expressly stated in the License.                  *
%  * No license under any patent, copyright, trade secret or other intellectual property     *
%  * right is granted to or conferred upon you by disclosure or delivery of the Materials,   *
%  * either expressly, by implication, inducement, estoppel or otherwise. Any license under  *
%  * such intellectual property rights must be express and approved by Intel in writing.     *
%  *                                                                                         *
%  ******************************************************************************************/
%there must be a minimum margin between occupied carriers and FFT size
fr1RBMatrix=[25,52,79,106,133,160,188,216,242,270,NaN,NaN,NaN,NaN,NaN;11,24,38,51,65,78,92,106,119,133,162,189,217,245,273;NaN,11,18,24,31,38,44,51,58,65,79,93,107,121,135];
fr2_1RBMatrix=[66,132,264,NaN;32,66,132,264];
fr2_2RBMatrix=[66,264,NaN,NaN,NaN;NaN,66,124,248,NaN;NaN,33,62,124,148];
if(fr==1)
  scsindex=log2(scs/15E3)+1;
  switch(bw/1E6)
      case 5
          bwindex=1;
      case 10
          bwindex=2;
      case 15
          bwindex=3;
      case 20
          bwindex=4;
      case 25
          bwindex=5;
      case 30
          bwindex=6;
      case 35
          bwindex=7;
      case 40
          bwindex=8;
      case 45
          bwindex=9;
      case 50
          bwindex=10;
      case 60
          bwindex=11;
      case 70
          bwindex=12;
      case 80
          bwindex=13;
      case 90
          bwindex=14;
      case 100
          bwindex=15;
      otherwise
          bwindex=-1;
  end
  if(bwindex~=-1 && scsindex<4)
    subCarriers=fr1RBMatrix(scsindex,bwindex)*12;
  else
      subCarriers=NaN;
  end
elseif(fr==2)
  scsindex=scs/60E3;
  switch(bw/1E6)
      case 50
          bwindex=1;
      case 100
          bwindex=2;
      case 200
          bwindex=3;
      case 400
          bwindex=4;
      otherwise
          bwindex=-1;
  end
  if(bwindex~=-1 && scsindex>=1 && scsindex<=2)
    subCarriers=fr2_1RBMatrix(scsindex,bwindex)*12;
  else
      subCarriers=NaN;
  end
else %FR2_2
  scsindex=1+floor(scs/480E3);
  switch(bw/1E6)
      case 100
          bwindex=1;
      case 400
          bwindex=2;
      case 800
          bwindex=3;
      case 1600
          bwindex=4;
      case 2000
          bwindex=5;
      otherwise
          bwindex=-1;
  end
  if(bwindex~=-1 && scsindex>=1 && scs>=120E3)
    subCarriers=fr2_2RBMatrix(scsindex,bwindex)*12;
  else
      subCarriers=NaN;
  end
end

%calculate elements of numerology
expand=1.1;
if(bw==15E6 || bw==30E6 || bw==35E6 || bw==60E6 || bw==70E6)
    fftSize=2^ceil(log2(bw/scs*expand*4/3))*3/4;
elseif(bw==2000E6)
    fftSize=2048;
else
    fftSize=2^ceil(log2(bw/scs*expand));
end
mu=log2(scs/15E3);
kappa=scs*fftSize/(15E3*2048);

%short CP length
shortCP=144*kappa*2^-mu;

%long CP length
longCP=144*kappa*2^-mu+16*kappa;

%symbols per long CP
symLCP=7*2^mu;

%calculate EVM measurement window
if(fr==1) %FR1 varies from 40-60%
    if(bw<=20E6) % 40%
        evmWindow=round(shortCP*2/5/2)*2;
        if(scs==60E3 && bw==15E6)
            evmWindow=11;
        end
    elseif(bw<=50E6) % 50%
        evmWindow=round(shortCP/2/2)*2;
        if(scs==60E3 && (bw==30E6 || bw==35E6))
            evmWindow=26;
        end
    else % 60%
        evmWindow=round(shortCP*3/5/2)*2;
    end
else %FR2 is always 50%
    evmWindow=shortCP/2;
end

%minimum guard band
if(fr==1)
    if(scs==15e3)
        GB=[242.5E3,312.5E3,382.5E3,452.5E3,522.5E3,592.5E3,572.5,552.5E3,712.5E3,692.5E3,nan,nan,nan,nan,nan];
    elseif(scs==30e3)
        GB=[505E3,665E3,645E3,805E3,785E3,945E3,925E3,905E3,1065E3,1045E3,825E3,965E3,925E3,885E3,845E3];
    else
        GB=[nan,1010E3,990E3,1330E3,1310E3,1290E3,1630E3,1610E3,1590E3,1570E3,1530E3,1490E3,1450E3,1410E3,1370E3];
    end
elseif(fr==2)
    if(scs==60e3)
        GB=[1210E3,2450E3,4930E3,nan];
    else
        GB=[1900E3,2420E3,4900E3,9860E3];
    end
else %fr2-2
    if(scs==120e3)
        GB=[2480E3,9920E3,NaN,NaN,NaN];
    elseif(scs==480E3)
        GB=[NaN,9680E3,42640E3,85520E3,NaN];
    else
        GB=[NaN,9440E3,42400E3,85280E3,147040E3];
    end
end
if(bwindex~=-1)
    minGB=GB(bwindex);
else
    minGB=NaN;
end

end