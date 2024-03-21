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

/* Resting leg position
   --------------------
*/

// Degres left femur
#define femur_l 180
#define tibia_l 0

// Degrees right femur
#define femur_r 0
#define tibia_r 180

/* Standing leg positions
   ----------------------
*/

// Left legs
#define FL_stand 135
#define TL_stand 60  // 65

// Right legs
#define FR_stand 45
#define TR_stand 120  // 115

/* Time delay
   ----------
*/
#define stand 4
#define rest 4
#define femur_hold 400
#define tibia_hold 300
#define rotate 200
#define hold 400

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

  /* Resting position
   ----------------
*/

  // Left leg
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));  // A
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));  // B
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));  // C
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));  // D

  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C
  delay(rest);

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));
  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
  delay(rest);

}

void loop() {
  // put your main code here, to run repeatedly:

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