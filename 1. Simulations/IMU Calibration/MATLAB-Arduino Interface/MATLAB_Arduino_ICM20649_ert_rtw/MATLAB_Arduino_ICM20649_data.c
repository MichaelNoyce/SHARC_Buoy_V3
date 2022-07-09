/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MATLAB_Arduino_ICM20649_data.c
 *
 * Code generated for Simulink model 'MATLAB_Arduino_ICM20649'.
 *
 * Model version                  : 1.24
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat Jul  9 17:41:55 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MATLAB_Arduino_ICM20649.h"
#include "MATLAB_Arduino_ICM20649_private.h"

/* Block parameters (default storage) */
P_MATLAB_Arduino_ICM20649_T MATLAB_Arduino_ICM20649_P = {
  /* Expression: [1 0 0 0 0 0 0 0]
   * Referenced by: '<S1>/Constant'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /* Expression: 0.01
   * Referenced by: '<Root>/X Acceleration '
   */
  0.01,

  /* Expression: 0.01
   * Referenced by: '<Root>/X Gyroscope'
   */
  0.01,

  /* Expression: 0.01
   * Referenced by: '<Root>/Y Acceleration'
   */
  0.01,

  /* Expression: 0.01
   * Referenced by: '<Root>/Y Gyroscope'
   */
  0.01,

  /* Expression: 0.01
   * Referenced by: '<Root>/Z Acceleration '
   */
  0.01,

  /* Expression: 0.01
   * Referenced by: '<Root>/Z Gyroscope'
   */
  0.01,

  /* Expression: -92.2236
   * Referenced by: '<Root>/Constant2'
   */
  -92.2236,

  /* Expression: (1/1686.46)
   * Referenced by: '<Root>/Gain'
   */
  0.00059295803043060615,

  /* Expression: +103.519
   * Referenced by: '<Root>/Constant'
   */
  103.519,

  /* Expression: (1/1669.316)
   * Referenced by: '<Root>/Gain2'
   */
  0.00059904775369073321,

  /* Expression: +42.729
   * Referenced by: '<Root>/Constant3'
   */
  42.729,

  /* Expression: (1/1668.9)
   * Referenced by: '<Root>/Gain1'
   */
  0.00059919707591826949,

  /* Expression: -20.5908
   * Referenced by: '<Root>/Constant6'
   */
  -20.5908,

  /* Expression: 1/145.342
   * Referenced by: '<Root>/Gain3'
   */
  0.0068803236504245153,

  /* Expression: +74.9
   * Referenced by: '<Root>/Constant4'
   */
  74.9,

  /* Expression: 1/131.226
   * Referenced by: '<Root>/Gain5'
   */
  0.0076204410711291967,

  /* Expression: -190.96
   * Referenced by: '<Root>/Constant5'
   */
  -190.96,

  /* Expression: 1/137.732
   * Referenced by: '<Root>/Gain4'
   */
  0.0072604768681206978,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<Root>/Discrete-Time Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<Root>/Discrete-Time Integrator'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Delay'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant1'
   */
  0.0,

  /* Computed Parameter: Gain7_Gain
   * Referenced by: '<Root>/Gain7'
   */
  32018,

  /* Computed Parameter: Gain6_Gain
   * Referenced by: '<Root>/Gain6'
   */
  20106
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
