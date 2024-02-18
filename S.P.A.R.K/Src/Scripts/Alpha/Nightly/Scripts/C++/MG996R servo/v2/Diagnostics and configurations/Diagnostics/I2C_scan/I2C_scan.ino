/* I2C_scan
  Project: O.D.R.I.N mini
  Start date: 3 April 2023
  Last edited: 11 April 2023
  Info:

  The Arduino scans for devices connected to the I2C communication bus to detect if the device's logic board is working properly.
  This code is designed for the Adafruit PCA9865 16 channel servo driver.
  If a device is detected the Arduino will print the device's communication address including chained PCA9865 boards seperatly via the serial monitor.

  Made by Nathan-Busse.
*/

// The code

// Calling Libraries


#include <Wire.h>


void setup() {
  Wire.begin();

  Serial.begin(9600);
  while (!Serial)
    ;  // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);  // wait 5 seconds for next scan
}