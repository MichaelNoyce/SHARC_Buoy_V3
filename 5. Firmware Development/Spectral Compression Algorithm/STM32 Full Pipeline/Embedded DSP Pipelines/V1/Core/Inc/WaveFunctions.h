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
//Input Data Definitions
#define RAW_DATA_LENGTH 5120
#define FFT_LENGTH 1024


//LPF Decimate Defintions
#define SNR_THRESHOLD_F32    75.0f
#define BLOCK_SIZE            32
/* Must be a multiple of 16 */
#define NUM_TAPS_ARRAY_SIZE              29
#define NUM_TAPS              29
#define M 50
#define DEC_LENGTH 6400/M

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
void detrend(float32_t* calOutput, float32_t* detrendOutput);

/**
 * @brief Decimating input low pass filtering function
 * @param detrendOutput
 * @param decimatedOutput
 */
void LPFDecimate(float32_t* detrendOutput, float32_t* decimatedOutput);

/**
 * @brief Performs Four Step FFT method on time series greater than 1024 (allows use of CMSIS DSP)
 * @param timeSeries
 * @param frequencyOutput
 * @param FFT_Length
 */
void FourStepDFT(float32_t* timeSeries, float32_t* frequencyOutput);

/**
 * @brief Double Integrating time series
 * @param detrendOutput
 * @param waveAmplitude
 */
void HPFDoubleIntegration(float32_t* detrendOutput, float32_t* waveAmplitude);

/**
 *
 * @param x
 * @param XR
 * @param size
 */
void DFT(float32_t* x, float32_t* XR, uint16_t size);
