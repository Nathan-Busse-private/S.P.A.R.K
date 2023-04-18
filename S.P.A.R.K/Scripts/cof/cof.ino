
/* Servo_joint_
  Project: S.P.A.R.K
  Start date: 10 April 2023
  Last edited: 16 April 2023
  Info:

  Callibrating all servos before assembly.

  Made by Nathan-Busse.
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
  Leg A
  -------
*/
#define Hip_A 0
#define Leg_A 1
#define Foot_A 2

/*
  -------
  Leg B
  -------
*/
#define Hip_B 4
#define Leg_B 5
#define Foot_B 6

/*
  -------
  Leg C
  -------
*/
#define Hip_C 8
#define Leg_C 9
#define Foot_C 10

/*
  -------
  Leg D
  -------
*/

#define Hip_D 12
#define Leg_D 13
#define Foot_D 14

// servo

#define hip_l 90
#define leg_l 180
#define foot_l 0

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
  //  servos to 90 degrees for each leg.
  //--------------------------------------------------------------------

  pwm.setPWM(Hip_A, 0, pulseWidth(hip_l));  // A
  pwm.setPWM(Leg_A, 0, pulseWidth(leg_l));  // A
  pwm.setPWM(Foot_A, 0, pulseWidth(foot_l));  // A
  delay(hold);

  /*
  pwm.setPWM(Hip_B, 0, pulseWidth());   // B
  pwm.setPWM(Leg_B, 0, pulseWidth());  // B
  pwm.setPWM(Foot_B, 0, pulseWidth());  // B

  pwm.setPWM(Hip_C, 0, pulseWidth());   // C
  pwm.setPWM(Foot_C, 0, pulseWidth());  // C
  pwm.setPWM(Leg_C, 0, pulseWidth());  // C

  pwm.setPWM(Hip_D, 0, pulseWidth());   // D
  pwm.setPWM(Leg_D, 0, pulseWidth());  // D
  pwm.setPWM(Foot_D, 0, pulseWidth());  // D
  delay(hold);
  */
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
