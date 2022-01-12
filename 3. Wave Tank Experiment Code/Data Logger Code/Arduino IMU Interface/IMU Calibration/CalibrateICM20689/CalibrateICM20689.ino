#include <Wire.h>

#define ADDRESS      0x68 // AD0 = 0 : 0x68, AD0 = 1 : 0x69

#define GYRO_CONFIG             0x1B
#define ACCEL_CONFIG            0x1C

#define ACCEL_XOUT_H            0x3B
#define ACCEL_YOUT_H            0x3D
#define ACCEL_ZOUT_H            0x3F
#define GYRO_XOUT_H             0x43
#define GYRO_YOUT_H             0x45
#define GYRO_ZOUT_H             0x47

#define PWR_MGMT_1              0x6B
#define PWR_MGMT_2              0x6C


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
