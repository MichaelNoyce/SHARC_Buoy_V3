/*
 * MATLAB_Arduino_ICM20689_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "MATLAB_Arduino_ICM20689".
 *
 * Model version              : 1.21
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu Jun 16 15:34:43 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(void*),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int16_T),
  sizeof(int32_T),
  sizeof(int16_T),
  sizeof(int32_T),
  sizeof(codertarget_arduinobase_inter_T),
  sizeof(codertarget_arduinobase_int_f_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "int16_T",
  "int32_T",
  "int16_T",
  "int32_T",
  "codertarget_arduinobase_inter_T",
  "codertarget_arduinobase_int_f_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&MATLAB_Arduino_ICM20689_B.ZAcc), 0, 0, 7 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_B.ZAcc_n[0]), 15, 0, 6 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_B.Z_Gyro), 4, 0, 6 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_B.ZGyroscope_o2), 3, 0, 6 }
  ,

  { (char_T *)(&MATLAB_Arduino_ICM20689_DW.obj), 19, 0, 6 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_DW.obj_l), 18, 0, 2 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_DW.DiscreteTimeIntegrator_DSTATE), 0, 0,
    2 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_DW.UncalibratedOutput_PWORK.LoggedData),
    11, 0, 5 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC), 2, 0,
    1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  9U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&MATLAB_Arduino_ICM20689_P.Constant_Value[0]), 0, 0, 38 },

  { (char_T *)(&MATLAB_Arduino_ICM20689_P.Gain7_Gain), 16, 0, 2 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  2U,
  rtPTransitions
};

/* [EOF] MATLAB_Arduino_ICM20689_dt.h */
