/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MATLAB_Arduino_ICM20689.h
 *
 * Code generated for Simulink model 'MATLAB_Arduino_ICM20689'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Jun 16 15:34:43 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MATLAB_Arduino_ICM20689_h_
#define RTW_HEADER_MATLAB_Arduino_ICM20689_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef MATLAB_Arduino_ICM20689_COMMON_INCLUDES_
#define MATLAB_Arduino_ICM20689_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "dt_info.h"
#include "ext_work.h"
#include "MW_I2C.h"
#endif                            /* MATLAB_Arduino_ICM20689_COMMON_INCLUDES_ */

#include "MATLAB_Arduino_ICM20689_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "MW_target_hardware_resources.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T ZAcc;                         /* '<Root>/Gain' */
  real_T XAcc;                         /* '<Root>/Gain2' */
  real_T Gain1;                        /* '<Root>/Gain1' */
  real_T Gain3;                        /* '<Root>/Gain3' */
  real_T Gain5;                        /* '<Root>/Gain5' */
  real_T Gain4;                        /* '<Root>/Gain4' */
  real_T DiscreteTimeIntegrator;       /* '<Root>/Discrete-Time Integrator' */
  int32_T ZAcc_n[3];                   /* '<Root>/Gain6' */
  int32_T ZAcc_d[3];                   /* '<Root>/Gain7' */
  int16_T Z_Gyro;                      /* '<Root>/Z Gyroscope' */
  int16_T Z_Accel;                     /* '<Root>/Z Acceleration ' */
  int16_T Y_Gyro;                      /* '<Root>/Y Gyroscope' */
  int16_T Y_Accel;                     /* '<Root>/Y Acceleration' */
  int16_T X_Gyro;                      /* '<Root>/X Gyroscope' */
  int16_T X_Accel;                     /* '<Root>/X Acceleration ' */
  uint8_T ZGyroscope_o2;               /* '<Root>/Z Gyroscope' */
  uint8_T ZAcceleration_o2;            /* '<Root>/Z Acceleration ' */
  uint8_T YGyroscope_o2;               /* '<Root>/Y Gyroscope' */
  uint8_T YAcceleration_o2;            /* '<Root>/Y Acceleration' */
  uint8_T XGyroscope_o2;               /* '<Root>/X Gyroscope' */
  uint8_T XAcceleration_o2;            /* '<Root>/X Acceleration ' */
} B_MATLAB_Arduino_ICM20689_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_f_T obj; /* '<Root>/Z Gyroscope' */
  codertarget_arduinobase_int_f_T obj_e;/* '<Root>/Z Acceleration ' */
  codertarget_arduinobase_int_f_T obj_ej;/* '<Root>/Y Gyroscope' */
  codertarget_arduinobase_int_f_T obj_h;/* '<Root>/Y Acceleration' */
  codertarget_arduinobase_int_f_T obj_n;/* '<Root>/X Gyroscope' */
  codertarget_arduinobase_int_f_T obj_p;/* '<Root>/X Acceleration ' */
  codertarget_arduinobase_inter_T obj_l;/* '<S1>/Power Managment Register 1 ' */
  codertarget_arduinobase_inter_T obj_k;/* '<S1>/Power Management Register 2' */
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real_T Delay_DSTATE;                 /* '<Root>/Delay' */
  struct {
    void *LoggedData;
  } UncalibratedOutput_PWORK;          /* '<Root>/Uncalibrated Output ' */

  struct {
    void *LoggedData;
  } CalibratedAccOutput_PWORK;         /* '<Root>/Calibrated Acc Output ' */

  struct {
    void *LoggedData;
  } UncalibratedOrientationOutput_P;
                                 /* '<Root>/Uncalibrated Orientation Output ' */

  struct {
    void *LoggedData;
  } CalibratedOrientationOutput_PWO;/* '<Root>/Calibrated Orientation Output' */

  struct {
    void *LoggedData;
  } CalibratedYPosition_PWORK;         /* '<Root>/Calibrated Y Position' */

  int8_T EnabledSubsystem_SubsysRanBC; /* '<Root>/Enabled Subsystem' */
} DW_MATLAB_Arduino_ICM20689_T;

