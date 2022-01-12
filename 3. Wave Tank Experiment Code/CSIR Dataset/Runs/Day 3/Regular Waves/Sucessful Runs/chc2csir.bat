c---- get command line arguments
@rem  call getarg (1, chcFile)         ! chc input file
@rem  call getarg (2, channels)        ! no probe(s) use
@rem  call getarg (3, csirFile)        ! output file name 
@rem  call getarg (4, Hz)              ! Test Hz used
@rem  call getarg (5, date)            ! Test date
@rem  call getarg (6, times)           ! Test time
@rem  call getarg (7, type)            ! Analysis method      

@rem chc2csir <inputFile> <no probes> <outputFile> <hz> <date> <time> <method> 


chc2csir B-1-REG_001_chc 2 B-1-REG_001_csir 50 22-07-2010 05:07:29 waves
chc2csir B-2-REG_001_chc 2 B-2-REG_001_csir 50 22-07-2010 05:26:58 waves
chc2csir B-3-REG_001_chc 2 B-3-REG_001_csir 50 22-07-2010 05:48:14 waves
chc2csir B-4-REG_001_chc 2 B-4-REG_001_csir 50 22-07-2010 06:13:04 waves
chc2csir B-5-REG_001_chc 2 B-5-REG_001_csir 50 22-07-2010 06:33:43 waves

chc2csir D3-RUN-TETHER_002_chc 2 D3-RUN-TETHER_002_csir 50 17-07-2010 06:33:40 waves

@rem Christiaan - US Student                            

@rem chc2csir A3-CAL_001_chc 2 A3-CAL_001_csir 20 17-07-2010 02:58:11 refl probesFile
@rem chc2csir CDW_002_chc 6 CDW_002_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_003_chc 6 CDW_003_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_004_chc 6 CDW_004_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_005_chc 6 CDW_005_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_006_chc 6 CDW_006_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_007_chc 6 CDW_007_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_008_chc 6 CDW_001_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_009_chc 6 CDW_002_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_010_chc 6 CDW_003_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_011_chc 6 CDW_004_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_012_chc 6 CDW_005_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_013_chc 6 CDW_006_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_014_chc 6 CDW_007_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_015_chc 6 CDW_001_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_016_chc 6 CDW_002_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_017_chc 6 CDW_003_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_018_chc 6 CDW_004_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_019_chc 6 CDW_005_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_020_chc 6 CDW_006_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_021_chc 6 CDW_001_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_022_chc 6 CDW_002_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_023_chc 6 CDW_003_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_024_chc 6 CDW_004_csir 20 04-08-2009 16:00:00 refl probesFile
@rem chc2csir CDW_025_chc 6 CDW_005_csir 20 04-08-2009 16:00:00 refl probesFile
                                                                     
@rem Pieter                                                          
@rem chc2csir PVA_001_chc 6 PVA_001_chc 20 14-08-2009 11:10:57 refl  probesFile
@rem chc2csir PVA_002_chc 6 PVA_002_chc 20 14-08-2009 11:35:05 refl  probesFile
@rem chc2csir PVA_003_chc 6 PVA_003_chc 20 14-08-2009 11:37:14 refl  probesFile
@rem chc2csir PVA_004_chc 6 PVA_004_chc 20 14-08-2009 12:01:18 refl  probesFile
@rem chc2csir PVA_005_chc 6 PVA_005_chc 20 14-08-2009 12:55:11 refl  probesFile
@rem chc2csir PVA_006_chc 6 PVA_006_chc 20 14-08-2009 13:25:53 refl  probesFile
@rem chc2csir PVA_007_chc 6 PVA_007_chc 20 14-08-2009 14:05:05 refl  probesFile
@rem chc2csir PVA_008_chc 6 PVA_008_chc 20 14-08-2009 15:40:05 refl  probesFile
@rem chc2csir PVA_009_chc 6 PVA_009_chc 20 24-08-2009 16:24:48 refl  probesFile
@rem chc2csir PVA_010_chc 6 PVA_010_chc 20 24-08-2009 16:24:48 refl  probesFile
@rem chc2csir PVA_011_chc 6 PVA_011_chc 20 24-08-2009 16:51:34 refl  probesFile
@rem chc2csir PVA_012_chc 6 PVA_012_chc 20 24-08-2009 17:21:25 refl  probesFile
@rem chc2csir PVA_013_chc 6 PVA_013_chc 20 24-08-2009 17:55:09 refl  probesFile
@rem chc2csir PVA_014_chc 6 PVA_014_chc 20 25-08-2009 17:12:34 refl  probesFile
@rem chc2csir PVA_015_chc 6 PVA_015_chc 20 26-08-2009 13:43:57 refl  probesFile
@rem chc2csir PVA_016_chc 6 PVA_016_chc 20 26-08-2009 14:06:41 refl  probesFile
@rem chc2csir PVA_017_chc 6 PVA_017_chc 20 26-08-2009 14:27:36 refl  probesFile
@rem chc2csir PVA_018_chc 6 PVA_018_chc 20 26-08-2009 14:52:26 refl  probesFile
@rem chc2csir PVA_019_chc 6 PVA_019_chc 20 26-08-2009 15:20:38 refl  probesFile
@rem chc2csir PVA_020_chc 6 PVA_020_chc 20 26-08-2009 15:51:28 refl  probesFile
@rem chc2csir PVA_021_chc 6 PVA_021_chc 20 26-08-2009 16:35:58 refl  probesFile
@rem chc2csir PVA_022_chc 6 PVA_022_chc 20 26-08-2009 16:49:33 refl  probesFile
@rem chc2csir PVA_023_chc 6 PVA_023_chc 20 26-08-2009 17:23:22 refl  probesFile
@rem chc2csir PVA_024_chc 6 PVA_024_chc 20 26-08-2009 17:36:25 refl  probesFile

