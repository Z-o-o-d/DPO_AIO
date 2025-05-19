/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
// #include "arm_math.h"

// #include "usbd_cdc_if.h"

#include "st7789.h"
#include "ft6336.h"
#include "Views.h"
#include "ws2812.h"
#include "mylib.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define DEBUGING
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;
ADC_HandleTypeDef hadc4;
ADC_HandleTypeDef hadc5;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc3;

COMP_HandleTypeDef hcomp2;
COMP_HandleTypeDef hcomp5;

CORDIC_HandleTypeDef hcordic;

DAC_HandleTypeDef hdac1;
DAC_HandleTypeDef hdac2;
DAC_HandleTypeDef hdac3;
DAC_HandleTypeDef hdac4;

I2C_HandleTypeDef hi2c3;

OPAMP_HandleTypeDef hopamp1;
OPAMP_HandleTypeDef hopamp2;
OPAMP_HandleTypeDef hopamp3;
OPAMP_HandleTypeDef hopamp4;
OPAMP_HandleTypeDef hopamp5;
OPAMP_HandleTypeDef hopamp6;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi3_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim17;
TIM_HandleTypeDef htim20;
DMA_HandleTypeDef hdma_tim17_ch1;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM8_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM6_Init(void);
static void MX_DAC4_Init(void);
static void MX_I2C3_Init(void);
static void MX_OPAMP4_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM17_Init(void);
static void MX_TIM20_Init(void);
static void MX_DAC1_Init(void);
static void MX_DAC2_Init(void);
static void MX_TIM7_Init(void);
static void MX_TIM15_Init(void);
static void MX_OPAMP5_Init(void);
static void MX_DAC3_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_ADC3_Init(void);
static void MX_ADC4_Init(void);
static void MX_ADC5_Init(void);
static void MX_COMP2_Init(void);
static void MX_COMP5_Init(void);
static void MX_OPAMP1_Init(void);
static void MX_OPAMP2_Init(void);
static void MX_OPAMP3_Init(void);
static void MX_OPAMP6_Init(void);
static void MX_CORDIC_Init(void);
/* USER CODE BEGIN PFP */

int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 USARTx */
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return (ch);
}




volatile char BUFFER_TEMP[100] = "Hello World\r\n";
volatile uint16_t LCD_BRIGHTNESS = 10000;
volatile uint8_t KEY_PRESSED = 0x79;
uint8_t CURRENT_VIEW = VIEW_INTRO;



uint8_t BUFFER_AFG[24] = {0};


uint32_t BUFFER_DPO1[DPO_DEEP] = {0};
uint32_t BUFFER_DPO2[DPO_DEEP] = {0};

uint32_t Show_Value1[DPO_DEEP] = {0};
uint32_t Show_Value2[DPO_DEEP] = {0};


volatile uint16_t LED_BLINK=0;
uint32_t cnt = 0;

#define KEY_BUF_LEN 3  // 修改这个值可以控制历史长度（例如 5、6）

uint16_t key_buf[KEY_BUF_LEN] = {0};
uint16_t KEY_PROCESS = 0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


DPO_AnalogStates DPO_FE = {
  .CH1_OFFSET = 1024,
  .CH2_OFFSET = 1024,
  .CH1_BIAS   = 2048,
  .CH2_BIAS   = 2048,
  .CH1_AC_DC  = 0,
  .CH2_AC_DC  = 0,
  .DPO_EN1    = 0,
  .DPO_EN2    = 0,
  .TRIG_MODE  = 0,
  .TRIG_LEVEL = 2048,
  .TRIG_FALL_EN = 1,
  .TRIG_RISI_EN = 0,
  .CH_SELECT  = 1,
  .OPAGAIN1 = 0,
  .OPAGAIN2 = 0,
  .Y_ZOOM1   = 32,
  .Y_ZOOM2   = 32,
  .H_ZOOM    = 128,
};

AFG_AnalogStates AFG_FE = {
  .AFG_EN1   = 0,
  .AFG_EN2   = 0,
  .CH1_DC    = 10000,
  .CH2_DC    = 10000,
  .CH1_REF   = 15000,
  .CH2_REF   = 1700,
  .CH1_FREQ  = 10000,
  .CH2_FREQ  = 10000,
  .CH1_TYPE  = 0,
  .CH2_TYPE  = 0,
  .TRIG_MODE = 0,
  .CH_SELECT = 0,
};

//gbr
THEMEs THEME_DPO_1 = {
  .MAIN = 0x00FFFF,
  .WAKE = 0x001F1F,
  .SHUT = 0x000F0F,
};

THEMEs THEME_DPO_2 = {
  .MAIN = 0xFF0000,
  .WAKE = 0x1F0000,
  .SHUT = 0x0F0000,
};

THEMEs THEME_AFG_1 = {
  .MAIN = 0xFFFF00,
  .WAKE = 0x1F1F00,
  .SHUT = 0x000000,
};

THEMEs THEME_AFG_2 = {
  .MAIN = 0x0000FF,
  .WAKE = 0x00001F,
  .SHUT = 0x000000,
};

THEMEs THEME_CONFIG = {0};

void THEME_CONVER_565(THEMEs *theme)
{
  theme->MAIN_565 = convert_24bit_to_16bit(theme->MAIN);
  theme->WAKE_565 = convert_24bit_to_16bit(theme->WAKE);
  theme->SHUT_565 = convert_24bit_to_16bit(theme->SHUT);
}



uint8_t wave_buf[94 * 204 * 2]={0}; // 每段缓冲区


void DrawLine(uint16_t part_w, uint16_t h, uint8_t *buf, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
              uint8_t H, uint8_t L) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy;

    while (1) {
        if (x0 < part_w && y0 < h) {
            uint32_t index = y0 * part_w + x0;
            buf[2 * index]     = H;
            buf[2 * index + 1] = L;
        }
        if (x0 == x1 && y0 == y1) break;
        int16_t e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}


void DrawWaveSegment(uint16_t start_x, uint16_t part_w, uint16_t h, uint16_t x_offset,
                     uint8_t H_DPO1, uint8_t L_DPO1,
                     uint8_t H_DPO2, uint8_t L_DPO2) {
    memset(wave_buf, 0, sizeof(wave_buf));

    for (uint16_t px = 0; px < part_w - 1; px++) {
        uint16_t gx1 = start_x + px;
        uint16_t gx2 = start_x + px + 1;

        uint16_t y11 = Show_Value1[gx1] / 20;
        uint16_t y12 = Show_Value1[gx2] / 20;
        uint16_t y21 = Show_Value2[gx1] / 20;
        uint16_t y22 = Show_Value2[gx2] / 20;


        

                       // 绘制触发电平线（整条横线）
        uint16_t trig_y = DPO_FE.TRIG_LEVEL / 20;




        
        if (DPO_FE.CH_SELECT) {
          if (DPO_FE.DPO_EN2)
          {
            DrawLine(part_w, h, wave_buf, px, y21, px + 1, y22, H_DPO2, L_DPO2);  // 通道2先
          }
           if (DPO_FE.DPO_EN1)
          {
            DrawLine(part_w, h, wave_buf, px, y11, px + 1, y12, H_DPO1, L_DPO1);  // 通道1后
          }

            if (trig_y < h) {
                for (uint16_t px = 0; px < part_w; px++) {
                    uint32_t index = trig_y * part_w + px;
                    wave_buf[2 * index]     = H_DPO1;
                    wave_buf[2 * index + 1] = L_DPO1;
                  }
                }
              } else {

          if (DPO_FE.DPO_EN1)
          {
            DrawLine(part_w, h, wave_buf, px, y11, px + 1, y12, H_DPO1, L_DPO1);  // 通道1后
          }
          if (DPO_FE.DPO_EN2)
          {
            DrawLine(part_w, h, wave_buf, px, y21, px + 1, y22, H_DPO2, L_DPO2);  // 通道2先
          }

            if (trig_y < h) {
                for (uint16_t px = 0; px < part_w; px++) {
                    uint32_t index = trig_y * part_w + px;
                    wave_buf[2 * index]     = H_DPO2;
                    wave_buf[2 * index + 1] = L_DPO2;
                }
            }
        }
    }



    ST7789_SetAddressWindow(x_offset, 18, x_offset + part_w - 1, 18 + h - 1);
    ST7789_WriteData(wave_buf, part_w * h * 2);
}



