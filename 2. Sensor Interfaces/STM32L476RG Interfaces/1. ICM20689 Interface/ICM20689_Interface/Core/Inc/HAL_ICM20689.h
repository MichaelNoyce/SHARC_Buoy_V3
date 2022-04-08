/*
 * HAL_ICM20689.h
 *
 *  Created on: Mar 3, 2021
 *      Author: Michael Noyce
 *      Student No: NYCMIC002
 *      For: The University of Cape Town
 *
 *  This Library is designed to be used with the STM32 HAL Driver files version 1.15.1
 *  Version 1.14.x is also supported
 *
 *  This library is designed to interface with the ICM20689 Inertial Measurement Unit (IMU). This
 *  device is a 6 degree of Freedom MEMs-based IMU that communicates via I2C. The device measures
 *  3-axis acceleration, 3-axis rotation and contains an on-board temperature sensor. In addition,
 *  The chip contains a digital motion processor that fuses accelerometer and gyroscope readings to
 *  get roll,pitch,heave measurements.
 *
 *  This library contains all the functions and definitions to interface with and configure the sensor.
 *  This includes functions that
 *
 *  1. Set the ACC and GYRO Full Scale Resolution
 *  2. Set the Power Mode
 *  3. Set The Sampling Rate
 *  4. Configure the Digital Low Pass Filter
 *  5. Enable/Disable and Configure Interrupts
 *  6. Initialise a FIFO buffer.
 *  7. Read from and write to the on-board register
 *
 *
 */

#ifndef HAL_ICM20689_H_
#define HAL_ICM20689_H_

//============================= 1. Includes ==============================================

#include "stm32l4xx_hal.h"	//HAL library includes
#include "math.h"			//Math Functions
#include "stdint.h"			//integers
#include "string.h"			//Mem functions

//========================== 2. Structs & Enums ===========================================

/*
 * ICM_20689_Register_t
 *
 * Complete 8-bit Register Map of the ICM20689 chip.
 */
typedef enum
{
	//Self Test Registers
	SELF_TEST_X_GYRO = 0X00,
	SELF_TEST_Y_GYRO = 0x01,
	SELF_TEST_Z_GYRO = 0x02,
	SELF_TEST_X_ACCEL = 0X0D,
	SELF_TEST_Y_ACCEL = 0x0E,
	SELF_TEST_Z_ACCEL = 0x0F,
	SMPLRT_DIV = 0x19,
	CONFIG = 0x26,
	GYRO_CONFIG = 0x1B ,
	ACCEL_CONFIG = 0x1C,
	ACCEL_CONFIG_2 = 0x1D,
	LP_MODE_CFG = 0x1E,
	FIFO_EN = 0x23,
	FSYNC_INT = 0x36,
	INT_PIN_CFG = 0x37,
	INT_ENABLE = 0x38,
	INT_STATUS = 0x58,
	ACCEL_XOUT_H = 0x3B,
	ACCEL_XOUT_L = 0x3C,
	ACCEL_YOUT_H = 0x3D,
	ACCEL_YOUT_L = 0x3E,
	ACCEL_ZOUT_H = 0x3F,
	ACCEL_ZOUT_L = 0x40,
	TEMP_OUT_H = 0x41,
	TEMP_OUT_L = 0x42,
	GYRO_XOUT_H = 0x43,
	GYRO_XOUT_L = 0x44,
	GYRO_YOUT_H = 0x45,
	GYRO_YOUT_L = 0x46,
	GYRO_ZOUT_H = 0x47,
	GYRO_Z_OUT_L = 0x48,
	USER_CTRL = 0x6A,
	PWR_MGMT_1 = 0x6B,
	PWR_MGMT_2 = 0x6C,
	FIFO_COUNTH = 0x72,
	FIFO_COUNTL = 0x73,
	FIFO_R_W = 0x74,
	WHO_AM_I = 0x68,
}ICM_20689_Register_t;

/*
 * IMU_Status_t
 *
 * @brief:	Used to represent numeric statuses returned as a result of
 * 		    running Sensor-register level functions e.g. using i2c to write
 * 		    a value for Power mode. Successful return
 */
