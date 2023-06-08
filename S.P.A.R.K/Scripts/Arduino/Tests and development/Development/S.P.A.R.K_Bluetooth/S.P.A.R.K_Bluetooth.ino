/* S.P.A.R.K_Bluetooth
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 8 June 2023
   Info:

   Experimenting how to make S.P.A.R.K walk by manual control via Bluetooth.

   Made by Nathan-Busse
   */

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

// Leg position identification
// Degree for rest
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
// Standing position
#define C_idle 91       // Coxae idle
#define FF_stand_L 134  // Femur left while standing
#define FF_stand_R 46   // Femur right while standing

#define BF_stand_L 134  // Femur left while standing
#define BF_stand_R 46   // Femur right while standing

#define FT_stand 70  // Tibia stand
#define BT_stand 70

// Define time delay
#define pause 400
#define hold 4000
// Walking position

// Tibia
#define FT_Rise 60
#define BT_Rise 60
#define FT_Lower 70
#define BT_Lower 70

// Femur
#define FF_Rise_L 115
#define BF_Rise_L 115
#define FF_Lower_L 135
#define BF_Lower_L 135

#define FF_Rise_R 45
#define BF_Rise_R 45
#define FF_Lower_R 25
#define BF_Lower_R 25


// PWM setup
#define MIN_PulseLength 500
#define MAX_PulseLength 2500
#define MED_PulseLength 2500
#define Frequency 50  // 50 HRz

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int degrees;


//Initializing pins for bluetooth Module
int bluetoothTx = 3;  // bluetooth tx to 2 pin
int bluetoothRx = 4;  // bluetooth rx to 3 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

char command;  //variable to store the data

void setup() {
  //Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600);
  bluetooth.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(Frequency);
}

void loop() {

  // When their is no Bluetooth connection S.P.A.R.K will enter its rest position
  if (bluetooth.available() < 1) {

    pwm.setPWM(Coxae_A, 0, pulseWidth(coxae_l));  // A
    pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
    pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

    pwm.setPWM(Coxae_B, 0, pulseWidth(coxae_l));  // B
    pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
    pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

    pwm.setPWM(Coxae_C, 0, pulseWidth(coxae_r));  // C
    pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
    pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

    pwm.setPWM(Coxae_D, 0, pulseWidth(coxae_r));  // D
    pwm.setPWM(Femur_D, 0, pulseWidth(femur_r));  // D
    pwm.setPWM(Tibia_D, 0, pulseWidth(tibia_r));  // D
    delay(hold);
  }


  // When their is a Bluetooth connection S.P.A.R.K will enter its stand position.
  else
    (bluetooth.available() > 0);
  {                              //Checking if there is some data available or not
    command = bluetooth.read();  //Storing the data in the 'command' variable
    Serial.println(command);     //Printing it on the serial monitor

    //Change pin mode only if new command is different from previous.
    switch (command) {
      case 'F':  //Moving the Car Forward
        pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
        pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
        pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));
        pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));

        // Rise
        pwm.setPWM(Tibia_A, 0, pulseWidth(FT_Rise));
        pwm.setPWM(Tibia_C, 0, pulseWidth(BT_Rise));
        pwm.setPWM(Femur_A, 0, pulseWidth(FF_Rise_L));
        pwm.setPWM(Femur_C, 0, pulseWidth(BF_Rise_R));
        delay(pause);

        pwm.setPWM(Tibia_D, 0, pulseWidth(FT_Rise));
        pwm.setPWM(Tibia_B, 0, pulseWidth(BT_Rise));
        pwm.setPWM(Femur_D, 0, pulseWidth(FF_Rise_R));
        pwm.setPWM(Femur_B, 0, pulseWidth(BF_Rise_L));

        // Lower
        pwm.setPWM(Femur_A, 0, pulseWidth(FF_Lower_L));
        pwm.setPWM(Femur_C, 0, pulseWidth(BF_Lower_R));
        pwm.setPWM(Tibia_A, 0, pulseWidth(FT_Lower));
        pwm.setPWM(Tibia_C, 0, pulseWidth(BT_Lower));
        delay(pause);

        pwm.setPWM(Femur_D, 0, pulseWidth(FF_Lower_R));
        pwm.setPWM(Femur_B, 0, pulseWidth(BF_Lower_L));
        pwm.setPWM(Tibia_D, 0, pulseWidth(FT_Lower));
        pwm.setPWM(Tibia_B, 0, pulseWidth(BT_Lower));
        break;
      case 'B':  //Moving the Car Backward

        break;
      case 'L':  //Moving the Car Left

        break;
      case 'R':  //Moving the Car Right

        break;
      case 'S':  //Stop
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
        break;
    }
  }
}

// Pulsewidth declaration
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  Serial.println(analog_value);
  return analog_value;
}
