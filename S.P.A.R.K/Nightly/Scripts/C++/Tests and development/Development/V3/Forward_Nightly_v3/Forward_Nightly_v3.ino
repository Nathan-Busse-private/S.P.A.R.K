/* Backward_Forward
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

/* Walking BACK leg positions
   --------------------------
*/
// Left legs
#define BTL_rise 45
#define BFL_forward 125
#define BTL_lower 55  // 65
#define BFL_back 160

// Right legs
#define BTR_rise 135
#define BFR_forward 55
#define BTR_lower 125  // 115
#define BFR_back 20

/* Time delay
   ----------
*/
#define stand 4000
#define rest 4000
#define femur_hold 400
#define tibia_hold 400
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
  pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));  // B
  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));  // C
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));  // D
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

  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

  // Cycle 1
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_forward));
  femur_wait();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_back));

  // Cycle 2
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_forward));
  femur_wait();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_back));

  // Cycle 3
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_forward));
  femur_wait();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_back));

  // Cycle 4
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_forward));
  femur_wait();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_back));
}

// Milli function currently using (delay) between femur movement.
void femur_delay() {
  delay(femur_hold);
}

void femur_wait(void) {
  femur_delay();
}

// Milli function currently using (delay) between tibia movement.
void tibia_delay() {
  delay(tibia_hold);
}

void tibia_wait(void) {
  tibia_delay();
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