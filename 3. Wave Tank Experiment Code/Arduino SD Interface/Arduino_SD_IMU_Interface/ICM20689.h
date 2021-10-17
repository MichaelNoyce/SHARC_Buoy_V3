//------------------------------------------------------------
//Program: ICM20689.h I
//Author: Michael Noyce
//Description: Header file with the ICM20689 IMU register defines,
//             classes 
//Note: RA = register address (e.g. ICM20689_RA_PWR_MGMT_1)
//------------------------------------------------------------

#ifndef ICM20689_H
#define ICM20689_H

#include <Arduino.h>
#include "I2cdev.h"

#define ICM20689_SLAVE_ADDRESS              0x68 // device address (ADDR SEL in position 0) 

//Configuration registers
#define ICM20689_RA_GYRO_CONFIG             0x1B
#define ICM20689_RA_ACCEL_CONFIG            0x1C

//Acceleration registers
#define ICM20689_RA_ACCEL_XOUT_H            0x3B
#define ICM20689_RA_ACCEL_XOUT_L            0x3C
#define ICM20689_RA_ACCEL_YOUT_H            0x3D
#define ICM20689_RA_ACCEL_YOUT_L            0x3E
#define ICM20689_RA_ACCEL_ZOUT_H            0x3F
#define ICM20689_RA_ACCEL_ZOUT_L            0x40

#define ICM20689_ACCEL_FS_SEL_LENGTH        2
#define ICM20689_ACCEL_FS_SEL_BIT           4  
#define ICM20689_ACCEL_FS_2G                0x0
#define ICM20689_ACCEL_FS_4G                0x01
#define ICM20689_ACCEL_FS_8G                0x02
#define ICM20689_ACCEL_FS_16G               0x03

//Gyroscope registers
#define ICM20689_RA_GYRO_XOUT_H             0x43
#define ICM20689_RA_GYRO_XOUT_L             0x44
#define ICM20689_RA_GYRO_YOUT_H             0x45
#define ICM20689_RA_GYRO_YOUT_L             0x46
#define ICM20689_RA_GYRO_ZOUT_H             0x47
#define ICM20689_RA_GYRO_ZOUT_L             0x48

#define ICM20689_GYRO_FS_SEL_LENGTH        2
#define ICM20689_GYRO_FS_SEL_BIT           4  
#define ICM20689_GYRO_FS_250_DPS           0x0
#define ICM20689_GYRO_FS_500_DPS           0x01
#define ICM20689_GYRO_FS_1000_DPS          0x02
#define ICM20689_GYRO_FS_2000_DPS          0x03

//Power registers
#define ICM20689_RA_PWR_MGMT_1              0x6B // 
#define ICM20689_RA_PWR_MGMT_2              0x6C //

//PWR_MGMT_1
#define ICM20689_DEVICE_RESET               7
#define ICM20689_SLEEP_BIT                  6
#define ICM20689_ACCEL_CYCLE_BIT            5
#define ICM20689_GYRO_STANDBY_BIT           4
#define ICM20689_TEMP_DIS_BIT               3
#define ICM20689_CLKSEL_LENGTH              3
#define ICM20689_CLKSEL_BIT                 2
#define ICM20689_SOFT_RESET                 0x81
#define ICM20689_CLK_INTERNAL               0x0
#define ICM20689_CLK_PLL_INTERNAL_AUTO      0x01
#define ICM20689_STOP_CLK                   0x07

//PWR_MGMT_2
#define ICM20689_FIFO_LP_EN_BIT             7
#define ICM20689_DMP_LP_DIS_BIT             6
#define ICM20689_STBY_XA_BIT                5
#define ICM20689_STBY_YA_BIT                4
#define ICM20689_STBY_ZA_BIT                3
#define ICM20689_STBY_XG_BIT                2
#define ICM20689_STBY_XG_BIT                1
#define ICM20689_STBY_XG_BIT                0

//Temperature Sensor Registers 
#define ICM20689_RA_TEMP_OUT_H              0x41
#define ICM20689_RA_TEMP_OUT_L              0x42

//WHO_AM_I Register
#define ICM20689_RA_WHO_AM_I                0x75
#define ICM20689_WHO_AM_I_BIT               7
#define ICM20689_WHO_AM_I_LENGTH            8

//ACCEL_OUT Registers
#define ICM20689_ACCEL_XOUT_H            0x3B
#define ICM20689_ACCEL_XOUT_L            0x3C
#define ICM20689_ACCEL_YOUT_H            0x3D
#define ICM20689_ACCEL_YOUT_L            0x3E
#define ICM20689_ACCEL_ZOUT_H            0x3F
#define ICM20689_ACCEL_ZOUT_L            0x40

//GYRO_OUT Registers 


class ICM20689 { 
  public: 
    
    ICM20689(uint8_t address=ICM20689_SLAVE_ADDRESS);
    
    //Initialization function
    void initialize();

    //PWR_MGMT_1 Register
    void setClockSource(uint8_t source);
    void setTempSensorEnable();
    void setGyroStandby();
    void setAccelCycle();
    void setSleepMode();
    void reset(); 
    void softReset(); // (see datasheet pg. 25 sec. 4.19)


    //PWR_MGMT_2 Register 
    void setFIFOLowPowerEnable();
    void setDMPLowPowerDisable();
    void setstandyByXAccelEnabled(); //1 X-accelerometer off, 0 on 
    void setstandyByYAccelEnabled(); //1 Y-accelerometer off, 0 on 
    void setstandyByZAccelEnabled(); //1 Z-accelerometer off, 0 on 
    void setstandyByXGyroEnabled(); //1 X-gyroscope off, 0 on 
    void setstandyByYGyroEnabled(); //1 Y-gyroscope off, 0 on 
    void setstandyByZGyroEnabled(); //1 Z-gyroscope off, 0 on 
    
    //GYRO_CONFIG Registers
    void setFullScaleGyroRange(uint8_t range); 

    //ACCEL_CONFIG Registers
    void setFullScaleAccelRange(uint8_t range);

    //WHO_AM_I Register
     uint8_t getDeviceID();
     bool testConnection();

     //TEMP_OUT Registers 
     int16_t getTemperature(); 

     //ACCEL_OUT Registers 
     void getAcceleration(int16_t* x, int16_t* y, int16_t* z);
     int16_t getAccelerationX();
     int16_t getAccelerationY();
     int16_t getAccelerationZ();
     

    private:
        uint8_t devAddr;
        uint8_t buffer[14];
    
};


#endif
