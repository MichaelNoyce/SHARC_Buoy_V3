/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: periodogram.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "periodogram.h"
#include "computeperiodogram.h"
#include "mod.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x1
 *                double varargin_2
 *                double varargin_3
 *                emxArray_real_T *Px
 *                emxArray_real_T *w
 * Return Type  : void
 */
void periodogram(const emxArray_real_T *x1, double varargin_2,
                 double varargin_3, emxArray_real_T *Px, emxArray_real_T *w)
{
  static const char b[8] = {'o', 'n', 'e', 's', 'i', 'd', 'e', 'd'};
  emxArray_creal_T *RPxx;
  emxArray_creal_T *Sxx;
  emxArray_real_T *b_Sxx;
  emxArray_real_T *b_select;
  emxArray_real_T *wc;
  emxArray_real_T *win2;
  double b_b;
  double c_Sxx;
  int i;
  int i1;
  int ret;
  emxInit_real_T(&win2, 1);
  frexp(x1->size[0], &ret);
  ret = x1->size[0];
  i = win2->size[0];
  win2->size[0] = x1->size[0];
  emxEnsureCapacity_real_T(win2, i);
  for (i = 0; i < ret; i++) {
    win2->data[i] = 1.0;
  }
  emxInit_real_T(&wc, 2);
  emxInit_creal_T(&Sxx, 1);
  emxInit_real_T(&b_Sxx, 1);
  computeperiodogram(x1, win2, varargin_2, varargin_3, b, false, b_Sxx, w, Sxx,
                     wc);
  ret = memcmp(&b[0], &b[0], 8);
  emxFree_creal_T(&Sxx);
  emxFree_real_T(&wc);
  if (ret == 0) {
    emxInit_real_T(&b_select, 2);
    if (b_mod(varargin_2, 2.0) == 1.0) {
      b_b = (varargin_2 + 1.0) / 2.0;
      if (rtIsNaN(b_b)) {
        i = b_select->size[0] * b_select->size[1];
        b_select->size[0] = 1;
        b_select->size[1] = 1;
        emxEnsureCapacity_real_T(b_select, i);
        b_select->data[0] = rtNaN;
      } else if (b_b < 1.0) {
        b_select->size[0] = 1;
        b_select->size[1] = 0;
      } else if (rtIsInf(b_b) && (1.0 == b_b)) {
        i = b_select->size[0] * b_select->size[1];
        b_select->size[0] = 1;
        b_select->size[1] = 1;
        emxEnsureCapacity_real_T(b_select, i);
        b_select->data[0] = rtNaN;
      } else {
        i = b_select->size[0] * b_select->size[1];
        b_select->size[0] = 1;
        ret = (int)floor(b_b - 1.0);
        b_select->size[1] = ret + 1;
        emxEnsureCapacity_real_T(b_select, i);
        for (i = 0; i <= ret; i++) {
          b_select->data[i] = (double)i + 1.0;
        }
      }
      i = win2->size[0];
      win2->size[0] = b_select->size[1];
      emxEnsureCapacity_real_T(win2, i);
      ret = b_select->size[1];
      for (i = 0; i < ret; i++) {
        win2->data[i] = b_Sxx->data[(int)b_select->data[i] - 1];
      }
      if (2 > b_select->size[1]) {
        i = 0;
        i1 = 0;
      } else {
        i = 1;
        i1 = b_select->size[1];
      }
      b_b = b_Sxx->data[(int)b_select->data[0] - 1];
      ret = i1 - i;
      i1 = b_Sxx->size[0];
      b_Sxx->size[0] = ret + 1;
      emxEnsureCapacity_real_T(b_Sxx, i1);
      b_Sxx->data[0] = b_b;
      for (i1 = 0; i1 < ret; i1++) {
        b_Sxx->data[i1 + 1] = 2.0 * win2->data[i + i1];
      }
    } else {
      b_b = varargin_2 / 2.0 + 1.0;
      if (rtIsNaN(b_b)) {
        i = b_select->size[0] * b_select->size[1];
        b_select->size[0] = 1;
        b_select->size[1] = 1;
        emxEnsureCapacity_real_T(b_select, i);
        b_select->data[0] = rtNaN;
      } else if (b_b < 1.0) {
        b_select->size[0] = 1;
        b_select->size[1] = 0;
      } else if (rtIsInf(b_b) && (1.0 == b_b)) {
        i = b_select->size[0] * b_select->size[1];
        b_select->size[0] = 1;
        b_select->size[1] = 1;
        emxEnsureCapacity_real_T(b_select, i);
        b_select->data[0] = rtNaN;
      } else {
        i = b_select->size[0] * b_select->size[1];
        b_select->size[0] = 1;
        ret = (int)floor(b_b - 1.0);
        b_select->size[1] = ret + 1;
        emxEnsureCapacity_real_T(b_select, i);
        for (i = 0; i <= ret; i++) {
          b_select->data[i] = (double)i + 1.0;
        }
      }
      i = win2->size[0];
      win2->size[0] = b_select->size[1];
      emxEnsureCapacity_real_T(win2, i);
      ret = b_select->size[1];
      for (i = 0; i < ret; i++) {
        win2->data[i] = b_Sxx->data[(int)b_select->data[i] - 1];
      }
      if (2 > b_select->size[1] - 1) {
        i = 0;
        i1 = 1;
      } else {
        i = 1;
        i1 = b_select->size[1];
      }
      b_b = b_Sxx->data[(int)b_select->data[0] - 1];
      c_Sxx = b_Sxx->data[(int)b_select->data[b_select->size[1] - 1] - 1];
      ret = i1 - i;
      i1 = b_Sxx->size[0];
      b_Sxx->size[0] = ret + 1;
      emxEnsureCapacity_real_T(b_Sxx, i1);
      b_Sxx->data[0] = b_b;
      for (i1 = 0; i1 <= ret - 2; i1++) {
        b_Sxx->data[i1 + 1] = 2.0 * win2->data[i + i1];
      }
      b_Sxx->data[ret] = c_Sxx;
    }
    i = win2->size[0];
    win2->size[0] = b_select->size[1];
    emxEnsureCapacity_real_T(win2, i);
    ret = b_select->size[1];
    for (i = 0; i < ret; i++) {
      win2->data[i] = w->data[(int)b_select->data[i] - 1];
    }
    emxFree_real_T(&b_select);
    i = w->size[0];
    w->size[0] = win2->size[0];
    emxEnsureCapacity_real_T(w, i);
    ret = win2->size[0];
    for (i = 0; i < ret; i++) {
      w->data[i] = win2->data[i];
    }
  }
  emxFree_real_T(&win2);
  if (!rtIsNaN(varargin_3)) {
    ret = b_Sxx->size[0];
    for (i = 0; i < ret; i++) {
      b_Sxx->data[i] /= varargin_3;
    }
  } else {
    ret = b_Sxx->size[0];
    for (i = 0; i < ret; i++) {
      b_Sxx->data[i] /= 6.2831853071795862;
    }
  }
  emxInit_creal_T(&RPxx, 2);
  i = RPxx->size[0] * RPxx->size[1];
  RPxx->size[0] = b_Sxx->size[0];
  RPxx->size[1] = 1;
  emxEnsureCapacity_creal_T(RPxx, i);
  ret = b_Sxx->size[0];
  for (i = 0; i < ret; i++) {
    RPxx->data[i].re = b_Sxx->data[i];
    RPxx->data[i].im = 0.0;
  }
  emxFree_real_T(&b_Sxx);
  i = Px->size[0] * Px->size[1];
  Px->size[0] = RPxx->size[0];
  Px->size[1] = 1;
  emxEnsureCapacity_real_T(Px, i);
  ret = RPxx->size[0];
  for (i = 0; i < ret; i++) {
    Px->data[i] = RPxx->data[i].re;
  }
  emxFree_creal_T(&RPxx);
}

/*
 * File trailer for periodogram.c
 *
 * [EOF]
 */
