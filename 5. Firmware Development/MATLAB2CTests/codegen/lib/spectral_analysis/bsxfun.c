/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: bsxfun.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "bsxfun.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_types.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *a
 *                const emxArray_real_T *b
 *                emxArray_real_T *c
 * Return Type  : void
 */
void bsxfun(const emxArray_real_T *a, const emxArray_real_T *b,
            emxArray_real_T *c)
{
  int acoef;
  int bcoef;
  int csz_idx_0;
  int i;
  acoef = b->size[0];
  bcoef = a->size[0];
  if (acoef < bcoef) {
    bcoef = acoef;
  }
  if (b->size[0] == 1) {
    csz_idx_0 = a->size[0];
  } else if (a->size[0] == 1) {
    csz_idx_0 = b->size[0];
  } else if (a->size[0] == b->size[0]) {
    csz_idx_0 = a->size[0];
  } else {
    csz_idx_0 = bcoef;
  }
  i = c->size[0];
  acoef = b->size[0];
  bcoef = a->size[0];
  if (acoef < bcoef) {
    bcoef = acoef;
  }
  if (b->size[0] == 1) {
    c->size[0] = a->size[0];
  } else if (a->size[0] == 1) {
    c->size[0] = b->size[0];
  } else if (a->size[0] == b->size[0]) {
    c->size[0] = a->size[0];
  } else {
    c->size[0] = bcoef;
  }
  emxEnsureCapacity_real_T(c, i);
  if (csz_idx_0 != 0) {
    acoef = (a->size[0] != 1);
    bcoef = (b->size[0] != 1);
    i = csz_idx_0 - 1;
    for (csz_idx_0 = 0; csz_idx_0 <= i; csz_idx_0++) {
      c->data[csz_idx_0] =
          a->data[acoef * csz_idx_0] * b->data[bcoef * csz_idx_0];
    }
  }
}

/*
 * File trailer for bsxfun.c
 *
 * [EOF]
 */
