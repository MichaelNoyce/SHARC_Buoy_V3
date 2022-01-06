/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeDFT.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

#ifndef COMPUTEDFT_H
#define COMPUTEDFT_H

/* Include Files */
#include "rtwtypes.h"
#include "spectral_analysis_types.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void computeDFT(const emxArray_real_T *xin, double nfft, double varargin_1,
                emxArray_creal_T *Xx, emxArray_real_T *f);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeDFT.h
 *
 * [EOF]
 */