void ST7789_DrawWave() {
    uint16_t x = 31;
    uint16_t y = 18;
    uint16_t w = 282;
    uint16_t h = 204;

    if (x >= ST7789_WIDTH || y >= ST7789_HEIGHT)
        return;

    if ((x + w - 1) >= ST7789_WIDTH)
        w = ST7789_WIDTH - x;

    if ((y + h - 1) >= ST7789_HEIGHT)
        h = ST7789_HEIGHT - y;

    ST7789_Select();

    // 每段宽度
    uint16_t part_w = w / 3;

    uint8_t H_DPO1 = THEME_DPO_1.MAIN_565 >> 8;
    uint8_t L_DPO1 = THEME_DPO_1.MAIN_565 & 0xFF;

    uint8_t H_DPO2 = THEME_DPO_2.MAIN_565 >> 8;
    uint8_t L_DPO2 = THEME_DPO_2.MAIN_565 & 0xFF;


    ST7789_Select();

    // 绘制段0：左
    DrawWaveSegment(0, part_w, h, x, H_DPO1, L_DPO1, H_DPO2, L_DPO2);

    // 绘制段1：中
    DrawWaveSegment(part_w, part_w, h, x + part_w, H_DPO1, L_DPO1, H_DPO2, L_DPO2);

    // 绘制段2：右
    DrawWaveSegment(2 * part_w, part_w, h, x + 2 * part_w, H_DPO1, L_DPO1, H_DPO2, L_DPO2);

    ST7789_UnSelect();
}


void DPO_FE_Update(void) {
	//SET OFFSET
	HAL_DAC_SetValue(&hdac2, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DPO_FE.CH1_OFFSET);
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DPO_FE.CH2_OFFSET);
  HAL_DAC_SetValue(&hdac4, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DPO_FE.CH1_BIAS);
	HAL_DAC_SetValue(&hdac4, DAC_CHANNEL_2, DAC_ALIGN_12B_R, DPO_FE.CH2_BIAS);
  HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, DPO_FE.TRIG_LEVEL);
	HAL_DAC_SetValue(&hdac3, DAC_CHANNEL_2, DAC_ALIGN_12B_R, DPO_FE.TRIG_LEVEL);

	HAL_DAC_Start(&hdac2, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
  HAL_DAC_Start(&hdac4, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac4, DAC_CHANNEL_2);
  HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
  HAL_DAC_Start(&hdac3, DAC_CHANNEL_2);

  HAL_GPIO_WritePin(DPO_AC1_GPIO_Port,DPO_AC1_Pin, DPO_FE.CH1_AC_DC);
  HAL_GPIO_WritePin(DPO_AC2_GPIO_Port,DPO_AC2_Pin, DPO_FE.CH2_AC_DC);
  // HAL_GPIO_WritePin(DPO_EN1_GPIO_Port,DPO_EN1_Pin, DPO_FE.DPO_EN1);
  // HAL_GPIO_WritePin(DPO_EN2_GPIO_Port,DPO_EN2_Pin, DPO_FE.DPO_EN2);


  switch (DPO_FE.OPAGAIN1)
  {
    case PGA_GAIN_1: 
        hopamp1.Init.Mode       = OPAMP_FOLLOWER_MODE;
        hopamp2.Init.Mode       = OPAMP_FOLLOWER_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_NO;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_NO;
        break;
    case PGA_GAIN_2: 
        hopamp1.Init.Mode       = OPAMP_PGA_MODE;
        hopamp2.Init.Mode       = OPAMP_PGA_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp1.Init.PgaGain    = OPAMP_PGA_GAIN_2_OR_MINUS_1;
        hopamp2.Init.PgaGain    = OPAMP_PGA_GAIN_2_OR_MINUS_1;
        break;
    case PGA_GAIN_4: 
        hopamp1.Init.Mode       = OPAMP_PGA_MODE;
        hopamp2.Init.Mode       = OPAMP_PGA_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp1.Init.PgaGain    = OPAMP_PGA_GAIN_4_OR_MINUS_3;        
        hopamp2.Init.PgaGain    = OPAMP_PGA_GAIN_4_OR_MINUS_3;
        break;
    case PGA_GAIN_8: 
        hopamp1.Init.Mode       = OPAMP_PGA_MODE;
        hopamp2.Init.Mode       = OPAMP_PGA_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp1.Init.PgaGain    = OPAMP_PGA_GAIN_8_OR_MINUS_7;
        hopamp2.Init.PgaGain    = OPAMP_PGA_GAIN_8_OR_MINUS_7;
        break;
    case PGA_GAIN_16: 
        hopamp1.Init.Mode       = OPAMP_PGA_MODE;
        hopamp2.Init.Mode       = OPAMP_PGA_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp1.Init.PgaGain    = OPAMP_PGA_GAIN_16_OR_MINUS_15;
        hopamp2.Init.PgaGain    = OPAMP_PGA_GAIN_16_OR_MINUS_15;
        break;
    case PGA_GAIN_32: 
        hopamp1.Init.Mode       = OPAMP_PGA_MODE;
        hopamp2.Init.Mode       = OPAMP_PGA_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp1.Init.PgaGain    = OPAMP_PGA_GAIN_32_OR_MINUS_31;
        hopamp2.Init.PgaGain    = OPAMP_PGA_GAIN_32_OR_MINUS_31;
        break;
    case PGA_GAIN_64: 
        hopamp1.Init.Mode       = OPAMP_PGA_MODE;
        hopamp2.Init.Mode       = OPAMP_PGA_MODE;
        hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp1.Init.PgaGain    = OPAMP_PGA_GAIN_64_OR_MINUS_63;
        hopamp2.Init.PgaGain    = OPAMP_PGA_GAIN_64_OR_MINUS_63;
 default: 
    break;
  }


  switch (DPO_FE.OPAGAIN2)
  {
    case PGA_GAIN_1: 
        hopamp3.Init.Mode       = OPAMP_FOLLOWER_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_NO;
        break;
    case PGA_GAIN_2: 
        hopamp3.Init.Mode       = OPAMP_PGA_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp3.Init.PgaGain    = OPAMP_PGA_GAIN_2_OR_MINUS_1;
        break;
    case PGA_GAIN_4: 
        hopamp3.Init.Mode       = OPAMP_PGA_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp3.Init.PgaGain    = OPAMP_PGA_GAIN_4_OR_MINUS_3;
        break;
    case PGA_GAIN_8: 
        hopamp3.Init.Mode       = OPAMP_PGA_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp3.Init.PgaGain    = OPAMP_PGA_GAIN_8_OR_MINUS_7;
        break;
    case PGA_GAIN_16: 
        hopamp3.Init.Mode       = OPAMP_PGA_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp3.Init.PgaGain    = OPAMP_PGA_GAIN_16_OR_MINUS_15;
        break;
    case PGA_GAIN_32: 
        hopamp3.Init.Mode       = OPAMP_PGA_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp3.Init.PgaGain    = OPAMP_PGA_GAIN_32_OR_MINUS_31;
        break;
    case PGA_GAIN_64: 
        hopamp3.Init.Mode       = OPAMP_PGA_MODE;
        hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
        hopamp3.Init.PgaGain    = OPAMP_PGA_GAIN_64_OR_MINUS_63;
 default: 
    break;
  }
  HAL_OPAMP_Init(&hopamp1);
  HAL_OPAMP_Init(&hopamp2);
  HAL_OPAMP_Init(&hopamp3);
  HAL_OPAMP_Init(&hopamp6);


if (DPO_FE.CH_SELECT)
  {
    LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP5);
    LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP5);

    if (DPO_FE.TRIG_FALL_EN) 
      LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP2);
    else 
      LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP2);

    if (DPO_FE.TRIG_RISI_EN)  
      LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP2); 
    else 
      LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP2);

      HAL_COMP_Start(&hcomp2);    
    }else{
      LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP2);
      LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP2);

    if (DPO_FE.TRIG_FALL_EN)
      LL_EXTI_EnableFallingTrig_0_31(COMP_EXTI_LINE_COMP5);
    else
      LL_EXTI_DisableFallingTrig_0_31(COMP_EXTI_LINE_COMP5);

    if (DPO_FE.TRIG_RISI_EN)
      LL_EXTI_EnableRisingTrig_0_31(COMP_EXTI_LINE_COMP5); 
    else
      LL_EXTI_DisableRisingTrig_0_31(COMP_EXTI_LINE_COMP5);

      HAL_COMP_Start(&hcomp5);
  }
}




