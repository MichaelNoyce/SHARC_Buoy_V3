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
/*End User Includes--------------------------------------------*/

/*Private Variables---------------------------------------------*/


//LPFDecimate Variables
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
const float32_t firCoeffs32[NUM_TAPS_ARRAY_SIZE] = {
		-0.0017925669,-0.0018788835,-0.0020285056,-0.00167121,1.0227572e-18,0.0038552603,0.010606038,0.020585455,0.033584619,0.048789469,0.064842044,0.080022746,0.092522426,0.10075151,0.10362319,0.10075151,
		0.092522426,0.080022746,0.064842044,0.048789469,0.033584619,0.020585455,0.010606038,0.0038552603,1.0227572e-18,-0.00167121,-0.0020285056,-0.0018788835,-0.0017925669
};
uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = RAW_DATA_LENGTH/BLOCK_SIZE;

float32_t  snr;
arm_fir_decimate_instance_f32 S;
arm_status status;


/*---------------------------------------------------------------*/


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
		calOutput[i] = (rawData[i] - 92.22)/1686.50 -9.81; //remove bias offset, scale and subtract g
	}

}

/**
 * @brief Detrending function
 * @param rawData
 * @param detrendOutput
 */
void detrend(float32_t* calOutput, float32_t* detrendOutput)
{

	//Determining Mean of data
	uint32_t i;
	float32_t sumTotal, dataMean;

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		sumTotal = sumTotal + calOutput[i];
	}

	dataMean = sumTotal/RAW_DATA_LENGTH;

	for (i= 0; i < RAW_DATA_LENGTH; i++)
	{
		detrendOutput[i] = calOutput[i] - dataMean;
	}
	// RC Highpass function	for detrending (moving average filter)
	float32_t k = 0.9995;
	float32_t s[RAW_DATA_LENGTH];

	s[0] = 0;

	for (i= 1; i < RAW_DATA_LENGTH; i++)
	{
		 s[i] = detrendOutput[i] + k*(s[i-1]);
		 detrendOutput[i] = detrendOutput[i] - (1 - k)*(s[i]);
	}

}

/**
 * @brief LPFDecimate
 * @param testInput
 * @param testOutput
 */
void LPFDecimate(float32_t* testInput, float32_t* testOutput)
{
	uint32_t i;

	arm_fir_decimate_init_f32(&S, NUM_TAPS, M, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);

    for(i=0; i < numBlocks; i++)
    {
      arm_fir_decimate_f32(&S, testInput + (i * blockSize), testOutput + (i * blockSize), blockSize);
    }
}

/**
 * @brief embeddedFFT
 * @param inputArray
 * @param frequencyOutput
 */
void embeddedFFT(float32_t* inputArray, float32_t* frequencyOutput)
{

	uint32_t ifftFlag = 0;
	arm_rfft_fast_instance_f32 varInstRfftF32;

	arm_status status;
	status = ARM_MATH_SUCCESS;
	status = arm_rfft_fast_init_f32(&varInstRfftF32, FFT_LENGTH);

	 //Process the data through the CFFT/CIFFT module
	 arm_rfft_fast_f32(&varInstRfftF32, testInput_f32, testOutput_f32, ifftFlag);

	 //Process the data through the Complex Magnitude Module for calculating the magnitude at each bin
	 arm_cmplx_mag_f32(testOutput_f32, magnitudeOutput, FFT_LENGTH);


	   if (status != ARM_MATH_SUCCESS)
	   {
		  printmsg("Failure \r\n");
	   }
	   else {
		  printmsg("SUCCESS!\r\n");
	   }

	  for (uint32_t j = 0; j < FFT_LENGTH; j++)
	  {
	  	printmsg("%.2f \r\n", magnitudeOutput[j]);
	  }

}


void HPFDoubleIntegration(float32_t* detrendOutput, float32_t* waveAmplitude)
{

	float32_t freq1 = 0.02;
	float32_t freq2 = 0.03;

	for()


}




