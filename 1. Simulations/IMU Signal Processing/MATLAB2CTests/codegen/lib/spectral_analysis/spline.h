/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: spline.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

#ifndef SPLINE_H
#define SPLINE_H

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
void spline(const emxArray_real_T *x, const emxArray_real_T *y,
            emxArray_real_T *output_breaks, emxArray_real_T *output_coefs);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for spline.h
 *
 * [EOF]
 */
