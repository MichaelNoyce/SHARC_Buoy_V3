/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: spectral_analysis.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "spectral_analysis.h"
#include "periodogram.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_data.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_initialize.h"
#include "spectral_analysis_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double d;
  double d1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * Function that builds the wave spectrum from a wave record (water elevation)
 * and give some output parameters. The output parameters are the significant
 * wave height and the mean wave period.
 * It is based on Spectral.m Script (and Spectral2.m) reconverted into a
 * function
 *
 *  Input parameters
 *  t = time series input
 *  W = Water elevation series input
 *  p = number of periodograms
 *
 *  Output parameters
 *  Hm0 = Spectral wave height/significant wave height = 4*sqrt(m0)
 *  HRMS = Root mean square wave height = sqrt(8*m0)
 *  Tp = peak wave period
 *  Tm01 = mean wave period = m0/m1
 *  Tm_10 = m_1/m0
 * At: time interval between the results written on the table!
 * At=t(2)-t(1);
 *
 * Arguments    : const double t[5001]
 *                const double W[5001]
 *                double p
 *                double *Hm0
 *                double *Tp
 *                double *Tm01
 *                double *Tm_10
 *                double *Hrms
 * Return Type  : void
 */
void spectral_analysis(const double t[5001], const double W[5001], double p,
                       double *Hm0, double *Tp, double *Tm01, double *Tm_10,
                       double *Hrms)
{
  emxArray_real_T *Pxx;
  emxArray_real_T *bsum;
  emxArray_real_T *f;
  emxArray_real_T *mW;
  emxArray_real_T *r;
  emxArray_real_T *x;
  emxArray_real_T *y;
  double At;
  double apnd;
  double cdiff;
  double d;
  double ex;
  double fr;
  double ndbl;
  int bvstride;
  int ib;
  int idx;
  int k;
  int lastBlockLength;
  int nblocks;
  int nx;
  int vstride;
  int xj;
  int xoffset;
  boolean_T b;
  boolean_T exitg1;
  if (!isInitialized_spectral_analysis) {
    spectral_analysis_initialize();
  }
  b = rtIsNaN(t[0]);
  if (!b) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5002)) {
      if (!rtIsNaN(t[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    ex = t[0];
  } else {
    ex = t[idx - 1];
    xoffset = idx + 1;
    for (k = xoffset; k < 5002; k++) {
      d = t[k - 1];
      if (ex < d) {
        ex = d;
      }
    }
  }
  if (!b) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5002)) {
      if (!rtIsNaN(t[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    At = t[0];
  } else {
    At = t[idx - 1];
    xoffset = idx + 1;
    for (k = xoffset; k < 5002; k++) {
      d = t[k - 1];
      if (At > d) {
        At = d;
      }
    }
  }
  emxInit_real_T(&f, 2);
  At = (ex - At) / 5000.0;
  /* Sampling frequency */
  fr = 1.0 / At;
  /* Length of the water elevation record */
  /* Frequency series */
  xoffset = f->size[0] * f->size[1];
  f->size[0] = 1;
  f->size[1] = 2501;
  emxEnsureCapacity_real_T(f, xoffset);
  for (xoffset = 0; xoffset < 2501; xoffset++) {
    f->data[xoffset] = At * (double)xoffset / 5001.0;
  }
  emxInit_real_T(&x, 2);
  /* number of periodograms */
  /* p=10; */
  /* p=5; */
  /* W is divided into 20 samples/periodograms 18000/20=900 samples/periodogram
   */
  /* W is divided into 10 periodograms 18000/10=1800 samples/peridogram */
  /* W is divided into 5 periodograms 18000/5=3600 samples/periodogram */
  /* Very long records needed!!! 90 min for 10 periodograms or 45 for 5. */
  /* Periodogram samples */
  d = floor(5001.0 / p);
  xoffset = x->size[0] * x->size[1];
  x->size[0] = (int)d;
  x->size[1] = (int)d;
  emxEnsureCapacity_real_T(x, xoffset);
  nx = (int)d * (int)d;
  for (xoffset = 0; xoffset < nx; xoffset++) {
    x->data[xoffset] = 0.0;
  }
  xoffset = (int)p;
  emxInit_real_T(&y, 2);
  for (lastBlockLength = 0; lastBlockLength < xoffset; lastBlockLength++) {
    At = (((double)lastBlockLength + 1.0) - 1.0) * 5001.0 / p + 1.0;
    ex = 5001.0 / p * ((double)lastBlockLength + 1.0);
    if (rtIsNaN(At) || rtIsNaN(ex)) {
      idx = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, idx);
      y->data[0] = rtNaN;
    } else if (ex < At) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if ((rtIsInf(At) || rtIsInf(ex)) && (At == ex)) {
      idx = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, idx);
      y->data[0] = rtNaN;
    } else if (floor(At) == At) {
      idx = y->size[0] * y->size[1];
      y->size[0] = 1;
      nx = (int)floor(ex - At);
      y->size[1] = nx + 1;
      emxEnsureCapacity_real_T(y, idx);
      for (idx = 0; idx <= nx; idx++) {
        y->data[idx] = At + (double)idx;
      }
    } else {
      ndbl = floor((ex - At) + 0.5);
      apnd = At + ndbl;
      cdiff = apnd - ex;
      if (fabs(cdiff) < 4.4408920985006262E-16 * fmax(fabs(At), fabs(ex))) {
        ndbl++;
        apnd = ex;
      } else if (cdiff > 0.0) {
        apnd = At + (ndbl - 1.0);
      } else {
        ndbl++;
      }
      if (ndbl >= 0.0) {
        nx = (int)ndbl;
      } else {
        nx = 0;
      }
      idx = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = nx;
      emxEnsureCapacity_real_T(y, idx);
      if (nx > 0) {
        y->data[0] = At;
        if (nx > 1) {
          y->data[nx - 1] = apnd;
          idx = (nx - 1) / 2;
          for (k = 0; k <= idx - 2; k++) {
            y->data[k + 1] = At + ((double)k + 1.0);
            y->data[(nx - k) - 2] = apnd - ((double)k + 1.0);
          }
          if (idx << 1 == nx - 1) {
            y->data[idx] = (At + apnd) / 2.0;
          } else {
            y->data[idx] = At + (double)idx;
            y->data[idx + 1] = apnd - (double)idx;
          }
        }
      }
    }
    nx = y->size[1];
    for (k = 0; k < nx; k++) {
      y->data[k] = floor(y->data[k]);
    }
    nx = y->size[1];
    for (idx = 0; idx < nx; idx++) {
      x->data[idx + x->size[0] * lastBlockLength] = W[(int)y->data[idx] - 1];
    }
  }
  emxFree_real_T(&y);
  /* Next power of 2 greater or equal to length of the sample vector to */
  /* calculate fft. FFT needs a length power of 2 to be efficient. For a */
  /* shorter record, zeros will be added to reach this value. */
  At = frexp(x->size[0], &nblocks);
  if (At == 0.5) {
    nblocks--;
  }
  emxInit_real_T(&Pxx, 2);
  At = rt_powd_snf(2.0, nblocks);
  d = At / 2.0 + 1.0;
  idx = Pxx->size[0] * Pxx->size[1];
  Pxx->size[0] = (int)d;
  Pxx->size[1] = (int)d;
  emxEnsureCapacity_real_T(Pxx, idx);
  nx = (int)d * (int)d;
  for (idx = 0; idx < nx; idx++) {
    Pxx->data[idx] = 0.0;
  }
  emxInit_real_T(&mW, 1);
  emxInit_real_T(&r, 2);
  emxInit_real_T(&bsum, 1);
  for (lastBlockLength = 0; lastBlockLength < xoffset; lastBlockLength++) {
    /* PSD */
    nx = x->size[0];
    idx = mW->size[0];
    mW->size[0] = x->size[0];
    emxEnsureCapacity_real_T(mW, idx);
    for (idx = 0; idx < nx; idx++) {
      mW->data[idx] = x->data[idx + x->size[0] * lastBlockLength];
    }
    periodogram(mW, At, fr, r, bsum);
    nx = Pxx->size[0];
    for (idx = 0; idx < nx; idx++) {
      Pxx->data[idx + Pxx->size[0] * lastBlockLength] = r->data[idx];
    }
    nx = bsum->size[0];
    idx = f->size[0] * f->size[1];
    f->size[0] = bsum->size[0];
    f->size[1] = 1;
    emxEnsureCapacity_real_T(f, idx);
    for (idx = 0; idx < nx; idx++) {
      f->data[idx] = bsum->data[idx];
    }
    /* [Pxx(:,i),w]=periodogram(x(:,i),[],nfft,fr); */
  }
  emxFree_real_T(&r);
  emxFree_real_T(&x);
  /* Average periodograms */
  vstride = Pxx->size[0] - 1;
  bvstride = Pxx->size[0] << 10;
  xoffset = mW->size[0];
  mW->size[0] = Pxx->size[0];
  emxEnsureCapacity_real_T(mW, xoffset);
  xoffset = bsum->size[0];
  bsum->size[0] = Pxx->size[0];
  emxEnsureCapacity_real_T(bsum, xoffset);
  if (Pxx->size[1] <= 1024) {
    idx = Pxx->size[1];
    lastBlockLength = 0;
    nblocks = 1;
  } else {
    idx = 1024;
    nblocks = Pxx->size[1] / 1024;
    lastBlockLength = Pxx->size[1] - (nblocks << 10);
    if (lastBlockLength > 0) {
      nblocks++;
    } else {
      lastBlockLength = 1024;
    }
  }
  for (xj = 0; xj <= vstride; xj++) {
    mW->data[xj] = Pxx->data[xj];
    bsum->data[xj] = 0.0;
  }
  for (k = 2; k <= idx; k++) {
    xoffset = (k - 1) * (vstride + 1);
    for (xj = 0; xj <= vstride; xj++) {
      mW->data[xj] += Pxx->data[xoffset + xj];
    }
  }
  for (ib = 2; ib <= nblocks; ib++) {
    idx = (ib - 1) * bvstride;
    for (xj = 0; xj <= vstride; xj++) {
      bsum->data[xj] = Pxx->data[idx + xj];
    }
    if (ib == nblocks) {
      nx = lastBlockLength;
    } else {
      nx = 1024;
    }
    for (k = 2; k <= nx; k++) {
      xoffset = idx + (k - 1) * (vstride + 1);
      for (xj = 0; xj <= vstride; xj++) {
        bsum->data[xj] += Pxx->data[xoffset + xj];
      }
    }
    for (xj = 0; xj <= vstride; xj++) {
      mW->data[xj] += bsum->data[xj];
    }
  }
  emxFree_real_T(&bsum);
  emxFree_real_T(&Pxx);
  nx = mW->size[0];
  for (xoffset = 0; xoffset < nx; xoffset++) {
    mW->data[xoffset] /= p;
  }
  /* f = Frequency vector */
  /* f=w */
  /* Wave period vector for the plot */
  /* ft=1./w; */
  /* Computation of some wave parameters. */
  /* To do that 2 integrals must be numerically computed. Since the */
  /* analytical function is unknown and the available data is a set of points */
  /* (theorically equidistant), a Newton-Cotes quadrature will be used.  */
  /* As the spectrum graph is built using linear interpolation, a composite */
  /* trapezoidal rule will be used for numerical integration. */
  /* Spectrum function E(f)=mW */
  /* total number of points */
  /* number of subintervals */
  /* length of the subinterval */
  ndbl = (f->data[mW->size[0] - 1] - f->data[0]) / ((double)mW->size[0] - 1.0);
  /* Integral I1 m0=int{E(f)df} I1 */
  apnd = 0.0;
  xoffset = mW->size[0];
  for (lastBlockLength = 0; lastBlockLength <= xoffset - 3; lastBlockLength++) {
    apnd += mW->data[lastBlockLength + 1];
    /* sum(2,m) f(xi) */
  }
  cdiff = 0.5 * ndbl * ((mW->data[0] + 2.0 * apnd) + mW->data[mW->size[0] - 1]);
  /* Integral I2 m1=int{f*E(f)df} I2 */
  apnd = 0.0;
  /* f=f*E(f)=f*mW */
  xoffset = mW->size[0];
  for (lastBlockLength = 0; lastBlockLength <= xoffset - 3; lastBlockLength++) {
    apnd += f->data[lastBlockLength + 1] * mW->data[lastBlockLength + 1];
  }
  At = 0.5 * ndbl *
       ((f->data[0] * mW->data[0] + 2.0 * apnd) +
        f->data[mW->size[0] - 1] * mW->data[mW->size[0] - 1]);
  /* Integral I3 m2=int{f^2*E(f)df} I3 */
  /* Integral I4 m_1=int{f^(-1)*E(f)df} I4 */
  apnd = 0.0;
  xoffset = mW->size[0];
  for (lastBlockLength = 0; lastBlockLength <= xoffset - 4; lastBlockLength++) {
    apnd += mW->data[lastBlockLength + 2] / f->data[lastBlockLength + 2];
  }
  /* Note: f(1)=0 and so it is expluded. The integral is not fully computed. */
  /* There is a mistake there! */
  /* Spectrum analysis output */
  /* Significant wave height */
  /* Hm0=4*sqrt(int{E(f)df}) */
  *Hm0 = 4.0 * sqrt(cdiff);
  /* Mean spectral wave period */
  /* Tm01=(int{E(f)df}/(f*int{E(f)df})) */
  *Tm01 = cdiff / At;
  /* Peak wave period */
  nx = mW->size[0];
  if (mW->size[0] <= 2) {
    if (mW->size[0] == 1) {
      idx = 1;
    } else if ((mW->data[0] < mW->data[1]) ||
               (rtIsNaN(mW->data[0]) && (!rtIsNaN(mW->data[1])))) {
      idx = 2;
    } else {
      idx = 1;
    }
  } else {
    if (!rtIsNaN(mW->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= nx)) {
        if (!rtIsNaN(mW->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      idx = 1;
    } else {
      ex = mW->data[idx - 1];
      xoffset = idx + 1;
      for (k = xoffset; k <= nx; k++) {
        d = mW->data[k - 1];
        if (ex < d) {
          ex = d;
          idx = k;
        }
      }
    }
  }
  *Tp = 1.0 / f->data[idx - 1];
  /* Mean zero-crossing period */
  /* Mean spectral wave period Tm-1,0 with a higher weight of the longer waves
   */
  *Tm_10 = 0.5 * ndbl *
           ((1.0 / f->data[1] * mW->data[1] + 2.0 * apnd) +
            1.0 / f->data[mW->size[0] - 1] * mW->data[mW->size[0] - 1]) /
           cdiff;
  /* Remember that one point has been ommited to compute Tm_10. I am not sure */
  /* if it does not affect the result! */
  /* Root Mean Square Wave height */
  *Hrms = 0.70710678118654757 * *Hm0;
  emxFree_real_T(&mW);
  emxFree_real_T(&f);
}

/*
 * File trailer for spectral_analysis.c
 *
 * [EOF]
 */
