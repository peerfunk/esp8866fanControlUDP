import sys
import socket
from struct import *
import time

UDP_IP = "192.168.8.178"
UDP_PORT = 26
MOTORID = 5

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.connect( (UDP_IP, UDP_PORT) )

for i in range(11):
    sock.send(pack('ii',int(MOTORID),int(i*10)))
    time.sleep(1)
