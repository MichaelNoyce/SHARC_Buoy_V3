/**
 * welch.c
 *
 * Created on: Feb 16, 2022
 *
 * Author: Michael Noyce
 */

/*User Includes-------------------------------------------------*/
#include "welch.h"
/*End User Includes--------------------------------------------*/

/*User Variables-----------------------------------------------*/

// EEG reading
extern float32_t EEG_Input [ TEST_LENGTH_SAMPLES ];
// Array to store PSD
float32_t PSD[ FFT_LENGTH ];

/*End User Variables-------------------------------------------*/
/**
 *
 * @param testInput
 * @param testOutput
 */
void Welch(float32_t* testInput, float32_t* testOutput )
{
	uint32_t i;
	uint32_t j;

	// 0 for FFT / 1 for IFFT
	uint32_t ifftFlag = 0;

	// Size of FFT array
	uint32_t fftSize = FFT_LENGTH ;

	// Variable for periodograms averaging
	float32_t testOutput_aux ;

	// Bidimentional array to store overlapping windows
	float32_t windows [ NUMBER_OF_WINDOWS ][ WINDOW_LENGTH ];

	// Bidimentional array to store the one sided FFT of each window
	float32_t windows_fft [ NUMBER_OF_WINDOWS ][ WINDOW_LENGTH ];

	// Bidimentional array to store the magnitude of the FFT
	float32_t windows_mag [ NUMBER_OF_WINDOWS ][ FFT_LENGTH ];

	// FFT status
	arm_status status ;

	// FFT instance
	arm_rfft_fast_instance_f32 S;

	// Windowing in input signal
	for (i = 0; i < NUMBER_OF_WINDOWS ; i++)
	{
		for (j = 0; j < WINDOW_LENGTH ; j++)
		{
			windows [i][j] = testInput [j + i * ( WINDOW_LENGTH /2) ];
		}
	}

	// FFT init routine
	status = arm_rfft_fast_init_f32 (&S, WINDOW_LENGTH ) ;
	if( status != ARM_MATH_SUCCESS )
	{
		while (1) ;
	}

	// Computes the magnitude of the complex one sided FFT
	for (i = 0; i < NUMBER_OF_WINDOWS ; i++)
	{
		arm_rfft_fast_f32 (&S, windows [i] , windows_fft [i] , ifftFlag ) ;
		arm_cmplx_mag_f32 ( windows_fft [i] , windows_mag [i] , fftSize ) ;
	}

	// Periodogram calculation
	for (i = 0; i < NUMBER_OF_WINDOWS ; i++)
	{
		for (j = 0; j < FFT_LENGTH ; j++)
		{
			windows_mag [i][j] = ( windows_mag [i][j] *
		    windows_mag [i][j]) / ( FFT_LENGTH * SAMPLING_F ) ;
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
}
