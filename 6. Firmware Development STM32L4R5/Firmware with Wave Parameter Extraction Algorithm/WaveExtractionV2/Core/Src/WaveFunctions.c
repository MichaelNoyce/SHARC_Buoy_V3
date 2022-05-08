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

//LPF Filter variables
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
const float32_t firCoeffs32[NUM_TAPS_ARRAY_SIZE] = {
		-0.000507108,0.00060588544,0.0022346291,0.0041320574,0.0049896598,0.0027761064,-0.0039325649,-0.014233556,-0.02388016,-0.025932499,-0.013265496,0.017937982,0.065337906,0.1198292,0.16786738,0.19604058,
		0.19604058,0.16786738,0.1198292,0.065337906,0.017937982,-0.013265496,-0.025932499,-0.02388016,-0.014233556,-0.0039325649,0.0027761064,0.0049896598,0.0041320574,0.0022346291,0.00060588544,-0.000507108
};

/*----------------------------------------------------------------*/

/**
 * @brief fullPipeline
 * @param freqSegments
 * @param PSDOutput
 */
void fullPipeline(float32_t freqSegments[SEGMENT_NO][FFT_LENGTH], float32_t PSDOutput)
{

	//for loop to populate function
	uint32_t i;

	for(i=0; i<SEGMENT_NO; i++)
	{
		//read in raw data here

		singleSegmentPipeline(rawDataBuf, decArray);

		//read segments into contiguous array
	}

	//Welch Method


	//Wave Extraction Algorithm


}

/**
 *
 * @param rawData
 * @param decArray
 */
void singleSegmentPipeline(float32_t* rawData, float32_t* decArray)
{

    uint32_t count;
    uint32_t j;

    float32_t smallBuf[128];
    float32_t tempBuf[FFT_LENGTH];
    float32_t tempBuf2[FFT_LENGTH];
    float32_t magnitudeOutput[FFT_LENGTH];


    for(count = 1; count<DECIMATION_CONSTANT; count++)
    {
    	calibrate(rawData, tempBuf);

    	detrend(tempBuf, tempBuf2);

    	LPFDecimate(tempBuf2, smallBuf);

    	//Append detrended, calibrated and decimated array

        for (j = 0; j < FFT_LENGTH/DECIMATION_CONSTANT ; j++)
        {
    		   decArray[count*(FFT_LENGTH)/(DECIMATION_CONSTANT) + j] = smallBuf[j];
        }

    }

    embeddedFFT(decArray, magnitudeOutput, 0);

    HPFDoubleIntegration(magnitudeOutput, tempBuf);

    embeddedFFT(tempBuf2, magnitudeOutput, 1);

    //Hanning Window

}


/**
 * @brief Calibration function for the ICM20689
 * @param rawData
 * @param calOutput
 */
void calibrate(float32_t* rawData, float32_t* calOutput)
{
	uint32_t i;

	for (i = 0; i < FFT_LENGTH ; i++)
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

	for (i= 0; i < FFT_LENGTH; i++)
	{
		sumTotal = sumTotal + calOutput[i];
	}

	dataMean = sumTotal/FFT_LENGTH;

	for (i= 0; i < FFT_LENGTH; i++)
	{
		detrendOutput[i] = calOutput[i] - dataMean;
	}
	// RC Highpass function	for detrending (moving average filter)
	float32_t k = 0.9995;
	float32_t s[FFT_LENGTH];
	float32_t detrendTemp[FFT_LENGTH];


	s[0] = 0;

	for (i= 1; i < FFT_LENGTH; i++)
	{
		 s[i] = detrendTemp[i] + k*(s[i-1]);
		 detrendTemp[i] = detrendTemp[i] - (1 - k)*(s[i]);
	}

	detrendOutput = detrendTemp;

}

/**
 * @brief LPFDecimate
 * @param testInput
 * @param testOutput
 */
void LPFDecimate(float32_t* testInput, float32_t* testOutput)
{

	uint32_t blockSize = BLOCK_SIZE;
	uint32_t numBlocks = FFT_LENGTH/BLOCK_SIZE;
	arm_fir_decimate_instance_f32 S;
	uint32_t i;
	float32_t  *inputF32, *outputF32;

	/* Initialize input and output buffer pointers */
	inputF32 = &testInput[0];
	outputF32 = &testOutput[0];

    arm_fir_decimate_init_f32(&S, NUM_TAPS, DECIMATION_CONSTANT, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);

    for(i=0; i < numBlocks; i++)
    {
      arm_fir_decimate_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
    }

}

/**
 * @brief embeddedFFT
 * @param inputArray
 * @param frequencyOutput
 */
void embeddedFFT(float32_t* inputArray,float32_t* magOut, uint32_t ifftFlag)
{

	arm_rfft_fast_instance_f32 varInstRfftF32;
	float32_t freqOut[FFT_LENGTH];

	arm_rfft_fast_init_f32(&varInstRfftF32, FFT_LENGTH);

	 //Process the data through the CFFT/CIFFT module
	 arm_rfft_fast_f32(&varInstRfftF32, inputArray, freqOut, ifftFlag);

	 //Process the data through the Complex Magnitude Module for calculating the magnitude at each bin
	 arm_cmplx_mag_f32(freqOut, magOut, FFT_LENGTH);

}

/**
 * @brief HPFDoubleIntegration
 * @param fftInput
 * @param waveAmplitude
 */
void HPFDoubleIntegration(float32_t* fftInput, float32_t* waveAmplitude)
{

	float32_t freq1 = 0.02;
	float32_t freq2 = 0.03;
	float32_t fnyq = 5;
	uint32_t i;
	float32_t Fs = F_SAMPLE/DECIMATION_CONSTANT;
	float32_t freq[FFT_LENGTH];

	for(i=0; i<FFT_LENGTH; i++)
	{
		freq[i] = Fs*(i/FFT_LENGTH);
	}

	for(i=0;i<FFT_LENGTH; i++)
	{
		if(freq[i]<freq1)
		{
			fftInput[i] = 0;
		}

		if(freq[i]>freq1 && freq[i]<freq2)
		{
			fftInput[i] *= (1/2)*(1-cos(PI*(freq[i]-freq1)/(freq2-freq1))*(-1/(2*PI*(freq[i])*(fftInput[i]))));
		}

		if(freq[i]>freq2 && freq[i]<fnyq)
		{
			fftInput[i] = -1/(2*PI*((freq[i])*(freq[i])))*fftInput[i];
		}
	}

}


//Welch Method

void WelchMethod(float32_t* waveAmplitudeArray, float32_t* PSD)
{

/*
	// Computes the magnitude of the complex one sided FFT
		for (i = 0; i < NUMBER_OF_WINDOWS ; i++)
		{

			embeddedFFT{]
		}


		for (i = 0; i < SEGMENT_NO ; i++)
		{
			for (j = 0; j < FFT_LENGTH ; j++)
			{
				waveAmplitudeArray [i][j] = ( waveAmplitudeArray [i][j] *
						waveAmplitudeArray [i][j]) / ( FFT_LENGTH * F_SAMPLE ) ;
			}
		}

		// Periodograms averaging
		for (i = 0; i < FFT_LENGTH ; i++)
		{
			testOutput_aux = 0;
			for (j = 0; j < NUMBER_OF_WINDOWS ; j++)
			{
				testOutput_aux += windows_mag [j][i];
			}
			testOutput [i] = testOutput_aux / NUMBER_OF_WINDOWS ;
			}


		testOutput [0] /= 2;

		*/
}

//Hanning Window

//Wave Parameter extraction




