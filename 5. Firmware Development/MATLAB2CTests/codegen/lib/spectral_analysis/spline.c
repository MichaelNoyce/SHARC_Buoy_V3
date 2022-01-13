/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: spline.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 06-Jan-2022 15:16:04
 */

/* Include Files */
#include "spline.h"
#include "rt_nonfinite.h"
#include "spectral_analysis_emxutil.h"
#include "spectral_analysis_types.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *output_breaks
 *                emxArray_real_T *output_coefs
 * Return Type  : void
 */
void spline(const emxArray_real_T *x, const emxArray_real_T *y,
            emxArray_real_T *output_breaks, emxArray_real_T *output_coefs)
{
  emxArray_real_T *dvdf;
  emxArray_real_T *dx;
  emxArray_real_T *md;
  emxArray_real_T *pp_coefs;
  emxArray_real_T *s;
  double c_data[4];
  double pp1_coefs[4];
  double dnnm2;
  double dzzdx;
  double r;
  double szdvdf_idx_1;
  int dvdf_tmp;
  int i;
  int nxm1;
  int szs_idx_1;
  int yoffset;
  boolean_T has_endslopes;
  has_endslopes = (y->size[0] == x->size[1] + 2);
  emxInit_real_T(&s, 2);
  emxInit_real_T(&dvdf, 2);
  emxInit_real_T(&dx, 2);
  emxInit_real_T(&md, 2);
  emxInit_real_T(&pp_coefs, 2);
  if ((x->size[1] <= 2) || ((x->size[1] <= 3) && (!has_endslopes))) {
    has_endslopes = (y->size[0] == x->size[1] + 2);
    if (x->size[1] <= 2) {
      if (has_endslopes) {
        dvdf_tmp = 4;
      } else {
        dvdf_tmp = 2;
      }
      if (has_endslopes) {
        if (0 <= x->size[1] - 2) {
          dnnm2 = x->data[1] - x->data[0];
          szdvdf_idx_1 = (y->data[2] - y->data[1]) / dnnm2;
          dzzdx = (szdvdf_idx_1 - y->data[0]) / dnnm2;
          szdvdf_idx_1 = (y->data[y->size[0] - 1] - szdvdf_idx_1) / dnnm2;
          pp1_coefs[0] = (szdvdf_idx_1 - dzzdx) / dnnm2;
          pp1_coefs[1] = 2.0 * dzzdx - szdvdf_idx_1;
          pp1_coefs[2] = y->data[0];
          pp1_coefs[3] = y->data[1];
        }
        if (0 <= dvdf_tmp - 1) {
          memcpy(&c_data[0], &pp1_coefs[0], dvdf_tmp * sizeof(double));
        }
      } else {
        c_data[0] = (y->data[1] - y->data[0]) / (x->data[1] - x->data[0]);
        c_data[1] = y->data[0];
      }
      i = output_breaks->size[0] * output_breaks->size[1];
      output_breaks->size[0] = 1;
      output_breaks->size[1] = x->size[1];
      emxEnsureCapacity_real_T(output_breaks, i);
      szs_idx_1 = x->size[1];
      for (i = 0; i < szs_idx_1; i++) {
        output_breaks->data[i] = x->data[i];
      }
    } else {
      dvdf_tmp = 3;
      szdvdf_idx_1 = x->data[1] - x->data[0];
      dnnm2 = (y->data[1] - y->data[0]) / szdvdf_idx_1;
      c_data[0] =
          ((y->data[2] - y->data[1]) / (x->data[2] - x->data[1]) - dnnm2) /
          (x->data[2] - x->data[0]);
      c_data[1] = dnnm2 - c_data[0] * szdvdf_idx_1;
      c_data[2] = y->data[0];
      i = output_breaks->size[0] * output_breaks->size[1];
      output_breaks->size[0] = 1;
      output_breaks->size[1] = 2;
      emxEnsureCapacity_real_T(output_breaks, i);
      output_breaks->data[0] = x->data[0];
      output_breaks->data[1] = x->data[2];
    }
    i = output_coefs->size[0] * output_coefs->size[1];
    output_coefs->size[0] = 1;
    output_coefs->size[1] = dvdf_tmp;
    emxEnsureCapacity_real_T(output_coefs, i);
    for (i = 0; i < dvdf_tmp; i++) {
      output_coefs->data[i] = c_data[i];
    }
  } else {
    nxm1 = x->size[1] - 1;
    if (has_endslopes) {
      szdvdf_idx_1 = (double)(unsigned int)y->size[0] - 3.0;
      szs_idx_1 = y->size[0] - 2;
      yoffset = 1;
    } else {
      szdvdf_idx_1 = (double)(unsigned int)y->size[0] - 1.0;
      szs_idx_1 = y->size[0];
      yoffset = 0;
    }
    i = s->size[0] * s->size[1];
    s->size[0] = 1;
    s->size[1] = szs_idx_1;
    emxEnsureCapacity_real_T(s, i);
    i = dvdf->size[0] * dvdf->size[1];
    dvdf->size[0] = 1;
    dvdf->size[1] = (int)szdvdf_idx_1;
    emxEnsureCapacity_real_T(dvdf, i);
    i = dx->size[0] * dx->size[1];
    dx->size[0] = 1;
    dx->size[1] = x->size[1] - 1;
    emxEnsureCapacity_real_T(dx, i);
    for (szs_idx_1 = 0; szs_idx_1 < nxm1; szs_idx_1++) {
      szdvdf_idx_1 = x->data[szs_idx_1 + 1] - x->data[szs_idx_1];
      dx->data[szs_idx_1] = szdvdf_idx_1;
      dvdf_tmp = yoffset + szs_idx_1;
      dvdf->data[szs_idx_1] =
          (y->data[dvdf_tmp + 1] - y->data[dvdf_tmp]) / szdvdf_idx_1;
    }
    for (szs_idx_1 = 2; szs_idx_1 <= nxm1; szs_idx_1++) {
      s->data[szs_idx_1 - 1] =
          3.0 * (dx->data[szs_idx_1 - 1] * dvdf->data[szs_idx_1 - 2] +
                 dx->data[szs_idx_1 - 2] * dvdf->data[szs_idx_1 - 1]);
    }
    if (has_endslopes) {
      szdvdf_idx_1 = 0.0;
      dnnm2 = 0.0;
      s->data[0] = y->data[0] * dx->data[1];
      s->data[x->size[1] - 1] =
          dx->data[x->size[1] - 3] * y->data[x->size[1] + 1];
    } else {
      szdvdf_idx_1 = x->data[2] - x->data[0];
      dnnm2 = x->data[x->size[1] - 1] - x->data[x->size[1] - 3];
      s->data[0] =
          ((dx->data[0] + 2.0 * szdvdf_idx_1) * dx->data[1] * dvdf->data[0] +
           dx->data[0] * dx->data[0] * dvdf->data[1]) /
          szdvdf_idx_1;
      s->data[x->size[1] - 1] =
          ((dx->data[x->size[1] - 2] + 2.0 * dnnm2) * dx->data[x->size[1] - 3] *
               dvdf->data[x->size[1] - 2] +
           dx->data[x->size[1] - 2] * dx->data[x->size[1] - 2] *
               dvdf->data[x->size[1] - 3]) /
          dnnm2;
    }
    i = md->size[0] * md->size[1];
    md->size[0] = 1;
    md->size[1] = x->size[1];
    emxEnsureCapacity_real_T(md, i);
    md->data[0] = dx->data[1];
    md->data[x->size[1] - 1] = dx->data[x->size[1] - 3];
    for (szs_idx_1 = 2; szs_idx_1 <= nxm1; szs_idx_1++) {
      md->data[szs_idx_1 - 1] =
          2.0 * (dx->data[szs_idx_1 - 1] + dx->data[szs_idx_1 - 2]);
    }
    r = dx->data[1] / md->data[0];
    md->data[1] -= r * szdvdf_idx_1;
    s->data[1] -= r * s->data[0];
    for (szs_idx_1 = 3; szs_idx_1 <= nxm1; szs_idx_1++) {
      r = dx->data[szs_idx_1 - 1] / md->data[szs_idx_1 - 2];
      md->data[szs_idx_1 - 1] -= r * dx->data[szs_idx_1 - 3];
      s->data[szs_idx_1 - 1] -= r * s->data[szs_idx_1 - 2];
    }
    r = dnnm2 / md->data[x->size[1] - 2];
    md->data[x->size[1] - 1] -= r * dx->data[x->size[1] - 3];
    s->data[x->size[1] - 1] -= r * s->data[x->size[1] - 2];
    s->data[x->size[1] - 1] /= md->data[x->size[1] - 1];
    for (szs_idx_1 = nxm1; szs_idx_1 >= 2; szs_idx_1--) {
      s->data[szs_idx_1 - 1] = (s->data[szs_idx_1 - 1] -
                                dx->data[szs_idx_1 - 2] * s->data[szs_idx_1]) /
                               md->data[szs_idx_1 - 1];
    }
    s->data[0] = (s->data[0] - szdvdf_idx_1 * s->data[1]) / md->data[0];
    nxm1 = x->size[1];
    szs_idx_1 = s->size[1] - 1;
    i = pp_coefs->size[0] * pp_coefs->size[1];
    pp_coefs->size[0] = s->size[1] - 1;
    pp_coefs->size[1] = 4;
    emxEnsureCapacity_real_T(pp_coefs, i);
    for (dvdf_tmp = 0; dvdf_tmp <= nxm1 - 2; dvdf_tmp++) {
      szdvdf_idx_1 = dvdf->data[dvdf_tmp];
      dnnm2 = s->data[dvdf_tmp];
      r = dx->data[dvdf_tmp];
      dzzdx = (szdvdf_idx_1 - dnnm2) / r;
      szdvdf_idx_1 = (s->data[dvdf_tmp + 1] - szdvdf_idx_1) / r;
      pp_coefs->data[dvdf_tmp] = (szdvdf_idx_1 - dzzdx) / r;
      pp_coefs->data[szs_idx_1 + dvdf_tmp] = 2.0 * dzzdx - szdvdf_idx_1;
      pp_coefs->data[(szs_idx_1 << 1) + dvdf_tmp] = dnnm2;
      pp_coefs->data[3 * szs_idx_1 + dvdf_tmp] = y->data[yoffset + dvdf_tmp];
    }
    i = output_breaks->size[0] * output_breaks->size[1];
    output_breaks->size[0] = 1;
    output_breaks->size[1] = x->size[1];
    emxEnsureCapacity_real_T(output_breaks, i);
    szs_idx_1 = x->size[1];
    for (i = 0; i < szs_idx_1; i++) {
      output_breaks->data[i] = x->data[i];
    }
    i = output_coefs->size[0] * output_coefs->size[1];
    output_coefs->size[0] = pp_coefs->size[0];
    output_coefs->size[1] = 4;
    emxEnsureCapacity_real_T(output_coefs, i);
    szs_idx_1 = pp_coefs->size[0] * 4;
    for (i = 0; i < szs_idx_1; i++) {
      output_coefs->data[i] = pp_coefs->data[i];
    }
  }
  emxFree_real_T(&pp_coefs);
  emxFree_real_T(&md);
  emxFree_real_T(&dx);
  emxFree_real_T(&dvdf);
  emxFree_real_T(&s);
}

/*
 * File trailer for spline.c
 *
 * [EOF]
 */