typedef enum
{
	IMU_I2C_ERROR,
	IMU_PERIPHERAL_INIT_ERROR,
	IMU_I2C_DEVICE_BUSY,
	IMU_I2C_ACK_NACK,
	IMU_CONFIG_ERROR,
	IMU_I2C_DEVICE_OFFLINE,
	IMU_I2C_DEVICE_ONLINE,
	IMU_I2C_ID_ERROR,
	IMU_CONFIG_OUT_OF_RANGE,
	IMU_INIT_CMD_ERROR,
	IMU_SELF_TEST_PASS,
	IMU_SELF_TEST_FAIL,
	IMU_STR_READ_ERROR,
	IMU_RESET_FAIL,
	IMU_RESET_SUCCESS,
	IMU_FIFO_READ_ERROR,
	IMU_CAL_SUCCESS,
	IMU_OK

}imu_status_t;

/*
 * IMU_PowerMode
 *
 * @brief: Represents the possible operating modes the sensor can be placed in
 */
typedef enum
{
	IMU_STANDBY,
	IMU_SLEEP,
	IMU_WAKE,
	IMU_LP,
	IMU_Cycle,
	IMU_RESET,
}IMU_PowerMode;

/*
 * Interrupt_source_t
 *
 * Representation of the interrupt sources available on the chip
 */
typedef enum
{
	FIFO_OVERFLOW,
	I2C_MST_INT,
	DATA_READY
}Interrupt_source_t;

/*
 * IMU_SelfTest_t
 *
 * Struct to store the values located in the self-test register
 */
typedef struct
{
	uint8_t A_x;
	uint8_t A_y;
	uint8_t A_z;
	uint8_t G_x;
	uint8_t G_y;
	uint8_t G_z;
}IMU_SelfTest_t;

/*
 * IMU_FT_t
 *
 * struct to store IMU data as a float representation
 */
typedef struct
{
	float A_x;
	float A_y;
	float A_z;
	float G_x;
	float G_y;
	float G_z;
}IMU_FT_t;

/*
 * Stores Raw IMU data as an unsigned 16-bit integer
 */
typedef struct
{
	uint16_t Accel[3];
	uint16_t Gyro[3];
	uint16_t Temp;
}IMU_data_t;


//======================== 3. Macro Definitions =========================================

/*The DLPF is configured by DLPF_CFG. The accelerometer and gyroscope are filtered according to
 * the value of DLPF_CFG as shown in the table below.
 * DLPF_CFG Accelerometer
 * (Fs = 1kHz)
 * Gyroscope
 * Bandwidth
 * (Hz)
 * Delay
 * (ms)
 * Bandwidth
 * (Hz)
 * Delay
 * (ms)
 * Fs (kHz)
 * 0 260 0 256 0.98 8
 * 1 184 2.0 188 1.9 1
 * 2 94 3.0 98 2.8 1
 * 3 44 4.9 42 4.8 1
 * 4 21 8.5 20 8.3 1
 * 5 10 13.8 10 13.4 1
 * 6 5 19.0 5 18.6 1
 * 7 RESERVED RESERVED 8
 */

#define CONFIG_DLFP_MSK 0b111
#define CONFIG_DLFP_0 ~CONFIG_DLFP_MSK
#define CONFIG_DLFP_1 1
#define CONFIG_DLFP_2 2
#define CONFIG_DLFP_3 3
#define CONFIG_DLFP_4 4
#define CONFIG_DLFP_5 5
#define CONFIG_DLFP_6 6
#define CONFIG_DLFP_7 CONFIG_DLFP_MSK

//GYRO_CONFIG Macros
#define GYRO_CONFIG_FSSEL_MSK		0b11
#define GYRO_CONFIG_FSSEL_250DPS	0<<3
#define GYRO_CONFIG_FSSEL_500DPS	1<<3
#define GYRO_CONFIG_FSSEL_1000DPS	2<<3
#define GYRO_CONFIG_FSSEL_2000DPS	GYRO_CONFIG_FSSEL_MSK<<3

#define GYRO_CONFIG_ST_EN_X	0b1<<7
#define GYRO_CONFIG_ST_EN_Y	0b1<<6
#define GYRO_CONFIG_ST_EN_Z	0b1<<5

//ACC_CONFIG Macros
#define ACC_CONFIG_AFSSEL_MSK 0b11
#define ACC_CONFIG_AFSSEL_2G	0<<3
#define ACC_CONFIG_AFSSEL_4G	1<<3
#define ACC_CONFIG_AFSSEL_8G	2<<3
#define ACC_CONFIG_AFSSEL_16G	ACC_CONFIG_AFSSEL_MSK<<3

#define ACC_CONFIG_ST_EN_X	0b1<<7
#define ACC_CONFIG_ST_EN_Y	0b1<<6
#define ACC_CONFIG_ST_EN_Z	0b1<<5

