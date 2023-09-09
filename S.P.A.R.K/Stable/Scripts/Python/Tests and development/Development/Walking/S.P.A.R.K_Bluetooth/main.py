import time
from adafruit_servokit import ServoKit # https://learn.adafruit.com/16-channel-pwm-servo-driver/python-circuitpython

import bluetooth
from walk import *


# Setting number of channels for PCA9865


bt_buttonPin = 31

commands = {
	"f" : "forward",
	"b" : "backward",
	"l" : "left",
	"r" : "right",
	"s" : "stop",
	"q" : "quit"
}

server_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
server_socket.bind(("", 1))
server_socket.listen(1)

def setup():
	kit = ServoKit(channels=16)
	setupWheels()
	
	
def loop():
	connection = False
	while True:
		while not connection:
			if GPIO.input(bt_buttonPin) == GPIO.LOW:
				client_socket, address = server_socket.accept()
				connection = True
				
				client_socket.send("Use the following commands to move the car\n")
				for command_char, command_action in commands.items():
					client_socket.send(command_char + " - " + command_action + "\n")
		while connection:
			command = client_socket.recv(1024)
			if command == b"f\r\n":
				forward("all-wheels")
				client_socket.send("Moving forward...\n")
			elif command == b"b\r\n":
				backward("all-wheels")
				client_socket.send("Moving backward...\n")
			elif command == b"l\r\n":
				turn("left")
				client_socket.send("Turning left...\n")
			elif command == b"r\r\n":
				turn("right")
				client_socket.send("Turning right...\n")
			elif command == b"s\r\n":
				stop("all-wheels")
				client_socket.send("Stopping...\n")
			elif command == b"q\r\n":
				stop("all-wheels")
				
				client_socket.send("Bye!\n")
				connection = False
				break
		
def destroy():
	GPIO.cleanup()
	
if __name__ == "__main__":
	setup()
	try:
		loop()
	except KeyboardInterrupt:
		pass
	finally:
		destroy()