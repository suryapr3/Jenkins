%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Function           : open_tcp_socket(ipaddr,portno)
%Description        : This function will open the socket to the server whose 
%                     IP addr is passed as an parameter
%@input parameter   : ipaddr => ipaddr of the server
%                     e.g '10.122.117.45' if server ipaddr is 10.122.117.45
%@input parameter   : port no => 
%                     e.g 9999 if server starts the port no.
%                   : these two parameters are dependant on server
%global frio_socket : frio_socket is global variable, used for sending and
%                     receing data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function open_tcp_socket(ipaddr, portno)
  global frio_socket;
  frio_socket = tcpclient(ipaddr, portno);
end

