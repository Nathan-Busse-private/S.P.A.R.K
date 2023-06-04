/* S.P.A.R.K moving forward
   Project: S.P.A.R.K
   Start date: 31 May 2023
   Last edited: 4 June 2023
   Info:

  My first attempt to make S.P.A.R.K walk forward for the first time.

  My walking theory:
  ------------------
  Their will be 2 legs touching the ground and 2 in the air per step.
  The 2 legs will operate in sync with the other leg diagnal from its partner.
  For example:

  Leg A will partner with Leg C
  Leg B will partner with Leg D.

  The Tibia of the paired legs will lift first and the Femur will then lift second. 
  Once the second pair of legs begin to lift, the already raised Femur will then lower
  first then the Tibia will lower second which follows on indefinitly, thus making the robot walk.

  Made by Nathan-Busse.
*/

// Calling Libraries

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Declaring pins

// Pin declarations
#define Coxae_A 0
#define Femur_A 1
#define Tibia_A 2

#define Coxae_B 4
#define Femur_B 5
#define Tibia_B 6

#define Coxae_C 8
#define Femur_C 9
#define Tibia_C 10

#define Coxae_D 12
#define Femur_D 13
#define Tibia_D 14

// Leg position identification

// Standing position
#define C_idle 90       // Coxae idle
#define FF_stand_L 135  // Femur left while standing
#define FF_stand_R 45   // Femur right while standing

#define BF_stand_L 135  // Femur left while standing
#define BF_stand_R 45   // Femur right while standing

#define FT_stand 50  // Tibia stand
#define BT_stand 65

// Define time delay
#define pause 400
// Walking position

// Tibia
#define FT_Rise 50
#define BT_Rise 50
#define FT_Lower 70
#define BT_Lower 70

// Femur
#define FF_Rise_L 115
#define BF_Rise_L 115
#define FF_Lower_L 135
#define BF_Lower_L 135

#define FF_Rise_R 45
#define BF_Rise_R 45
#define FF_Lower_R 25
#define BF_Lower_R 25

// PWM setup
#define MIN_PulseLength 500
#define MAX_PulseLength 2500
#define MED_PulseLength 2500
#define Frequency 50  // 50 HRz

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int degrees;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(Frequency);
}

void loop() {
  
  // Walking position
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));

  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(FT_Rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BT_Rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(FF_Rise_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(BF_Rise_R));
  delay(pause);

  pwm.setPWM(Tibia_D, 0, pulseWidth(FT_Rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BT_Rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FF_Rise_R));
  pwm.setPWM(Femur_B, 0, pulseWidth(BF_Rise_L));
  
  // Lower
  pwm.setPWM(Femur_A, 0, pulseWidth(FF_Lower_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(BF_Lower_R));
  pwm.setPWM(Tibia_A, 0, pulseWidth(FT_Lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BT_Lower));
  delay(pause);

  pwm.setPWM(Femur_D, 0, pulseWidth(FF_Lower_R));
  pwm.setPWM(Femur_B, 0, pulseWidth(BF_Lower_L));
  pwm.setPWM(Tibia_D, 0, pulseWidth(FT_Lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BT_Lower));
}

// Pulsewidth declaration
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  Serial.println(analog_value);
  return analog_value;
}
