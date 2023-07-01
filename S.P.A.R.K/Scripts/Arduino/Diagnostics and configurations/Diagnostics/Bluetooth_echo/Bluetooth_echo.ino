
/*
Bluetooth_echo
Project: S.P.A.R.K 
Start date: 30 June 2023
Last edited: 1 July 2023
Script name: Bluetooth_echo
Info:

This code tests that the HC-06 bluetooth module is working
 properly by establishing a connection between the 
 module and the device throough a 3rd party app called
 Bluetooth terminal and is developed by qwerty.

To determine that their is a successful handshake between 
the module and the device the user will enter a command via
the app to enable and disable built-in LED in pin 13.

When a recieved command has been proccessed successfuly,
the Arduino will echo a string to the app notifying
the user the command has been recieved and has been executed

Input commands:

LED on: "1" 
Return string: LED is ON.

LED off: "2"
Return string: LED is OFF.

HELP: "?"
Return string: Prints the executable input commands.

Made by Nathan Busse
*/

// Libraries
#include <SoftwareSerial.h>  
SoftwareSerial BT(0, 1);
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup() {
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  BT.println("Hello from Arduino");
}
char a;  // stores incoming character from other device
void loop() {
  if (BT.available())
  // if text arrived in from BT serial...
  {
    a = (BT.read());
    if (a == '1') {
      digitalWrite(13, HIGH);
      BT.println("LED is ON");
      Serial.println("ON");
    }
    if (a == '2') {
      digitalWrite(13, LOW);
      BT.println("LED is OFF");
    }
    if (a == '?') {
      BT.println("Send '1' to turn LED on");
      BT.println("Send '2' to turn LED off");
    }
  }
}
