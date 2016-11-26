import socket                   # Import socket module

s = socket.socket()             # Create a socket object
host = socket.gethostname()     # Get local machine name
port = 60000                    # Reserve a port for your service.
s.bind((host, port))            # Bind to the port
s.listen(5)                     # Now wait for client connection.

filename = 'mytext.txt'

while True:
    try:
        conn, addr = s.accept()     # Establish connection with client.
    except KeyboardInterrupt:
        s.close()
        break

    f = open(filename, 'rb')
    piece = f.read(1024)

    while (piece):
        conn.send(piece)
        piece = f.read(1024)

    print 'file is sent'

    f.close()
    conn.close() 