@rem  AlakhdarSept09
@rem chc2csir ALAKSEP_001_chc 6 ALAKSEP_001_csir 20 11-09-2009 11:18:02 refl @rem probesFile
@rem chc2csir ALAKSEP_002_chc 6 ALAKSEP_002_csir 20 11-09-2009 12:34:40 refl @rem probesFile
@rem chc2csir ALAKSEP_003_chc 6 ALAKSEP_003_csir 20 11-09-2009 14:40:48 refl @rem probesFile
@rem chc2csir ALAKSEP_004_chc 6 ALAKSEP_004_csir 20 11-09-2009 15:21:47 refl @rem probesFile
@rem chc2csir ALAKSEP_005_chc 6 ALAKSEP_005_csir 20 11-09-2009 16:18:23 refl @rem probesFile
@rem chc2csir ALAKSEP_006_chc 6 ALAKSEP_006_csir 20 11-09-2009 16:50:47 refl @rem probesFile 

@rem Ras Al Akdhar 3D Wave Calibrations
@rem chc2csir D3-RUN-TETHER_002_chc 2 D3-RUN-TETHER_002_csir 20 17-07-2010 06:33:40 waves
@rem chc2csir 3DALAKCALIB_039_chc  9 3DALAKCALIB_039_csir 25 02OCT-2009 11:43:14 waves
@rem chc2csir 3DALAKCALIB_040_chc  9 3DALAKCALIB_040_csir 20 02OCT-2009 12:48:13 waves
@rem chc2csir 3DALAKCALIB_042_chc  9 3DALAKCALIB_042_csir 20 02OCT-2009 14:22:59 waves
@rem chc2csir 3DALAKCALIB_043_chc  9 3DALAKCALIB_043_csir 20 02OCT-2009 14:36:28 waves
@rem chc2csir 3DALAKCALIB_047_chc  9 3DALAKCALIB_047_csir 20 02OCT-2009 15:22:09 waves
@rem chc2csir 3DALAKCALIB_048_chc  9 3DALAKCALIB_048_csir 20 02OCT-2009 15:54:13 waves
@rem chc2csir 3DALAKCALIB_049_chc  9 3DALAKCALIB_049_csir 20 02OCT-2009 16:20:39 waves

