//------------------------------------------------------------
//Program: ICM20689.cppI
//Author: Michael Noyce
//Description: Cpp Library file of the ICM20689
//Notes: Uses the I2Cdev library developed by Jeff Rowberg
//------------------------------------------------------------

#include "ICM20689.h"


/** Specific address constructor.
 * @param address I2C address, uses default I2C address if none is specified
 */

 ICM20689::ICM20689(uint8_t address):devAddr(ICM20689_SLAVE_ADDRESS) {
}

/** Initialize ICM20689
 * @param None
 * @see 
 * @return 
 */
void ICM20689::initialize() {
  softReset(); 
  setClockSource(ICM20689_CLK_PLL_INTERNAL_AUTO);
  setFullScaleAccelRange(ICM20689_ACCEL_FS_2G);
  setFullScaleGyroRange(ICM20689_GYRO_FS_250_DPS);
}


/** Test device connections
 * @param None
 * @see 
 * @return 
 */
bool ICM20689::testConnection() {
    return getDeviceID() == 0x98;
}

//PWR_MGMT Registers

/** Set the clock source for the ICM20689
 * @param None
 * @see 
 * @return 
 */
void ICM20689::setClockSource(uint8_t source) {
    I2Cdev::writeBits(ICM20689_SLAVE_ADDRESS, ICM20689_RA_PWR_MGMT_1, ICM20689_CLKSEL_BIT, ICM20689_CLKSEL_LENGTH, source);
}


/** Soft reset in case of incorrect power up ICM20689
 * @see 
 * @return 
 */
void ICM20689::softReset() {
   I2Cdev::writeByte(ICM20689_SLAVE_ADDRESS, ICM20689_RA_PWR_MGMT_1, ICM20689_SOFT_RESET); 
}

//ACCEL_CONFIG Registers

/** Set Accelerometer measurement range
 * @see 
 * @return 
 */
void ICM20689::setFullScaleAccelRange(uint8_t range) {
    I2Cdev::writeBits(ICM20689_SLAVE_ADDRESS, ICM20689_RA_ACCEL_CONFIG, ICM20689_ACCEL_FS_SEL_BIT, ICM20689_ACCEL_FS_SEL_LENGTH, range);
}

//Gyro_CONFIG Registers

/** Set Gyroscope measurement range
 * @see 
 * @return 
 */
void ICM20689::setFullScaleGyroRange(uint8_t range) {
    I2Cdev::writeBits(ICM20689_SLAVE_ADDRESS, ICM20689_RA_GYRO_CONFIG, ICM20689_GYRO_FS_SEL_BIT, ICM20689_GYRO_FS_SEL_LENGTH, range);
}

//WHO_AM_I Registers

/** Get Device ID.
 * This register is used to verify the identity of the device (0b110100, 0x34).
 * @return Device ID (8 bit) 0x98 
 * @see ICM20689_RA_WHO_AM_I
 * @see ICM20689_WHO_AM_I_BIT
 * @see ICM20689_WHO_AM_I_LENGTH
 */
uint8_t ICM20689::getDeviceID() {
    I2Cdev::readBits(devAddr, ICM20689_RA_WHO_AM_I, ICM20689_WHO_AM_I_BIT, ICM20689_WHO_AM_I_LENGTH, buffer);
    return buffer[0];
}


//ACCEL_OUT Registers

/** Get 3-axis accelerometer readings.
 * @param x 16-bit signed integer container for X-axis acceleration
 * @param y 16-bit signed integer container for Y-axis acceleration
 * @param z 16-bit signed integer container for Z-axis acceleration
 * @see 
 */
void ICM20689::getAcceleration(int16_t* x, int16_t* y, int16_t* z) {
    I2Cdev::readBytes(devAddr, ICM20689_ACCEL_XOUT_H, 6, buffer);
    *x = (((int16_t)buffer[0]) << 8) | buffer[1];
    *y = (((int16_t)buffer[2]) << 8) | buffer[3];
    *z = (((int16_t)buffer[4]) << 8) | buffer[5];
}

/** Get X-axis accelerometer reading.
 * @return X-axis acceleration measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
int16_t ICM20689::getAccelerationX() {
    I2Cdev::readBytes(devAddr, ICM20689_ACCEL_XOUT_H, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Y-axis accelerometer reading.
 * @return Y-axis acceleration measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_ACCEL_YOUT_H
 */
int16_t ICM20689::getAccelerationY() {
    I2Cdev::readBytes(devAddr, ICM20689_ACCEL_YOUT_H, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
/** Get Z-axis accelerometer reading.
 * @return Z-axis acceleration measurement in 16-bit 2's complement format
 * @see getMotion6()
 * @see MPU6050_RA_ACCEL_ZOUT_H
 */
int16_t ICM20689::getAccelerationZ() {
    I2Cdev::readBytes(devAddr, ICM20689_ACCEL_ZOUT_H, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}

// TEMP_OUT_* registers

/** Get current internal temperature.
 * @return Temperature reading in 16-bit 2's complement format
 * @see MPU6050_RA_TEMP_OUT_H
 */
int16_t ICM20689::getTemperature() {
    I2Cdev::readBytes(devAddr, ICM20689_RA_TEMP_OUT_H, 2, buffer);
    return (((int16_t)buffer[0]) << 8) | buffer[1];
}
