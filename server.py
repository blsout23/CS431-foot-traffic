'''
This program reads input from an arduino and sends it to another machine over TCP.

Ben Southwick, Massimo Fontaine, Kuukua Dampey
03/20/24
'''


from socket import *

data = None # data from sensors

serverPort = 31415

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen()
print("The server is ready to receive")

while True:
    connectionSocket, addr = serverSocket.accept()
    data = serverSocket.recvfrom(1024).decode()
    print("Received!")
    connectionSocket.close() 