void AFG_Update(void) {
	//SET OFFSET
  TIM2->CCR4 = AFG_FE.CH1_DC;



  if (AFG_FE.AFG_EN1)
  {
  TIM2->CCR3 = AFG_FE.CH1_REF;
  }else
  {
      TIM2->CCR3 = 0;
  }
    
  if (AFG_FE.AFG_EN2)
  {
  TIM15->CCR2 = AFG_FE.CH2_REF;
  }else
  {
  TIM15->CCR2 = 0;
  }


  TIM15->CCR1 = AFG_FE.CH2_DC;
}




void WS2812_VIEW_Update(void) {
  if (DPO_FE.DPO_EN1) {
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_DPO_1);
  } else {
    WS2812_Write_Data(THEME_DPO_1.SHUT, LED_DPO_1);
  }


  if (DPO_FE.DPO_EN2) {
  {
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_DPO_2);
  }
  } else {
    WS2812_Write_Data(THEME_DPO_2.SHUT, LED_DPO_2);
  }


    if (AFG_FE.AFG_EN1)
  {
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_AFG_1U);
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_AFG_1D);  
  } else {
    WS2812_Write_Data(THEME_AFG_1.WAKE, LED_AFG_1U);
    WS2812_Write_Data(THEME_AFG_1.WAKE, LED_AFG_1D);
  }


  if (AFG_FE.AFG_EN2)
  {
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_AFG_2U);
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_AFG_2D);  
  } else {
    WS2812_Write_Data(THEME_AFG_2.WAKE, LED_AFG_2U);
    WS2812_Write_Data(THEME_AFG_2.WAKE, LED_AFG_2D);
  }

  switch (CURRENT_VIEW)
  {
  case VIEW_INTRO:

    break;
    
  case VIEW_DPO1:
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_ENC_3U);
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_ENC_3D);
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_ENC_1U);
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_ENC_1D);
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_ENC_4U);
    WS2812_Write_Data(THEME_DPO_1.MAIN, LED_ENC_4D);
  break;

  case VIEW_DPO2:
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_ENC_3U);
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_ENC_3D);
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_ENC_1U);
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_ENC_1D);
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_ENC_4U);
    WS2812_Write_Data(THEME_DPO_2.MAIN, LED_ENC_4D);
    break;

  case VIEW_AFG1:
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_ENC_3U);
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_ENC_3D);
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_ENC_1U);
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_ENC_1D);
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_ENC_4U);
    WS2812_Write_Data(THEME_AFG_1.MAIN, LED_ENC_4D);
    break;

  case VIEW_AFG2:
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_ENC_3U);
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_ENC_3D);
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_ENC_1U);
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_ENC_1D);
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_ENC_4U);
    WS2812_Write_Data(THEME_AFG_2.MAIN, LED_ENC_4D);
    break;

  case VIEW_CONFIG:
    WS2812_Write_Data(THEME_CONFIG.MAIN, LED_ENC_3U);
    WS2812_Write_Data(THEME_CONFIG.MAIN, LED_ENC_3D);
    WS2812_Write_Data(THEME_CONFIG.MAIN, LED_ENC_1U);
    WS2812_Write_Data(THEME_CONFIG.MAIN, LED_ENC_1D);
    WS2812_Write_Data(THEME_CONFIG.MAIN, LED_ENC_4U);
    WS2812_Write_Data(THEME_CONFIG.MAIN, LED_ENC_4D);
    break;
    

  default:
    break;
  }

    WS2812_Update();
}


void Key_Update(uint16_t KEY_PRESSED)
{
    // 移位
    for (uint8_t i = 0; i < KEY_BUF_LEN - 1; ++i) {
        key_buf[i] = key_buf[i + 1];
    }
    key_buf[KEY_BUF_LEN - 1] = KEY_PRESSED;

    // 判断后 N-1 个相同，且第一个不同
    uint8_t match = 1;
    for (uint8_t i = 1; i < KEY_BUF_LEN - 1; ++i) {
        if (key_buf[i] != key_buf[i + 1]) {
            match = 0;
            break;
        }
    }

    if (match && key_buf[0] != key_buf[1]) {
        KEY_PROCESS = key_buf[1];
    }else{
        KEY_PROCESS = 0x00;
    }
}


void View_ONCE_INTRO(void) {
  ST7789_Fill_Color(0x0000);
  ST7789_DrawImage(80, 0, 160, 160, (uint16_t *)doubao);
  ST7789_WriteString(80, 175, " !\"#$\%&\'\()", Han_Array32, WHITE, BLACK);
  ST7789_WriteString(40, 210, "TOUCH SCREEN TO START", Font_11x18, GRAY, BLACK);
  ST7789_WriteString(0, 230, "https://github.com/Z-o-o-d", Font_7x10, GRAY, BLACK);


}

void View_ONCE_PROC(void) {
  ST7789_DrawFilledRectangle(0, 0, 24, 60,  (AFG_FE.AFG_EN1 ? THEME_AFG_1.MAIN_565 : THEME_AFG_1.WAKE_565));

  ST7789_DrawFilledRectangle(0, 60, 24, 60,  (AFG_FE.AFG_EN2 ? THEME_AFG_2.MAIN_565 : THEME_AFG_2.WAKE_565));


  ST7789_DrawFilledRectangle(0, 120, 24, 60,  (DPO_FE.DPO_EN1 ? THEME_DPO_1.MAIN_565 : THEME_DPO_1.WAKE_565));
  if (DPO_FE.CH1_AC_DC)
  {
    ST7789_WriteString(1, 140, "DC", Font_11x18,  (DPO_FE.DPO_EN1 ? THEME_DPO_1.WAKE_565 : THEME_DPO_1.MAIN_565),  (DPO_FE.DPO_EN1 ? THEME_DPO_1.MAIN_565 : THEME_DPO_1.WAKE_565));
  }
  else
  {
    ST7789_WriteString(1, 140, "AC", Font_11x18,  (DPO_FE.DPO_EN1 ? THEME_DPO_1.WAKE_565 : THEME_DPO_1.MAIN_565),  (DPO_FE.DPO_EN1 ? THEME_DPO_1.MAIN_565 : THEME_DPO_1.WAKE_565));
  }
  
  ST7789_DrawFilledRectangle(0, 180, 24, 60,  (DPO_FE.DPO_EN2 ? THEME_DPO_2.MAIN_565 : THEME_DPO_2.WAKE_565));    
  if (DPO_FE.CH2_AC_DC)
  {
    ST7789_WriteString(1, 200, "DC", Font_11x18,  (DPO_FE.DPO_EN2 ? THEME_DPO_2.WAKE_565 : THEME_DPO_2.MAIN_565), ( DPO_FE.DPO_EN2 ? THEME_DPO_2.MAIN_565 : THEME_DPO_2.WAKE_565));
  }else
  {
    ST7789_WriteString(1, 200, "AC", Font_11x18,  (DPO_FE.DPO_EN2 ? THEME_DPO_2.WAKE_565 : THEME_DPO_2.MAIN_565), ( DPO_FE.DPO_EN2 ? THEME_DPO_2.MAIN_565 : THEME_DPO_2.WAKE_565));
  }


    ST7789_DrawRectangle(25, 12, 319, 227,  (THEME_CONFIG.MAIN_565),4);

  


}

// INTRO PROCESS
void ENC_PROC_INTRO(void) {
	int32_t diff;
	uint32_t current_cnt;

	current_cnt = TIM3->CNT;
	TIM3->CNT=32767;
	diff = (int32_t)(current_cnt - 32767);

	current_cnt = TIM1->CNT;
	TIM1->CNT=32767;
	diff = (int32_t)(current_cnt - 32767);

  current_cnt = TIM4->CNT;
	TIM4->CNT=32767;
	diff = (int32_t)(current_cnt - 32767);
}

