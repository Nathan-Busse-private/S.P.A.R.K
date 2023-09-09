/* S.P.A.R.K_walking_troubleshoot
   Project: S.P.A.R.K
   Start date: 11 June 2023
   Last edited:13 June 2023
   Info:

Figuring out the issues with S.P.A.R.K's ability to walk.

Issues have been resolved.

   Made by Nathan-Busse
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

/* Standing leg positions
   ----------------------
*/

// Left legs
#define FL_stand 135
#define TL_stand 45

// Right legs
#define FR_stand 45
#define TR_stand 45


/* Walking leg positions
   ---------------------
*/

// Left legs
#define TL_rise 35
#define FL_forward 130
#define TL_lower 45
#define FL_back 160

// Right legs
#define TR_rise 35
#define FR_forward 50
#define TR_lower 45
#define FR_back 20


/* Coxae positions
   ---------------
*/
#define CL_idle 90
#define CR_idle 90

/* Time delay
   ----------
*/
#define stand 1000
#define hold 400

/* PWM setup
   ---------
*/
#define MIN_PulseLength 500
#define MAX_PulseLength 2500
#define MED_PulseLength 2500
#define Frequency 50  // 50 HRz

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int degrees;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(Frequency);

  // Standing
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
  delay(stand);
}

void loop() {

  // Walking
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));


// Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_forward));
  delay(hold);

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_back));

// Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(FL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_forward));
  delay(hold);
  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_back));
  delay(hold);
}

/* Pulsewidth declaration
   ----------------------
*/
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  Serial.println(analog_value);
  return analog_value;
}