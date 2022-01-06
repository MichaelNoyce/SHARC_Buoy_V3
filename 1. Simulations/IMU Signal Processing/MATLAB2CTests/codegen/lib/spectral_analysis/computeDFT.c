/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeDFT.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_types.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>
#include <string.h>

/* Function Declarations */
static int div_s32(int numerator, int denominator);

static double rt_remd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32(int numerator, int denominator)
{
  unsigned int b_denominator;
  unsigned int b_numerator;
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      b_numerator = ~(unsigned int)numerator + 1U;
    } else {
      b_numerator = (unsigned int)numerator;
    }
    if (denominator < 0) {
      b_denominator = ~(unsigned int)denominator + 1U;
    } else {
      b_denominator = (unsigned int)denominator;
    }
    b_numerator /= b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int)b_numerator;
    } else {
      quotient = (int)b_numerator;
    }
  }
  return quotient;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd_snf(double u0, double u1)
{
  double q;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = rtNaN;
  } else if (rtIsInf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }
  return y;
}

/*
 * Arguments    : const emxArray_real_T *xin
 *                double nfft
 *                double varargin_1
 *                emxArray_creal_T *Xx
 *                emxArray_real_T *f
 * Return Type  : void
 */
void computeDFT(const emxArray_real_T *xin, double nfft, double varargin_1,
                emxArray_creal_T *Xx, emxArray_real_T *f)
{
  emxArray_real_T *costab;
  emxArray_real_T *costab1q;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_real_T *wrappedData;
  emxArray_real_T *xw;
  double halfNPTS;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int b_remainder;
  int i;
  int ihi;
  int istart;
  int j;
  int k;
  int nFullPasses;
  int nRowsD2;
  int offset;
  int temp_re_tmp;
  boolean_T exitg1;
  boolean_T useRadix2;
  emxInit_real_T(&xw, 1);
  istart = (int)nfft;
  temp_re_tmp = xw->size[0];
  xw->size[0] = (int)nfft;
  emxEnsureCapacity_real_T(xw, temp_re_tmp);
  for (temp_re_tmp = 0; temp_re_tmp < istart; temp_re_tmp++) {
    xw->data[temp_re_tmp] = 0.0;
  }
  if (xin->size[0] > nfft) {
    emxInit_real_T(&wrappedData, 2);
    if (xin->size[0] == 1) {
      temp_re_tmp = wrappedData->size[0] * wrappedData->size[1];
      wrappedData->size[0] = 1;
      wrappedData->size[1] = (int)nfft;
      emxEnsureCapacity_real_T(wrappedData, temp_re_tmp);
      for (temp_re_tmp = 0; temp_re_tmp < istart; temp_re_tmp++) {
        wrappedData->data[temp_re_tmp] = 0.0;
      }
    } else {
      temp_re_tmp = wrappedData->size[0] * wrappedData->size[1];
      wrappedData->size[0] = (int)nfft;
      wrappedData->size[1] = 1;
      emxEnsureCapacity_real_T(wrappedData, temp_re_tmp);
      for (temp_re_tmp = 0; temp_re_tmp < istart; temp_re_tmp++) {
        wrappedData->data[temp_re_tmp] = 0.0;
      }
    }
    nFullPasses = div_s32(xin->size[0], (int)nfft);
    offset = nFullPasses * (int)nfft;
    b_remainder = (xin->size[0] - offset) - 1;
    for (k = 0; k <= b_remainder; k++) {
      wrappedData->data[k] = xin->data[offset + k];
    }
    temp_re_tmp = b_remainder + 2;
    for (k = temp_re_tmp; k <= istart; k++) {
      wrappedData->data[k - 1] = 0.0;
    }
    for (j = 0; j < nFullPasses; j++) {
      offset = j * (int)nfft;
      for (k = 0; k < istart; k++) {
        wrappedData->data[k] += xin->data[offset + k];
      }
    }
    offset = wrappedData->size[0] * wrappedData->size[1];
    for (temp_re_tmp = 0; temp_re_tmp < offset; temp_re_tmp++) {
      xw->data[temp_re_tmp] = wrappedData->data[temp_re_tmp];
    }
    emxFree_real_T(&wrappedData);
  } else {
    temp_re_tmp = xw->size[0];
    xw->size[0] = xin->size[0];
    emxEnsureCapacity_real_T(xw, temp_re_tmp);
    offset = xin->size[0];
    for (temp_re_tmp = 0; temp_re_tmp < offset; temp_re_tmp++) {
      xw->data[temp_re_tmp] = xin->data[temp_re_tmp];
    }
  }
  emxInit_real_T(&costab1q, 2);
  if (xw->size[0] == 0) {
    temp_re_tmp = Xx->size[0];
    Xx->size[0] = (int)nfft;
    emxEnsureCapacity_creal_T(Xx, temp_re_tmp);
    for (temp_re_tmp = 0; temp_re_tmp < istart; temp_re_tmp++) {
      Xx->data[temp_re_tmp].re = 0.0;
      Xx->data[temp_re_tmp].im = 0.0;
    }
  } else {
    useRadix2 = (((int)nfft & ((int)nfft - 1)) == 0);
    nFullPasses = 1;
    if (useRadix2) {
      offset = (int)nfft;
    } else {
      ihi = ((int)nfft + (int)nfft) - 1;
      b_remainder = 31;
      if (ihi <= 1) {
        b_remainder = 0;
      } else {
        offset = 0;
        exitg1 = false;
        while ((!exitg1) && (b_remainder - offset > 1)) {
          k = (offset + b_remainder) >> 1;
          nFullPasses = 1 << k;
          if (nFullPasses == ihi) {
            b_remainder = k;
            exitg1 = true;
          } else if (nFullPasses > ihi) {
            b_remainder = k;
          } else {
            offset = k;
          }
        }
      }
      nFullPasses = 1 << b_remainder;
      offset = nFullPasses;
    }
    twid_re = 6.2831853071795862 / (double)offset;
    ihi = offset / 2 / 2;
    temp_re_tmp = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = ihi + 1;
    emxEnsureCapacity_real_T(costab1q, temp_re_tmp);
    costab1q->data[0] = 1.0;
    b_remainder = ihi / 2 - 1;
    for (k = 0; k <= b_remainder; k++) {
      costab1q->data[k + 1] = cos(twid_re * ((double)k + 1.0));
    }
    temp_re_tmp = b_remainder + 2;
    b_remainder = ihi - 1;
    for (k = temp_re_tmp; k <= b_remainder; k++) {
      costab1q->data[k] = sin(twid_re * (double)(ihi - k));
    }
    costab1q->data[ihi] = 0.0;
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    if (!useRadix2) {
      ihi = costab1q->size[1] - 1;
      b_remainder = (costab1q->size[1] - 1) << 1;
      temp_re_tmp = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = b_remainder + 1;
      emxEnsureCapacity_real_T(costab, temp_re_tmp);
      temp_re_tmp = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = b_remainder + 1;
      emxEnsureCapacity_real_T(sintab, temp_re_tmp);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      temp_re_tmp = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = b_remainder + 1;
      emxEnsureCapacity_real_T(sintabinv, temp_re_tmp);
      for (k = 0; k < ihi; k++) {
        sintabinv->data[k + 1] = costab1q->data[(ihi - k) - 1];
      }
      temp_re_tmp = costab1q->size[1];
      for (k = temp_re_tmp; k <= b_remainder; k++) {
        sintabinv->data[k] = costab1q->data[k - ihi];
      }
      for (k = 0; k < ihi; k++) {
        costab->data[k + 1] = costab1q->data[k + 1];
        sintab->data[k + 1] = -costab1q->data[(ihi - k) - 1];
      }
      temp_re_tmp = costab1q->size[1];
      for (k = temp_re_tmp; k <= b_remainder; k++) {
        costab->data[k] = -costab1q->data[b_remainder - k];
        sintab->data[k] = -costab1q->data[k - ihi];
      }
    } else {
      ihi = costab1q->size[1] - 1;
      b_remainder = (costab1q->size[1] - 1) << 1;
      temp_re_tmp = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = b_remainder + 1;
      emxEnsureCapacity_real_T(costab, temp_re_tmp);
      temp_re_tmp = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = b_remainder + 1;
      emxEnsureCapacity_real_T(sintab, temp_re_tmp);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      for (k = 0; k < ihi; k++) {
        costab->data[k + 1] = costab1q->data[k + 1];
        sintab->data[k + 1] = -costab1q->data[(ihi - k) - 1];
      }
      temp_re_tmp = costab1q->size[1];
      for (k = temp_re_tmp; k <= b_remainder; k++) {
        costab->data[k] = -costab1q->data[b_remainder - k];
        sintab->data[k] = -costab1q->data[k - ihi];
      }
      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
    }
    if (useRadix2) {
      temp_re_tmp = Xx->size[0];
      Xx->size[0] = (int)nfft;
      emxEnsureCapacity_creal_T(Xx, temp_re_tmp);
      if ((int)nfft > xw->size[0]) {
        temp_re_tmp = Xx->size[0];
        Xx->size[0] = (int)nfft;
        emxEnsureCapacity_creal_T(Xx, temp_re_tmp);
        for (temp_re_tmp = 0; temp_re_tmp < istart; temp_re_tmp++) {
          Xx->data[temp_re_tmp].re = 0.0;
          Xx->data[temp_re_tmp].im = 0.0;
        }
      }
      if ((int)nfft != 1) {
        c_FFTImplementationCallback_doH(xw, Xx, (int)nfft, costab, sintab);
      } else {
        offset = xw->size[0];
        istart = (int)nfft;
        if (offset < istart) {
          istart = offset;
        }
        offset = (int)nfft - 2;
        nRowsD2 = (int)nfft / 2;
        k = nRowsD2 / 2;
        b_remainder = 0;
        nFullPasses = 0;
        for (i = 0; i <= istart - 2; i++) {
          Xx->data[b_remainder].re = xw->data[i];
          Xx->data[b_remainder].im = 0.0;
          ihi = (int)nfft;
          useRadix2 = true;
          while (useRadix2) {
            ihi >>= 1;
            nFullPasses ^= ihi;
            useRadix2 = ((nFullPasses & ihi) == 0);
          }
          b_remainder = nFullPasses;
        }
        Xx->data[b_remainder].re = xw->data[istart - 1];
        Xx->data[b_remainder].im = 0.0;
        if ((int)nfft > 1) {
          for (i = 0; i <= offset; i += 2) {
            temp_re = Xx->data[i + 1].re;
            temp_im = Xx->data[i + 1].im;
            twid_re = Xx->data[i].re;
            twid_im = Xx->data[i].im;
            Xx->data[i + 1].re = Xx->data[i].re - Xx->data[i + 1].re;
            Xx->data[i + 1].im = Xx->data[i].im - Xx->data[i + 1].im;
            twid_re += temp_re;
            twid_im += temp_im;
            Xx->data[i].re = twid_re;
            Xx->data[i].im = twid_im;
          }
        }
        b_remainder = 2;
        offset = 4;
        nFullPasses = ((k - 1) << 2) + 1;
        while (k > 0) {
          for (i = 0; i < nFullPasses; i += offset) {
            temp_re_tmp = i + b_remainder;
            temp_re = Xx->data[temp_re_tmp].re;
            temp_im = Xx->data[temp_re_tmp].im;
            Xx->data[temp_re_tmp].re = Xx->data[i].re - temp_re;
            Xx->data[temp_re_tmp].im = Xx->data[i].im - temp_im;
            Xx->data[i].re += temp_re;
            Xx->data[i].im += temp_im;
          }
          istart = 1;
          for (j = k; j < nRowsD2; j += k) {
            twid_re = costab->data[j];
            twid_im = sintab->data[j];
            i = istart;
            ihi = istart + nFullPasses;
            while (i < ihi) {
              temp_re_tmp = i + b_remainder;
              temp_re = twid_re * Xx->data[temp_re_tmp].re -
                        twid_im * Xx->data[temp_re_tmp].im;
              temp_im = twid_re * Xx->data[temp_re_tmp].im +
                        twid_im * Xx->data[temp_re_tmp].re;
              Xx->data[temp_re_tmp].re = Xx->data[i].re - temp_re;
              Xx->data[temp_re_tmp].im = Xx->data[i].im - temp_im;
              Xx->data[i].re += temp_re;
              Xx->data[i].im += temp_im;
              i += offset;
            }
            istart++;
          }
          k /= 2;
          b_remainder = offset;
          offset += offset;
          nFullPasses -= b_remainder;
        }
      }
    } else {
      c_FFTImplementationCallback_dob(xw, nFullPasses, (int)nfft, costab,
                                      sintab, sintabinv, Xx);
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
  emxFree_real_T(&xw);
  if (rtIsNaN(varargin_1)) {
    twid_re = 6.2831853071795862;
  } else {
    twid_re = varargin_1;
  }
  twid_im = twid_re / nfft;
  if (rtIsInf(nfft - 1.0) && (0.0 == nfft - 1.0)) {
    temp_re_tmp = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = 1;
    emxEnsureCapacity_real_T(costab1q, temp_re_tmp);
    costab1q->data[0] = rtNaN;
  } else {
    temp_re_tmp = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    offset = (int)floor(nfft - 1.0);
    costab1q->size[1] = offset + 1;
    emxEnsureCapacity_real_T(costab1q, temp_re_tmp);
    for (temp_re_tmp = 0; temp_re_tmp <= offset; temp_re_tmp++) {
      costab1q->data[temp_re_tmp] = temp_re_tmp;
    }
  }
  temp_re_tmp = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  emxEnsureCapacity_real_T(costab1q, temp_re_tmp);
  offset = costab1q->size[1] - 1;
  for (temp_re_tmp = 0; temp_re_tmp <= offset; temp_re_tmp++) {
    costab1q->data[temp_re_tmp] *= twid_im;
  }
  temp_re = twid_re / 2.0;
  temp_im = twid_im / 2.0;
  if (rt_remd_snf(nfft, 2.0) != 0.0) {
    halfNPTS = (nfft + 1.0) / 2.0;
    costab1q->data[(int)halfNPTS - 1] = temp_re - temp_im;
    costab1q->data[(int)(unsigned int)halfNPTS] = temp_re + temp_im;
  } else {
    costab1q->data[(int)(nfft / 2.0 + 1.0) - 1] = temp_re;
  }
  costab1q->data[(int)nfft - 1] = twid_re - twid_im;
  temp_re_tmp = f->size[0];
  f->size[0] = costab1q->size[1];
  emxEnsureCapacity_real_T(f, temp_re_tmp);
  offset = costab1q->size[1];
  for (temp_re_tmp = 0; temp_re_tmp < offset; temp_re_tmp++) {
    f->data[temp_re_tmp] = costab1q->data[temp_re_tmp];
  }
  emxFree_real_T(&costab1q);
}

/*
 * File trailer for computeDFT.c
 *
 * [EOF]
 */
