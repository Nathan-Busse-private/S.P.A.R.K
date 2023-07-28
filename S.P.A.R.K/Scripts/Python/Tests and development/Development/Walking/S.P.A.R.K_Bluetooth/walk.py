from adafruit_servokit import ServoKit # https://learn.adafruit.com/16-channel-pwm-servo-driver/python-circuitpython



def setupWheels():
    kit = ServoKit(channels=16)



def rightWheels(direction):
   
    if direction == "forward":
        
    elif direction == "backward":
        



def forward(wheels):
    if wheels == "right-wheels":
        rightWheels("forward")
    elif wheels == "left-wheels":
        leftWheels("forward")
    else:
        rightWheels("forward")
        leftWheels("forward")

def backward(wheels):
    if wheels == "right-wheels":
        rightWheels("backward")
    elif wheels == "left-wheels":
        leftWheels("backward")
    else:
        rightWheels("backward")
        leftWheels("backward")

def stop(wheels):
    if wheels == "right-wheels":
        rightWheels("stop")
    elif wheels == "left-wheels":
        leftWheels("stop")
    else:
        rightWheels("stop")
        leftWheels("stop")

def turn(direction):
    if direction == "right":
        forward("left-wheels")
        backward("right-wheels")
    else:
        forward("right-wheels")
        backward("left-wheels")