# Importing Libraries
import serial
import time
arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data
while True:

    Stand = "S" # Taking input from user
    value_S = write_read(Stand)
    print(value_S) # printing the value

    Forward = "F" # Taking input from user
    value_F = write_read(Forward)
    print(value_F) # printing the value

    Back = "B" # Taking input from user
    value_B = write_read(Back)
    print(value_B) # printing the value

    Left = "L" # Taking input from user
    value_L = write_read(Left)
    print(value_L) # printing the value

    Right = "R" # Taking input from user
    value_R = write_read(Right)
    print(value_R) # printing the value

    Rest = "Z" # Taking input from user
    value_Z = write_read(Rest)
    print(value_Z) # printing the value

    Sit = "W" # Taking input from user
    value_W = write_read(Sit)
    print(value_W) # printing the value

    Jump = "U" # Taking input from user
    value_U = write_read(Jump)
    print(value_U) # printing the value

    Jog = "J" # Taking input from user
    value_J = write_read(Jog)
    print(value_J) # printing the value

    Emergency = "E" # Taking input from user
    value_E = write_read(Emergency)
    print(value_E) # printing the value