/* Parameters (default storage) */
struct P_MATLAB_Arduino_ICM20689_T_ {
  real_T Constant_Value[8];            /* Expression: [0 0 0 0 0 0 0 1]
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Constant1_Value[8];           /* Expression: [0 0 0 0 0 0 0 0]
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T XAcceleration_SampleTime;     /* Expression: 0.01
                                        * Referenced by: '<Root>/X Acceleration '
                                        */
  real_T XGyroscope_SampleTime;        /* Expression: 0.01
                                        * Referenced by: '<Root>/X Gyroscope'
                                        */
  real_T YAcceleration_SampleTime;     /* Expression: 0.01
                                        * Referenced by: '<Root>/Y Acceleration'
                                        */
  real_T YGyroscope_SampleTime;        /* Expression: 0.01
                                        * Referenced by: '<Root>/Y Gyroscope'
                                        */
  real_T ZAcceleration_SampleTime;     /* Expression: 0.01
                                        * Referenced by: '<Root>/Z Acceleration '
                                        */
  real_T ZGyroscope_SampleTime;        /* Expression: 0.01
                                        * Referenced by: '<Root>/Z Gyroscope'
                                        */
  real_T Constant2_Value;              /* Expression: -92.2236
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Gain_Gain;                    /* Expression: (1/1686.46)
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Constant_Value_d;             /* Expression: +103.519
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Gain2_Gain;                   /* Expression: (1/1669.316)
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T Constant3_Value;              /* Expression: +42.729
                                        * Referenced by: '<Root>/Constant3'
                                        */
  real_T Gain1_Gain;                   /* Expression: (1/1668.9)
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Constant6_Value;              /* Expression: -20.5908
                                        * Referenced by: '<Root>/Constant6'
                                        */
  real_T Gain3_Gain;                   /* Expression: 1/145.342
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real_T Constant4_Value;              /* Expression: +74.9
                                        * Referenced by: '<Root>/Constant4'
                                        */
  real_T Gain5_Gain;                   /* Expression: 1/131.226
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real_T Constant5_Value;              /* Expression: -190.96
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real_T Gain4_Gain;                   /* Expression: 1/137.732
                                        * Referenced by: '<Root>/Gain4'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<Root>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 1
                                        * Referenced by: '<Root>/Delay'
                                        */
  real_T Constant1_Value_f;            /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  int16_T Gain7_Gain;                  /* Computed Parameter: Gain7_Gain
                                        * Referenced by: '<Root>/Gain7'
                                        */
  int16_T Gain6_Gain;                  /* Computed Parameter: Gain6_Gain
                                        * Referenced by: '<Root>/Gain6'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_MATLAB_Arduino_ICM206_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_MATLAB_Arduino_ICM20689_T MATLAB_Arduino_ICM20689_P;

/* Block signals (default storage) */
extern B_MATLAB_Arduino_ICM20689_T MATLAB_Arduino_ICM20689_B;

/* Block states (default storage) */
extern DW_MATLAB_Arduino_ICM20689_T MATLAB_Arduino_ICM20689_DW;

/* Model entry point functions */
extern void MATLAB_Arduino_ICM20689_initialize(void);
extern void MATLAB_Arduino_ICM20689_step(void);
extern void MATLAB_Arduino_ICM20689_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MATLAB_Arduino_ICM20_T *const MATLAB_Arduino_ICM20689_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MATLAB_Arduino_ICM20689'
 * '<S1>'   : 'MATLAB_Arduino_ICM20689/Enabled Subsystem'
 */
#endif                               /* RTW_HEADER_MATLAB_Arduino_ICM20689_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
