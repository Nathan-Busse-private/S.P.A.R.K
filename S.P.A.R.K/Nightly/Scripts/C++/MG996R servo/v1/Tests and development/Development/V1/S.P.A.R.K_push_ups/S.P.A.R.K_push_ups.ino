/* S.P.A.R.K_push_ups
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 5 June 2023
   Info:

    S.P.A.R.K doing some pushups.
 
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
// Degres left femur
#define coxae_l 90
#define femur_l 179
#define tibia_l 1

// Degrees right femur
#define coxae_r 90
#define femur_r 1
#define tibia_r 1

// Standing position (Currently un-used)
#define C_idle 90       // Coxae idle
#define FF_stand_L 134  // Femur left while standing
#define FF_stand_R 46   // Femur right while standing

#define BF_stand_L 134  // Femur left while standing
#define BF_stand_R 46   // Femur right while standing

#define FT_stand 70  // Tibia stand
#define BT_stand 70

// Define time delay
#define hold 600

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
  // put your main code here, to run repeatedly:

  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));

  pwm.setPWM(Femur_A, 0, pulseWidth(FF_stand_L));
  pwm.setPWM(Femur_B, 0, pulseWidth(BF_stand_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(BF_stand_R));
  pwm.setPWM(Femur_D, 0, pulseWidth(FF_stand_R));

  pwm.setPWM(Tibia_A, 0, pulseWidth(FT_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BT_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BT_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(FT_stand));
  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(coxae_l));  // A
  pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(coxae_l));  // B
  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(Coxae_C, 0, pulseWidth(coxae_r));  // C
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(coxae_r));  // D
  pwm.setPWM(Femur_D, 0, pulseWidth(femur_r));  // D
  pwm.setPWM(Tibia_D, 0, pulseWidth(tibia_r));  // D
  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));

  pwm.setPWM(Femur_A, 0, pulseWidth(FF_stand_L));
  pwm.setPWM(Femur_B, 0, pulseWidth(BF_stand_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(BF_stand_R));
  pwm.setPWM(Femur_D, 0, pulseWidth(FF_stand_R));

  pwm.setPWM(Tibia_A, 0, pulseWidth(FT_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BT_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BT_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(FT_stand));
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