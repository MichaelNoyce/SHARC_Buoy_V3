/**
 * waveFunctions.c
 *
 * Created on: Feb 24, 2022
 *
 * Author: Michael Noyce
 */

/*User Includes-------------------------------------------------*/
#include "WaveFunctions.h"
#include "waveData.h"
#include "arm_math.h"
/*End User Includes--------------------------------------------*/




/**
 * @brief Calibration function for the ICM20689
 * @param rawData
 * @param calOutput
 */
void calibrate(float32_t* rawData, float32_t* calOutput)
{
	uint32_t i;

	for (i = 0; i < 1000 ; i++)
	{
		calOutput[i] = (rawData[i] - 92.22)/1686.50 -9.81; //remove bias offset, scale and subtract g
	}

}

/**
 * @brief Detrending function
 * @param rawData
 * @param detrendOutput
 */
void detrend(float32_t* rawData, float32_t* detrendOutput)
{

	//Determining Mean of data
	uint32_t i;
	float32_t sumTotal, dataMean;

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		sumTotal = sumTotal + rawData[i];
	}

	dataMean = sumTotal/RAW_DATA_LENGTH;

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		detrendOutput[i] = rawData[i] - dataMean;
	}
	//Highpass function	for detrending
	float32_t k = 0.9995;
	float32_t s[RAW_DATA_LENGTH];

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		 s[i+1] = detrendOutput[i+1] + k*(s[i]);
		 detrendOutput[i] = detrendOutput[i] - (1 - k)*(s[i]);
	}

}


/*User Variables-----------------------------------------------*/

/*End User Variables-------------------------------------------*/


/*User Functions-----------------------------------------------*/

/*End User Functions-----------------------------------------------*/
