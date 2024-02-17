/*
   S.P.A.R.K_command_bug_test
   Project: S.P.A.R.K
   Start date: 2 September 2023
   Last edited: 2 September 2023
   Info:

  This script will determine whether S.P.A.R.K's code
  is the colperate for not responding to commands 
  when the button is held down in the app. 
   Made by Nathan-Busse

*/

//including the libraries
#include <SoftwareSerial.h>  // TX RX software library for bluetooth

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
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  if (bluetooth.available() > 0) {  //Checking if there is some data available or not
    command = bluetooth.read();     //Storing the data in the 'command' variable
    Serial.println(command);        //Printing it on the serial monitor
  }
}
