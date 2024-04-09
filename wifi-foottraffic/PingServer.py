import datetime
import numpy
import pandas
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(0)
print("The server is ready to receive")

timematrix = numpy.zeros(shape=(24, 7))

connectionSocket, addr = serverSocket.accept()
while True:
    try:
        ping = int(connectionSocket.recv(1024).decode())
        print('Ping from client: ', ping)
        if ping != 0:
            day = datetime.datetime.weekday(datetime.datetime.today())
            time = datetime.datetime.now().hour
            timematrix[time, day] += ping
    except KeyboardInterrupt:
        break

connectionSocket.close()
print('Socket is closing')

print(timematrix)
myFrame = pandas.DataFrame(timematrix)
myFrame.rename({0:"midnight-1:00 AM", 1:"1:00-2:00 AM", 2:"2:00-3:00 AM", 3:"3:00-4:00 AM", 4:"4:00-5:00 AM", 5:"5:00-6:00 AM", 6:"6:00-7:00 AM", 7:"7:00-8:00 AM", 8:"8:00-9:00 AM", 9:"9:00-10:00 AM", 10:"10:00-11:00 AM", 11:"11:00-12:00 AM", 12:"12:00-1:00 PM", 13:"1:00-2:00 PM", 14:"2:00-3:00 PM", 15:"3:00-4:00 PM", 16:"4:00-5:00 PM", 17:"5:00-6:00 PM", 18:"6:00-7:00 PM", 19:"7:00-8:00 PM", 20:"8:00-9:00 PM", 21:"9:00-10:00 PM", 22:"10:00-11:00 PM", 23:"11:00-12:00 PM"}, axis='index', errors="raise")
myFrame.to_csv("pingtimes.csv", index_label="day", header=["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"])