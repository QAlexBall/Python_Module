import socket
import threading
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 9999))
# 接受消息
print(s.recv(1024).decode('utf-8'))
for data in [b'Alex', b'Tracy', b'Sarah']:
	# 发送数据
	s.send(data)
	print(s.recv(1024).decode('utf-8'))
s.send(b'exit')
s.close()