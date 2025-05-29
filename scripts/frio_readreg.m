%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Function           : rdata = frio_readreg(addr)
%Description        : This function reads the content of the
%                     register/memory addr ( four bytes only)
%@input parameter   : addr => address of memory register location in hex
%@output            : rdata => the read data is returned back in rdata var                    
%global frio_socket : frio_socket is global variable,defined while opening
%                     a socket
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


function rdata = frio_readreg(addr)
  global frio_socket;
  addr_hex = dec2hex(addr);
  %addr_string = fprintf('%s', addr);
  command_string = strcat('srpRead 0x', addr_hex);
  write(frio_socket, command_string, 'uint8');
  rdbytes = read(frio_socket, 28, 'uint8');
  read_data = rdbytes(end-9:end-2);
  %fprintf('%s', read_data);
  rdata = char(read_data);
end


