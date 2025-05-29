%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Function           : frio_writereg(addr,wdata)
%Description        : This function write the wdata into the
%                     register/memory addr ( four bytes only)
%@input parameter   : addr => address of memory register location in hex
%@input parameter   : wdata => data to be written in hex                    
%global frio_socket : frio_socket is global variable,defined while opening
%                     a socket
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function frio_writereg(addr, wdata)
  global frio_socket;
  addr_hex = dec2hex(addr);
  wdata_hex = dec2hex(wdata);
  %addr_string = fprintf('%s', dec2hex(addr));
  %wdata_string = fprintf('%s', dec2hex(wdata));
  command_string = strcat('srpWrite 0x', addr_hex, " 0x", wdata_hex);
  write(frio_socket, command_string, 'uint8');
end
