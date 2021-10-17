//------------------------------------------------------------
//Program: Interface_ICM20689.ino 
//Author: Michael Noyce
//Description: Function to test the ICM20689 library
//Notes: Uses the I2Cdev library developed and MPU6050 format
//       developed by Jeff Rowberg
//------------------------------------------------------------

#include "ICM20689.h" 
#include "I2Cdev.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//Acceleration and Orientation Variables
byte rawAX[2], rawAY[2], rawAZ[2];
byte rawGX[2], rawGY[2], rawGZ[2];
int16_t ax, ay, az, gx, gy, gz; 
float rawGYROX, rawGYROY, rawGYROZ;
bool connectionStatus;

//Local Instance of ICM2689 class
ICM20689 ICM20689Test;

void setup() {

    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
  
   Serial.begin(9600);
   ICM20689Test.initialize(); 

   Serial.println("Testing device connections...");
   Serial.println(ICM20689Test.testConnection() ? "ICM20689 connection successful" : "ICM20689 connection failed");
   
}

void loop() {

   ICM20689Test.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 

   Serial.print("a/g:\t");
   Serial.print(ax, DEC); Serial.print("\t");
   Serial.print(ay, DEC); Serial.print("\t");
   Serial.print(az, DEC); Serial.print("\t");
   Serial.print(gx, DEC); Serial.print("\t");
   Serial.print(gy, DEC); Serial.print("\t");
   Serial.print(gz, DEC); Serial.print("\t");   
   Serial.print("\n"); 


  
  delay(500); //Pseudo Sampling delay (make more accurate by updating SMPLRT_DIV)

}
