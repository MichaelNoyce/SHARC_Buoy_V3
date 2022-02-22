/**
 * welch.h
 *
 * Created on: Feb 16, 2022
 * Based on:
 *
 * Author: Michael Noyce
 */

#include "main.h"
#include <stdio.h>
#include "arm_math.h"


/*Definitions-------------------------------------------------*/
// Elements in input array ( Power of 2 and MINIMUM 256)
# define TEST_LENGTH_SAMPLES 4096
// Sampling frequency of input data
# define SAMPLING_F 2
// Length for each window
# define WINDOW_LENGTH ( TEST_LENGTH_SAMPLES / 4)
// Length of FFT array
# define FFT_LENGTH ( WINDOW_LENGTH / 1)
// Number of overlapped windows
# define NUMBER_OF_WINDOWS ((2 * TEST_LENGTH_SAMPLES/ WINDOW_LENGTH ) - 1)

/*End Definitions ---------------------------------------------*/


/*
 * Function Name: Welch
 *
 * @brief: Function using the Welch method to calculate the PSD of a time series
 *
 * @param: void
 *
 * @return: HAL_StatusTypeDef - return status of the function based on HAL_StatusTypeDef
 */
void Welch(float32_t* testInput, float32_t* testOutput );
