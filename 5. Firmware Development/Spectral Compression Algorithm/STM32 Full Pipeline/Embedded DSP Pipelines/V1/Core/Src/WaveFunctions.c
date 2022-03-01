/**
 * waveFunctions.c
 *
 * Created on: Feb 24, 2022
 *
 * Author: Michael Noyce
 */

/*User Includes-------------------------------------------------*/
#include "WaveFunctions.h"
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

	for (i = 0; i < RAW_DATA_LENGTH ; i++)
	{
		rawData[i] = rawData[i] - 92.2236; //remove bias offset
		rawData[i] = rawData[i]/1686.46 -9.8172; //Scaling
	}

	calOutput = rawData;
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
	float32_t detrendData[RAW_DATA_LENGTH];

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		sumTotal = sumTotal + rawData[i];
	}

	dataMean = sumTotal/RAW_DATA_LENGTH;

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		detrendData[i] = rawData[i] - dataMean;
	}
	//Highpass function	for detrending
	float32_t k = 0.9995;
	float32_t s[RAW_DATA_LENGTH];

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		 s[i+1] = detrendData[i+1] + k*(s[i]);
		 detrendData[i] = detrendData[i] - (1 - k)*(s[i]);
	}

}


/*User Variables-----------------------------------------------*/

/*End User Variables-------------------------------------------*/


/*User Functions-----------------------------------------------*/

/*End User Functions-----------------------------------------------*/
