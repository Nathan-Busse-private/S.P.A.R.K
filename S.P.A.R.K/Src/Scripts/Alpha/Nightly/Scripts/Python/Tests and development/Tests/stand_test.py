from adafruit_servokit import ServoKit
import time

# Channel pins
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

# Coxae positions
CL_idle = 92
CR_idle = 92

# Resting leg positions

# Degrees left femur

coxae_l = 92
femur_l = 180
tibia_l = 0

# Degrees right femur

coxae_r = 92
femur_r = 0
tibia_r = 180

# Standing leg positions

# Left leg
FL_stand = 135
TL_stand = 70

# Right leg
FR_stand = 45
TR_stand = 110

# Walking BACK leg positions
# Left leg
BTL_rise = 50
BTL_forward = 130
BTL_lower = 70
BTL_back = 160

# Right leg
BTR_rise = 130
BTR_forward = 50
BTR_lower = 110
BTR_back = 20

# Walking FORWARD leg positions
# Left leg
FTL_rise = 50
FTL_forward = 130
FTL_lower = 70
FTL_back = 160

# Right leg
FTR_rise = 130
FTR_forward = 50
FTR_lower = 110
FTR_back = 20

# Walking LEFT leg positions
# Left leg
LTL_rise = 50
LTL_forward = 160
LTL_lower = 70
LTL_back = 130

# Right leg
LTR_rise = 130
LTR_forward = 45
LTR_lower = 110
LTR_back = 30

# Walking RIGHT leg positions
# Left leg
RTL_rise = 50
RTL_forward = 134
RTL_lower = 70
RTL_back = 150

# Right leg
RTR_rise = 130
RTR_forward = 25
RTR_lower = 110
RTR_back = 46

# Time delay
stand = 4000
rest = 4000
move = 300
rotate = 200
wait = 100

kit = ServoKit(channels=16)

kit.set_pwm_freq(50)


kit.servo[Coxae_A].set_pulse_width_range(500, 2500)
kit.servo[Femur_A].set_pulse_width_range(500, 2500)
kit.servo[Tibia_A].set_pulse_width_range(500, 2500)

kit.servo[Coxae_B].set_pulse_width_range(500, 2500)
kit.servo[Femur_B].set_pulse_width_range(500, 2500)
kit.servo[Tibia_B].set_pulse_width_range(500, 2500)

kit.servo[Coxae_C].set_pulse_width_range(500, 2500)
kit.servo[Femur_C].set_pulse_width_range(500, 2500)
kit.servo[Tibia_C].set_pulse_width_range(500, 2500)

kit.servo[Coxae_D].set_pulse_width_range(500, 2500)
kit.servo[Femur_D].set_pulse_width_range(500, 2500)
kit.servo[Tibia_D].set_pulse_width_range(500, 2500)


# Leg A
for Coxae_A in range(len(kit.servo)):
    kit.servo[Coxae_A].angle = coxae_l
time.sleep(wait)

for Femur_A in range(len(kit.servo)):
    kit.servo[Femur_A].angle = FL_stand
time.sleep(wait)

for Tibia_A in range(len(kit.servo)):
    kit.servo[Tibia_A].angle = TL_stand
time.sleep(wait)

# Leg B
for Coxae_B in range(len(kit.servo)):
    kit.servo[Coxae_B].angle = coxae_l
time.sleep(wait)

for Femur_B in range(len(kit.servo)):
    kit.servo[Femur_B].angle = FL_stand
time.sleep(wait)

for Tibia_B in range(len(kit.servo)):
    kit.servo[Tibia_B].angle = TL_stand
time.sleep(wait)

# Leg C
for Coxae_C in range(len(kit.servo)):
    kit.servo[Coxae_C].angle = coxae_r
time.sleep(wait)

for Femur_C in range(len(kit.servo)):
    kit.servo[Femur_C].angle = FR_stand
time.sleep(wait)

for Tibia_C in range(len(kit.servo)):
    kit.servo[Tibia_C].angle = TR_stand
time.sleep(wait)

# Leg D
for Coxae_D in range(len(kit.servo)):
    kit.servo[Coxae_D].angle = coxae_r
time.sleep(wait)

for Femur_D in range(len(kit.servo)):
    kit.servo[Femur_D].angle = FR_stand
time.sleep(wait)

for Tibia_D in range(len(kit.servo)):
    kit.servo[Tibia_D].angle = TR_stand
time.sleep(wait)