void KEY_PROC_INTRO(){
  Key_Update(KEY_PRESSED);
  switch(KEY_PROCESS) {
    case KEY_AFG_1: 
        printf("处理AFG通道1按键\n");
        CURRENT_VIEW   = VIEW_AFG1;
        AFG_FE.AFG_EN1 = 1;
        ST7789_Fill_Color(0x0000);
        THEME_CONFIG = THEME_AFG_1;
        View_ONCE_PROC();
        break;
        
    case KEY_AFG_2: 
        printf("处理AFG通道2按键\n");
        CURRENT_VIEW   = VIEW_AFG2;
        AFG_FE.AFG_EN2 = 1;
        ST7789_Fill_Color(0x0000);
        THEME_CONFIG = THEME_AFG_2;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1: 
        printf("处理DPO通道1按键\n");
        CURRENT_VIEW   = VIEW_DPO1;
        DPO_FE.DPO_EN1 = 1;
        ST7789_Fill_Color(0x0000);
        THEME_CONFIG = THEME_DPO_1;
        DPO_FE.CH_SELECT =1;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2: 
        printf("处理DPO通道2按键\n");
        CURRENT_VIEW   = VIEW_DPO2;
        DPO_FE.DPO_EN2 = 1;
        ST7789_Fill_Color(0x0000);
        THEME_CONFIG = THEME_DPO_2;
        DPO_FE.CH_SELECT =0;

        View_ONCE_PROC();

        break;
        
    case KEY_DPO_1_AC: 
        printf("处理DPO通道1交流耦合按键\n");
        DPO_FE.CH1_AC_DC = !DPO_FE.CH1_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2_AC: 
        printf("处理DPO通道2交流耦合按键\n");
        DPO_FE.CH2_AC_DC = !DPO_FE.CH2_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_RUN_STOP: 
        printf("切换运行/停止状态\n");

        break;
        
    case KEY_SINGLE: 
        printf("触发单次采集\n");

        break;
        
    case KEY_UP: 
        printf("向上导航\n");

        break;
        
    case KEY_DOWN: 
        printf("向下导航\n");

        break;
        
    case KEY_LEFT: 
        printf("向左导航\n");

        break;
        
    case KEY_RIGHT: 
        printf("向右导航\n");

        break;
        
    case KEY_0: 
        printf("数字键 {0} 被按下\n");

        break;
        
    case KEY_1: 
        printf("数字键 {1} 被按下\n");

        break;
        
    case KEY_2: 
        printf("数字键 {2} 被按下\n");

        break;
        
    case KEY_3: 
        printf("数字键 {3} 被按下\n");

        break;
        
    case KEY_4: 
        printf("数字键 {4} 被按下\n");

        break;
        
    case KEY_5: 
        printf("数字键 {5} 被按下\n");

        break;
        
    case KEY_6: 
        printf("数字键 {6} 被按下\n");
        break;
        
    case KEY_7: 
        printf("数字键 {7} 被按下\n");
        break;
        
    case KEY_8: 
        printf("数字键 {8} 被按下\n");
        break;
        
    case KEY_9: 
        printf("数字键 {9} 被按下\n");
        break;
        
    case KEY_INVERSE: 
        printf("切换显示反转\n");
        break;
        
    case KEY_POINT: 
        printf("输入小数点\n");
        break;
        
    case KEY_ENTER: 
        printf("确认输入\n");
        break;
        
    case KEY_ENC3: 
        printf("编码器3被按下\n");
        break;
        
    case KEY_ENC1: 
        printf("编码器1被按下\n");
        break;
        
    case KEY_ENC4: 
        printf("编码器4被按下\n");
        break;
        
    default: 
        break;
      }
      
    }
    

    // DPO1 PROCESS
