/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MATLAB_Arduino_ICM20649_types.h
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

#ifndef RTW_HEADER_MATLAB_Arduino_ICM20649_types_h_
#define RTW_HEADER_MATLAB_Arduino_ICM20649_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Model Code Variants */

/* Custom Type definition for MATLABSystem: '<Root>/Z Gyroscope' */
#include "MW_SVD.h"
#ifndef struct_tag_jbIFaTBEZATkkvPSmnoPa
#define struct_tag_jbIFaTBEZATkkvPSmnoPa

struct tag_jbIFaTBEZATkkvPSmnoPa
{
  MW_Handle_Type MW_I2C_HANDLE;
};

#endif                                 /* struct_tag_jbIFaTBEZATkkvPSmnoPa */

#ifndef typedef_c_arduinodriver_ArduinoI2C_MA_T
#define typedef_c_arduinodriver_ArduinoI2C_MA_T

typedef struct tag_jbIFaTBEZATkkvPSmnoPa c_arduinodriver_ArduinoI2C_MA_T;

#endif                             /* typedef_c_arduinodriver_ArduinoI2C_MA_T */

#ifndef struct_tag_3coDYKg8JwMUxQ16KBcXBE
#define struct_tag_3coDYKg8JwMUxQ16KBcXBE

struct tag_3coDYKg8JwMUxQ16KBcXBE
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoI2C_MA_T I2CDriverObj;
  uint32_T BusSpeed;
  real_T DefaultMaximumBusSpeedInHz;
};

#endif                                 /* struct_tag_3coDYKg8JwMUxQ16KBcXBE */

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_3coDYKg8JwMUxQ16KBcXBE codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

#ifndef struct_tag_chY474Xs2EmAHQmJ9UhmtD
#define struct_tag_chY474Xs2EmAHQmJ9UhmtD

struct tag_chY474Xs2EmAHQmJ9UhmtD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoI2C_MA_T I2CDriverObj;
  uint32_T BusSpeed;
  real_T DefaultMaximumBusSpeedInHz;
  real_T SampleTime;
};

#endif                                 /* struct_tag_chY474Xs2EmAHQmJ9UhmtD */

#ifndef typedef_codertarget_arduinobase_int_o_T
#define typedef_codertarget_arduinobase_int_o_T

typedef struct tag_chY474Xs2EmAHQmJ9UhmtD codertarget_arduinobase_int_o_T;

#endif                             /* typedef_codertarget_arduinobase_int_o_T */

/* Parameters (default storage) */
typedef struct P_MATLAB_Arduino_ICM20649_T_ P_MATLAB_Arduino_ICM20649_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_MATLAB_Arduino_ICM206_T RT_MODEL_MATLAB_Arduino_ICM20_T;

#endif                         /* RTW_HEADER_MATLAB_Arduino_ICM20649_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
