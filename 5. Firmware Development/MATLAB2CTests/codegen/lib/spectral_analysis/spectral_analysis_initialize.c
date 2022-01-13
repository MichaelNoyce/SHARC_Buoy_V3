/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: spectral_analysis_initialize.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "spectral_analysis_initialize.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_data.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void spectral_analysis_initialize(void)
{
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_spectral_analysis = true;
}

/*
 * File trailer for spectral_analysis_initialize.c
 *
 * [EOF]
 */
