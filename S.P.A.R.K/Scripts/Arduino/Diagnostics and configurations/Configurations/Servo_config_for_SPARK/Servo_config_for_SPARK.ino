
/* Servo_config_for_SPARK
  Project: S.P.A.R.K
  Start date: 10 April 2023
  Last edited: 30 May 2023
  Info:

  Callibrating all servos before assembly.

  Made by Nathan-Busse.
*/

/*

Leg position identification

*/

// The code

// Calling Libraries

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Declaring pins

// Channel definitions


//pwm (Board 1)
/*
  -------
  femur A
  -------
*/
#define coxae_A 0
#define femur_A 1
#define tibia_A 2

/*
  -------
  femur B
  -------
*/
#define coxae_B 4
#define femur_B 5
#define tibia_B 6

/*
  -------
  femur C
  -------
*/
#define coxae_C 8
#define femur_C 9
#define tibia_C 10

/*
  -------
  femur D
  -------
*/

#define coxae_D 12
#define femur_D 13
#define tibia_D 14

// Degres left femur
#define coxae_l 90
#define femur_l 179
#define tibia_l 1

// Degrees right femur
#define coxae_r 90
#define femur_r 1
#define tibia_r 1



//Min and Max pulse values

#define MIN_PULSE_WIDTH 500
#define MAX_PULSE_WIDTH 2500
#define DEFAULT_PULSE_WIDTH 2500
#define FREQUENCY 50

int degrees;

// Millis declarations
#define hold 0
#define pause 5000

// Address definitions for servo controllers
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);



void setup() {
  // put your setup code here, to run once:

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);  // Analog servos run at ~60 Hz updates
}

void loop() {
  //--------------------------------------------------------------------
  //  Set servos to resting state before assembly.
  //--------------------------------------------------------------------

  // Left leg
  pwm.setPWM(coxae_A, 0, pulseWidth(coxae_l));  // A
  pwm.setPWM(femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(coxae_B, 0, pulseWidth(coxae_l));   // B
  pwm.setPWM(femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(coxae_C, 0, pulseWidth(coxae_r));   // C
  pwm.setPWM(tibia_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(femur_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(coxae_D, 0, pulseWidth(coxae_r));   // D
  pwm.setPWM(femur_D, 0, pulseWidth(femur_r));  // D
  pwm.setPWM(tibia_D, 0, pulseWidth(tibia_r));  // D
  delay(hold);
  
}

//--------------------------------------------------------------------
// Pulsewidth declaration
//--------------------------------------------------------------------

int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  Serial.println(analog_value);
  return analog_value;
}