@rem Ras Al Akdhar 3D - 2009-10-09
@rem chc2csir ALAK3D_001_chc 8 ALAK3D_001_csir 20 09-OCT-2009 13:12:34 waves 
@rem chc2csir ALAK3D_002_chc 8 ALAK3D_002_csir 20 09-OCT-2009 12:44:13 waves
@rem chc2csir ALAK3D_003_chc 8 ALAK3D_003_csir 20 09-OCT-2009 11:09:30 waves
@rem chc2csir ALAK3D_004_chc 8 ALAK3D_004_csir 20 09-OCT-2009 10:34:50 waves
@rem chc2csir ALAK3D_005_chc 8 ALAK3D_005_csir 20 09-OCT-2009 09:34:05 waves
@rem chc2csir ALAK3D_006_chc 8 ALAK3D_006_csir 20 09-OCT-2009 08:50:54 waves
@rem chc2csir ALAK3D_007_chc 8 ALAK3D_007_csir 20 08-OCT-2009 16:34:12 waves
@rem chc2csir ALAK3D_008_chc 8 ALAK3D_008_csir 20 08-OCT-2009 15:55:58 waves
@rem chc2csir ALAK3D_009_chc 8 ALAK3D_009_csir 20 08-OCT-2009 15:29:51 waves
@rem chc2csir ALAK3D_010_chc 8 ALAK3D_010_csir 20 08-OCT-2009 14:52:14 waves
@rem chc2csir ALAK3D_011_chc 8 ALAK3D_011_csir 20 08-OCT-2009 13:00:44 waves
@rem chc2csir ALAK3D_012_chc 8 ALAK3D_012_csir 20 08-OCT-2009 12:17:25 waves
@rem chc2csir ALAK3D_013_chc 8 ALAK3D_013_csir 20 08-OCT-2009 11:50:01 waves
@rem chc2csir ALAK3D_014_chc 8 ALAK3D_014_csir 20 08-OCT-2009 10:13:31 waves
@rem chc2csir ALAK3D_015_chc 8 ALAK3D_015_csir 20 08-OCT-2009 09:38:02 waves
@rem chc2csir ALAK3D_016_chc 8 ALAK3D_016_csir 20 08-OCT-2009 09:07:10 waves

@rem Ras Al Akdhar 3D - 2009-10-28
@rem chc2csir ALAK3D_017_chc 8 ALAK3D_017_csir 20 28-OCT-2009 09:59:08 waves
@rem chc2csir ALAK3D_018_chc 8 ALAK3D_018_csir 20 28-OCT-2009 10:34:59 waves

@rem Barrow Island Wave Calibration 2009-11-26
@rem chc2csir BARROWCALIB_001_chc 6 BARROWCALIB_001_csir 20 24-NOV-2009 16:58:27 refl 
@rem chc2csir BARROWCALIB_002_chc 6 BARROWCALIB_002_csir 20 24-NOV-2009 09:31:02 refl 
@rem chc2csir BARROWCALIB_003_chc 6 BARROWCALIB_003_csir 20 24-NOV-2009 10:08:51 refl
@rem chc2csir BARROWCALIB_004_chc 6 BARROWCALIB_004_csir 20 24-NOV-2009 11:10:19 refl
@rem chc2csir BARROWCALIB_005_chc 6 BARROWCALIB_005_csir 20 24-NOV-2009 11:27:56 refl
@rem chc2csir BARROWCALIB_006_chc 6 BARROWCALIB_006_csir 20 24-NOV-2009 12:11:05 refl
@rem chc2csir BARROWCALIB_007_chc 6 BARROWCALIB_007_csir 20 24-NOV-2009 12:44:33 refl

@rem chc2csir BARROWCALIB_008_chc 6 BARROWCALIB_008_csir 20 26-NOV-2009 14:06:18 refl
@rem chc2csir BARROWCALIB_009_chc 6 BARROWCALIB_009_csir 20 26-NOV-2009 14:33:18 refl
@rem chc2csir BARROWCALIB_010_chc 6 BARROWCALIB_010_csir 20 26-NOV-2009 15:02:11 refl
@rem chc2csir BARROWCALIB_011_chc 6 BARROWCALIB_011_csir 20 26-NOV-2009 15:42:12 refl
@rem chc2csir BARROWCALIB_012_chc 6 BARROWCALIB_012_csir 20 26-NOV-2009 16:12:50 refl
@rem chc2csir BARROWCALIB_013_chc 6 BARROWCALIB_013_csir 20 26-NOV-2009 16:40:10 refl

@rem Barrow Island Wave Calibration 2009-11-27
@rem chc2csir BARROWCALIB_016_chc 6 BARROWCALIB_016_csir 20 27-NOV-2009 11:22:58 refl
@rem chc2csir BARROWCALIB_017_chc 6 BARROWCALIB_017_csir 20 27-NOV-2009 11:34:59 refl
@rem chc2csir BARROWCALIB_018_chc 6 BARROWCALIB_018_csir 20 27-NOV-2009 12:06:06 refl
@rem chc2csir BARROWCALIB_019_chc 6 BARROWCALIB_019_csir 20 27-NOV-2009 12:26:58 refl
@rem chc2csir BARROWCALIB_020_chc 6 BARROWCALIB_020_csir 20 27-NOV-2009 12:37:02 refl

@rem chc2csir BARROWCALIB_021_chc 6 BARROWCALIB_021_csir 20 27-NOV-2009 13:45:53 refl
@rem chc2csir BARROWCALIB_022_chc 6 BARROWCALIB_022_csir 20 27-NOV-2009 14:01:19 refl
@rem chc2csir BARROWCALIB_023_chc 6 BARROWCALIB_023_csir 20 27-NOV-2009 14:08:23 refl

