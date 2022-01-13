/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: periodogram.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

#ifndef PERIODOGRAM_H
#define PERIODOGRAM_H

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
void periodogram(const emxArray_real_T *x1, double varargin_2,
                 double varargin_3, emxArray_real_T *Px, emxArray_real_T *w);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for periodogram.h
 *
 * [EOF]
 */
