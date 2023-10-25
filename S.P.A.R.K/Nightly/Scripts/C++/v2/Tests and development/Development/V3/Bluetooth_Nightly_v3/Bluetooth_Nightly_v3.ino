// Libraries
#include <SoftwareSerial.h>
#include <spark_pwm.h>
#include <Wire.h>

// PWM channel declarations
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

// Position declarations

// Coxae idle positions
#define C_idle 90

// Rest positions
#define FL_rest 180
#define TL_rest 0

#define FR_rest 0
#define TR_rest 180

// Stand position
#define FL_stand 135
#define TL_stand 65

#define FR_stand 45
#define TR_stand 115

// Forward position
#define FTL_rise 50
#define FFL_forward 120
#define FTL_lower 65
#define FFL_back 150

#define FTR_rise 130
#define FFR_forward 60
#define FTR_lower 115
#define FFR_back 30

// Time delay
#define stand 400
#define rest 400
#define femur_hold 400
#define tibia_hold 400
#define rotate 200
#define hold 400

// PWM setup
#define MIN_PulseLength 500
#define MAX_PulseLength 2500
#define MED_PulseLength 2500
#define Frequency 50  // 50HRz

spark_pwm pwm = spark_pwm();
int degrees;

// Bluetooth setup
int bluetoothTX = 10;
int bluetoothRX = 11;
SoftwareSerial bluetooth(bluetoothTX, bluetoothRX);
char command;  // Variable to store incoming data.

void setup() {

  // PWM initialization
  pwm.begin();
  pwm.setPWMFreq(Frequency);

  // Rest at startup
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));   // A
  pwm.setPWM(Femur_A, 0, pulseWidth(FL_rest));  // A
  pwm.setPWM(Tibia_A, 0, pulseWidth(TL_rest));  // A

  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));   // B
  pwm.setPWM(Femur_B, 0, pulseWidth(FL_rest));  // B
  pwm.setPWM(Tibia_B, 0, pulseWidth(TL_rest));  // B

  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));   // C
  pwm.setPWM(Femur_C, 0, pulseWidth(FR_rest));  // C
  pwm.setPWM(Tibia_C, 0, pulseWidth(TR_rest));  // C

  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));   // D
  pwm.setPWM(Femur_D, 0, pulseWidth(FR_rest));  // D
  pwm.setPWM(Tibia_D, 0, pulseWidth(TR_rest));  // D
  delay(rest);

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available() > 0) {  //Checking if there is some data available or not
    command = bluetooth.read();     //Storing the data in the 'command' variable
    Serial.println(command);        //Printing it on the serial monitor

    switch (command) {
      case 'F':  // Moving Forward
        forward();
        break;

      case 'S':  // Stop
        stop();
        break;
    }
  }
}

void stop() {
  // Stand mode
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));

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
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));

  // Cycle 1
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_forward));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));

  // Cycle 2
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_forward));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));

  // Cycle 3
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_forward));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));

  // Cycle 4
  // Back legs
  // Rise
  pwm.setPWM(Tibia_D, 0, pulseWidth(FTR_rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(FTL_rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FFR_forward));
  pwm.setPWM(Femur_B, 0, pulseWidth(FFL_forward));
  femur_wait();

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
  tibia_wait();

  // Lower
  pwm.setPWM(Tibia_A, 0, pulseWidth(FTL_lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(FTR_lower));
  pwm.setPWM(Femur_A, 0, pulseWidth(FFL_back));
  pwm.setPWM(Femur_C, 0, pulseWidth(FFR_back));
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


// PulseWidth declaration
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  return analog_value;
}
