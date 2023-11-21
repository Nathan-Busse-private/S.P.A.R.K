/* S.P.A.R.K_Bluetooth_Stable
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 16 September 2023
   Info:

   Experimenting how to make S.P.A.R.K walk by manual control via Bluetooth.

   Made by Nathan-Busse
   */

//including the libraries
#include <SoftwareSerial.h>  // TX RX software library for bluetooth

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
#define tibia_r 180


/* Standing leg positions
   ----------------------
*/

// Left legs
#define FL_stand 135
#define TL_stand 70

// Right legs
#define FR_stand 45
#define TR_stand 110



/* Walking FORWARD leg positions
   -----------------------------
*/

// Left legs
#define FTL_rise 50
#define FFL_forward 130
#define FTL_lower 80
#define FFL_back 140

// Right legs
#define FTR_rise 130
#define FFR_forward 50
#define FTR_lower 100
#define FFR_back 40


/* Time delay
   ----------
*/
#define stand 4000
#define rest 4000
#define move 300
#define rotate 200
#define desync_delay 250

/* PWM setup
   ---------
*/
#define MIN_PulseLength 500
#define MAX_PulseLength 2500
#define MED_PulseLength 2500
#define Frequency 50  // 50 HRz

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int degrees;




//Initializing pins for bluetooth Module
int bluetoothTx = 10;  // bluetooth tx to 2 pin
int bluetoothRx = 11;  // bluetooth rx to 3 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

char command;  //variable to store the data

int previousMillisServo = 0;
int pos = 0;
long servoInterval = 400;
unsigned long currentMillis = 0;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(Frequency);
  Serial.begin(9600);
}

void loop() {

  // Walking forward
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

  // Cycle 1
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_back));
  walk();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_back));
  desync();

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));
  walk();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));
  //desync();
}


void desync_walk() {
  delay(desync_delay);
}

void desync(void) {
  desync_walk();
}
void walking() {
  //while (1)

  delay(move);

  /*

  if (currentMillis - previousMillisServo > servoInterval) {
    previousMillisServo = currentMillis;
    for (pos = 0; pos = pulseWidth;) {
      bluetooth.read();  //delay(15);
    }
    for (pos = 0; pos = pulseWidth;) {
      bluetooth.read();  //delay(15);
        //delay(15);
    }
  }

  */
}
/* Wail till all servos to finish movinng.
   --------------------------------------
*/



/* Wail till all servos to finish movinng.
   --------------------------------------
*/

void walk(void) {
  walking();
}

void turning() {
  //while (1)

  delay(rotate);

  /*

  if (currentMillis - previousMillisServo > servoInterval) {
    previousMillisServo = currentMillis;
    for (pos = 0; pos = pulseWidth;) {
      bluetooth.read();  //delay(15);
    }
    for (pos = 0; pos = pulseWidth;) {
      bluetooth.read();  //delay(15);
        //delay(15);
    }
  }

  */
}

void turn() {
  //while (1)

  turning();

  /*

  if (currentMillis - previousMillisServo > servoInterval) {
    previousMillisServo = currentMillis;
    for (pos = 0; pos = pulseWidth;) {
      bluetooth.read();  //delay(15);
    }
    for (pos = 0; pos = pulseWidth;) {
      bluetooth.read();  //delay(15);
        //delay(15);
    }
  }

  */
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