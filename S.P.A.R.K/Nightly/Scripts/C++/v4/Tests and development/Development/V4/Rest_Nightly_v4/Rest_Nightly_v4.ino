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
#define TL_rest 180

#define FR_rest 0
#define TR_rest 0


// Time delay
#define rest 400

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
  
}

// PulseWidth declaration
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  return analog_value;
}
