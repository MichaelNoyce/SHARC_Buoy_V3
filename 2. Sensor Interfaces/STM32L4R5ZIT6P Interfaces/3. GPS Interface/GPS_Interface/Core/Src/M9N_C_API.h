/**
  ******************************************************************************
  * @file           : M9N_C_API.h
  * @brief          : Source / Header file for M9N_C_API.c/.h
  * @author			: Lawrence Stanton
  ******************************************************************************
  * @attention
  *
  * © LD Stanton 2022
  * 
  * This file and its content are the copyright property of the author. All 
  * rights are reserved. No warranty is given. No liability is assumed.
  * Confidential unless licensed otherwise. If licensed, refer to the 
  * accompanying file "LICENCE" for license details.
  * 
  ******************************************************************************
  */

#ifndef CORE_INC_M9N_C_API_H_
#define CORE_INC_M9N_C_API_H_


#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/* Begin Public Includes */
#include "GPS_Struct.h"
/* End Public Includes */

/* --------------------------------------------------------------------------- */
/* Begin Public Defines */


/* End Public Defines */

/* --------------------------------------------------------------------------- */
/* Begin Public Typedefs */


//Initialisation/config enum
typedef enum{
	GPS_Init_OK = 1,
	GPS_Init_Ack_Error = 2,
	GPS_Init_Baud_Config_Error = 3,
	GPS_Init_MSG_Config_Error = 4,
	GPS_Init_Ack_Tx_Error = 5,
	GPS_Init_Periph_Config_Error = 6,
	GPS_Init_Offline_Error = 7
}GPS_Init_msg_t;


typedef enum{
	GPS_MSG_RDY = 1,
	GPS_BUSY= 2,
	GPS_OFFLINE = 3,
	GPS_ERROR = 4,
}GPS_Status_t;


typedef enum{
	UBX_OK = 2,
	UBX_ACK_ACK = 1,
	UBX_ACK_NACK = 0,
	UBX_ERROR = -1,
	UBX_TIMEOUT_Tx = -2,
	UBX_TIMEOUT_Rx = -3,

} UBX_MSG_t;




/* End Public Typedefs */

/* --------------------------------------------------------------------------- */
/* Begin Public Variables */


/* End Public Variables */

/* --------------------------------------------------------------------------- */
/* Begin Public Function Prototypes */

/**
 * @brief Initialize GPS with initial configuration and interfaces
 *
 * @return
 */
GPS_Init_msg_t GPS_Init();

/**
 * @brief Configure update rate
 *
 * @param UpdateRate
 * @return GPS_Init_msg_t
 */
UBX_MSG_t GPS_UpdateRate_Config(int UpdateRate);



/**
 * @brief Enable Low power GPS mode
 *
 * @return UBX_MSG_t
 */
UBX_MSG_t GPS_LP_Enable();

/***
 * @brief Disable Low Power Mode
 *
 * @return UBX_MSG_t
 */
UBX_MSG_t GPS_LP_Disable();


/**
 * @brief Retrieve latest NMEA string
 *
 * @return GPS_Status_t
 */
GPS_Status_t GPS_Log(GPS_Data_t gpsDataInstance);

/* End Public Function Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* CORE_INC_M9N_C_API_H_ */

/*** END OF FILE ***/
