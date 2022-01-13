/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ppval.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "ppval.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const struct_T pp
 *                const emxArray_real_T *x
 *                emxArray_real_T *v
 * Return Type  : void
 */
void ppval(const struct_T pp, const emxArray_real_T *x, emxArray_real_T *v)
{
  double b_v;
  double xloc;
  int coefStride;
  int high_i;
  int ix;
  int low_i;
  int low_ip1;
  int mid_i;
  int numTerms;
  int ub_loop;
  coefStride = pp.breaks->size[1] - 1;
  numTerms = pp.coefs->size[1];
  ub_loop = v->size[0];
  v->size[0] = x->size[0];
  emxEnsureCapacity_real_T(v, ub_loop);
  ub_loop = x->size[0] - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    high_i, b_v, low_i, low_ip1, xloc, mid_i)

  for (ix = 0; ix <= ub_loop; ix++) {
    if ((numTerms > 1) && rtIsNaN(x->data[ix])) {
      b_v = x->data[ix];
    } else {
      high_i = pp.breaks->size[1];
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }
        if (x->data[ix] >= pp.breaks->data[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      xloc = x->data[ix] - pp.breaks->data[low_i - 1];
      b_v = pp.coefs->data[low_i - 1];
      for (high_i = 2; high_i <= numTerms; high_i++) {
        b_v = xloc * b_v +
              pp.coefs->data[(low_i + (high_i - 1) * coefStride) - 1];
      }
    }
    v->data[ix] = b_v;
  }
}

/*
 * File trailer for ppval.c
 *
 * [EOF]
 */
