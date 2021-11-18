//-------------------------------------------------------------------
//Name: ICM20689 Interface
//Author: Michael Noyce 
//Description: i2c interface for the ICM20689 IMU  
//-------------------------------------------------------------------
#include <Wire.h>

#define ADDRESS      0x68 // device address (ADDR SEL in position 0) 

//Configuration registers
#define GYRO_CONFIG             0x1B
#define ACCEL_CONFIG            0x1C

//Acceleration registers
#define ACCEL_XOUT_H            0x3B
#define ACCEL_XOUT_L            0x3C
#define ACCEL_YOUT_H            0x3D
#define ACCEL_YOUT_L            0x3E
#define ACCEL_ZOUT_H            0x3F
#define ACCEL_ZOUT_L            0x40

//Gyroscope registers
#define GYRO_XOUT_H             0x43
#define GYRO_XOUT_L             0x44
#define GYRO_YOUT_H             0x45
#define GYRO_YOUT_L             0x46
#define GYRO_ZOUT_H             0x47
#define GYRO_ZOUT_L             0x48

//Power registers
#define PWR_MGMT_1              0x6B // 
#define PWR_MGMT_2              0x6C //

//Temperature Sensor Registers 
#define TEMP_OUT_H              0x41
#define TEMP_OUT_L              0x42

//Acceleration and Orientation Variables
int16_t rawAX, rawAY, rawAZ;
int16_t rawGX, rawGY, rawGZ;
float rawACCX, rawACCY, rawACCZ;
float rawGYROX, rawGYROY, rawGYROZ;

void setup() {
  
   Serial.begin(9600); 
   Wire.begin(); //Initialize i2c

   //Power Management Configuration
   Wire.beginTransmission(ADDRESS);
   Wire.write(PWR_MGMT_1); //Power management register 1
   Wire.write(0x01); //binary 
   
   if (Wire.endTransmission () == 0)
    {
    Serial.println("PWR_MGMT_1 configured");
    }
   else
    {
    Serial.println("PWR_MGMT_1 not configured, i2c issue");
    }

   Wire.beginTransmission(ADDRESS);
   Wire.write(PWR_MGMT_2); //Power management register 2
   Wire.write(0x00);
   Wire.endTransmission();
   if (Wire.endTransmission () == 0)
    {
    Serial.println("PWR_MGMT_2 configured");
    }
   else
    {
    Serial.println("PWR_MGMT_2 not configured, i2c issue");
    }

    //Accelerometer Configuration 
   Wire.beginTransmission(ADDRESS);
   Wire.write(ACCEL_CONFIG); //Accelerometer configuration register 2
   Wire.write(0x00);
   Wire.endTransmission();
   if (Wire.endTransmission () == 0)
    {
    Serial.println("ACCEL_CONFIG configured");
    }
   else
    {
    Serial.println("ACCEL_CONFIG not configured, i2c issue");
    }
    
    //Gyroscope Configuration 
   Wire.beginTransmission(ADDRESS);
   Wire.write(GYRO_CONFIG); //Accelerometer configuration register 2
   Wire.write(0x00);
   Wire.endTransmission();
   if (Wire.endTransmission () == 0)
    {
    Serial.println("ACCEL_CONFIG configured");
    }
   else
    {
    Serial.println("ACCEL_CONFIG not configured, i2c issue");
    }    

}

void loop() {

  //Retrieve X Acceleration and print out 
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS,2,1);  

  rawAX = (Wire.read() << 8 | Wire.read());
  rawACCX = (float)rawAX/16384*9.81;
  
  Serial.print(rawACCX, DEC);
  Serial.print("\t"); 

  
  //Retrieve Y Acceleration and print out 
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_YOUT_H);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS,2,1);  
  
  rawAY = (Wire.read() << 8 | Wire.read());
  rawACCY = (float)rawAY/16384*9.81;
  
  Serial.print(rawACCY, DEC);
  Serial.print("\t"); 

    //Retrieve Z Acceleration and print out 
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_ZOUT_H);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS,2,1);  

  rawAZ = (Wire.read() << 8 | Wire.read());
  rawACCZ = (float)rawAZ/16384*9.81;
  
  Serial.print(rawACCZ, DEC);
  Serial.print("\n"); 
  
  delay(1000); //Pseudo Sampling delay (make more accurate by updating SMPLRT_DIV)
}
