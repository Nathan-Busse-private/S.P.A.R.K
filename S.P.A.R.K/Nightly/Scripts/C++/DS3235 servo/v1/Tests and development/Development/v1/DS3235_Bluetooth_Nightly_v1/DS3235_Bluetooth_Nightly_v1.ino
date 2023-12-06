/* S.P.A.R.K_Bluetooth_Nightly
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 14 October 2023
   Info:

   Experimenting how to make S.P.A.R.K walk by manual control via Bluetooth.

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
#define FL_stand 150
#define TL_stand 45  // 65

// Right legs
#define FR_stand 30
#define TR_stand 135  // 115


/* Walking FORWARD leg positions
   -----------------------------
*/

/* Walking leg positions
   ---------------------
*/

// Left legs
#define TL_rise 40
#define FL_forward 135
#define TL_lower 45
#define FL_back 160

// Right legs
#define TR_rise 140
#define FR_forward 45
#define TR_lower 135
#define FR_back 20


/* Walking BACK leg positions
   --------------------------
*/
// Left legs
#define BTL_rise 40
#define BFL_forward 135
#define BTL_lower 45  // 65
#define BFL_back 160

// Right legs
#define BTR_rise 140
#define BFR_forward 45
#define BTR_lower 135  // 115
#define BFR_back 20

/* Walking LEFT leg positions
   --------------------------
*/

// Left legs
#define LTL_rise 40
#define LFL_forward 160  // 155
#define LTL_lower 45     // 65
#define LFL_back 130

// Right legs
#define LTR_rise 140
#define LFR_forward 45  // 45
#define LTR_lower 135
#define LFR_back 30

/* Walking RIGHT positions
   -----------------------
*/
// Left legs
#define RTL_rise 40
#define RFL_forward 134
#define RTL_lower 45  // 65
#define RFL_back 150

// Right legs
#define RTR_rise 140
#define RFR_forward 25
#define RTR_lower 135  // 115
#define RFR_back 46

/* Pivot left
-------------
*/
#define FCL0 70   // Coxae idle
#define FCR0 70   // Coxae idle
#define BCL0 110  // Coxae idle
#define BCR0 110  // Coxae idle

#define FCL10 74   // Coxae idle
#define FCR10 74   // Coxae idle
#define BCL10 106  // Coxae idle
#define BCR10 106  // Coxae idle

#define FCL20 78   // Coxae idle
#define FCR20 78   // Coxae idle
#define BCL20 102  // Coxae idle
#define BCR20 102  // Coxae idle

#define FCL30 82  // Coxae idle
#define FCR30 82  // Coxae idle
#define BCL30 98  // Coxae idle
#define BCR30 98  // Coxae idle

#define FCL40 86  // Coxae idle
#define FCR40 86  // Coxae idle
#define BCL40 94  // Coxae idle
#define BCR40 94  // Coxae idle

#define FCL50 90  // Coxae idle
#define FCR50 90  // Coxae idle
#define BCL50 90  // Coxae idle
#define BCR50 90  // Coxae idle

/* Pivot Right
-------------
*/
#define BCL60 86  // Coxae idle
#define BCR60 86  // Coxae idle
#define FCL60 94  // Coxae idle
#define FCR60 94  // Coxae idle

#define BCL70 82  // Coxae idle
#define BCR70 82  // Coxae idle
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

