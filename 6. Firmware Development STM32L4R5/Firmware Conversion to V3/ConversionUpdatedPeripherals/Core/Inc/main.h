/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BATT_SDA_Pin GPIO_PIN_0
#define BATT_SDA_GPIO_Port GPIOF
#define BATT_SCL_Pin GPIO_PIN_1
#define BATT_SCL_GPIO_Port GPIOF
#define IRID_NETAV_Pin GPIO_PIN_2
#define IRID_NETAV_GPIO_Port GPIOF
#define IRID_RI_Pin GPIO_PIN_3
#define IRID_RI_GPIO_Port GPIOF
#define SD_DETECT_Pin GPIO_PIN_5
#define SD_DETECT_GPIO_Port GPIOF
#define IRID_ONOFF_Pin GPIO_PIN_1
#define IRID_ONOFF_GPIO_Port GPIOC
#define GPS_INT_Pin GPIO_PIN_3
#define GPS_INT_GPIO_Port GPIOC
#define GPS_RX_Pin GPIO_PIN_0
#define GPS_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_1
#define GPS_TX_GPIO_Port GPIOA
#define GPS_PPS_Pin GPIO_PIN_2
#define GPS_PPS_GPIO_Port GPIOA
#define ENV_CS_Pin GPIO_PIN_4
#define ENV_CS_GPIO_Port GPIOA
#define ENV_SDK_Pin GPIO_PIN_5
#define ENV_SDK_GPIO_Port GPIOA
#define ENV_SDO_Pin GPIO_PIN_6
#define ENV_SDO_GPIO_Port GPIOA
#define ENV_SDI_Pin GPIO_PIN_7
#define ENV_SDI_GPIO_Port GPIOA
#define IRID_TXD_Pin GPIO_PIN_4
#define IRID_TXD_GPIO_Port GPIOC
#define IRID_RXD_Pin GPIO_PIN_5
#define IRID_RXD_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_14
#define LED_3_GPIO_Port GPIOB
#define IMU_INT_Pin GPIO_PIN_14
#define IMU_INT_GPIO_Port GPIOD
#define DEBUG_TX_Pin GPIO_PIN_7
#define DEBUG_TX_GPIO_Port GPIOG
#define DEBUG_RX_Pin GPIO_PIN_8
#define DEBUG_RX_GPIO_Port GPIOG
#define LED_1_Pin GPIO_PIN_7
#define LED_1_GPIO_Port GPIOC
#define EX_TX_Pin GPIO_PIN_5
#define EX_TX_GPIO_Port GPIOD
#define EX_RX_Pin GPIO_PIN_6
#define EX_RX_GPIO_Port GPIOD
#define LED_2_Pin GPIO_PIN_7
#define LED_2_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_8
#define IMU_SCL_GPIO_Port GPIOB
#define IMU_SDA_Pin GPIO_PIN_9
#define IMU_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
