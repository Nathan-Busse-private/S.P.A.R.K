/* S.P.A.R.K_Bluetooth
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 9 June 2023
   Info:

   Experimenting how to make S.P.A.R.K walk by manual control via Bluetooth.

   Made by Nathan-Busse
   */
#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Declaring pins

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
// Rest position
#define coxae_l 90
#define femur_l 179
#define tibia_l 1

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



// Tibia
#define FT_Rise 60
#define BT_Rise 60
#define FT_Lower 70
#define BT_Lower 70

// Femur
#define FF_Rise_L 115
#define BF_Rise_L 115
#define FF_Lower_L 154
#define BF_Lower_L 154

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
// Define time delay
#define pause 400
#define hold 500

unsigned long myTime = 400;//const long interval = 400;
unsigned long time = 1;//const long interval = 400;
int degrees;
int incomingByte = 0;
int command;   

void setup() {

Serial.begin(9600);
Serial.println("I received");
pwm.begin();
  pwm.setPWMFreq(Frequency);
}

void loop() {



  // When their is a Bluetooth connection S.P.A.R.K will enter its stand position.
  if (Serial.available() >0) {
  // read the incoming byte:
  incomingByte = Serial.read();
}
/*
else
{

Serial.println("Waiting for connection...");
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
    delay(0);
    
  }
*/
switch (incomingByte)
{
{
case 'S':

Stop(1);
Serial.println("Stop");
//lcd.setCursor(5,19);
//lcd.println("");
incomingByte =  'DEC';
}
break;

case 'F':
{
    
Forward(time = millis());;

//lightFront;
Serial.println("Forward");
//lcd.setCursor(5,19);
//lcd.println("Forward");
incomingByte = 'DEC';
}
break;
case 'B':
{
Backward(1);
Serial.println("Backward");
//lcd.setCursor(5,19);
//lcd.println("Backward");
incomingByte = 'DEC';
}
break;
case 'R':
{
turnRight(1);
Serial.println("turn Right");
//lcd.setCursor(5,19);
//lcd.println("Turning Right");
incomingByte = 'DEC';
}
break;
case 'L':
{
turnLeft(1);
Serial.println("turn Left");
//lcd.setCursor(5,19);
//lcd.println("Turning Left");
incomingByte = 'DEC';
//{
//break;
//case 'J':

//horn(1);
//Serial.println("Buzzed");
//incomingByte = 'DEC';

}
}
}


void Forward(int time) // <--- Look into here for millis that dould be the solution to the problem
{

 
  
    
  pwm.setPWM(Coxae_A, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_C, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_D, 0, pulseWidth(C_idle));
  pwm.setPWM(Coxae_B, 0, pulseWidth(C_idle));
//-------------------------------------------------------

  // Rise
  pwm.setPWM(Tibia_A, 0, pulseWidth(FT_Rise));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BT_Rise));
  pwm.setPWM(Femur_A, 0, pulseWidth(FF_Rise_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(BF_Rise_R));
//if (currentMillis - previousMillis >= interval) {

  pwm.setPWM(Tibia_D, 0, pulseWidth(FT_Rise));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BT_Rise));
  pwm.setPWM(Femur_D, 0, pulseWidth(FF_Rise_R));
  pwm.setPWM(Femur_B, 0, pulseWidth(BF_Rise_L));

  // Lower
 pwm.setPWM(Femur_A, 0, pulseWidth(FF_Lower_L));
  pwm.setPWM(Femur_C, 0, pulseWidth(BF_Lower_R));
  pwm.setPWM(Tibia_A, 0, pulseWidth(FT_Lower));
  pwm.setPWM(Tibia_C, 0, pulseWidth(BT_Lower));
//}
//if (currentMillis - previousMillis >= interval) {
  pwm.setPWM(Femur_D, 0, pulseWidth(FF_Lower_R));
  pwm.setPWM(Femur_B, 0, pulseWidth(BF_Lower_L));
  pwm.setPWM(Tibia_D, 0, pulseWidth(FT_Lower));
  pwm.setPWM(Tibia_B, 0, pulseWidth(BT_Lower));
delay(myTime);

    //delay(1); // <----- not really needed (unless this is really a PC simulation) since you are using millis() already!!!!
  }




void Backward(int time)
{

delay(time);
}

void turnLeft(int time)
{

delay(time);
}

void turnRight(int time)
{

delay(time);
}

void Stop(int time)
{
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
  //delay(hold);
delay(time);
}


// Pulsewidth declaration
int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PulseLength, MAX_PulseLength);
  analog_value = int(float(pulse_wide) / 1000000 * Frequency * 4096);
  //Serial.println(analog_value);
  return analog_value;
}