//FIFO EN
//Data stored inside the sensor data registers (Registers 59 to 96) will be loaded into the FIFO buffer if
//a sensor�s respective FIFO_EN bit is set to 1 in this register.
#define FIFO_EN_TEMP 0b1<<7
#define FIFO_EN_XG	 0b1<<6
#define FIFO_EN_YG	 0b1<<5
#define FIFO_EN_ZG	 0b1<<4
#define FIFO_EN_ACC	 0b1<<3
#define FIFO_EN_SLV2 0b1<<2
#define FIFO_EN_SLV1 0b1<<1
#define FIFO_EN_SLV0 0b1



//INT_PIN_CFG

#define INT_PIN_CFG_LEVEL_LOW 0b1<<7 //active logic level for pin
#define INT_PIN_CFG_LEVEL_HIGH (uint8_t)(~INT_PIN_CFG_LEVEL_LOW)
#define INT_PIN_CFG_PIN_OPEN_DRAIN 0b1<<6
#define INT_PIN_CFG_PIN_PUSH_PULL  0b0<<6
#define INT_PIN_CFG_LATCH_INT_EN 0b1<<5 //pin held high untill interrupt is cleared (if set to 0, pin emits a 50 us pulse)
#define INT_PIN_CFG_INT_RD_CLEAR 0b1<<4
#define INT_PIN_CFG_FSYNC_INT_LEVEL_LOW 0b1<<3
#define INT_PIN_CFG_FSYNC_INT_LEVEL_HIGH ~INT_PIN_FSYNC_INT_LEVEL_LOW
#define INT_PIN_CFG_FSYNC_INT_EN 0b1<<2


//INT_ENABLE
#define INT_ENABLE_FIFO_OFLOW_EN 0b1<<4
#define INT_ENABLE_DATA_RDY_EN 0b1

//INT_STATUS
#define INT_STATUS_FIFO_OVERFLOW	0b1<<4
#define INT_STATUS_DATA_RDY			0b1

//SIGNAL_PATH_RESET
#define SIGNAL_PATH_ACC_RESET  0b1<<1
#define SIGNAL_PATH_TEMP_RESET 0b1

//USER_CTRL
#define USER_CTRL_FIFO_EN 0b1<<6
#define USER_CTRL_I2C_IF_DIS 0b1<<4//disabling interface allows for SPI mode
#define USER_CTRL_FIFO_RESET 0b1<<2
#define USER_CTRL_SIG_COND_RESET 0b1

//PWR_MGMT
/*
	An internal 8MHz oscillator, gyroscope based clock, or external sources can be selected as the
	ICM20689 clock source. When the internal 8 MHz oscillator or an external source is chosen as the
	clock source, the IMU20689 can operate in low power modes with the gyroscopes disabled.
	Upon power up, the IMU20689 clock source defaults to the internal oscillator. However, it is highly
	recommended that the device be configured to use one of the gyroscopes (or an external clock
	source) as the clock reference for improved stability. The clock source can be selected according to
	the following table.
	CLKSEL Clock Source
	0 Internal 8MHz oscillator
	1 PLL with X axis gyroscope reference
	2 PLL with Y axis gyroscope reference
	3 PLL with Z axis gyroscope reference
	4 PLL with external 32.768kHz reference
	5 PLL with external 19.2MHz reference
	6 Reserved
	7 Stops the clock and keeps the timing generator in reset

 */

#define PWR_MGMT_1_CLK_SEL_MSK  0b111
#define PWR_MGMT_1_CLK_SEL_0 	~PWR_MGMT_1_CLK_SEL_MSK
#define PWR_MGMT_1_CLK_SEL_1 	1
#define PWR_MGMT_1_CLK_SEL_2 	2
#define PWR_MGMT_1_CLK_SEL_3 	3
#define PWR_MGMT_1_CLK_SEL_4 	4
#define PWR_MGMT_1_CLK_SEL_5 	5
#define PWR_MGMT_1_CLK_SEL_6 	6
#define PWR_MGMT_1_CLK_SEL_7 	PWR_MGMT_1_CLK_SEL_MSK

/*
	By setting SLEEP to 1, the ICM20689 can be put into low power sleep mode. When CYCLE is set to
	1 while SLEEP is disabled, the ICM20689 will be put into Cycle Mode. In Cycle Mode, the device
	cycles between sleep mode and waking up to take a single sample of data from accelerometer at a
	rate determined by LP_WAKE_CTRL (register 108). To configure the wake frequency, use
	LP_WAKE_CTRL within the Power Management 2 register (Register 108).
 */

