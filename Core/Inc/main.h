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


enum LEDS
{
  LED_RUN_STOP = 0,
  LED_SINGLE   = 1,
  LED_AFG_2D   = 2,
  LED_AFG_2U   = 3,
  LED_AFG_1D   = 4,
  LED_AFG_1U   = 5,
  LED_ENC_3U   = 6,
  LED_ENC_3D   = 7,
  LED_ENC_1U   = 8,
  LED_ENC_1D   = 9,
  LED_ENC_4U   = 10,
  LED_ENC_4D   = 11,
  LED_USB_U    = 12,
  LED_USB_D    = 13,
  LED_DOWN_R   = 14,
  LED_DOWN_M   = 15,
  LED_DOWN_L   = 16,
  LED_DPO_2    = 17,
  LED_DPO_1    = 18,
};

enum KEYS
{
  KEY_AFG_1    = 0x6F,
  KEY_AFG_2    = 0x6E,
  KEY_DPO_1    = 0x6D,
  KEY_DPO_2    = 0x6C,
  KEY_DPO_1_AC = 0x65,
  KEY_DPO_2_AC = 0x64,
  KEY_RUN_STOP = 0x67,
  KEY_SINGLE   = 0x5F,
  KEY_UP       = 0x5E,
  KEY_DOWN     = 0x5C,
  KEY_LEFT     = 0x66,
  KEY_RIGHT    = 0x5D,
  KEY_1        = 0x55,
  KEY_2        = 0x4D,
  KEY_3        = 0x45,
  KEY_4        = 0x56,
  KEY_5        = 0x4E,
  KEY_6        = 0x46,
  KEY_7        = 0x57,
  KEY_8        = 0x4F,
  KEY_9        = 0x47,
  KEY_0        = 0x4C,
  KEY_INVERSE  = 0x54,
  KEY_POINT    = 0x44,
  KEY_ENTER    = 0x74,
  KEY_ENC3     = 0x77,
  KEY_ENC1     = 0x76,
  KEY_ENC4     = 0x75,
};

enum TRIGMODE
{
  TRIGMODE_AUTO   = 0,
  TRIGMODE_SINGLE = 1,
  TRIGMODE_NORMAL = 2,
};

enum WAVEFORM
{
  WAVEFORM_SINE      = 0,
  WAVEFORM_SQUARE    = 1,
  WAVEFORM_RAMP      = 2,
  WAVEFORM_RAMP_UP   = 3,
  WAVEFORM_RAMP_DOWN = 4,
  WAVEFORM_NOISE     = 5,
};

enum VIEWS
{
  VIEW_INTRO  = 0,
  VIEW_DPO1   = 1,
  VIEW_DPO2   = 2,
  VIEW_AFG1   = 3,
  VIEW_AFG2   = 4,
  VIEW_CONFIG = 5,
};

typedef struct {
	uint32_t CH1_OFFSET;
	uint32_t CH2_OFFSET;
  uint32_t CH1_BIAS;
	uint32_t CH2_BIAS;
  uint16_t DPO_EN1;
	uint16_t DPO_EN2;
  uint16_t CH1_AC_DC;
	uint16_t CH2_AC_DC;
  uint16_t TRIG_MODE;
  uint16_t TRIG_LEVEL;
  uint16_t TRIG_FALL_EN;
  uint16_t TRIG_RISI_EN;
  uint16_t SELECT_CH;
} DPO_AnalogStates;


typedef struct {
  uint16_t AFG_EN1;
	uint16_t AFG_EN2;
	uint16_t CH1_DC;
	uint16_t CH2_DC;
  uint16_t CH1_REF;
	uint16_t CH2_REF;
  uint64_t CH1_FREQ;
  uint64_t CH2_FREQ;
  uint16_t CH1_TYPE;
  uint16_t CH2_TYPE;
  uint16_t TRIG_MODE;
} AFG_AnalogStates;

typedef struct {
	uint32_t MAIN;
	uint32_t WAKE;
	uint32_t SHUT;
} THEMEs;



/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define DPO_DEEP 512

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
#define T8C4N_ST_BRI_Pin GPIO_PIN_13
#define T8C4N_ST_BRI_GPIO_Port GPIOC
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
#define D2C1_OFFSET2_Pin GPIO_PIN_6
#define D2C1_OFFSET2_GPIO_Port GPIOA
#define O1P_O2P_DPO_IN_Pin GPIO_PIN_7
#define O1P_O2P_DPO_IN_GPIO_Port GPIOA
#define DPO_EN1_Pin GPIO_PIN_4
#define DPO_EN1_GPIO_Port GPIOC
#define DPO_AC1_Pin GPIO_PIN_5
#define DPO_AC1_GPIO_Port GPIOC
#define DPO_EN2_Pin GPIO_PIN_0
#define DPO_EN2_GPIO_Port GPIOB
#define DPO_AC2_Pin GPIO_PIN_1
#define DPO_AC2_GPIO_Port GPIOB
#define T2C3_REF1_Pin GPIO_PIN_10
#define T2C3_REF1_GPIO_Port GPIOB
#define T2C4_DC1_Pin GPIO_PIN_11
#define T2C4_DC1_GPIO_Port GPIOB
#define O4O_D4C1_BIAS1_Pin GPIO_PIN_12
#define O4O_D4C1_BIAS1_GPIO_Port GPIOB
#define O6P_O3P_DPO_IN2_Pin GPIO_PIN_13
#define O6P_O3P_DPO_IN2_GPIO_Port GPIOB
#define T15C1_DC2_Pin GPIO_PIN_14
#define T15C1_DC2_GPIO_Port GPIOB
#define T15C2_REF2_Pin GPIO_PIN_15
#define T15C2_REF2_GPIO_Port GPIOB
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
#define FT_INT_EXTI4_Pin GPIO_PIN_4
#define FT_INT_EXTI4_GPIO_Port GPIOB
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
