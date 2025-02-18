/* S.P.A.R.K moving forward
   Project: S.P.A.R.K
   Start date: 31 May 2023
   Last edited: 13 June 2023
   Info:

  My attempt to make S.P.A.R.K walk forward for the first time.

  My walking theory:
  ------------------
  Their will be 2 legs touching the ground and 2 in the air for each step.
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

/* Coxae positions
   ---------------
*/
#define CL_idle 90
#define CR_idle 90

/* Resting leg position
   --------------------
*/

// Degres left femur
#define coxae_l 90
#define femur_l 180
#define tibia_l 0

// Degrees right femur
#define coxae_r 90
#define femur_r 0
#define tibia_r 0


/* Standing leg positions
   ----------------------
*/

// Left legs
#define FL_stand 135
#define TL_stand 70

// Right legs
#define FR_stand 45
#define TR_stand 70


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




/* Time delay
   ----------
*/
#define stand 4000
#define hold 400
#define rest 4000

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

/* Resting position
   ----------------
*/

// Left leg
  pwm.setPWM(Coxae_A, 0, pulseWidth(coxae_l));  // A
  pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(coxae_l));   // B
  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(Coxae_C, 0, pulseWidth(coxae_r));   // C
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(coxae_r));   // D
  pwm.setPWM(Femur_D, 0, pulseWidth(femur_r));  // D
  pwm.setPWM(Tibia_D, 0, pulseWidth(tibia_r));  // D

  // Left leg
  pwm.setPWM(Coxae_A, 0, pulseWidth(coxae_l));  // A
  pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(coxae_l));   // B
  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(Coxae_C, 0, pulseWidth(coxae_r));   // C
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(coxae_r));   // D
  pwm.setPWM(Femur_D, 0, pulseWidth(femur_r));  // D
  pwm.setPWM(Tibia_D, 0, pulseWidth(tibia_r));  // D
  delay(rest);

  /* Standing position
   ----------------
  */
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