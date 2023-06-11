/* S.P.A.R.K_Bluetooth
   Project: S.P.A.R.K
   Start date: 5 June 2023
   Last edited: 11 June 2023
   Info:

   Experimenting how to make S.P.A.R.K walk by manual control via Bluetooth.

   Made by Nathan-Busse
   */

//including the libraries
#include <SoftwareSerial.h> // TX RX software library for bluetooth




//Initializing pins for bluetooth Module
int bluetoothTx = 10; // bluetooth tx to 2 pin
int bluetoothRx = 11; // bluetooth rx to 3 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);



char command ; //variable to store the data

void setup() 
{       
  //Set the baud rate of serial communication and bluetooth module at same rate.
  Serial.begin(9600);  
  bluetooth.begin(9600);

  
}

void loop(){
  if(bluetooth.available() > 0){  //Checking if there is some data available or not
    command = bluetooth.read();   //Storing the data in the 'command' variable
    Serial.println(command);      //Printing it on the serial monitor
    
    //Change pin mode only if new command is different from previous.

    /* Walking commands
       ----------------
    */      
    switch(command){
    case 'F':  //Moving the Car Forward
      
      break;
    case 'B':  //Moving the Car Backward
      
      break;
    case 'L':  //Moving the Car Left
      
      break;
    case 'R':   //Moving the Car Right
     
      break;
    case 'S':   //Stop
      
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
    case 'x': // Enable servos

    break;
    case 'X': // Disable servos
      
    break;


      }
    }
  }

 
  