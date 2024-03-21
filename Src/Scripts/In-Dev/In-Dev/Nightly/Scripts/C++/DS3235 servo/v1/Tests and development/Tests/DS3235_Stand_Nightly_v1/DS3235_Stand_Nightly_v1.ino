/* Stand_Nightly_v4
   Project: S.P.A.R.K
   Start date: 9 October 2023
   Last edited: 14 October 2023
   Info:

   Experimenting how to make S.P.A.R.K walk forward.

   Made by Nathan-Busse
*/

//including the libraries
#include <SoftwareSerial.h>  // TX RX software library for bluetooth
#include <spark_pwm.h>
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

/* Coxae flat angle positions
   ---------------
*/
#define CL_idle 90
#define CR_idle 90

/* Standing leg positions
   ----------------------
*/

// Left legs
#define FL_stand 150
#define TL_stand 45  // 65

// Right legs
#define FR_stand 30
#define TR_stand 135  // 115

/* Time delay
   ----------
*/
#define stand 4000

/* PWM setup
   ---------
*/
#define MIN_PulseLength 500
#define MAX_PulseLength 2500
#define MED_PulseLength 2500
#define Frequency 50  // 50 HRz

spark_pwm pwm = spark_pwm();
int degrees;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(Frequency);

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

}

/* Pulsewidth declaration
   ----------------------
*/
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  return analog_value;
}