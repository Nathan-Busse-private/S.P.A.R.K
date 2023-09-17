/*
Stand_pivot_test

Project: S.P.A.R.K
Start date: 10 September2023
Last edited: 16 September 2023
Info:

S.P.A.R.K will perform a series of transitoms from its default pivot position.

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

// Standing position

#define FCL0 70  // Coxae idle
#define FCR0 70  // Coxae idle
#define BCL0 110   // Coxae idle
#define BCR0 110   // Coxae idle

#define FCL10 74  // Coxae idle
#define FCR10 74  // Coxae idle
#define BCL10 106   // Coxae idle
#define BCR10 106   // Coxae idle

#define FCL20 78  // Coxae idle
#define FCR20 78  // Coxae idle
#define BCL20 102   // Coxae idle
#define BCR20 102   // Coxae idle

#define FCL30 82  // Coxae idle
#define FCR30 82  // Coxae idle
#define BCL30 98   // Coxae idle
#define BCR30 98   // Coxae idle

#define FCL40 86  // Coxae idle
#define FCR40 86  // Coxae idle
#define BCL40 94   // Coxae idle
#define BCR40 94   // Coxae idle

#define FCL50 90  // Coxae idle
#define FCR50 90  // Coxae idle
#define BCL50 90   // Coxae idle
#define BCR50 90   // Coxae idle

#define BCL60 86   // Coxae idle
#define BCR60 86   // Coxae idle
#define FCL60 94  // Coxae idle
#define FCR60 94  // Coxae idle

#define BCL70 82   // Coxae idle
#define BCR70 82   // Coxae idle
#define FCL70 98  // Coxae idle
#define FCR70 98  // Coxae idle

#define BCL80 78   // Coxae idle
#define BCR80 78   // Coxae idle
#define FCL80 102  // Coxae idle
#define FCR80 102  // Coxae idle

#define BCL90 74   // Coxae idle
#define BCR90 74   // Coxae idle
#define FCL90 106  // Coxae idle
#define FCR90 106  // Coxae idle

#define BCL100 70   // Coxae idle
#define BCR100 70   // Coxae idle
#define FCL100 110  // Coxae idle
#define FCR100 110  // Coxae idle

// Left legs
#define FL_stand 135
#define TL_stand 70

// Right legs
#define FR_stand 45
#define TR_stand 110


#define FF_stand_L 135  // Femur left while standing
#define FF_stand_R 45   // Femur right while standing

#define BF_stand_L 135  // Femur left while standing
#define BF_stand_R 45   // Femur right while stand4ing

#define FT_stand 70  // Tibia stand
#define BT_stand 70

// Define time delay
//#define wait 10000   // Period of time to pause the servos before transitioning to the standing position.
#define hold 200  // Period of time to remain standing.

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


  // Stand position
  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL0));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL0));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR0));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR0));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL10));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL10));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR10));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR10));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL20));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL20));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR20));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR20));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL30));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL30));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR30));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR30));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL40));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL40));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR40));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR40));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL50));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL50));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR50));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR50));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL60));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL60));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR60));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR60));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL70));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL70));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR70));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR70));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL80));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL80));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR80));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR80));

delay(hold);


  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL90));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL90));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR90));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR90));

delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL100));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL100));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR100));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR100));


  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
  
delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL100));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL100));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR100));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR100));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL90));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL90));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR90));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR90));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL80));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL80));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR80));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR80));

delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL70));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL70));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR70));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR70));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL60));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL60));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR60));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR60));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL50));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL50));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR50));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR50));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL40));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL40));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR40));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR40));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL30));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL30));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR30));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR30));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL20));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL20));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR20));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR20));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL10));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL10));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR10));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR10));

  delay(hold);

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL0));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL0));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR0));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR0));

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
