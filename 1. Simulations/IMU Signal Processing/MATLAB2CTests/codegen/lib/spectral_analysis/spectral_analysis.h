/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: spectral_analysis.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

#ifndef SPECTRAL_ANALYSIS_H
#define SPECTRAL_ANALYSIS_H

/* Include Files */
#include "rtwtypes.h"
#include "omp.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void spectral_analysis(const double t[5001], const double W[5001],
                              double p, double *Hm0, double *Tp, double *Tm01,
                              double *Tm_10, double *Hrms);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for spectral_analysis.h
 *
 * [EOF]
 */
