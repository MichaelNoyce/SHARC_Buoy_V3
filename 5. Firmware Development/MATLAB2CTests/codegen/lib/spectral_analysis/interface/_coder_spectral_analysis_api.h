/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_spectral_analysis_api.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

#ifndef _CODER_SPECTRAL_ANALYSIS_API_H
#define _CODER_SPECTRAL_ANALYSIS_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void spectral_analysis(real_T t[5001], real_T W[5001], real_T p, real_T *Hm0,
                       real_T *Tp, real_T *Tm01, real_T *Tm_10, real_T *Hrms);

void spectral_analysis_api(const mxArray *const prhs[3], int32_T nlhs,
                           const mxArray *plhs[5]);

void spectral_analysis_atexit(void);

void spectral_analysis_initialize(void);

void spectral_analysis_terminate(void);

void spectral_analysis_xil_shutdown(void);

void spectral_analysis_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_spectral_analysis_api.h
 *
 * [EOF]
 */
