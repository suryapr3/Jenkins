# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Lovekesh Gupta
# Created Date: January 1 2024
# =============================================================================
# Description : to start a server onhost machine connected to FRIO
# =============================================================================
# Import statements
# =============================================================================
import socket
import threading
import sys
import subprocess
import os

COMMAND_SIZE = 64
FORMAT ='utf-8'
SERVER = socket.gethostbyname(socket.gethostname())
print(SERVER)
print(socket.gethostname())
PORT = 9999
ADDR = (SERVER, PORT)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

def handle_client(communication_socket, addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    connected = True
    while connected:
        #print(f"waiting for command from client")
        message = communication_socket.recv(COMMAND_SIZE).decode(FORMAT)
        #communication_socket.send(f"Got your command".encode(FORMAT))
        result = subprocess.run(message,shell=True,stdout=subprocess.PIPE)
        #if result.returncode == 0:
        #    communication_socket.send(f"command executed successfully".encode('utf-8'))
        #else:
        #    communication_socket.send(f"error in command execution".encode('utf-8'))
        if "srpRead" in message:
            print(message)
            print(result.stdout)
            communication_socket.send(result.stdout)
        if "srpWrite" in message:
            print(message)
            print(f"srpWrite completed")
            
            


def start():
    server.listen(1)
    communication_socket, addr = server.accept()
    handle_client(communication_socket,addr)


print("Starting server.....")
start()
