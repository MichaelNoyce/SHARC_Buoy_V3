/*
* Welch Method Implementation for SHARC Buoy
* -----------------------------
* Author: Michael Noyce
* Last revision : 16/2/2022
*/
# include " arm_math .h"
# include " arm_const_structs .h"


// Elements in input array ( Power of 2 and MINIMUM 256)
# define TEST_LENGTH_SAMPLES 512
// Sampling frequency of input data
# define SAMPLING_F 160
// Length for each window
# define WINDOW_LENGTH ( TEST_LENGTH_SAMPLES / 4)
// Length of FFT array
# define FFT_LENGTH ( WINDOW_LENGTH / 2)
// Number of overlapped windows

# define NUMBER_OF_WINDOWS ((2 * TEST_LENGTH_SAMPLES/ WINDOW_LENGTH ) - 1)
// EEG reading
extern float32_t EEG_Input [ TEST_LENGTH_SAMPLES ];
// Array to store PSD
float32_t PSD[ FFT_LENGTH ];
void Welch ( float32_t * testInput , float32_t * testOutput ) ;
void Init ( void ) ;
int32_t main ( void )
{
Welch ( EEG_Input , PSD) ;
}
/*
* Function : Init
* --------------------
* Initialization routine for MSP432
*
* returns : none
*/
void Init ( void )
{
// Stop watchdog timer
WDTCTL = WDTPW | WDTHOLD ;
// Core voltaje selection
PCM_setPowerState ( PCM_AM_DCDC_VCORE1 ) ;
// Operating frequency
CS_setDCOFrequency (48000000) ;
// Clock source selection
CS_initClockSignal ( CS_MCLK , CS_DCOCLK_SELECT ,
CS_CLOCK_DIVIDER_1 ) ;
}
/*
* Function : Welch
* --------------------------
* Computes the Power Spectral Density (PSD) of an input signal
* using Welch ’s method . The algorithm performs an overlapping
* windowing of the input signal , then computes the periodogram
* for each window and finally calulates an average of all
* periodograms to estimate PSD.
*
* * testInput : pointer to input signal array
* * testOutput : pointer to the array that will store PSD
*
* returns : none
*/

void Welch ( float32_t * testInput , float32_t * testOutput )
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
// Bidimentional array to storethe magnitude of the FFT
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
windows [i][j] = testInput [j +
i * ( WINDOW_LENGTH /2) ];
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
arm_rfft_fast_f32 (&S, windows [i] , windows_fft [i] ,
ifftFlag ) ;
arm_cmplx_mag_f32 ( windows_fft [i] , windows_mag [i] ,
fftSize ) ;
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


