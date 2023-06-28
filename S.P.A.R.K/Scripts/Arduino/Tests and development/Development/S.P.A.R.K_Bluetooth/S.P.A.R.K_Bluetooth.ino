/* S.P.A.R.K_Bluetooth
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 28 June 2023
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

/* Walking BACK leg positions
   --------------------------
*/

// Left legs
#define BTL_rise 50
#define BFL_forward 130
#define BTL_lower 70
#define BFL_back 160

// Right legs
#define BTR_rise 50
#define BFR_forward 50
#define BTR_lower 70
#define BFR_back 20

/* Walking FORWARD leg positions
   -----------------------------
*/

// Left legs
#define FTL_rise 50
#define FFL_forward 130
#define FTL_lower 70
#define FFL_back 160

// Right legs
#define FTR_rise 50
#define FFR_forward 50
#define FTR_lower 70
#define FFR_back 20

/* Walking LEFT leg positions
   --------------------------
*/

// Left legs
#define LTL_rise 50
#define LFL_forward 160  // 155
#define LTL_lower 70
#define LFL_back 130

// Right legs
#define LTR_rise 50
#define LFR_forward 45  // 45
#define LTR_lower 70
#define LFR_back 30

/* Walking RIGHT positions
   -----------------------
*/

// Left legs
#define RTL_rise 50
#define RFL_forward 134
#define RTL_lower 70
#define RFL_back 150

// Right legs
#define RTR_rise 50
#define RFR_forward 25
#define RTR_lower 70
#define RFR_back 46


/* Time delay
   ----------
*/
#define stand 4000
#define rest 4000
#define move 300
#define rotate 200

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

  /* Resting position
   ----------------
*/

  // Left leg
  pwm.setPWM(Coxae_A, 0, pulseWidth(coxae_l));  // A
  pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(coxae_l));  // B
  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(Coxae_C, 0, pulseWidth(coxae_r));  // C
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(coxae_r));  // D
  pwm.setPWM(Femur_D, 0, pulseWidth(femur_r));  // D
  pwm.setPWM(Tibia_D, 0, pulseWidth(tibia_r));  // D

  // Left leg
  pwm.setPWM(Coxae_A, 0, pulseWidth(coxae_l));  // A
  pwm.setPWM(Femur_A, 0, pulseWidth(femur_l));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(tibia_l));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(coxae_l));  // B
  pwm.setPWM(Femur_B, 0, pulseWidth(femur_l));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(tibia_l));  // B

  // Right leg
  pwm.setPWM(Coxae_C, 0, pulseWidth(coxae_r));  // C
  pwm.setPWM(Femur_C, 0, pulseWidth(femur_r));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(tibia_r));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(coxae_r));  // D
  pwm.setPWM(Femur_D, 0, pulseWidth(femur_r));  // D
  pwm.setPWM(Tibia_D, 0, pulseWidth(tibia_r));  // D
  delay(rest);

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available() > 0) {  //Checking if there is some data available or not
    command = bluetooth.read();     //Storing the data in the 'command' variable
    Serial.println(command);        //Printing it on the serial monitor

    //Change pin mode only if new command is different from previous.

    /* Walking commands
       ----------------
    */

    currentMillis = millis();
    switch (command) {
      case 'F':  //Moving the Car Forward
        forward();
        break;
      case 'B':  //Moving the Car Backward
        back();

        break;
      case 'L':  //Moving the Car Left
        left();

        break;
      case 'R':  //Moving the Car Right
        right();

        break;
      case 'S':  //Stop
        stop();
        break;

      case 'I':  //Moving the Car Forward right

        break;
      case 'J':  //Moving the Car backward right

        break;
      case 'G':  //Moving the Car Forward left

        break;
      case 'H':  //Moving the Car backward left

        break;

        /* Tricks
     ------
   */
      case 'W':  // Sit

        break;
      case 'w':  // Stand

        break;
      case 'U':  // Jump

        break;
      case 'u':  // Stand

        break;
      case 'V':  // Jog on the spot

        break;
      case 'v':  // Stand

        break;

      /* EMERGENCY SHUTOFF
       -----------------
    */
      case 'x':  // Enable servos

        break;
      case 'X':  // Disable servos

        break;
    }
  }
}

void stop() {
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
}

void forward() {

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
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_forward));
  walk();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_back));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_forward));
  walk();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));
  //walk();

  // Walking forward
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

// Cycle 2
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_forward));
  walk();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_back));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_forward));
  walk();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));
  //walk();
}

void back() {
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

// Cycle 1
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));
  walk();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_forward));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_back));
  walk();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
  // walk();

  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

// Cycle 2
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));
  walk();

  // Lower
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_forward));

  // Front legs
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_back));
  walk();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
  // walk();
}

void left() {
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

// Cycle 1
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(LTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(LTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(LFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(LFR_forward));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(LFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(LFL_forward));
  pwm.setPWM(Tibia_D, 0, pulseWidth(LTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(LTL_rise));

  // Lower
  pwm.setPWM(Femur_A, 0, pulseWidth(LFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(LFR_back));
  pwm.setPWM(Tibia_A, 0, pulseWidth(LTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(LTR_lower));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(LFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(LFL_back));
  pwm.setPWM(Tibia_D, 0, pulseWidth(LTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(LTL_lower));
  //turn();

// Cycle 2
   pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(LTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(LTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(LFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(LFR_forward));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(LFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(LFL_forward));
  pwm.setPWM(Tibia_D, 0, pulseWidth(LTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(LTL_rise));

  // Lower
  pwm.setPWM(Femur_A, 0, pulseWidth(LFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(LFR_back));
  pwm.setPWM(Tibia_A, 0, pulseWidth(LTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(LTR_lower));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(LFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(LFL_back));
  pwm.setPWM(Tibia_D, 0, pulseWidth(LTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(LTL_lower));
  //turn();
}

void right() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

// Cycle 1
  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(RTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(RTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(RFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(RFR_forward));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(RFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(RFL_forward));
  pwm.setPWM(Tibia_D, 0, pulseWidth(RTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(RTL_rise));

  // Lower
  pwm.setPWM(Femur_A, 0, pulseWidth(RFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(RFR_back));
  pwm.setPWM(Tibia_A, 0, pulseWidth(RTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(RTR_lower));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(RFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(RFL_back));
  pwm.setPWM(Tibia_D, 0, pulseWidth(RTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(RTL_lower));
  //turn();

// Cycle 2
  pwm.setPWM(Coxae_A, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(CL_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(CR_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(CR_idle));

  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(RTL_rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(RTR_rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(RFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(RFR_forward));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(RFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(RFL_forward));
  pwm.setPWM(Tibia_D, 0, pulseWidth(RTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(RTL_rise));

  // Lower
  pwm.setPWM(Femur_A, 0, pulseWidth(RFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(RFR_back));
  pwm.setPWM(Tibia_A, 0, pulseWidth(RTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(RTR_lower));
  turn();

  pwm.setPWM(Femur_D, 0, pulseWidth(RFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(RFL_back));
  pwm.setPWM(Tibia_D, 0, pulseWidth(RTR_lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(RTL_lower));
  //turn();
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