@rem chc2csir BARROWCALIB_024_chc 6 BARROWCALIB_024_csir 20 27-NOV-2009 14:55:36 refl
@rem chc2csir BARROWCALIB_025_chc 6 BARROWCALIB_025_csir 20 27-NOV-2009 15:12:06 refl
@rem chc2csir BARROWCALIB_026_chc 6 BARROWCALIB_026_csir 20 27-NOV-2009 14:08:23 refl
@rem chc2csir BARROWCALIB_026_chc 6 BARROWCALIB_026_csir 20 27-NOV-2009 14:08:23 waves
                                                                            
@rem CALIBRATION CHECKS WITH DIFFRENT WATER                                                                            

@rem chc2csir CALCHECK20111202OLD325_chc 1 CALCHECK20111202OLD325_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK20111202OLD0_chc 1 CALCHECK20111202OLD0_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK20111202NEW325_chc 1 CALCHECK20111202NEW325_csir 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK20111202NEW0_chc 1 CALCHECK20111202NEW0_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK20111202OLDM325_chc 1 CALCHECK20111202OLDM325_csir 20 02-DEC-2011 14:08:23 refl

@rem chc2csir CALCHECKOld0_chc 1 CALCHECKOLD0_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECKOLD325_chc 1 CALCHECKOLD325_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECKNew0_chc 1 CALCHECKNew0_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECKNew325_chc 1 CALCHECKNew325_csir 20 02-DEC-2011 14:08:23 refl

@rem chc2csir CALCHECK5DaNew0_chc 1 CALCHECK5DaNew0_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK5DaNew325_chc 1 CALCHECK5DaNew325_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK5DbNew0_chc 1 CALCHECK5DbNew0_csir 20 02-DEC-2011 14:08:23 refl
@rem chc2csir CALCHECK5DbNew325_chc 1 CALCHECK5DbNew325_csir 20 02-DEC-2011 14:08:23 refl

@rem chc2csir calcheck6new325_chc 1 calcheck6new325_csir 20 06-DEC-2011 23:51:23 refl
@rem chc2csir calcheck7new325_chc 1 calcheck7new325_csir 20 07-DEC-2011 21:15:23 refl
@rem chc2csir calcheck7bnew325_chc 1 calcheck7bnew325_csir 20 07-DEC-2011 21:15:23 refl

@rem chc2csir calcheck8dnew325_chc 2 calcheck8dnew325_csir 20 08-DEC-2011 21:15:23 refl

@rem chc2csir calcheck12dnew325_chc 2 calcheck12dnew325_csir 20 12-DEC-2011 21:15:23 refl
@rem chc2csir calcheck12dbnew325_chc 2 calcheck12dbnew325_csir 20 12-DEC-2011 21:15:23 refl

@rem chc2csir calcheck13new325_chc 1 calcheck13new325_csir 20 13-DEC-2011 07:33:23 refl
@rem chc2csir cacheck13bnew_chc 1 cacheck13bnew_csir 20 13-DEC-2011 15:35:23 refl


@rem DOHA____QEZ3

@rem chc2csir calcheck20120221_chc 3 calcheck20120221_csir 25 21-FEB-2012 10:13:00 refl
@rem chc2csir calcheck20120221b_chc 3 calcheck20120221b_csir 25 21-FEB-2012 10:13:00 refl
@rem chc2csir calcheck20120221c_chc 3 calcheck20120221c_csir 25 21-FEB-2012 10:13:00 refl
@rem chc2csir calcheck20120222a_chc 3 calcheck20120222a_csir 25 22-FEB-2012 10:00:00 refl
@rem chc2csir calcheck20120222d_chc 3 calcheck20120222d_csir 25 22-FEB-2012 10:15:00 refl
@rem chc2csir calcheck20120223_chc 3 calcheck20120223_csir 25 22-FEB-2012 10:15:00 refl
@rem chc2csir calcheck20120224_chc 3 calcheck20120224_csir 25 24-FEB-2012 10:07:00 refl
@rem chc2csir calcheck20120224b_chc 4 calcheck20120224b_csir 25 24-FEB-2012 11:06:00 refl
@rem chc2csir calcheck20120227a_chc 4 calcheck20120227a_csir 25 24-FEB-2012 11:06:00 refl
@rem chc2csir calcheck20120229_chc 4 calcheck20120229_csir 25 29-FEB-2012 10:11:00 refl
chc2csir calcheck01_chc 4 calcheck01_csir 25 29-FEB-2012 10:11:00 refl