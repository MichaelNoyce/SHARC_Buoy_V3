/**
 * waveFunctions.h
 *
 * Created on: Feb 24, 2022
 *
 * Author: Michael Noyce
 */

/*User Includes------------------------------------------------*/
#include "arm_math.h"
/*End User Includes-------------------------------------------*/

/*Definitions-------------------------------------------------*/
#define RAW_DATA_LENGTH 1000
/*End Definitions ---------------------------------------------*/


/**
 * @brief Calibration Function for the ICM20689
 * @param rawData
 * @param calOutput
 */
void calibrate(float32_t* rawData, float32_t* calOutput);

/**
 * @brief Detrending function
 * @param rawData
 * @param detrendOutput
 */
void detrend(float32_t* rawData, float32_t* detrendOutput);


