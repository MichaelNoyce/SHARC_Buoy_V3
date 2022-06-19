  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (MATLAB_Arduino_ICM20689_P)
    ;%
      section.nData     = 24;
      section.data(24)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_P.Constant_Value
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant1_Value
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% MATLAB_Arduino_ICM20689_P.XAcceleration_SampleTime
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% MATLAB_Arduino_ICM20689_P.XGyroscope_SampleTime
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 17;
	
	  ;% MATLAB_Arduino_ICM20689_P.YAcceleration_SampleTime
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 18;
	
	  ;% MATLAB_Arduino_ICM20689_P.YGyroscope_SampleTime
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 19;
	
	  ;% MATLAB_Arduino_ICM20689_P.ZAcceleration_SampleTime
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 20;
	
	  ;% MATLAB_Arduino_ICM20689_P.ZGyroscope_SampleTime
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 21;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant2_Value
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 22;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain_Gain
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 23;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant_Value_d
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 24;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain2_Gain
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 25;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant3_Value
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 26;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain1_Gain
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 27;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant6_Value
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 28;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain3_Gain
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 29;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant4_Value
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 30;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain5_Gain
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 31;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant5_Value
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 32;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain4_Gain
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 33;
	
	  ;% MATLAB_Arduino_ICM20689_P.DiscreteTimeIntegrator_gainval
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 34;
	
	  ;% MATLAB_Arduino_ICM20689_P.DiscreteTimeIntegrator_IC
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 35;
	
	  ;% MATLAB_Arduino_ICM20689_P.Delay_InitialCondition
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 36;
	
	  ;% MATLAB_Arduino_ICM20689_P.Constant1_Value_f
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_P.Gain7_Gain
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_P.Gain6_Gain
	  section.data(2).logicalSrcIdx = 25;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (MATLAB_Arduino_ICM20689_B)
    ;%
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_B.ZAcc
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_B.XAcc
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% MATLAB_Arduino_ICM20689_B.Gain1
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% MATLAB_Arduino_ICM20689_B.Gain3
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% MATLAB_Arduino_ICM20689_B.Gain5
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% MATLAB_Arduino_ICM20689_B.Gain4
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% MATLAB_Arduino_ICM20689_B.DiscreteTimeIntegrator
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_B.ZAcc_n
	  section.data(1).logicalSrcIdx = 7;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_B.ZAcc_d
	  section.data(2).logicalSrcIdx = 8;
	  section.data(2).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_B.Z_Gyro
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_B.Z_Accel
	  section.data(2).logicalSrcIdx = 10;
	  section.data(2).dtTransOffset = 1;
	
	  ;% MATLAB_Arduino_ICM20689_B.Y_Gyro
	  section.data(3).logicalSrcIdx = 11;
	  section.data(3).dtTransOffset = 2;
	
	  ;% MATLAB_Arduino_ICM20689_B.Y_Accel
	  section.data(4).logicalSrcIdx = 12;
	  section.data(4).dtTransOffset = 3;
	
	  ;% MATLAB_Arduino_ICM20689_B.X_Gyro
	  section.data(5).logicalSrcIdx = 13;
	  section.data(5).dtTransOffset = 4;
	
	  ;% MATLAB_Arduino_ICM20689_B.X_Accel
	  section.data(6).logicalSrcIdx = 14;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_B.ZGyroscope_o2
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_B.ZAcceleration_o2
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 1;
	
	  ;% MATLAB_Arduino_ICM20689_B.YGyroscope_o2
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 2;
	
	  ;% MATLAB_Arduino_ICM20689_B.YAcceleration_o2
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 3;
	
	  ;% MATLAB_Arduino_ICM20689_B.XGyroscope_o2
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 4;
	
	  ;% MATLAB_Arduino_ICM20689_B.XAcceleration_o2
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 5;
    sectIdxOffset = 4;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (MATLAB_Arduino_ICM20689_DW)
    ;%
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_DW.obj
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_DW.obj_e
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% MATLAB_Arduino_ICM20689_DW.obj_ej
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% MATLAB_Arduino_ICM20689_DW.obj_h
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% MATLAB_Arduino_ICM20689_DW.obj_n
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% MATLAB_Arduino_ICM20689_DW.obj_p
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_DW.obj_l
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_DW.obj_k
	  section.data(2).logicalSrcIdx = 7;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_DW.DiscreteTimeIntegrator_DSTATE
	  section.data(1).logicalSrcIdx = 8;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_DW.Delay_DSTATE
	  section.data(2).logicalSrcIdx = 9;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_DW.UncalibratedOutput_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% MATLAB_Arduino_ICM20689_DW.CalibratedAccOutput_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
	  ;% MATLAB_Arduino_ICM20689_DW.UncalibratedOrientationOutput_P.LoggedData
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 2;
	
	  ;% MATLAB_Arduino_ICM20689_DW.CalibratedOrientationOutput_PWO.LoggedData
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 3;
	
	  ;% MATLAB_Arduino_ICM20689_DW.CalibratedYPosition_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% MATLAB_Arduino_ICM20689_DW.EnabledSubsystem_SubsysRanBC
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 3532148901;
  targMap.checksum1 = 2175305276;
  targMap.checksum2 = 563047928;
  targMap.checksum3 = 60727417;