void ENC_PROC_DPO1(void) {
	int32_t diff;
	uint32_t current_cnt;

	current_cnt = TIM3->CNT;
	TIM3->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
  handle_overflow(&DPO_FE.H_ZOOM,diff,0,64);

	current_cnt = TIM1->CNT;
	TIM1->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
        DPO_FE.H_ZOOM+=diff;

	current_cnt = TIM4->CNT;
	TIM4->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
  handle_overflow(&DPO_FE.TRIG_LEVEL,5*diff,0,4096);


}
void KEY_PROC_DPO1(){
  Key_Update(KEY_PRESSED);
  switch(KEY_PROCESS) {
    case KEY_AFG_1: 
        printf("处理AFG通道1按键\n");
        CURRENT_VIEW     = VIEW_AFG1;
        AFG_FE.AFG_EN1   = 1;
        THEME_CONFIG     = THEME_AFG_1;
        AFG_FE.CH_SELECT = 1;
        View_ONCE_PROC();
        break;
        
    case KEY_AFG_2: 
        printf("处理AFG通道2按键\n");
        CURRENT_VIEW     = VIEW_AFG2;
        AFG_FE.AFG_EN2   = 1;
        THEME_CONFIG     = THEME_AFG_2;
        AFG_FE.CH_SELECT = 0;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1: 
        printf("处理DPO通道1按键\n");
        CURRENT_VIEW     = VIEW_DPO1;
        DPO_FE.DPO_EN1   = !DPO_FE.DPO_EN1;
        DPO_FE.CH_SELECT = 1;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2: 
        printf("处理DPO通道2按键\n");
        CURRENT_VIEW     = VIEW_DPO2;
        DPO_FE.DPO_EN2   = 1;
        THEME_CONFIG     = THEME_DPO_2;
        DPO_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1_AC: 
        printf("处理DPO通道1交流耦合按键\n");
        DPO_FE.CH1_AC_DC = !DPO_FE.CH1_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2_AC: 
        printf("处理DPO通道2交流耦合按键\n");
        DPO_FE.CH2_AC_DC = !DPO_FE.CH2_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_RUN_STOP: 
        printf("切换运行/停止状态\n");

        break;
        
    case KEY_SINGLE: 
        printf("触发单次采集\n");

        break;
        
    case KEY_UP: 
        printf("向上导航\n");

        break;
        
    case KEY_DOWN: 
        printf("向下导航\n");

        break;
        
    case KEY_LEFT: 
        printf("向左导航\n");

        break;
        
    case KEY_RIGHT: 
        printf("向右导航\n");

        break;
        
    case KEY_0: 
        printf("数字键 {0} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_1;
        break;
        
    case KEY_1: 
        printf("数字键 {1} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_2;
        break;
        
    case KEY_2: 
        printf("数字键 {2} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_4;
        break;
        
    case KEY_3: 
        printf("数字键 {3} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_8;
        break;
        
    case KEY_4: 
        printf("数字键 {4} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_16;
        break;
        
    case KEY_5: 
        printf("数字键 {5} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_32;
        break;
        
    case KEY_6: 
        printf("数字键 {6} 被按下\n");
        DPO_FE.OPAGAIN1 = PGA_GAIN_64;
        break;
        
    case KEY_7: 
        printf("数字键 {7} 被按下\n");
        break;
        
    case KEY_8: 
        printf("数字键 {8} 被按下\n");
        break;
        
    case KEY_9: 
        printf("数字键 {9} 被按下\n");
        break;
        
    case KEY_INVERSE: 
        printf("切换显示反转\n");
        break;
        
    case KEY_POINT: 
        printf("输入小数点\n");
        break;
        
    case KEY_ENTER: 
        printf("确认输入\n");
        break;
        
    case KEY_ENC3: 
        printf("编码器3被按下\n");
        break;
        
    case KEY_ENC1: 
        printf("编码器1被按下\n");
        break;
        
    case KEY_ENC4: 
        printf("编码器4被按下\n");
        break;
        
    default: 
        break;
  }

}

  // DPO2 PROCESS
void ENC_PROC_DPO2(void) {
	int32_t diff;
	uint32_t current_cnt;

	current_cnt = TIM3->CNT;
	TIM3->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);

	current_cnt = TIM1->CNT;
	TIM1->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
        DPO_FE.H_ZOOM+=diff;


	current_cnt = TIM4->CNT;
	TIM4->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
    handle_overflow(&DPO_FE.TRIG_LEVEL,5*diff,0,4096);

}
void KEY_PROC_DPO2(){
  Key_Update(KEY_PRESSED);
  switch(KEY_PROCESS) {
    case KEY_AFG_1: 
        printf("处理AFG通道1按键\n");
        CURRENT_VIEW     = VIEW_AFG1;
        AFG_FE.AFG_EN1   = 1;
        THEME_CONFIG     = THEME_AFG_1;
        AFG_FE.CH_SELECT = 1;

        View_ONCE_PROC();
        break;
        
    case KEY_AFG_2: 
        printf("处理AFG通道2按键\n");
        CURRENT_VIEW     = VIEW_AFG2;
        AFG_FE.AFG_EN2   = 1;
        THEME_CONFIG     = THEME_AFG_2;
        AFG_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1: 
        printf("处理DPO通道1按键\n");
        CURRENT_VIEW     = VIEW_DPO1;
        DPO_FE.DPO_EN1   = 1;
        THEME_CONFIG     = THEME_DPO_1;
        DPO_FE.CH_SELECT = 1;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2: 
        printf("处理DPO通道2按键\n");
        CURRENT_VIEW     = VIEW_DPO2;
        DPO_FE.DPO_EN2   = !DPO_FE.DPO_EN2;
        DPO_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1_AC: 
        printf("处理DPO通道1交流耦合按键\n");
        DPO_FE.CH1_AC_DC = !DPO_FE.CH1_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2_AC: 
        printf("处理DPO通道2交流耦合按键\n");
        DPO_FE.CH2_AC_DC = !DPO_FE.CH2_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_RUN_STOP: 
        printf("切换运行/停止状态\n");

        break;
        
    case KEY_SINGLE: 
        printf("触发单次采集\n");

        break;
        
    case KEY_UP: 
        printf("向上导航\n");

        break;
        
    case KEY_DOWN: 
        printf("向下导航\n");

        break;
        
    case KEY_LEFT: 
        printf("向左导航\n");

        break;
        
    case KEY_RIGHT: 
        printf("向右导航\n");

        break;
        
    case KEY_0: 
        printf("数字键 {0} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_1;
        break;
        
    case KEY_1: 
        printf("数字键 {1} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_2;
        break;
        
    case KEY_2: 
        printf("数字键 {2} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_4;
        break;
        
    case KEY_3: 
        printf("数字键 {3} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_8;
        break;
        
    case KEY_4: 
        printf("数字键 {4} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_16;
        break;
        
    case KEY_5: 
        printf("数字键 {5} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_32;
        break;
        
    case KEY_6: 
        printf("数字键 {6} 被按下\n");
        DPO_FE.OPAGAIN2 = PGA_GAIN_64;
        break;
        
    case KEY_7: 
        printf("数字键 {7} 被按下\n");
        break;
        
    case KEY_8: 
        printf("数字键 {8} 被按下\n");
        break;
        
    case KEY_9: 
        printf("数字键 {9} 被按下\n");
        break;
        
    case KEY_INVERSE: 
        printf("切换显示反转\n");
        break;
        
    case KEY_POINT: 
        printf("输入小数点\n");
        break;
        
    case KEY_ENTER: 
        printf("确认输入\n");
        break;
        
    case KEY_ENC3: 
        printf("编码器3被按下\n");
        break;
        
    case KEY_ENC1: 
        printf("编码器1被按下\n");
        break;
        
    case KEY_ENC4: 
        printf("编码器4被按下\n");
        break;
        
    default: 
        break;
  }

}

  // AFG1 PROCESS
void ENC_PROC_AFG1(void) {
	int32_t diff;
	uint32_t current_cnt;

	current_cnt = TIM3->CNT;
	TIM3->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
    AFG_FE.CH1_REF+=100*diff;

	current_cnt = TIM1->CNT;
	TIM1->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
    AFG_FE.CH1_REF+=10*diff;


	current_cnt = TIM4->CNT;
	TIM4->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
      AFG_FE.CH1_REF+=diff;

}
void KEY_PROC_AFG1(){
  Key_Update(KEY_PRESSED);
  switch(KEY_PROCESS) {
    case KEY_AFG_1: 
        printf("处理AFG通道1按键\n");
        CURRENT_VIEW     = VIEW_AFG1;
        AFG_FE.AFG_EN1   = !AFG_FE.AFG_EN1 ;
        AFG_FE.CH_SELECT = 1;

        View_ONCE_PROC();
        break;
        
    case KEY_AFG_2: 
        printf("处理AFG通道2按键\n");
        CURRENT_VIEW     = VIEW_AFG2;
        AFG_FE.AFG_EN2   = 1;
        THEME_CONFIG     = THEME_AFG_2;
        AFG_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1: 
        printf("处理DPO通道1按键\n");
        CURRENT_VIEW     = VIEW_DPO1;
        DPO_FE.DPO_EN1   = 1;
        THEME_CONFIG     = THEME_DPO_1;
        DPO_FE.CH_SELECT = 1;

        View_ONCE_PROC();        
        break;
        
    case KEY_DPO_2: 
        printf("处理DPO通道2按键\n");
        CURRENT_VIEW     = VIEW_DPO2;
        DPO_FE.DPO_EN2   = 1;
        THEME_CONFIG     = THEME_DPO_2;
        DPO_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1_AC: 
        printf("处理DPO通道1交流耦合按键\n");
        DPO_FE.CH1_AC_DC = !DPO_FE.CH1_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2_AC: 
        printf("处理DPO通道2交流耦合按键\n");
        DPO_FE.CH2_AC_DC = !DPO_FE.CH2_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_RUN_STOP: 
        printf("切换运行/停止状态\n");

        break;
        
    case KEY_SINGLE: 
        printf("触发单次采集\n");

        break;
        
    case KEY_UP: 
        printf("向上导航\n");

        break;
        
    case KEY_DOWN: 
        printf("向下导航\n");

        break;
        
    case KEY_LEFT: 
        printf("向左导航\n");

        break;
        
    case KEY_RIGHT: 
        printf("向右导航\n");

        break;
        
    case KEY_0: 
        printf("数字键 {0} 被按下\n");

        break;
        
    case KEY_1: 
        printf("数字键 {1} 被按下\n");

        break;
        
    case KEY_2: 
        printf("数字键 {2} 被按下\n");

        break;
        
    case KEY_3: 
        printf("数字键 {3} 被按下\n");

        break;
        
    case KEY_4: 
        printf("数字键 {4} 被按下\n");

        break;
        
    case KEY_5: 
        printf("数字键 {5} 被按下\n");

        break;
        
    case KEY_6: 
        printf("数字键 {6} 被按下\n");
        break;
        
    case KEY_7: 
        printf("数字键 {7} 被按下\n");
        break;
        
    case KEY_8: 
        printf("数字键 {8} 被按下\n");
        break;
        
    case KEY_9: 
        printf("数字键 {9} 被按下\n");
        break;
        
    case KEY_INVERSE: 
        printf("切换显示反转\n");
        break;
        
    case KEY_POINT: 
        printf("输入小数点\n");
        break;
        
    case KEY_ENTER: 
        printf("确认输入\n");
        break;
        
    case KEY_ENC3: 
        printf("编码器3被按下\n");
        break;
        
    case KEY_ENC1: 
        printf("编码器1被按下\n");
        break;
        
    case KEY_ENC4: 
        printf("编码器4被按下\n");
        break;
        
    default: 
        break;
  }

}

    // AFG2 PROCESS
void ENC_PROC_AFG2(void) {
	int32_t diff;
	uint32_t current_cnt;

	current_cnt = TIM3->CNT;
	TIM3->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
      AFG_FE.CH2_REF+=100*diff;

	current_cnt = TIM1->CNT;
	TIM1->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
      AFG_FE.CH2_REF+=10*diff;


	current_cnt = TIM4->CNT;
	TIM4->CNT   = 32767;
	diff        = (int32_t)(current_cnt - 32767);
        AFG_FE.CH2_REF+=diff;

}
void KEY_PROC_AFG2(){
  Key_Update(KEY_PRESSED);
  switch(KEY_PROCESS) {
    case KEY_AFG_1: 
        printf("处理AFG通道1按键\n");
        CURRENT_VIEW     = VIEW_AFG1;
        AFG_FE.AFG_EN1   = 1;
        THEME_CONFIG     = THEME_AFG_1;
        AFG_FE.CH_SELECT = 1;

        View_ONCE_PROC();
        break;
        
    case KEY_AFG_2: 
        printf("处理AFG通道2按键\n");
        CURRENT_VIEW     = VIEW_AFG2;
        AFG_FE.AFG_EN2   = !AFG_FE.AFG_EN2;
        AFG_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1: 
        printf("处理DPO通道1按键\n");
        CURRENT_VIEW     = VIEW_DPO1;
        DPO_FE.DPO_EN1   = 1;
        THEME_CONFIG     = THEME_DPO_1;
        DPO_FE.CH_SELECT = 1;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2: 
        printf("处理DPO通道2按键\n");
        CURRENT_VIEW     = VIEW_DPO2;
        DPO_FE.DPO_EN2   = 1;
        THEME_CONFIG     = THEME_DPO_2;
        DPO_FE.CH_SELECT = 0;

        View_ONCE_PROC();
        break;
        
    case KEY_DPO_1_AC: 
        printf("处理DPO通道1交流耦合按键\n");
        DPO_FE.CH1_AC_DC = !DPO_FE.CH1_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_DPO_2_AC: 
        printf("处理DPO通道2交流耦合按键\n");
        DPO_FE.CH2_AC_DC = !DPO_FE.CH2_AC_DC;
        View_ONCE_PROC();
        break;
        
    case KEY_RUN_STOP: 
        printf("切换运行/停止状态\n");

        break;
        
    case KEY_SINGLE: 
        printf("触发单次采集\n");

        break;
        
    case KEY_UP: 
        printf("向上导航\n");

        break;
        
    case KEY_DOWN: 
        printf("向下导航\n");

        break;
        
    case KEY_LEFT: 
        printf("向左导航\n");

        break;
        
    case KEY_RIGHT: 
        printf("向右导航\n");

        break;
        
    case KEY_0: 
        printf("数字键 {0} 被按下\n");

        break;
        
    case KEY_1: 
        printf("数字键 {1} 被按下\n");

        break;
        
    case KEY_2: 
        printf("数字键 {2} 被按下\n");

        break;
        
    case KEY_3: 
        printf("数字键 {3} 被按下\n");

        break;
        
    case KEY_4: 
        printf("数字键 {4} 被按下\n");

        break;
        
    case KEY_5: 
        printf("数字键 {5} 被按下\n");

        break;
        
    case KEY_6: 
        printf("数字键 {6} 被按下\n");
        break;
        
    case KEY_7: 
        printf("数字键 {7} 被按下\n");
        break;
        
    case KEY_8: 
        printf("数字键 {8} 被按下\n");
        break;
        
    case KEY_9: 
        printf("数字键 {9} 被按下\n");
        break;
        
    case KEY_INVERSE: 
        printf("切换显示反转\n");
        break;
        
    case KEY_POINT: 
        printf("输入小数点\n");
        break;
        
    case KEY_ENTER: 
        printf("确认输入\n");
        break;
        
    case KEY_ENC3: 
        printf("编码器3被按下\n");
        break;
        
    case KEY_ENC1: 
        printf("编码器1被按下\n");
        break;
        
    case KEY_ENC4: 
        printf("编码器4被按下\n");
        break;
        
    default: 
        break;
  }

}


void VIEW_UPDATE(void) {
  switch (CURRENT_VIEW)
  {
  case VIEW_INTRO:
    KEY_PROC_INTRO();
    ENC_PROC_INTRO();
    break;
  case VIEW_DPO1: 
    KEY_PROC_DPO1();
    ENC_PROC_DPO1();
    break;
  case VIEW_DPO2: 
    KEY_PROC_DPO2();
    ENC_PROC_DPO2();
    break;
  case VIEW_AFG1:
    KEY_PROC_AFG1();
    ENC_PROC_AFG1();
    break;
  case VIEW_AFG2:
    KEY_PROC_AFG2();
    ENC_PROC_AFG2();
    break;
  default:
    break;
  }
}



void HID_PROCESS(void) {
	//SET OFFSET

  FT6336_GetTouchPoint(&TouchPoints);    
  HAL_I2C_Master_Receive(&hi2c3, 0x49, &KEY_PRESSED,1, 1000);
  #ifdef DEBUGING
    // printf("1_x,1_y,2_x,2_y:%d,%d,%d,%d,0x%x\r\n", TouchPoints.point1_x,TouchPoints.point1_y,TouchPoints.point2_x,TouchPoints.point2_y,KEY_PRESSED);
  #endif


  // sprintf(&BUFFER_TEMP,"KEY:0x%x",KEY_PRESSED);
  // ST7789_WriteString(200, 10, &BUFFER_TEMP, Font_11x18, WHITE, BLACK);
  // sprintf(&BUFFER_TEMP,"ENC3:%5d",TIM3->CNT);
  // ST7789_WriteString(200, 30, &BUFFER_TEMP, Font_11x18, WHITE, BLACK);
  // sprintf(&BUFFER_TEMP,"ENC1:%5d",TIM1->CNT);
  // ST7789_WriteString(200, 50, &BUFFER_TEMP, Font_11x18, WHITE, BLACK);
  // sprintf(&BUFFER_TEMP,"ENC4:%5d",TIM4->CNT);
  // ST7789_WriteString(200, 70, &BUFFER_TEMP, Font_11x18, WHITE, BLACK);

  VIEW_UPDATE();
  WS2812_VIEW_Update();

}



void LCD_BRIGHT(uint16_t bright){
  TIM8->CCR4 = bright;
}




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USB_Device_Init();
  MX_TIM6_Init();
  MX_DAC4_Init();
  MX_I2C3_Init();
  MX_OPAMP4_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM17_Init();
  MX_TIM20_Init();
  MX_DAC1_Init();
  MX_DAC2_Init();
  MX_TIM7_Init();
  MX_TIM15_Init();
  MX_OPAMP5_Init();
  MX_DAC3_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_ADC5_Init();
  MX_COMP2_Init();
  MX_COMP5_Init();
  MX_OPAMP1_Init();
  MX_OPAMP2_Init();
  MX_OPAMP3_Init();
  MX_OPAMP6_Init();
  MX_CORDIC_Init();
  /* USER CODE BEGIN 2 */



  HAL_TIM_PWM_Start(&htim20, TIM_CHANNEL_2);

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);

  

  
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);



    printf("hello world\r\n");
  
  FT6336_Init();
  ST7789_Init();
  LCD_BRIGHT(LCD_BRIGHTNESS);
  HAL_I2C_Master_Transmit(&hi2c3, 0x48, &KEY_PRESSED,1, 1000);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&BUFFER_DPO1, DPO_DEEP);
  HAL_ADC_Start_DMA(&hadc3, (uint32_t*)&BUFFER_DPO2, DPO_DEEP);


  HAL_OPAMP_Start(&hopamp4);
  HAL_OPAMP_Start(&hopamp5);

  
  HAL_OPAMP_Start(&hopamp1);
  HAL_OPAMP_Start(&hopamp2);
  HAL_OPAMP_Start(&hopamp3);
  HAL_OPAMP_Start(&hopamp6);



  HAL_TIM_Base_Start(&htim6);
  HAL_TIM_Base_Start(&htim7);

  
  THEME_CONVER_565(&THEME_AFG_1);
  THEME_CONVER_565(&THEME_AFG_2);
  THEME_CONVER_565(&THEME_DPO_1);
  THEME_CONVER_565(&THEME_DPO_2);
  

  HAL_GPIO_WritePin(DPO_EN1_GPIO_Port,DPO_EN1_Pin, 1);
  HAL_GPIO_WritePin(DPO_EN2_GPIO_Port,DPO_EN2_Pin, 1);

  WS2812_Set_All(0x000010);
  HAL_TIMEx_PWMN_Start(&htim8,TIM_CHANNEL_4);
  View_ONCE_INTRO();
  WS2812_RunningHorse(100,100);
  View_ONCE_PROC();
  
  HAL_COMP_Start(&hcomp2);
  HAL_COMP_Start(&hcomp5);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    cnt+=1;
    DPO_FE_Update();
    AFG_Update();
    HID_PROCESS();
    WS2812_VIEW_Update();


  HAL_SPI_Transmit(&hspi3, (uint8_t*)&BUFFER_AFG, DPO_DEEP, 1000);
  uint32_t TIRG_P =  hadc1.DMA_Handle->Instance->CNDTR;
    uint32_t Show_Value[DPO_DEEP] = {0};
  uint32_t split_index = DPO_DEEP - TIRG_P;
  for (size_t i = 0; i < DPO_DEEP; i++)
  {
      size_t src_index = (i + split_index) % DPO_DEEP;
      Show_Value1[i] = BUFFER_DPO1[src_index];
      Show_Value2[i] = BUFFER_DPO2[src_index];
  }
  ST7789_DrawWave();
  TIM6->CR1 |= TIM_CR1_CEN;  // 设置CEN位来启动定时器
  


  sprintf(&BUFFER_TEMP,"REF1:%5d,REF2:%5d,H_ZOOM:%5d", AFG_FE.CH1_REF , AFG_FE.CH2_REF,DPO_FE.H_ZOOM );
  ST7789_WriteString(30, 0, &BUFFER_TEMP, Font_7x10, WHITE, BLACK);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV6;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.GainCompensation = 0;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T6_TRGO;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VOPAMP1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.GainCompensation = 0;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc2.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VOPAMP2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.GainCompensation = 0;
  hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc3.Init.LowPowerAutoWait = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T6_TRGO;
  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc3.Init.DMAContinuousRequests = ENABLE;
  hadc3.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc3.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc3, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VOPAMP3_ADC3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}

/**
  * @brief ADC4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC4_Init(void)
{

  /* USER CODE BEGIN ADC4_Init 0 */

  /* USER CODE END ADC4_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC4_Init 1 */

  /* USER CODE END ADC4_Init 1 */

  /** Common config
  */
  hadc4.Instance = ADC4;
  hadc4.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc4.Init.Resolution = ADC_RESOLUTION_12B;
  hadc4.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc4.Init.GainCompensation = 0;
  hadc4.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc4.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc4.Init.LowPowerAutoWait = DISABLE;
  hadc4.Init.ContinuousConvMode = DISABLE;
  hadc4.Init.NbrOfConversion = 1;
  hadc4.Init.DiscontinuousConvMode = DISABLE;
  hadc4.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc4.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc4.Init.DMAContinuousRequests = DISABLE;
  hadc4.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc4.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VOPAMP6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC4_Init 2 */

  /* USER CODE END ADC4_Init 2 */

}

/**
  * @brief ADC5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC5_Init(void)
{

  /* USER CODE BEGIN ADC5_Init 0 */

  /* USER CODE END ADC5_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC5_Init 1 */

  /* USER CODE END ADC5_Init 1 */

  /** Common config
  */
  hadc5.Instance = ADC5;
  hadc5.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc5.Init.Resolution = ADC_RESOLUTION_12B;
  hadc5.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc5.Init.GainCompensation = 0;
  hadc5.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc5.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc5.Init.LowPowerAutoWait = DISABLE;
  hadc5.Init.ContinuousConvMode = DISABLE;
  hadc5.Init.NbrOfConversion = 1;
  hadc5.Init.DiscontinuousConvMode = DISABLE;
  hadc5.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc5.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc5.Init.DMAContinuousRequests = DISABLE;
  hadc5.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc5.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc5) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VBAT;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc5, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC5_Init 2 */

  /* USER CODE END ADC5_Init 2 */

}

/**
  * @brief COMP2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_COMP2_Init(void)
{

  /* USER CODE BEGIN COMP2_Init 0 */

  /* USER CODE END COMP2_Init 0 */

  /* USER CODE BEGIN COMP2_Init 1 */

  /* USER CODE END COMP2_Init 1 */
  hcomp2.Instance = COMP2;
  hcomp2.Init.InputPlus = COMP_INPUT_PLUS_IO1;
  hcomp2.Init.InputMinus = COMP_INPUT_MINUS_DAC3_CH2;
  hcomp2.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp2.Init.Hysteresis = COMP_HYSTERESIS_20MV;
  hcomp2.Init.BlankingSrce = COMP_BLANKINGSRC_NONE;
  hcomp2.Init.TriggerMode = COMP_TRIGGERMODE_IT_RISING_FALLING;
  if (HAL_COMP_Init(&hcomp2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP2_Init 2 */

  /* USER CODE END COMP2_Init 2 */

}

/**
  * @brief COMP5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_COMP5_Init(void)
{

  /* USER CODE BEGIN COMP5_Init 0 */

  /* USER CODE END COMP5_Init 0 */

  /* USER CODE BEGIN COMP5_Init 1 */

  /* USER CODE END COMP5_Init 1 */
  hcomp5.Instance = COMP5;
  hcomp5.Init.InputPlus = COMP_INPUT_PLUS_IO1;
  hcomp5.Init.InputMinus = COMP_INPUT_MINUS_DAC1_CH2;
  hcomp5.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp5.Init.Hysteresis = COMP_HYSTERESIS_20MV;
  hcomp5.Init.BlankingSrce = COMP_BLANKINGSRC_NONE;
  hcomp5.Init.TriggerMode = COMP_TRIGGERMODE_IT_RISING_FALLING;
  if (HAL_COMP_Init(&hcomp5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP5_Init 2 */

  /* USER CODE END COMP5_Init 2 */

}

/**
  * @brief CORDIC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CORDIC_Init(void)
{

  /* USER CODE BEGIN CORDIC_Init 0 */

  /* USER CODE END CORDIC_Init 0 */

  /* USER CODE BEGIN CORDIC_Init 1 */

  /* USER CODE END CORDIC_Init 1 */
  hcordic.Instance = CORDIC;
  if (HAL_CORDIC_Init(&hcordic) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CORDIC_Init 2 */

  /* USER CODE END CORDIC_Init 2 */

}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */

  /** DAC Initialization
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_AUTOMATIC;
  sConfig.DAC_DMADoubleDataMode = DISABLE;
  sConfig.DAC_SignedFormat = DISABLE;
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
  sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_EXTERNAL;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_INTERNAL;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief DAC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC2_Init(void)
{

  /* USER CODE BEGIN DAC2_Init 0 */

  /* USER CODE END DAC2_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC2_Init 1 */

  /* USER CODE END DAC2_Init 1 */

  /** DAC Initialization
  */
  hdac2.Instance = DAC2;
  if (HAL_DAC_Init(&hdac2) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_AUTOMATIC;
  sConfig.DAC_DMADoubleDataMode = DISABLE;
  sConfig.DAC_SignedFormat = DISABLE;
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
  sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_EXTERNAL;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac2, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC2_Init 2 */

  /* USER CODE END DAC2_Init 2 */

}

/**
  * @brief DAC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC3_Init(void)
{

  /* USER CODE BEGIN DAC3_Init 0 */

  /* USER CODE END DAC3_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC3_Init 1 */

  /* USER CODE END DAC3_Init 1 */

  /** DAC Initialization
  */
  hdac3.Instance = DAC3;
  if (HAL_DAC_Init(&hdac3) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_AUTOMATIC;
  sConfig.DAC_DMADoubleDataMode = DISABLE;
  sConfig.DAC_SignedFormat = DISABLE;
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_INTERNAL;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac3, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac3, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC3_Init 2 */

  /* USER CODE END DAC3_Init 2 */

}

/**
  * @brief DAC4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC4_Init(void)
{

  /* USER CODE BEGIN DAC4_Init 0 */

  /* USER CODE END DAC4_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC4_Init 1 */

  /* USER CODE END DAC4_Init 1 */

  /** DAC Initialization
  */
  hdac4.Instance = DAC4;
  if (HAL_DAC_Init(&hdac4) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_HighFrequency = DAC_HIGH_FREQUENCY_INTERFACE_MODE_AUTOMATIC;
  sConfig.DAC_DMADoubleDataMode = DISABLE;
  sConfig.DAC_SignedFormat = DISABLE;
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
  sConfig.DAC_Trigger2 = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_INTERNAL;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac4, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac4, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC4_Init 2 */

  /* USER CODE END DAC4_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x40621236;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief OPAMP1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OPAMP1_Init(void)
{

  /* USER CODE BEGIN OPAMP1_Init 0 */

  /* USER CODE END OPAMP1_Init 0 */

  /* USER CODE BEGIN OPAMP1_Init 1 */

  /* USER CODE END OPAMP1_Init 1 */
  hopamp1.Instance = OPAMP1;
  hopamp1.Init.PowerMode = OPAMP_POWERMODE_HIGHSPEED;
  hopamp1.Init.Mode = OPAMP_PGA_MODE;
  hopamp1.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_IO2;
  hopamp1.Init.InternalOutput = ENABLE;
  hopamp1.Init.TimerControlledMuxmode = OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE;
  hopamp1.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
  hopamp1.Init.PgaGain = OPAMP_PGA_GAIN_2_OR_MINUS_1;
  hopamp1.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
  if (HAL_OPAMP_Init(&hopamp1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OPAMP1_Init 2 */

  /* USER CODE END OPAMP1_Init 2 */

}

/**
  * @brief OPAMP2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OPAMP2_Init(void)
{

  /* USER CODE BEGIN OPAMP2_Init 0 */

  /* USER CODE END OPAMP2_Init 0 */

  /* USER CODE BEGIN OPAMP2_Init 1 */

  /* USER CODE END OPAMP2_Init 1 */
  hopamp2.Instance = OPAMP2;
  hopamp2.Init.PowerMode = OPAMP_POWERMODE_HIGHSPEED;
  hopamp2.Init.Mode = OPAMP_PGA_MODE;
  hopamp2.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_IO0;
  hopamp2.Init.InternalOutput = ENABLE;
  hopamp2.Init.TimerControlledMuxmode = OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE;
  hopamp2.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
  hopamp2.Init.PgaGain = OPAMP_PGA_GAIN_2_OR_MINUS_1;
  hopamp2.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
  if (HAL_OPAMP_Init(&hopamp2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OPAMP2_Init 2 */

  /* USER CODE END OPAMP2_Init 2 */

}

/**
  * @brief OPAMP3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OPAMP3_Init(void)
{

  /* USER CODE BEGIN OPAMP3_Init 0 */

  /* USER CODE END OPAMP3_Init 0 */

  /* USER CODE BEGIN OPAMP3_Init 1 */

  /* USER CODE END OPAMP3_Init 1 */
  hopamp3.Instance = OPAMP3;
  hopamp3.Init.PowerMode = OPAMP_POWERMODE_HIGHSPEED;
  hopamp3.Init.Mode = OPAMP_PGA_MODE;
  hopamp3.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_IO1;
  hopamp3.Init.InternalOutput = ENABLE;
  hopamp3.Init.TimerControlledMuxmode = OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE;
  hopamp3.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
  hopamp3.Init.PgaGain = OPAMP_PGA_GAIN_2_OR_MINUS_1;
  hopamp3.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
  if (HAL_OPAMP_Init(&hopamp3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OPAMP3_Init 2 */

  /* USER CODE END OPAMP3_Init 2 */

}

/**
  * @brief OPAMP4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OPAMP4_Init(void)
{

  /* USER CODE BEGIN OPAMP4_Init 0 */

  /* USER CODE END OPAMP4_Init 0 */

  /* USER CODE BEGIN OPAMP4_Init 1 */

  /* USER CODE END OPAMP4_Init 1 */
  hopamp4.Instance = OPAMP4;
  hopamp4.Init.PowerMode = OPAMP_POWERMODE_HIGHSPEED;
  hopamp4.Init.Mode = OPAMP_FOLLOWER_MODE;
  hopamp4.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_DAC;
  hopamp4.Init.InternalOutput = DISABLE;
  hopamp4.Init.TimerControlledMuxmode = OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE;
  hopamp4.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
  if (HAL_OPAMP_Init(&hopamp4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OPAMP4_Init 2 */

  /* USER CODE END OPAMP4_Init 2 */

}

/**
  * @brief OPAMP5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OPAMP5_Init(void)
{

  /* USER CODE BEGIN OPAMP5_Init 0 */

  /* USER CODE END OPAMP5_Init 0 */

  /* USER CODE BEGIN OPAMP5_Init 1 */

  /* USER CODE END OPAMP5_Init 1 */
  hopamp5.Instance = OPAMP5;
  hopamp5.Init.PowerMode = OPAMP_POWERMODE_NORMALSPEED;
  hopamp5.Init.Mode = OPAMP_FOLLOWER_MODE;
  hopamp5.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_DAC;
  hopamp5.Init.InternalOutput = DISABLE;
  hopamp5.Init.TimerControlledMuxmode = OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE;
  hopamp5.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
  if (HAL_OPAMP_Init(&hopamp5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OPAMP5_Init 2 */

  /* USER CODE END OPAMP5_Init 2 */

}

/**
  * @brief OPAMP6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OPAMP6_Init(void)
{

  /* USER CODE BEGIN OPAMP6_Init 0 */

  /* USER CODE END OPAMP6_Init 0 */

  /* USER CODE BEGIN OPAMP6_Init 1 */

  /* USER CODE END OPAMP6_Init 1 */
  hopamp6.Instance = OPAMP6;
  hopamp6.Init.PowerMode = OPAMP_POWERMODE_HIGHSPEED;
  hopamp6.Init.Mode = OPAMP_PGA_MODE;
  hopamp6.Init.NonInvertingInput = OPAMP_NONINVERTINGINPUT_IO2;
  hopamp6.Init.InternalOutput = ENABLE;
  hopamp6.Init.TimerControlledMuxmode = OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE;
  hopamp6.Init.PgaConnect = OPAMP_PGA_CONNECT_INVERTINGINPUT_IO0_BIAS;
  hopamp6.Init.PgaGain = OPAMP_PGA_GAIN_2_OR_MINUS_1;
  hopamp6.Init.UserTrimming = OPAMP_TRIMMING_FACTORY;
  if (HAL_OPAMP_Init(&hopamp6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OPAMP6_Init 2 */

  /* USER CODE END OPAMP6_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 20000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 44;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 180;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 1000;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 1800;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 900;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/**
  * @brief TIM15 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM15_Init(void)
{

  /* USER CODE BEGIN TIM15_Init 0 */

  /* USER CODE END TIM15_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM15_Init 1 */

  /* USER CODE END TIM15_Init 1 */
  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 0;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 20000;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim15) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_TIM_DISABLE_OCxPRELOAD(&htim15, TIM_CHANNEL_2);
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM15_Init 2 */

  /* USER CODE END TIM15_Init 2 */
  HAL_TIM_MspPostInit(&htim15);

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 0;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 225;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */
  HAL_TIM_MspPostInit(&htim17);

}

/**
  * @brief TIM20 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM20_Init(void)
{

  /* USER CODE BEGIN TIM20_Init 0 */

  /* USER CODE END TIM20_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM20_Init 1 */

  /* USER CODE END TIM20_Init 1 */
  htim20.Instance = TIM20;
  htim20.Init.Prescaler = 0;
  htim20.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim20.Init.Period = 18000;
  htim20.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim20.Init.RepetitionCounter = 0;
  htim20.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim20) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim20, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim20) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim20, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 9000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim20, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim20, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM20_Init 2 */

  /* USER CODE END TIM20_Init 2 */
  HAL_TIM_MspPostInit(&htim20);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 921600 ;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA2_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel1_IRQn);
  /* DMA1_Channel8_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel8_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel8_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, FT6336_RST_Pin|ST_DC_Pin|DPO_EN1_Pin|DPO_AC1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DPO_EN2_Pin|DPO_AC2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST_CS_GPIO_Port, ST_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : FT6336_RST_Pin ST_DC_Pin DPO_EN1_Pin DPO_AC1_Pin */
  GPIO_InitStruct.Pin = FT6336_RST_Pin|ST_DC_Pin|DPO_EN1_Pin|DPO_AC1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DPO_EN2_Pin DPO_AC2_Pin */
  GPIO_InitStruct.Pin = DPO_EN2_Pin|DPO_AC2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ST_CS_Pin */
  GPIO_InitStruct.Pin = ST_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FT_INT_EXTI4_Pin PB8 */
  GPIO_InitStruct.Pin = FT_INT_EXTI4_Pin|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
