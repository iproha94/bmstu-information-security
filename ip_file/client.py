import socket                   # Import socket module
import sys

def parse(lineNS, lineIP):
    sys.stdout.write(lineIP)
    sys.stdout.write(' in ')
    sys.stdout.write(repr(lineNS)) 
    sys.stdout.write(' -> ')

    list = lineIP.split(".")

    for number in list:
        sys.stdout.write(repr(int(number, lineNS)))
        sys.stdout.write('.')

    print 
    print 

s = socket.socket()             # Create a socket object
host = socket.gethostname()     # Get local machine name
port = 60000                   # Reserve a port for your service.
s.connect((host, port))

filename = 'received_file.txt'

with open(filename, 'wb') as f:
    data = s.recv(1024)

    while data:
        f.write(data)
        data = s.recv(1024)

    print 'file accepted'

with open(filename, 'rb') as f:
    print 'open file'
    
    lineNS = f.readline()
    lineIP = f.readline()

    while lineNS and lineIP:
        try:
            parse(int(lineNS), lineIP);
        except ValueError:
            print 'invalid number system'

        lineNS = f.readline()
        lineIP = f.readline()

s.close()