#define PWR_MGMT_1_DEVICE_RESET 0b1<<7
#define PWR_MGMT_1_SLEEP_EN 	0b1<<6
#define PWR_MGMT_1_CYCLE_EN 	0b1<<5
#define PWR_MGMT_1_TEMP_DIS 	0b1<<3

//PWR_MGMT_2

/* Description:
 * The user can put individual accelerometer and gyroscopes axes into standby mode by using this
   register. If the device is using a gyroscope axis as the clock source and this axis is put into standby
   mode, the clock source will automatically be changed to the internal 8MHz oscillator.
*/
#define PWR_MGMT_FIFO_LP_EN				0b1<<7
#define PWR_MGMT_2_STBY_XA				0b1<<5
#define PWR_MGMT_2_STBY_YA				0b1<<4
#define PWR_MGMT_2_STBY_ZA				0b1<<3
#define PWR_MGMT_2_STBY_XG				0b1<<2
#define PWR_MGMT_2_STBY_YG				0b1<<1
#define PWR_MGMT_2_STBY_ZG				0b1


/* I2C Definitions:
 * S Start Condition: SDA goes from high to low while SCL is high
 * AD Slave I2C address
 * W Write bit (0)
 * R Read bit (1)
 * ACK Acknowledge: SDA line is low while the SCL line is high at the
 * 9th clock cycle
 * NACK Not-Acknowledge: SDA line stays high at the 9th clock cycle
 * RA ICM20689 internal register address
 * DATA Transmit or received data
 * P Stop condition: SDA going from low to high while SCL is high
 */
#define IMU_Device_Address 0x68

#define I2C_SLAVE_ADDRESS_HIGH 0b1101001
#define I2C_WRITE_BIT 0b1
#define I2C_READ_BIT  0b0
#define BASE_REGISTER_RESET_VALUE 0x00
#define PWR_MGMT_RESET_VALUE 0x40
#define WHO_AM_I_VALUE  0x68

//Sample Rate Value
#define SAMPLE_RATE 5//Hz
#define GYRO_OUTPUT_RATE_DLPF_EN 1000 //Hz
#define GYRO_OUTPUT_RATE_DLPF_DIS 8000 //Hz

//ACC ressolution values
#define ACC_2G_WORD_LENGTH 16384 //LSB/g
#define ACC_4G_WORD_LENGTH 8192
#define ACC_8G_WORD_LENGTH 4096
#define ACC_16G_WORD_LENGTH 2048

//Data Defines
#define N_Samples 28
#define IMU_BUFFER_SIZE N_Samples*12


//I2C Peripheral Defines

#define IMU_I2C I2C1					//I2C Port chosen for the IMU
#define IMU_SCL_PIN GPIO_PIN_8			// SCL Pin
#define IMU_SDA_PIN GPIO_PIN_9			//SDA Pin
#define IMU_SCL_PORT GPIOB				//SCL Pin Port
#define IMU_SDA_PORT GPIOB				//SDA Pin Port
#define IMU_I2C_AF	GPIO_AF4_I2C1		//AF Mapping for I2C peripheral
#define IMU_INT_Pin GPIO_PIN_5			//Interrupt GPIO Pin
#define IMU_INT_GPIO_Port GPIOC			//Interrupt GPIO Port
#define IMU_INT_EXTI_IRQn EXTI9_5_IRQn	//IRQn for the NVIC

//========================== 4. Global Variables ==========================================

uint16_t imu_sample_count;   //Keeps track of the number of samples from the IMU

uint8_t IMU_Log_On;			 //used in EXTI IRQ to determine what routine to run
//============================= 5. Handlers ===============================================

I2C_HandleTypeDef hi2c1;				//handler for I2C Communication

DMA_HandleTypeDef hdma_i2c1_rx;			//handler for I2C Peripheral to Memory DMA transfers


//============================ 6. Data Buffers ============================================

uint8_t IMU_Buffer[IMU_BUFFER_SIZE];	//Buffer to store data from the IMU



//======================== 8. Sensor Configuration Functions =========================================

