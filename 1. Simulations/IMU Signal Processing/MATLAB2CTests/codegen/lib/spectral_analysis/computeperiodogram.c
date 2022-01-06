/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeperiodogram.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "computeperiodogram.h"
#include "bsxfun.h"
#include "computeDFT.h"
#include "mod.h"
#include "ppval.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_types.h"
#include "spline.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */
/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *win
 *                double nfft
 *                double Fs
 *                const char options_range[8]
 *                boolean_T options_reassign
 *                emxArray_real_T *Pxx
 *                emxArray_real_T *F
 *                emxArray_creal_T *RPxx
 *                emxArray_real_T *Fc
 * Return Type  : void
 */
void computeperiodogram(const emxArray_real_T *x, const emxArray_real_T *win,
                        double nfft, double Fs, const char options_range[8],
                        boolean_T options_reassign, emxArray_real_T *Pxx,
                        emxArray_real_T *F, emxArray_creal_T *RPxx,
                        emxArray_real_T *Fc)
{
  static const char b[8] = {'t', 'w', 'o', 's', 'i', 'd', 'e', 'd'};
  emxArray_boolean_T *b_x;
  emxArray_boolean_T *r;
  emxArray_creal_T *Xx;
  emxArray_creal_T *Xxc;
  emxArray_real_T *b_Fc;
  emxArray_real_T *c;
  emxArray_real_T *p1;
  emxArray_real_T *pp_coefs;
  emxArray_real_T *rowIdx;
  emxArray_real_T *y;
  struct_T expl_temp;
  double xv_data[4];
  double yv_data[3];
  double ai;
  double ar;
  double bi;
  double bim;
  double br;
  double newLen;
  int bcoef;
  int j;
  int k;
  int loop_ub;
  int nx;
  int stride;
  unsigned int tempIdx;
  int yv_size;
  signed char outsize_idx_0;
  boolean_T b_y;
  boolean_T exitg1;
  if (rtIsNaN(Fs)) {
    Fs = 6.2831853071795862;
  }
  emxInit_creal_T(&Xx, 1);
  emxInit_real_T(&b_Fc, 1);
  bsxfun(x, win, b_Fc);
  computeDFT(b_Fc, nfft, Fs, Xx, F);
  emxInit_real_T(&p1, 1);
  if (options_reassign) {
    emxInit_real_T(&y, 2);
    if (win->size[0] < 1) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else {
      j = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = win->size[0];
      emxEnsureCapacity_real_T(y, j);
      stride = win->size[0] - 1;
      for (j = 0; j <= stride; j++) {
        y->data[j] = (double)j + 1.0;
      }
    }
    emxInit_real_T(&pp_coefs, 2);
    emxInitStruct_struct_T(&expl_temp);
    spline(y, win, expl_temp.breaks, pp_coefs);
    j = expl_temp.coefs->size[0] * expl_temp.coefs->size[1];
    expl_temp.coefs->size[0] = pp_coefs->size[0];
    expl_temp.coefs->size[1] = pp_coefs->size[1] - 1;
    emxEnsureCapacity_real_T(expl_temp.coefs, j);
    stride = pp_coefs->size[0] * (pp_coefs->size[1] - 1);
    for (j = 0; j < stride; j++) {
      expl_temp.coefs->data[j] = 0.0;
    }
    nx = pp_coefs->size[1];
    stride = pp_coefs->size[0];
    if (0 <= pp_coefs->size[0] - 1) {
      outsize_idx_0 = (signed char)pp_coefs->size[1];
      loop_ub = (signed char)pp_coefs->size[1];
    }
    for (j = 0; j < stride; j++) {
      bcoef = outsize_idx_0;
      if (0 <= loop_ub - 1) {
        memset(&xv_data[0], 0, loop_ub * sizeof(double));
      }
      for (k = 0; k < nx; k++) {
        xv_data[k] = pp_coefs->data[j + k * stride];
      }
      yv_size = outsize_idx_0 - 1;
      for (k = 0; k <= bcoef - 2; k++) {
        yv_data[k] = xv_data[k] * ((double)(outsize_idx_0 - k) - 1.0);
      }
      for (k = 0; k < yv_size; k++) {
        expl_temp.coefs->data[j + k * stride] = yv_data[k];
      }
    }
    emxFree_real_T(&pp_coefs);
    if (win->size[0] < 1) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else {
      j = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = win->size[0];
      emxEnsureCapacity_real_T(y, j);
      stride = win->size[0] - 1;
      for (j = 0; j <= stride; j++) {
        y->data[j] = (double)j + 1.0;
      }
    }
    j = p1->size[0];
    p1->size[0] = y->size[1];
    emxEnsureCapacity_real_T(p1, j);
    stride = y->size[1];
    for (j = 0; j < stride; j++) {
      p1->data[j] = y->data[j];
    }
    emxFree_real_T(&y);
    ppval(expl_temp, p1, b_Fc);
    newLen = Fs / 6.2831853071795862;
    j = p1->size[0];
    p1->size[0] = b_Fc->size[0];
    emxEnsureCapacity_real_T(p1, j);
    stride = b_Fc->size[0];
    emxFreeStruct_struct_T(&expl_temp);
    for (j = 0; j < stride; j++) {
      p1->data[j] = b_Fc->data[j] * newLen;
    }
    emxInit_creal_T(&Xxc, 1);
    bsxfun(x, p1, b_Fc);
    computeDFT(b_Fc, nfft, Fs, Xxc, p1);
    j = b_Fc->size[0];
    b_Fc->size[0] = Xxc->size[0];
    emxEnsureCapacity_real_T(b_Fc, j);
    j = Xxc->size[0];
    emxInit_boolean_T(&b_x, 1);
    emxInit_boolean_T(&r, 1);
    for (nx = 0; nx < j; nx++) {
      stride = b_Fc->size[0];
      yv_size = b_x->size[0];
      b_x->size[0] = b_Fc->size[0];
      emxEnsureCapacity_boolean_T(b_x, yv_size);
      yv_size = r->size[0];
      r->size[0] = b_Fc->size[0];
      emxEnsureCapacity_boolean_T(r, yv_size);
      for (yv_size = 0; yv_size < stride; yv_size++) {
        b_x->data[yv_size] = rtIsInf(b_Fc->data[yv_size]);
        r->data[yv_size] = rtIsNaN(b_Fc->data[yv_size]);
      }
      stride = b_x->size[0];
      for (yv_size = 0; yv_size < stride; yv_size++) {
        b_x->data[yv_size] = (b_x->data[yv_size] || r->data[yv_size]);
      }
      b_y = true;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k <= b_x->size[0] - 1)) {
        if (!b_x->data[k]) {
          b_y = false;
          exitg1 = true;
        } else {
          k++;
        }
      }
      if (b_y) {
        b_Fc->data[nx] = 0.0;
      } else {
        ar = Xxc->data[nx].re;
        ai = Xxc->data[nx].im;
        br = Xx->data[nx].re;
        bi = Xx->data[nx].im;
        if (bi == 0.0) {
          if (ai == 0.0) {
            newLen = 0.0;
          } else {
            newLen = ai / br;
          }
        } else if (br == 0.0) {
          if (ar == 0.0) {
            newLen = 0.0;
          } else {
            newLen = -(ar / bi);
          }
        } else {
          newLen = fabs(br);
          bim = fabs(bi);
          if (newLen > bim) {
            newLen = bi / br;
            newLen = (ai - newLen * ar) / (br + newLen * bi);
          } else if (bim == newLen) {
            if (br > 0.0) {
              br = 0.5;
            } else {
              br = -0.5;
            }
            if (bi > 0.0) {
              bi = 0.5;
            } else {
              bi = -0.5;
            }
            newLen = (ai * br - ar * bi) / newLen;
          } else {
            newLen = br / bi;
            newLen = (newLen * ai - ar) / (bi + newLen * br);
          }
        }
        b_Fc->data[nx] = -newLen;
      }
    }
    emxFree_boolean_T(&r);
    emxFree_boolean_T(&b_x);
    emxInit_real_T(&c, 2);
    j = c->size[0] * c->size[1];
    stride = Xxc->size[0];
    bcoef = F->size[0];
    if (stride < bcoef) {
      bcoef = stride;
    }
    if (Xxc->size[0] == 1) {
      c->size[0] = F->size[0];
    } else if (F->size[0] == 1) {
      c->size[0] = Xxc->size[0];
    } else if (F->size[0] == Xxc->size[0]) {
      c->size[0] = F->size[0];
    } else {
      c->size[0] = bcoef;
    }
    c->size[1] = 1;
    emxEnsureCapacity_real_T(c, j);
    stride = (F->size[0] != 1);
    bcoef = (Xxc->size[0] != 1);
    j = c->size[0] - 1;
    emxFree_creal_T(&Xxc);
    for (k = 0; k <= j; k++) {
      c->data[k] = F->data[stride * k] + b_Fc->data[bcoef * k];
    }
    j = Fc->size[0] * Fc->size[1];
    Fc->size[0] = c->size[0];
    Fc->size[1] = 1;
    emxEnsureCapacity_real_T(Fc, j);
    stride = c->size[0];
    for (j = 0; j < stride; j++) {
      Fc->data[j] = c->data[j];
    }
    emxFree_real_T(&c);
  } else {
    Fc->size[0] = 0;
    Fc->size[1] = 0;
  }
  newLen = 0.0;
  stride = win->size[0];
  for (j = 0; j < stride; j++) {
    newLen += win->data[j] * win->data[j];
  }
  j = Pxx->size[0];
  Pxx->size[0] = Xx->size[0];
  emxEnsureCapacity_real_T(Pxx, j);
  stride = Xx->size[0];
  for (j = 0; j < stride; j++) {
    bim = Xx->data[j].re;
    ar = -Xx->data[j].im;
    ai = Xx->data[j].re * bim - Xx->data[j].im * ar;
    if (Xx->data[j].re * ar + Xx->data[j].im * bim == 0.0) {
      bim = ai / newLen;
    } else if (ai == 0.0) {
      bim = 0.0;
    } else {
      bim = ai / newLen;
    }
    Pxx->data[j] = bim;
  }
  emxFree_creal_T(&Xx);
  if (options_reassign) {
    bcoef = F->size[0];
    stride = memcmp(&options_range[0], &b[0], 8);
    emxInit_real_T(&rowIdx, 1);
    if (stride == 0) {
      newLen = F->data[F->size[0] - 1] - F->data[0];
      j = b_Fc->size[0];
      b_Fc->size[0] = Fc->size[0] * Fc->size[1];
      emxEnsureCapacity_real_T(b_Fc, j);
      stride = Fc->size[0] * Fc->size[1];
      for (j = 0; j < stride; j++) {
        b_Fc->data[j] =
            (Fc->data[j] - F->data[0]) * ((double)F->size[0] - 1.0) / newLen;
      }
      nx = b_Fc->size[0];
      for (k = 0; k < nx; k++) {
        b_Fc->data[k] = rt_roundd_snf(b_Fc->data[k]);
      }
      j = rowIdx->size[0];
      rowIdx->size[0] = b_Fc->size[0];
      emxEnsureCapacity_real_T(rowIdx, j);
      nx = b_Fc->size[0];
      for (k = 0; k < nx; k++) {
        rowIdx->data[k] = b_mod(b_Fc->data[k], bcoef);
      }
      stride = rowIdx->size[0];
      for (j = 0; j < stride; j++) {
        rowIdx->data[j]++;
      }
    } else {
      newLen = F->data[F->size[0] - 1] - F->data[0];
      j = rowIdx->size[0];
      rowIdx->size[0] = Fc->size[0] * Fc->size[1];
      emxEnsureCapacity_real_T(rowIdx, j);
      stride = Fc->size[0] * Fc->size[1];
      for (j = 0; j < stride; j++) {
        rowIdx->data[j] =
            (Fc->data[j] - F->data[0]) * ((double)F->size[0] - 1.0) / newLen;
      }
      nx = rowIdx->size[0];
      for (k = 0; k < nx; k++) {
        rowIdx->data[k] = rt_roundd_snf(rowIdx->data[k]);
      }
      stride = rowIdx->size[0];
      for (j = 0; j < stride; j++) {
        rowIdx->data[j]++;
      }
    }
    newLen = 0.0;
    j = rowIdx->size[0];
    for (nx = 0; nx < j; nx++) {
      if ((rowIdx->data[nx] >= 1.0) && (rowIdx->data[nx] <= bcoef)) {
        newLen++;
      }
    }
    j = (int)newLen;
    yv_size = b_Fc->size[0];
    b_Fc->size[0] = (int)newLen;
    emxEnsureCapacity_real_T(b_Fc, yv_size);
    yv_size = p1->size[0];
    p1->size[0] = (int)newLen;
    emxEnsureCapacity_real_T(p1, yv_size);
    tempIdx = 1U;
    newLen = 1.0;
    yv_size = rowIdx->size[0];
    for (nx = 0; nx < yv_size; nx++) {
      if ((rowIdx->data[nx] >= 1.0) && (rowIdx->data[nx] <= bcoef)) {
        b_Fc->data[(int)tempIdx - 1] = rowIdx->data[nx];
        p1->data[(int)tempIdx - 1] = Pxx->data[(int)newLen - 1];
        tempIdx++;
      }
      newLen++;
      if (b_mod((double)nx + 1.0, Pxx->size[0]) == 0.0) {
        newLen = 1.0;
      }
    }
    emxFree_real_T(&rowIdx);
    yv_size = RPxx->size[0];
    RPxx->size[0] = F->size[0];
    emxEnsureCapacity_creal_T(RPxx, yv_size);
    stride = F->size[0];
    for (yv_size = 0; yv_size < stride; yv_size++) {
      RPxx->data[yv_size].re = 0.0;
      RPxx->data[yv_size].im = 0.0;
    }
    for (nx = 0; nx < j; nx++) {
      yv_size = (int)b_Fc->data[nx] - 1;
      RPxx->data[yv_size].re += p1->data[nx];
    }
  } else {
    RPxx->size[0] = 0;
    Fc->size[0] = 0;
    Fc->size[1] = 0;
  }
  emxFree_real_T(&p1);
  emxFree_real_T(&b_Fc);
}

/*
 * File trailer for computeperiodogram.c
 *
 * [EOF]
 */
