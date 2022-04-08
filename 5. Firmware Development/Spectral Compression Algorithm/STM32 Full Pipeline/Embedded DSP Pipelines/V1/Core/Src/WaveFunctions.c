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
#include "complex.h"
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

void LPFDecimate(float32_t* testInput, float32_t* testOutput)
{
	uint32_t i;

	arm_fir_decimate_init_f32(&S, NUM_TAPS, M, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);

    for(i=0; i < numBlocks; i++)
    {
      arm_fir_decimate_f32(&S, testInput + (i * blockSize), testOutput + (i * blockSize), blockSize);
    }
}


void FourStepDFT(float32_t* inputArray, float32_t* frequencyOutput)
{
	//1st Index
	uint32_t i;
	//2nd Index
	uint32_t j;

	//Instance of FFT
	arm_rfft_fast_instance_f32 S;
	//Status of FFT
	arm_status status;
	//ifftFlag
	uint8_t ifftFlag = 0;
	//Calculate number of FFT arrays needed
	uint8_t N = RAW_DATA_LENGTH/FFT_LENGTH;
	//Temporary Array
	float32_t FourStepArray[N][FFT_LENGTH];
	//Temporary Array
	float32_t FourStepArrayTranspose[FFT_LENGTH][N];

	//Initialize FFT Function
	status = arm_rfft_fast_init_f32 (&S, FFT_LENGTH);

	//Initialize matrix function
	// arm_matrix_instance_f32 A;      /* Matrix A Instance */
	// arm_matrix_instance_f32 AT;     /* Matrix AT(A transpose) instance */


	/* Four-Step FFT Algorithm */
	//Step 0: Break Down Signal Into a N*FFT_LENGTH Array
	//Each value is interleaved with a step of 5
	for(i=0; i<N; i++)
	{
		for(j=0; j<FFT_LENGTH; j+=1)
		{
		FourStepArray[i][j] = inputArray[j+FFT_LENGTH*i];
		}
	}


	printmsg("Step 0: Breakdown, done \r\n");

	//Step 1: FFT Rows of 2D array
	for(i=0; i<N; i++)
	{
		arm_rfft_fast_f32 (&S, FourStepArray[i], FourStepArray[i], ifftFlag);
	}

	printmsg("Step 1: FFT, done \r\n");

	//Step 2: Twiddle Factors
	for(i=0; i<N; i++)
	{
		for(j=0; j<FFT_LENGTH; j++)
		{
			FourStepArray[i][j] = FourStepArray[i][j] * exp(-2*M_PI*I*j*i/RAW_DATA_LENGTH);
		}


	}

	printmsg("Step 2: Twiddle, done \r\n");

	//Step 3: Transpose Matrix
	/* swap values on either side of the first diagonal */
	for (i = 0; i < FFT_LENGTH; i++) {
	    /* stop the inner loop when b == a */
	    for (j = 0; j < N; j++) {
	        FourStepArrayTranspose[i][j] = FourStepArray[j][i];
	    }
	}

	 printmsg("Step 3: Transpose done \r\n");

	//Step 4: DFT on rows of transposed matrix
	float32_t  XR[N];



	for(i=0; i<FFT_LENGTH; i++)
	{
		DFT(FourStepArrayTranspose[i], XR, N);

			for(j=0; j<N; j++)
			{
				FourStepArray[j][i] = XR[i];
				printmsg("%f \r\n", FourStepArray[j][i]);
			}
	}

	printmsg("Step 4: DFT, done \r\n");

	//Step 5: Recombine matrix and calculate magnitude output
	for(i=0; i<FFT_LENGTH; i++)
	{
		for(j=0; j<N; j++)
		{
			testOutput[i + j*FFT_LENGTH] = FourStepArray[j][i]/FFT_LENGTH;
		}
	}

	printmsg("Step 5: Recombination, done \r\n");

}

void HPFDoubleIntegration(float32_t* detrendOutput, float32_t* waveAmplitude)
{
	//Instance of FFT
	arm_rfft_fast_instance_f32 S;

	//Status of FFT
	arm_status status ;

	status = arm_rfft_fast_init_f32 (&S, FFT_LENGTH) ;



}

void DFT(float32_t* x, float32_t* XR, uint16_t size)
{
	uint16_t n,k;
	float32_t sumR;

 	for(k=0;k<size;k++)
	{
		sumR=0.0;
		for(n=0;n<size;n++)
 		{
 			sumR+=x[n]*cos(2*PI*k*n/(float32_t)size);
		}

	XR[k]=sumR;
	//printmsg("%f \r\n", XR[k]);
 	}

}




