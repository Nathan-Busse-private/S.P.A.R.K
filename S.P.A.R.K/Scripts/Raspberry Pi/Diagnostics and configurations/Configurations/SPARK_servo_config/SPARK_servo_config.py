"""
Project: S.P.A.R.K
Start date: 16 April 2023
Last edited: 3 May 2023
Info:

Callibrating all servos before assembly.
All twelve servos will be calibrated at the same time because 
I intend on using this code as S.P.A.R.K's resting position.

Made by Nathan-Busse.

"""

# Libraries
import time
from adafruit_servokit import ServoKit # https://learn.adafruit.com/16-channel-pwm-servo-driver/python-circuitpython

# Setting number of channels for PCA9865
kit = ServoKit(channels=16)

# Defining channels as a variable
Coxae_A = 0
Femur_A = 1
Tibia_A = 2

Coxae_B = 4
Femur_B = 5
Tibia_B = 6

Coxae_C = 8
Femur_C = 9
Tibia_C = 10

Coxae_D = 12
Femur_D = 13
Tibia_D = 14

#Degree definitions
coxae = 90
femur_L = 180
femur_R = 0
tibia = 0

# Sleep variables
idle = 1 # The number of seconds the servos will pause for incoming signals.


#Servo positions
# Leg A
for Coxae_A in range(len(kit.servo)):
    kit.servo[Coxae_A].angle = coxae
time.sleep(idle)

for Femur_A in range(len(kit.servo)):
    kit.servo[Femur_A].angle = femur_L
time.sleep(idle)

for Tibia_A in range(len(kit.servo)):
    kit.servo[Tibia_A].angle = tibia
time.sleep(idle)

# Leg B
for Coxae_B in range(len(kit.servo)):
    kit.servo[Coxae_B].angle = coxae
time.sleep(idle)

for Femur_B in range(len(kit.servo)):
    kit.servo[Femur_B].angle = femur_L
time.sleep(idle)

for Tibia_B in range(len(kit.servo)):
    kit.servo[Tibia_B].angle = tibia
time.sleep(idle)

# Leg C
for Coxae_C in range(len(kit.servo)):
    kit.servo[Coxae_C].angle = coxae
time.sleep(idle)

for Femur_C in range(len(kit.servo)):
    kit.servo[Femur_C].angle = femur_R
time.sleep(idle)

for Tibia_C in range(len(kit.servo)):
    kit.servo[Tibia_C].angle = tibia
time.sleep(idle)

# Leg D
for Coxae_D in range(len(kit.servo)):
    kit.servo[Coxae_D].angle = coxae
time.sleep(idle)

for Femur_D in range(len(kit.servo)):
    kit.servo[Femur_D].angle = femur_R
time.sleep(idle)

for Tibia_D in range(len(kit.servo)):
    kit.servo[Tibia_D].angle = tibia
time.sleep(idle)