/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeperiodogram.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

#ifndef COMPUTEPERIODOGRAM_H
#define COMPUTEPERIODOGRAM_H

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
void computeperiodogram(const emxArray_real_T *x, const emxArray_real_T *win,
                        double nfft, double Fs, const char options_range[8],
                        boolean_T options_reassign, emxArray_real_T *Pxx,
                        emxArray_real_T *F, emxArray_creal_T *RPxx,
                        emxArray_real_T *Fc);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for computeperiodogram.h
 *
 * [EOF]
 */