imu_status_t ICM20689_Set_Gyro_FSR(I2C_HandleTypeDef *hi2c,uint8_t FSR);
imu_status_t ICM20689_Set_Acc_FSR(I2C_HandleTypeDef *hi2c,uint8_t FSR);
imu_status_t ICM20689_Set_FSync(I2C_HandleTypeDef *hi2c, uint8_t Fsync);
imu_status_t ICM20689_Set_DLPF(I2C_HandleTypeDef *hi2c, uint8_t DLPF);
imu_status_t ICM20689_Set_Sample_Rate(I2C_HandleTypeDef *hi2c);
imu_status_t ICM20689_Set_PLLSrc(I2C_HandleTypeDef *hi2c, uint8_t PLL);
imu_status_t ICM20689_Config_FIFO(I2C_HandleTypeDef *hi2c, uint8_t fifo_mask, uint8_t cmd);
imu_status_t ICM20689_Config_Interrupt_Pin(Interrupt_source_t interrupt, uint8_t level, uint8_t latch);
imu_status_t ICM20689_FIFO_CMD(I2C_HandleTypeDef *hi2c,uint8_t cmd);


//======================= 9. Initializaiton Function Prototypes ========================================

/*Function Name imy_status_t ICM20689_Init_IMU(uint8_t g_fsr,uint8_t a_fsr, uint8_t dlpf_coeff)
 *
 * @brief: Initialise I2C and DMA Microcontroller Peripherals. Wake Up sensor and configure
 *
 */

imu_status_t ICM20689_Init_IMU(uint8_t g_fsr,uint8_t a_fsr, uint8_t dlpf_coeff);
imu_status_t ICM20689_Deinit_IMU(void);
imu_status_t ICM20689_Enable_Interrupt(I2C_HandleTypeDef *hi2c, uint8_t interrupts);
imu_status_t ICM20689_Disable_Interrupt(I2C_HandleTypeDef *hi2c, uint8_t interrupts);

/* Function Name imu_status_t ICM20689_Init_FIFO(I2C_HandleTypeDef *hi2c, uint8_t enable)
 *
 * @brief: Enables the IMU FIFO buffer and configures it to recieve
 * 		   Data from peripherals determined by the fifo_Mask
 * @param: hi2c - pointer to I2C handle typedef
 * 		   enable - can either be (ENABLE - enables FIFO Buffer), DISABLE - disables BUFFER, RESET (3)- resets buffer
 */
imu_status_t ICM20689_Init_FIFO(I2C_HandleTypeDef *hi2c, uint8_t enable);

/* Function Name imu_status_t ICM20689_Init_TempSensor(I2C_HandleTypeDef *hi2c, uint8_t cmd);
 *
 * @brief: Function to enable/disable the temperature sensor
 *
 * @param: hi2c - pointer to I2C handle
 * 		   cmd 	- set to ENABLE to enable the reading, DISABLE to disable
 */
imu_status_t ICM20689_Init_TempSensor(I2C_HandleTypeDef *hi2c, uint8_t cmd);

//======================= 10. Sensor Read Functions ====================================================

imu_status_t ICM20689_Get_SelfTestResponse_Values(I2C_HandleTypeDef *hi2c,IMU_SelfTest_t *IMU);
imu_status_t ICM20689_Get_ID(I2C_HandleTypeDef *hi2c,uint8_t* ID);
imu_status_t ICM20689_Get_MST_Status(I2C_HandleTypeDef *hi2c, uint8_t* status_byte);
imu_status_t ICM20689_Get_FIFO_Count(I2C_HandleTypeDef *hi2c,uint16_t* count);
imu_status_t ICM20689_SelfTest(I2C_HandleTypeDef *hi2c,float* test_res);
//======================= 11. Power Mode Config Function ===============================================

imu_status_t ICM20689_Set_Wake(I2C_HandleTypeDef *hi2c);
imu_status_t ICM20689_Set_Cycle_Power_Mode(I2C_HandleTypeDef *hi2c,uint8_t Cycles);
imu_status_t ICM20689_Set_Low_Power_Mode_Acc(I2C_HandleTypeDef *hi2c,uint8_t Cycles);
imu_status_t ICM20689_Set_Sleep_Power_Mode(I2C_HandleTypeDef *hi2c);
imu_status_t ICM20689_Get_Interrupt_Status(I2C_HandleTypeDef *hi2c, Interrupt_source_t interrupt_src,uint8_t* res);
imu_status_t ICM20689_Signal_conditioned_Reset(I2C_HandleTypeDef *hi2c);
imu_status_t ICM20689_Get_IMU_RawData(I2C_HandleTypeDef *hi2c,uint8_t* imu);
imu_status_t ICM20689_reset(I2C_HandleTypeDef *hi2c);

void ICM20689_DMA_PeriphIRQHandler(void);
void ICM20689_IntPin_IRQ(void);
#endif /* HAL_ICM20689_H_ */
