import bluetooth
from Serial_master import *
import time

server_socket=bluetooth.BluetoothSocket( bluetooth.RFCOMM ) 
port = 1
server_socket.bind(("",port))
server_socket.listen(1)
 
client_socket,address = server_socket.accept()
print("Accepted connection from "),address

data=""
while 1:
         data= client_socket.recv(1024)
         print ("Received: %s") % data
         if (data == "F"):    
            Forward()
         elif (data == "B"):    
            Back()
         elif (data == "L"):    
            Left()
         elif (data == "R"):    
            Right()
         elif (data == "S"):    
            Stand()
         elif (data == "Z"):    
            Rest()
         elif (data == "W"):
            Sit()
         elif (data == "U"):
            Jump()
         elif (data == "J"):
            Jog()
            break
client_socket.close()
server_socket.close()