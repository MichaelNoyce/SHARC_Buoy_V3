//------------------------------------------------------------
//Program: Interface_ICM20689.ino I
//Author: Michael Noyce
//Description: Function to test the ICM20689 library
//Notes: Uses the I2Cdev library developed and MPU6050 format
//       developed by Jeff Rowberg
//------------------------------------------------------------


#include <Wire.h>
#include "ICM20689.h" 

//Acceleration and Orientation Variables
byte rawAX[2], rawAY[2], rawAZ[2];
byte rawGX[2], rawGY[2], rawGZ[2];
float rawACCX, rawACCY, rawACCZ;
float rawGYROX, rawGYROY, rawGYROZ;
bool connectionStatus;

//Local Instance of ICM2689 class
ICM20689 ICM20689Test;

void setup() {
  
   Serial.begin(9600);
   ICM20689Test.initialize(); 
   
}

void loop() {

    connectionStatus = ICM20689Test.testConnection();

   delay(1000);

  if (connectionStatus)
    Serial.println("Connected!");
  else
    Serial.println("Failed!");



  //Serial.print(rawACCX/16384*9.81, DEC);
  //Serial.print("\t"); 

  //Serial.print(rawACCY/16384*9.81, DEC);
  //Serial.print("\t"); 

  //Serial.print(rawACCZ/16384*9.81, DEC);
  //Serial.print("\n"); 

  
  delay(500); //Pseudo Sampling delay (make more accurate by updating SMPLRT_DIV)

}
