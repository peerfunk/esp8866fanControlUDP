import sys
import socket
from struct import *
import time

UDP_IP = "192.168.8.178"
UDP_PORT = 26
MESSAGE = "Hello, World!"

print("UDP tar  get IP:", UDP_IP)
print("UDP target port:", UDP_PORT)


sock = socket.socket(socket.AF_INET, # Internet
             socket.SOCK_DGRAM) # UDP
sock.connect( ('192.168.8.178', 26) )
for i in range(11):
    sock.send(pack('ii',int(5),int(i*10)))
    time.sleep(1)
#tcpsocket.send(pack('ii',int(2),int(i)))
