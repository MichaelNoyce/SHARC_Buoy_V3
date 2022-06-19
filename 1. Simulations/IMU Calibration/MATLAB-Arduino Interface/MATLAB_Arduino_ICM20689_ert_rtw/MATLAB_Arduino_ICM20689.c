/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MATLAB_Arduino_ICM20689.c
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

#include "MATLAB_Arduino_ICM20689.h"
#include "MATLAB_Arduino_ICM20689_private.h"
#include "MATLAB_Arduino_ICM20689_dt.h"

/* Block signals (default storage) */
B_MATLAB_Arduino_ICM20689_T MATLAB_Arduino_ICM20689_B;

/* Block states (default storage) */
DW_MATLAB_Arduino_ICM20689_T MATLAB_Arduino_ICM20689_DW;

/* Real-time model */
static RT_MODEL_MATLAB_Arduino_ICM20_T MATLAB_Arduino_ICM20689_M_;
RT_MODEL_MATLAB_Arduino_ICM20_T *const MATLAB_Arduino_ICM20689_M =
  &MATLAB_Arduino_ICM20689_M_;

/* Model step function */
void MATLAB_Arduino_ICM20689_step(void)
{
  real_T tmp;
  int16_T i;
  uint8_T b_SwappedDataBytes[9];
  uint8_T b_x[2];
  uint8_T output_raw[2];
  uint8_T Data;

  /* Reset subsysRan breadcrumbs */
  srClearBC(MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC);

  /* MATLABSystem: '<Root>/X Acceleration ' */
  if (MATLAB_Arduino_ICM20689_DW.obj_p.SampleTime !=
      MATLAB_Arduino_ICM20689_P.XAcceleration_SampleTime) {
    MATLAB_Arduino_ICM20689_DW.obj_p.SampleTime =
      MATLAB_Arduino_ICM20689_P.XAcceleration_SampleTime;
  }

  Data = 59U;
  MATLAB_Arduino_ICM20689_B.XAcceleration_o2 = MW_I2C_MasterWrite
    (MATLAB_Arduino_ICM20689_DW.obj_p.I2CDriverObj.MW_I2C_HANDLE, 104UL, &Data,
     1UL, true, false);
  if (0 == MATLAB_Arduino_ICM20689_B.XAcceleration_o2) {
    MW_I2C_MasterRead
      (MATLAB_Arduino_ICM20689_DW.obj_p.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &output_raw[0], 2UL, false, true);
    memcpy((void *)&i, (void *)&output_raw[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    memcpy((void *)&output_raw[0], (void *)&i, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = output_raw[1];
    b_x[1] = output_raw[0];
    memcpy((void *)&MATLAB_Arduino_ICM20689_B.X_Accel, (void *)&b_x[0],
           (uint16_T)((size_t)1 * sizeof(int16_T)));
  } else {
    /* MATLABSystem: '<Root>/X Acceleration ' */
    MATLAB_Arduino_ICM20689_B.X_Accel = 0;
  }

  /* End of MATLABSystem: '<Root>/X Acceleration ' */

  /* MATLABSystem: '<Root>/Y Acceleration' */
  if (MATLAB_Arduino_ICM20689_DW.obj_h.SampleTime !=
      MATLAB_Arduino_ICM20689_P.YAcceleration_SampleTime) {
    MATLAB_Arduino_ICM20689_DW.obj_h.SampleTime =
      MATLAB_Arduino_ICM20689_P.YAcceleration_SampleTime;
  }

  Data = 61U;
  MATLAB_Arduino_ICM20689_B.YAcceleration_o2 = MW_I2C_MasterWrite
    (MATLAB_Arduino_ICM20689_DW.obj_h.I2CDriverObj.MW_I2C_HANDLE, 104UL, &Data,
     1UL, true, false);
  if (0 == MATLAB_Arduino_ICM20689_B.YAcceleration_o2) {
    MW_I2C_MasterRead
      (MATLAB_Arduino_ICM20689_DW.obj_h.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &output_raw[0], 2UL, false, true);
    memcpy((void *)&i, (void *)&output_raw[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    memcpy((void *)&output_raw[0], (void *)&i, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = output_raw[1];
    b_x[1] = output_raw[0];
    memcpy((void *)&MATLAB_Arduino_ICM20689_B.Y_Accel, (void *)&b_x[0],
           (uint16_T)((size_t)1 * sizeof(int16_T)));
  } else {
    /* MATLABSystem: '<Root>/Y Acceleration' */
    MATLAB_Arduino_ICM20689_B.Y_Accel = 0;
  }

  /* End of MATLABSystem: '<Root>/Y Acceleration' */

  /* MATLABSystem: '<Root>/Z Acceleration ' */
  if (MATLAB_Arduino_ICM20689_DW.obj_e.SampleTime !=
      MATLAB_Arduino_ICM20689_P.ZAcceleration_SampleTime) {
    MATLAB_Arduino_ICM20689_DW.obj_e.SampleTime =
      MATLAB_Arduino_ICM20689_P.ZAcceleration_SampleTime;
  }

  Data = 63U;
  MATLAB_Arduino_ICM20689_B.ZAcceleration_o2 = MW_I2C_MasterWrite
    (MATLAB_Arduino_ICM20689_DW.obj_e.I2CDriverObj.MW_I2C_HANDLE, 104UL, &Data,
     1UL, true, false);
  if (0 == MATLAB_Arduino_ICM20689_B.ZAcceleration_o2) {
    MW_I2C_MasterRead
      (MATLAB_Arduino_ICM20689_DW.obj_e.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &output_raw[0], 2UL, false, true);
    memcpy((void *)&i, (void *)&output_raw[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    memcpy((void *)&output_raw[0], (void *)&i, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = output_raw[1];
    b_x[1] = output_raw[0];
    memcpy((void *)&MATLAB_Arduino_ICM20689_B.Z_Accel, (void *)&b_x[0],
           (uint16_T)((size_t)1 * sizeof(int16_T)));
  } else {
    /* MATLABSystem: '<Root>/Z Acceleration ' */
    MATLAB_Arduino_ICM20689_B.Z_Accel = 0;
  }

  /* End of MATLABSystem: '<Root>/Z Acceleration ' */

  /* Gain: '<Root>/Gain6' incorporates:
   *  SignalConversion generated from: '<Root>/Gain6'
   */
  MATLAB_Arduino_ICM20689_B.ZAcc_n[0] = (int32_T)
    MATLAB_Arduino_ICM20689_P.Gain6_Gain * MATLAB_Arduino_ICM20689_B.X_Accel;
  MATLAB_Arduino_ICM20689_B.ZAcc_n[1] = (int32_T)
    MATLAB_Arduino_ICM20689_P.Gain6_Gain * MATLAB_Arduino_ICM20689_B.Y_Accel;
  MATLAB_Arduino_ICM20689_B.ZAcc_n[2] = (int32_T)
    MATLAB_Arduino_ICM20689_P.Gain6_Gain * MATLAB_Arduino_ICM20689_B.Z_Accel;

  /* Gain: '<Root>/Gain' incorporates:
   *  Constant: '<Root>/Constant2'
   *  Sum: '<Root>/Add1'
   */
  MATLAB_Arduino_ICM20689_B.ZAcc = (MATLAB_Arduino_ICM20689_P.Constant2_Value +
    (real_T)MATLAB_Arduino_ICM20689_B.Z_Accel) *
    MATLAB_Arduino_ICM20689_P.Gain_Gain;

  /* Gain: '<Root>/Gain2' incorporates:
   *  Constant: '<Root>/Constant'
   *  Sum: '<Root>/Add'
   */
  MATLAB_Arduino_ICM20689_B.XAcc = (MATLAB_Arduino_ICM20689_P.Constant_Value_d +
    (real_T)MATLAB_Arduino_ICM20689_B.X_Accel) *
    MATLAB_Arduino_ICM20689_P.Gain2_Gain;

  /* Gain: '<Root>/Gain1' incorporates:
   *  Constant: '<Root>/Constant3'
   *  Sum: '<Root>/Add2'
   */
  MATLAB_Arduino_ICM20689_B.Gain1 = (MATLAB_Arduino_ICM20689_P.Constant3_Value +
    (real_T)MATLAB_Arduino_ICM20689_B.Y_Accel) *
    MATLAB_Arduino_ICM20689_P.Gain1_Gain;

  /* MATLABSystem: '<Root>/X Gyroscope' */
  if (MATLAB_Arduino_ICM20689_DW.obj_n.SampleTime !=
      MATLAB_Arduino_ICM20689_P.XGyroscope_SampleTime) {
    MATLAB_Arduino_ICM20689_DW.obj_n.SampleTime =
      MATLAB_Arduino_ICM20689_P.XGyroscope_SampleTime;
  }

  Data = 67U;
  MATLAB_Arduino_ICM20689_B.XGyroscope_o2 = MW_I2C_MasterWrite
    (MATLAB_Arduino_ICM20689_DW.obj_n.I2CDriverObj.MW_I2C_HANDLE, 104UL, &Data,
     1UL, true, false);
  if (0 == MATLAB_Arduino_ICM20689_B.XGyroscope_o2) {
    MW_I2C_MasterRead
      (MATLAB_Arduino_ICM20689_DW.obj_n.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &output_raw[0], 2UL, false, true);
    memcpy((void *)&i, (void *)&output_raw[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    memcpy((void *)&output_raw[0], (void *)&i, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = output_raw[1];
    b_x[1] = output_raw[0];
    memcpy((void *)&MATLAB_Arduino_ICM20689_B.X_Gyro, (void *)&b_x[0], (uint16_T)
           ((size_t)1 * sizeof(int16_T)));
  } else {
    /* MATLABSystem: '<Root>/X Gyroscope' */
    MATLAB_Arduino_ICM20689_B.X_Gyro = 0;
  }

  /* End of MATLABSystem: '<Root>/X Gyroscope' */

  /* MATLABSystem: '<Root>/Y Gyroscope' */
  if (MATLAB_Arduino_ICM20689_DW.obj_ej.SampleTime !=
      MATLAB_Arduino_ICM20689_P.YGyroscope_SampleTime) {
    MATLAB_Arduino_ICM20689_DW.obj_ej.SampleTime =
      MATLAB_Arduino_ICM20689_P.YGyroscope_SampleTime;
  }

  Data = 69U;
  MATLAB_Arduino_ICM20689_B.YGyroscope_o2 = MW_I2C_MasterWrite
    (MATLAB_Arduino_ICM20689_DW.obj_ej.I2CDriverObj.MW_I2C_HANDLE, 104UL, &Data,
     1UL, true, false);
  if (0 == MATLAB_Arduino_ICM20689_B.YGyroscope_o2) {
    MW_I2C_MasterRead
      (MATLAB_Arduino_ICM20689_DW.obj_ej.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &output_raw[0], 2UL, false, true);
    memcpy((void *)&i, (void *)&output_raw[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    memcpy((void *)&output_raw[0], (void *)&i, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = output_raw[1];
    b_x[1] = output_raw[0];
    memcpy((void *)&MATLAB_Arduino_ICM20689_B.Y_Gyro, (void *)&b_x[0], (uint16_T)
           ((size_t)1 * sizeof(int16_T)));
  } else {
    /* MATLABSystem: '<Root>/Y Gyroscope' */
    MATLAB_Arduino_ICM20689_B.Y_Gyro = 0;
  }

  /* End of MATLABSystem: '<Root>/Y Gyroscope' */

  /* MATLABSystem: '<Root>/Z Gyroscope' */
  if (MATLAB_Arduino_ICM20689_DW.obj.SampleTime !=
      MATLAB_Arduino_ICM20689_P.ZGyroscope_SampleTime) {
    MATLAB_Arduino_ICM20689_DW.obj.SampleTime =
      MATLAB_Arduino_ICM20689_P.ZGyroscope_SampleTime;
  }

  Data = 71U;
  MATLAB_Arduino_ICM20689_B.ZGyroscope_o2 = MW_I2C_MasterWrite
    (MATLAB_Arduino_ICM20689_DW.obj.I2CDriverObj.MW_I2C_HANDLE, 104UL, &Data,
     1UL, true, false);
  if (0 == MATLAB_Arduino_ICM20689_B.ZGyroscope_o2) {
    MW_I2C_MasterRead(MATLAB_Arduino_ICM20689_DW.obj.I2CDriverObj.MW_I2C_HANDLE,
                      104UL, &output_raw[0], 2UL, false, true);
    memcpy((void *)&i, (void *)&output_raw[0], (uint16_T)((size_t)1 * sizeof
            (int16_T)));
    memcpy((void *)&output_raw[0], (void *)&i, (uint16_T)((size_t)2 * sizeof
            (uint8_T)));
    b_x[0] = output_raw[1];
    b_x[1] = output_raw[0];
    memcpy((void *)&MATLAB_Arduino_ICM20689_B.Z_Gyro, (void *)&b_x[0], (uint16_T)
           ((size_t)1 * sizeof(int16_T)));
  } else {
    /* MATLABSystem: '<Root>/Z Gyroscope' */
    MATLAB_Arduino_ICM20689_B.Z_Gyro = 0;
  }

  /* End of MATLABSystem: '<Root>/Z Gyroscope' */

  /* Gain: '<Root>/Gain7' incorporates:
   *  SignalConversion generated from: '<Root>/Gain7'
   */
  MATLAB_Arduino_ICM20689_B.ZAcc_d[0] = (int32_T)
    MATLAB_Arduino_ICM20689_P.Gain7_Gain * MATLAB_Arduino_ICM20689_B.X_Gyro;
  MATLAB_Arduino_ICM20689_B.ZAcc_d[1] = (int32_T)
    MATLAB_Arduino_ICM20689_P.Gain7_Gain * MATLAB_Arduino_ICM20689_B.Y_Gyro;
  MATLAB_Arduino_ICM20689_B.ZAcc_d[2] = (int32_T)
    MATLAB_Arduino_ICM20689_P.Gain7_Gain * MATLAB_Arduino_ICM20689_B.Z_Gyro;

  /* Gain: '<Root>/Gain3' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Sum: '<Root>/Add5'
   */
  MATLAB_Arduino_ICM20689_B.Gain3 = (MATLAB_Arduino_ICM20689_P.Constant6_Value +
    (real_T)MATLAB_Arduino_ICM20689_B.Z_Gyro) *
    MATLAB_Arduino_ICM20689_P.Gain3_Gain;

  /* Gain: '<Root>/Gain5' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Sum: '<Root>/Add3'
   */
  MATLAB_Arduino_ICM20689_B.Gain5 = (MATLAB_Arduino_ICM20689_P.Constant4_Value +
    (real_T)MATLAB_Arduino_ICM20689_B.X_Gyro) *
    MATLAB_Arduino_ICM20689_P.Gain5_Gain;

  /* Gain: '<Root>/Gain4' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Sum: '<Root>/Add4'
   */
  MATLAB_Arduino_ICM20689_B.Gain4 = (MATLAB_Arduino_ICM20689_P.Constant5_Value +
    (real_T)MATLAB_Arduino_ICM20689_B.Y_Gyro) *
    MATLAB_Arduino_ICM20689_P.Gain4_Gain;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  MATLAB_Arduino_ICM20689_B.DiscreteTimeIntegrator =
    MATLAB_Arduino_ICM20689_DW.DiscreteTimeIntegrator_DSTATE;

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Delay: '<Root>/Delay' */
  if (MATLAB_Arduino_ICM20689_DW.Delay_DSTATE > 0.0) {
    /* MATLABSystem: '<S1>/Power Managment Register 1 ' incorporates:
     *  DataTypeConversion: '<S1>/Data Type  Conversion'
     */
    b_SwappedDataBytes[0] = 6U;
    for (i = 0; i < 8; i++) {
      /* DataTypeConversion: '<S1>/Data Type  Conversion' incorporates:
       *  Constant: '<S1>/Constant'
       */
      tmp = floor(MATLAB_Arduino_ICM20689_P.Constant_Value[i]);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      b_SwappedDataBytes[i + 1] = (uint8_T)(tmp < 0.0 ? (int16_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int16_T)(uint8_T)tmp);
    }

    MW_I2C_MasterWrite
      (MATLAB_Arduino_ICM20689_DW.obj_l.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &b_SwappedDataBytes[0], 9UL, false, false);

    /* End of MATLABSystem: '<S1>/Power Managment Register 1 ' */

    /* MATLABSystem: '<S1>/Power Management Register 2' incorporates:
     *  DataTypeConversion: '<S1>/Data Type  Conversion1'
     */
    b_SwappedDataBytes[0] = 7U;
    for (i = 0; i < 8; i++) {
      /* DataTypeConversion: '<S1>/Data Type  Conversion1' incorporates:
       *  Constant: '<S1>/Constant1'
       */
      tmp = floor(MATLAB_Arduino_ICM20689_P.Constant1_Value[i]);
      if (rtIsNaN(tmp) || rtIsInf(tmp)) {
        tmp = 0.0;
      } else {
        tmp = fmod(tmp, 256.0);
      }

      b_SwappedDataBytes[i + 1] = (uint8_T)(tmp < 0.0 ? (int16_T)(uint8_T)
        -(int8_T)(uint8_T)-tmp : (int16_T)(uint8_T)tmp);
    }

    MW_I2C_MasterWrite
      (MATLAB_Arduino_ICM20689_DW.obj_k.I2CDriverObj.MW_I2C_HANDLE, 104UL,
       &b_SwappedDataBytes[0], 9UL, false, false);

    /* End of MATLABSystem: '<S1>/Power Management Register 2' */
    srUpdateBC(MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC);
  }

  /* End of Delay: '<Root>/Delay' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  MATLAB_Arduino_ICM20689_DW.DiscreteTimeIntegrator_DSTATE +=
    MATLAB_Arduino_ICM20689_P.DiscreteTimeIntegrator_gainval *
    MATLAB_Arduino_ICM20689_B.XAcc;

  /* Update for Delay: '<Root>/Delay' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  MATLAB_Arduino_ICM20689_DW.Delay_DSTATE =
    MATLAB_Arduino_ICM20689_P.Constant1_Value_f;

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.01s, 0.0s] */
    rtExtModeUpload(0, (real_T)MATLAB_Arduino_ICM20689_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(MATLAB_Arduino_ICM20689_M)!=-1) &&
        !((rtmGetTFinal(MATLAB_Arduino_ICM20689_M)-
           MATLAB_Arduino_ICM20689_M->Timing.taskTime0) >
          MATLAB_Arduino_ICM20689_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(MATLAB_Arduino_ICM20689_M, "Simulation finished");
    }

    if (rtmGetStopRequested(MATLAB_Arduino_ICM20689_M)) {
      rtmSetErrorStatus(MATLAB_Arduino_ICM20689_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  MATLAB_Arduino_ICM20689_M->Timing.taskTime0 =
    ((time_T)(++MATLAB_Arduino_ICM20689_M->Timing.clockTick0)) *
    MATLAB_Arduino_ICM20689_M->Timing.stepSize0;
}

/* Model initialize function */
void MATLAB_Arduino_ICM20689_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  rtmSetTFinal(MATLAB_Arduino_ICM20689_M, 10.0);
  MATLAB_Arduino_ICM20689_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  MATLAB_Arduino_ICM20689_M->Sizes.checksums[0] = (3532148901U);
  MATLAB_Arduino_ICM20689_M->Sizes.checksums[1] = (2175305276U);
  MATLAB_Arduino_ICM20689_M->Sizes.checksums[2] = (563047928U);
  MATLAB_Arduino_ICM20689_M->Sizes.checksums[3] = (60727417U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[10];
    MATLAB_Arduino_ICM20689_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[2] = (sysRanDType *)
      &MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[3] = (sysRanDType *)
      &MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(MATLAB_Arduino_ICM20689_M->extModeInfo,
      &MATLAB_Arduino_ICM20689_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(MATLAB_Arduino_ICM20689_M->extModeInfo,
                        MATLAB_Arduino_ICM20689_M->Sizes.checksums);
    rteiSetTPtr(MATLAB_Arduino_ICM20689_M->extModeInfo, rtmGetTPtr
                (MATLAB_Arduino_ICM20689_M));
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    MATLAB_Arduino_ICM20689_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    uint32_T i2cname;
    codertarget_arduinobase_int_f_T *obj;
    codertarget_arduinobase_inter_T *obj_0;
    uint32_T varargin_1;

    /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
    MATLAB_Arduino_ICM20689_DW.DiscreteTimeIntegrator_DSTATE =
      MATLAB_Arduino_ICM20689_P.DiscreteTimeIntegrator_IC;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    MATLAB_Arduino_ICM20689_DW.Delay_DSTATE =
      MATLAB_Arduino_ICM20689_P.Delay_InitialCondition;

    /* SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem' */
    /* Start for MATLABSystem: '<S1>/Power Managment Register 1 ' */
    MATLAB_Arduino_ICM20689_DW.obj_l.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_l.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_l.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_l.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_l.matlabCodegenIsDeleted = false;
    obj_0 = &MATLAB_Arduino_ICM20689_DW.obj_l;
    MATLAB_Arduino_ICM20689_DW.obj_l.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_l.isInitialized = 1L;
    i2cname = 0;
    obj_0->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_l.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_l.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_l.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_l.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Power Management Register 2' */
    MATLAB_Arduino_ICM20689_DW.obj_k.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_k.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_k.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_k.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_k.matlabCodegenIsDeleted = false;
    obj_0 = &MATLAB_Arduino_ICM20689_DW.obj_k;
    MATLAB_Arduino_ICM20689_DW.obj_k.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_k.isInitialized = 1L;
    i2cname = 0;
    obj_0->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_k.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_k.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_k.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_k.isSetupComplete = true;

    /* End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem' */

    /* Start for MATLABSystem: '<Root>/X Acceleration ' */
    MATLAB_Arduino_ICM20689_DW.obj_p.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_p.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_p.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_p.SampleTime = -1.0;
    MATLAB_Arduino_ICM20689_DW.obj_p.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_p.matlabCodegenIsDeleted = false;
    MATLAB_Arduino_ICM20689_DW.obj_p.SampleTime =
      MATLAB_Arduino_ICM20689_P.XAcceleration_SampleTime;
    obj = &MATLAB_Arduino_ICM20689_DW.obj_p;
    MATLAB_Arduino_ICM20689_DW.obj_p.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_p.isInitialized = 1L;
    i2cname = 0;
    obj->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_p.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_p.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_p.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_p.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Y Acceleration' */
    MATLAB_Arduino_ICM20689_DW.obj_h.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_h.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_h.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_h.SampleTime = -1.0;
    MATLAB_Arduino_ICM20689_DW.obj_h.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_h.matlabCodegenIsDeleted = false;
    MATLAB_Arduino_ICM20689_DW.obj_h.SampleTime =
      MATLAB_Arduino_ICM20689_P.YAcceleration_SampleTime;
    obj = &MATLAB_Arduino_ICM20689_DW.obj_h;
    MATLAB_Arduino_ICM20689_DW.obj_h.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_h.isInitialized = 1L;
    i2cname = 0;
    obj->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_h.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_h.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_h.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Z Acceleration ' */
    MATLAB_Arduino_ICM20689_DW.obj_e.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_e.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_e.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_e.SampleTime = -1.0;
    MATLAB_Arduino_ICM20689_DW.obj_e.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_e.matlabCodegenIsDeleted = false;
    MATLAB_Arduino_ICM20689_DW.obj_e.SampleTime =
      MATLAB_Arduino_ICM20689_P.ZAcceleration_SampleTime;
    obj = &MATLAB_Arduino_ICM20689_DW.obj_e;
    MATLAB_Arduino_ICM20689_DW.obj_e.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_e.isInitialized = 1L;
    i2cname = 0;
    obj->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_e.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_e.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_e.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_e.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/X Gyroscope' */
    MATLAB_Arduino_ICM20689_DW.obj_n.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_n.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_n.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_n.SampleTime = -1.0;
    MATLAB_Arduino_ICM20689_DW.obj_n.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_n.matlabCodegenIsDeleted = false;
    MATLAB_Arduino_ICM20689_DW.obj_n.SampleTime =
      MATLAB_Arduino_ICM20689_P.XGyroscope_SampleTime;
    obj = &MATLAB_Arduino_ICM20689_DW.obj_n;
    MATLAB_Arduino_ICM20689_DW.obj_n.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_n.isInitialized = 1L;
    i2cname = 0;
    obj->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_n.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_n.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_n.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_n.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Y Gyroscope' */
    MATLAB_Arduino_ICM20689_DW.obj_ej.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj_ej.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj_ej.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj_ej.SampleTime = -1.0;
    MATLAB_Arduino_ICM20689_DW.obj_ej.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj_ej.matlabCodegenIsDeleted = false;
    MATLAB_Arduino_ICM20689_DW.obj_ej.SampleTime =
      MATLAB_Arduino_ICM20689_P.YGyroscope_SampleTime;
    obj = &MATLAB_Arduino_ICM20689_DW.obj_ej;
    MATLAB_Arduino_ICM20689_DW.obj_ej.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj_ej.isInitialized = 1L;
    i2cname = 0;
    obj->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj_ej.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj_ej.BusSpeed;
    MW_I2C_SetBusSpeed
      (MATLAB_Arduino_ICM20689_DW.obj_ej.I2CDriverObj.MW_I2C_HANDLE, varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj_ej.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Z Gyroscope' */
    MATLAB_Arduino_ICM20689_DW.obj.matlabCodegenIsDeleted = true;
    MATLAB_Arduino_ICM20689_DW.obj.DefaultMaximumBusSpeedInHz = 400000.0;
    MATLAB_Arduino_ICM20689_DW.obj.isInitialized = 0L;
    MATLAB_Arduino_ICM20689_DW.obj.SampleTime = -1.0;
    MATLAB_Arduino_ICM20689_DW.obj.I2CDriverObj.MW_I2C_HANDLE = NULL;
    MATLAB_Arduino_ICM20689_DW.obj.matlabCodegenIsDeleted = false;
    MATLAB_Arduino_ICM20689_DW.obj.SampleTime =
      MATLAB_Arduino_ICM20689_P.ZGyroscope_SampleTime;
    obj = &MATLAB_Arduino_ICM20689_DW.obj;
    MATLAB_Arduino_ICM20689_DW.obj.isSetupComplete = false;
    MATLAB_Arduino_ICM20689_DW.obj.isInitialized = 1L;
    i2cname = 0;
    obj->I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(i2cname, 0);
    MATLAB_Arduino_ICM20689_DW.obj.BusSpeed = 100000UL;
    varargin_1 = MATLAB_Arduino_ICM20689_DW.obj.BusSpeed;
    MW_I2C_SetBusSpeed(MATLAB_Arduino_ICM20689_DW.obj.I2CDriverObj.MW_I2C_HANDLE,
                       varargin_1);
    MATLAB_Arduino_ICM20689_DW.obj.isSetupComplete = true;
  }
}

/* Model terminate function */
void MATLAB_Arduino_ICM20689_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/X Acceleration ' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_p.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_p.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_p.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_p.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/X Acceleration ' */

  /* Terminate for MATLABSystem: '<Root>/Y Acceleration' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_h.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_h.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_h.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_h.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Y Acceleration' */

  /* Terminate for MATLABSystem: '<Root>/Z Acceleration ' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_e.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_e.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_e.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_e.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_e.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Z Acceleration ' */

  /* Terminate for MATLABSystem: '<Root>/X Gyroscope' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_n.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_n.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_n.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_n.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_n.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/X Gyroscope' */

  /* Terminate for MATLABSystem: '<Root>/Y Gyroscope' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_ej.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_ej.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_ej.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_ej.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_ej.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Y Gyroscope' */

  /* Terminate for MATLABSystem: '<Root>/Z Gyroscope' */
  if (!MATLAB_Arduino_ICM20689_DW.obj.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Z Gyroscope' */

  /* Terminate for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  /* Terminate for MATLABSystem: '<S1>/Power Managment Register 1 ' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_l.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_l.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_l.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_l.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/Power Managment Register 1 ' */

  /* Terminate for MATLABSystem: '<S1>/Power Management Register 2' */
  if (!MATLAB_Arduino_ICM20689_DW.obj_k.matlabCodegenIsDeleted) {
    MATLAB_Arduino_ICM20689_DW.obj_k.matlabCodegenIsDeleted = true;
    if ((MATLAB_Arduino_ICM20689_DW.obj_k.isInitialized == 1L) &&
        MATLAB_Arduino_ICM20689_DW.obj_k.isSetupComplete) {
      MW_I2C_Close(MATLAB_Arduino_ICM20689_DW.obj_k.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/Power Management Register 2' */
  /* End of Terminate for SubSystem: '<Root>/Enabled Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
