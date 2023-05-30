/*
Stand_up test

Project: S.P.A.R.K
Start date: 10 April 2023
Last edited: 30 May 2023
Info:

S.P.A.R.K will perform a series of transitoms from its standing position and returning back to its resting position.
The perpose of this test is to see if the MG996R servos can support the weight of the robot.

Made by Nathan-Busse
*/

// Libraries
#include <Adafruit_PWMServoDriver.h>

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

// Degree declarations
// Resting position
#define C_idle 90     // Coxae idle
#define F_rest_L 180  // Femur left at rest
#define F_rest_R 1    // Femur right at rest
#define T_rest 1      // Tibia rest

// Standing position
#define C_idle 90      // Coxae idle
#define F_stand_L 135  // Femur left at rest
#define F_stand_R 45   // Femur right at rest
#define T_stand 45     // Tibia stand

// Define time delay
#define wait 100   // Period of time to pause the servos before transitioning to the standing position.
#define hold 2000  // Period of time to remain standing.

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
  // Rest postion
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));

  pwm.setPWM(Femur_A, 0, pulseWidth(F_rest_L));
  pwm.setPWM(Femur_B, 0, pulseWidth(F_rest_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(F_rest_R));
  pwm.setPWM(Femur_D, 0, pulseWidth(F_rest_R));

  pwm.setPWM(Tibia_A, 0, pulseWidth(T_rest));
  pwm.setPWM(Tibia_B, 0, pulseWidth(T_rest));
  pwm.setPWM(Tibia_C, 0, pulseWidth(T_rest));
  pwm.setPWM(Tibia_D, 0, pulseWidth(T_rest));
  delay(wait);

  // Stand position
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));

  pwm.setPWM(Femur_A, 0, pulseWidth(F_stand_L));
  pwm.setPWM(Femur_B, 0, pulseWidth(F_stand_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(F_stand_R));
  pwm.setPWM(Femur_D, 0, pulseWidth(F_stand_R));

  pwm.setPWM(Tibia_A, 0, pulseWidth(T_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(T_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(T_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(T_stand));
  delay(hold);
}

// Pulsewidth declaration
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  Serial.println(analog_value);
  return analog_value;
}