/* Time delay
   ----------
*/
#define stand 400
#define rest 400
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

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available() > 0) {  //Checking if there is some data available or not
    command = bluetooth.read();     //Storing the data in the 'command' variable
    Serial.println(command);        //Printing it on the serial monitor

    //Change pin mode only if new command is different from previous.

    /* tibia_waiting commands
     ----------------------
  */

    currentMillis = millis();
    switch (command) {
      case 'F':  // Moving Forward
        forward();
        break;
      case 'B':  // Moving Backward
        back();

        break;
      case 'L':  // Moving Left
        left();

        break;
      case 'R':  // Moving Right
        right();

        break;
      case 'S':  // Stop
        stop();
        break;

      case 'Z':  // Sleep
        sleep();
        break;

      case 'ZS':  // Sleep
        rest_stand();
        break;

        /*  Tricks
    ------
*/
      case 'W':  // Sit
        sit();

        break;

      case 'U':  // Jump

        break;

      case 'J':  // Jog on the spot

        break;

      case '0':  // pivot 180 degrees
        pivot_pos_0();
        break;

      case '1':  // pivot 180 degrees
        pivot_pos_10();

        break;

      case '2':  // pivot 180 degrees
        pivot_pos_20();

        break;

      case '3':  // pivot 180 degrees
        pivot_pos_30();

        break;

      case '4':  // pivot 180 degrees
        pivot_pos_40();

        break;

      case '5':  // pivot 180 degrees
        pivot_pos_50();

        break;

      case '6':  // pivot 180 degrees
        pivot_pos_60();

        break;

      case '7':  // pivot 180 degrees
        pivot_pos_70();

        break;

      case '8':  // pivot 180 degrees
        pivot_pos_80();

        break;

      case '9':  // pivot 180 degrees
        pivot_pos_90();

        break;

      case 'q':  // pivot 180 degrees
        pivot_pos_100();

        break;

      case '~':  // pivot 180 degrees
        pivot_pos_50();

        break;

        /* EMERGENCY SHUTOFF
   -----------------
*/

      case 'E':  // Disable servos
        emergency_shutoff();
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
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));

  // Cycle 2
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));

  // Cycle 3
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));

  // Cycle 4
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(BTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(BFR_back));
  pwm.setPWM(Femur_B, 0, pulseWidth(BFL_back));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(BTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(BFL_forward));
  pwm.setPWM(Femur_C, 0, pulseWidth(BFR_forward));
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

  // Cycle 3
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

  // Cycle 4
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

  // Cycle 3
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

  // Cycle 4
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
}

void sleep() {

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
}

void pivot_pos_0() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL0));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL0));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR0));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR0));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_10() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL10));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL10));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR10));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR10));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_20() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL20));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL20));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR20));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR20));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_30() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL30));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL30));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR30));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR30));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_40() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL40));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL40));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR40));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR40));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_50() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL50));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL50));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR50));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR50));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_60() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL60));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL60));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR60));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR60));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_70() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL70));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL70));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR70));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR70));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_80() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL80));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL80));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR80));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR80));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_90() {

  pwm.setPWM(Coxae_A, 0, pulseWidth(FCL90));
  pwm.setPWM(Coxae_B, 0, pulseWidth(BCL90));
  pwm.setPWM(Coxae_C, 0, pulseWidth(BCR90));
  pwm.setPWM(Coxae_D, 0, pulseWidth(FCR90));

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
}

void pivot_pos_100() {

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
}

void emergency_shutoff() {

  pwm.setPWM(Coxae_A, 0, 0);  // A
  pwm.setPWM(Femur_A, 0, 0);  // A
  pwm.setPWM(Tibia_A, 0, 0);  // A

  pwm.setPWM(Coxae_B, 0, 0);  // B
  pwm.setPWM(Femur_B, 0, 0);  // B
  pwm.setPWM(Tibia_B, 0, 0);  // B

  pwm.setPWM(Coxae_C, 0, 0);  // C
  pwm.setPWM(Femur_C, 0, 0);  // C
  pwm.setPWM(Tibia_C, 0, 0);  // C

  pwm.setPWM(Coxae_D, 0, 0);  // D
  pwm.setPWM(Femur_D, 0, 0);  // D
  pwm.setPWM(Tibia_D, 0, 0);  // D
}

void sit() {
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

void rest_stand() {

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

  pwm.setPWM(Femur_A, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_stand));
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_stand));
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_stand));

  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_stand));
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_stand));
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_stand));
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

void turning() {
  delay(rotate);
}

void turn() {
  turning();
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
