/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ST_BRI_Pin GPIO_PIN_13
#define ST_BRI_GPIO_Port GPIOC
#define FT6336_RST_Pin GPIO_PIN_14
#define FT6336_RST_GPIO_Port GPIOC
#define ST_DC_Pin GPIO_PIN_15
#define ST_DC_GPIO_Port GPIOC
#define ENC1_P_Pin GPIO_PIN_0
#define ENC1_P_GPIO_Port GPIOC
#define ENC1_N_Pin GPIO_PIN_1
#define ENC1_N_GPIO_Port GPIOC
#define T20C2_RUN_LED_Pin GPIO_PIN_2
#define T20C2_RUN_LED_GPIO_Port GPIOC
#define D1C1_OFFSET_Pin GPIO_PIN_4
#define D1C1_OFFSET_GPIO_Port GPIOA
#define D2C1_OFFSET__Pin GPIO_PIN_6
#define D2C1_OFFSET__GPIO_Port GPIOA
#define O1P_O2P_DPO_IN_Pin GPIO_PIN_7
#define O1P_O2P_DPO_IN_GPIO_Port GPIOA
#define DPO_EN_Pin GPIO_PIN_4
#define DPO_EN_GPIO_Port GPIOC
#define DPO_AC_Pin GPIO_PIN_5
#define DPO_AC_GPIO_Port GPIOC
#define DPO_EN__Pin GPIO_PIN_0
#define DPO_EN__GPIO_Port GPIOB
#define DPO_AC__Pin GPIO_PIN_1
#define DPO_AC__GPIO_Port GPIOB
#define T2C3_REF_Pin GPIO_PIN_10
#define T2C3_REF_GPIO_Port GPIOB
#define T2C4_DC_Pin GPIO_PIN_11
#define T2C4_DC_GPIO_Port GPIOB
#define O4O_D4C1_BIAS1_Pin GPIO_PIN_12
#define O4O_D4C1_BIAS1_GPIO_Port GPIOB
#define O6P_O3P_DPO_IN__Pin GPIO_PIN_13
#define O6P_O3P_DPO_IN__GPIO_Port GPIOB
#define T15C1_DC__Pin GPIO_PIN_14
#define T15C1_DC__GPIO_Port GPIOB
#define T15C2_REF__Pin GPIO_PIN_15
#define T15C2_REF__GPIO_Port GPIOB
#define ENC3_P_Pin GPIO_PIN_6
#define ENC3_P_GPIO_Port GPIOC
#define ENC3_N_Pin GPIO_PIN_7
#define ENC3_N_GPIO_Port GPIOC
#define O5O_D4C2_IAS0_Pin GPIO_PIN_8
#define O5O_D4C2_IAS0_GPIO_Port GPIOA
#define FPGA_SPI3_NSS_Pin GPIO_PIN_15
#define FPGA_SPI3_NSS_GPIO_Port GPIOA
#define FPGA_SPI3_SCK_Pin GPIO_PIN_10
#define FPGA_SPI3_SCK_GPIO_Port GPIOC
#define FPGA_SPI3_MISO_Pin GPIO_PIN_11
#define FPGA_SPI3_MISO_GPIO_Port GPIOC
#define FPGA_SPI3_MOSI_Pin GPIO_PIN_12
#define FPGA_SPI3_MOSI_GPIO_Port GPIOC
#define ST_CS_Pin GPIO_PIN_2
#define ST_CS_GPIO_Port GPIOD
#define ST_SPI3_SCK_Pin GPIO_PIN_3
#define ST_SPI3_SCK_GPIO_Port GPIOB
#define FT_INT_Pin GPIO_PIN_4
#define FT_INT_GPIO_Port GPIOB
#define ST_SPI3_MOSI_Pin GPIO_PIN_5
#define ST_SPI3_MOSI_GPIO_Port GPIOB
#define ENC4_P_Pin GPIO_PIN_6
#define ENC4_P_GPIO_Port GPIOB
#define ENC4_N_Pin GPIO_PIN_7
#define ENC4_N_GPIO_Port GPIOB
#define T17C1_WS2812_Pin GPIO_PIN_9
#define T17C1_WS2812_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
