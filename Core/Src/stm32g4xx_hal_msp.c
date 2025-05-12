/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32g4xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
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
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern DMA_HandleTypeDef hdma_adc1;

extern DMA_HandleTypeDef hdma_adc3;

extern DMA_HandleTypeDef hdma_spi1_tx;

extern DMA_HandleTypeDef hdma_spi3_tx;

extern DMA_HandleTypeDef hdma_tim17_ch1;

extern DMA_HandleTypeDef hdma_usart1_rx;

extern DMA_HandleTypeDef hdma_usart1_tx;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                                                                                    /**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
  */
  HAL_PWREx_DisableUCPDDeadBattery();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

static uint32_t HAL_RCC_ADC12_CLK_ENABLED=0;
static uint32_t HAL_RCC_ADC345_CLK_ENABLED=0;

/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
    PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_ADC12_CLK_ENABLED++;
    if(HAL_RCC_ADC12_CLK_ENABLED==1){
      __HAL_RCC_ADC12_CLK_ENABLE();
    }

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspInit 0 */

  /* USER CODE END ADC2_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
    PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_ADC12_CLK_ENABLED++;
    if(HAL_RCC_ADC12_CLK_ENABLED==1){
      __HAL_RCC_ADC12_CLK_ENABLE();
    }
  /* USER CODE BEGIN ADC2_MspInit 1 */

  /* USER CODE END ADC2_MspInit 1 */
  }
  else if(hadc->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC345;
    PeriphClkInit.Adc345ClockSelection = RCC_ADC345CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_ADC345_CLK_ENABLED++;
    if(HAL_RCC_ADC345_CLK_ENABLED==1){
      __HAL_RCC_ADC345_CLK_ENABLE();
    }

    /* ADC3 DMA Init */
    /* ADC3 Init */
    hdma_adc3.Instance = DMA1_Channel5;
    hdma_adc3.Init.Request = DMA_REQUEST_ADC3;
    hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc3.Init.Mode = DMA_CIRCULAR;
    hdma_adc3.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    if (HAL_DMA_Init(&hdma_adc3) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc3);

  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
  else if(hadc->Instance==ADC4)
  {
  /* USER CODE BEGIN ADC4_MspInit 0 */

  /* USER CODE END ADC4_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC345;
    PeriphClkInit.Adc345ClockSelection = RCC_ADC345CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_ADC345_CLK_ENABLED++;
    if(HAL_RCC_ADC345_CLK_ENABLED==1){
      __HAL_RCC_ADC345_CLK_ENABLE();
    }
  /* USER CODE BEGIN ADC4_MspInit 1 */

  /* USER CODE END ADC4_MspInit 1 */
  }
  else if(hadc->Instance==ADC5)
  {
  /* USER CODE BEGIN ADC5_MspInit 0 */

  /* USER CODE END ADC5_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC345;
    PeriphClkInit.Adc345ClockSelection = RCC_ADC345CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    HAL_RCC_ADC345_CLK_ENABLED++;
    if(HAL_RCC_ADC345_CLK_ENABLED==1){
      __HAL_RCC_ADC345_CLK_ENABLE();
    }
  /* USER CODE BEGIN ADC5_MspInit 1 */

  /* USER CODE END ADC5_MspInit 1 */
  }

}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC12_CLK_ENABLED--;
    if(HAL_RCC_ADC12_CLK_ENABLED==0){
      __HAL_RCC_ADC12_CLK_DISABLE();
    }

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC12_CLK_ENABLED--;
    if(HAL_RCC_ADC12_CLK_ENABLED==0){
      __HAL_RCC_ADC12_CLK_DISABLE();
    }
  /* USER CODE BEGIN ADC2_MspDeInit 1 */

  /* USER CODE END ADC2_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC345_CLK_ENABLED--;
    if(HAL_RCC_ADC345_CLK_ENABLED==0){
      __HAL_RCC_ADC345_CLK_DISABLE();
    }

    /* ADC3 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);
  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC4)
  {
  /* USER CODE BEGIN ADC4_MspDeInit 0 */

  /* USER CODE END ADC4_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC345_CLK_ENABLED--;
    if(HAL_RCC_ADC345_CLK_ENABLED==0){
      __HAL_RCC_ADC345_CLK_DISABLE();
    }
  /* USER CODE BEGIN ADC4_MspDeInit 1 */

  /* USER CODE END ADC4_MspDeInit 1 */
  }
  else if(hadc->Instance==ADC5)
  {
  /* USER CODE BEGIN ADC5_MspDeInit 0 */

  /* USER CODE END ADC5_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_ADC345_CLK_ENABLED--;
    if(HAL_RCC_ADC345_CLK_ENABLED==0){
      __HAL_RCC_ADC345_CLK_DISABLE();
    }
  /* USER CODE BEGIN ADC5_MspDeInit 1 */

  /* USER CODE END ADC5_MspDeInit 1 */
  }

}

/**
* @brief COMP MSP Initialization
* This function configures the hardware resources used in this example
* @param hcomp: COMP handle pointer
* @retval None
*/
void HAL_COMP_MspInit(COMP_HandleTypeDef* hcomp)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hcomp->Instance==COMP2)
  {
  /* USER CODE BEGIN COMP2_MspInit 0 */

  /* USER CODE END COMP2_MspInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**COMP2 GPIO Configuration
    PA7     ------> COMP2_INP
    */
    GPIO_InitStruct.Pin = O1P_O2P_DPO_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(O1P_O2P_DPO_IN_GPIO_Port, &GPIO_InitStruct);

    /* COMP2 interrupt Init */
    HAL_NVIC_SetPriority(COMP1_2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(COMP1_2_3_IRQn);
  /* USER CODE BEGIN COMP2_MspInit 1 */

  /* USER CODE END COMP2_MspInit 1 */
  }
  else if(hcomp->Instance==COMP5)
  {
  /* USER CODE BEGIN COMP5_MspInit 0 */

  /* USER CODE END COMP5_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**COMP5 GPIO Configuration
    PB13     ------> COMP5_INP
    */
    GPIO_InitStruct.Pin = O6P_O3P_DPO_IN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(O6P_O3P_DPO_IN2_GPIO_Port, &GPIO_InitStruct);

    /* COMP5 interrupt Init */
    HAL_NVIC_SetPriority(COMP4_5_6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(COMP4_5_6_IRQn);
  /* USER CODE BEGIN COMP5_MspInit 1 */

  /* USER CODE END COMP5_MspInit 1 */
  }

}

/**
* @brief COMP MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcomp: COMP handle pointer
* @retval None
*/
void HAL_COMP_MspDeInit(COMP_HandleTypeDef* hcomp)
{
  if(hcomp->Instance==COMP2)
  {
  /* USER CODE BEGIN COMP2_MspDeInit 0 */

  /* USER CODE END COMP2_MspDeInit 0 */

    /**COMP2 GPIO Configuration
    PA7     ------> COMP2_INP
    */
    HAL_GPIO_DeInit(O1P_O2P_DPO_IN_GPIO_Port, O1P_O2P_DPO_IN_Pin);

    /* COMP2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(COMP1_2_3_IRQn);
  /* USER CODE BEGIN COMP2_MspDeInit 1 */

  /* USER CODE END COMP2_MspDeInit 1 */
  }
  else if(hcomp->Instance==COMP5)
  {
  /* USER CODE BEGIN COMP5_MspDeInit 0 */

  /* USER CODE END COMP5_MspDeInit 0 */

    /**COMP5 GPIO Configuration
    PB13     ------> COMP5_INP
    */
    HAL_GPIO_DeInit(O6P_O3P_DPO_IN2_GPIO_Port, O6P_O3P_DPO_IN2_Pin);

    /* COMP5 interrupt DeInit */
    HAL_NVIC_DisableIRQ(COMP4_5_6_IRQn);
  /* USER CODE BEGIN COMP5_MspDeInit 1 */

  /* USER CODE END COMP5_MspDeInit 1 */
  }

}

/**
* @brief CORDIC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcordic: CORDIC handle pointer
* @retval None
*/
void HAL_CORDIC_MspInit(CORDIC_HandleTypeDef* hcordic)
{
  if(hcordic->Instance==CORDIC)
  {
  /* USER CODE BEGIN CORDIC_MspInit 0 */

  /* USER CODE END CORDIC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CORDIC_CLK_ENABLE();
  /* USER CODE BEGIN CORDIC_MspInit 1 */

  /* USER CODE END CORDIC_MspInit 1 */

  }

}

/**
* @brief CORDIC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcordic: CORDIC handle pointer
* @retval None
*/
void HAL_CORDIC_MspDeInit(CORDIC_HandleTypeDef* hcordic)
{
  if(hcordic->Instance==CORDIC)
  {
  /* USER CODE BEGIN CORDIC_MspDeInit 0 */

  /* USER CODE END CORDIC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CORDIC_CLK_DISABLE();
  /* USER CODE BEGIN CORDIC_MspDeInit 1 */

  /* USER CODE END CORDIC_MspDeInit 1 */
  }

}

/**
* @brief DAC MSP Initialization
* This function configures the hardware resources used in this example
* @param hdac: DAC handle pointer
* @retval None
*/
void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hdac->Instance==DAC1)
  {
  /* USER CODE BEGIN DAC1_MspInit 0 */

  /* USER CODE END DAC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DAC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC1 GPIO Configuration
    PA4     ------> DAC1_OUT1
    */
    GPIO_InitStruct.Pin = D1C1_OFFSET_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(D1C1_OFFSET_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN DAC1_MspInit 1 */

  /* USER CODE END DAC1_MspInit 1 */
  }
  else if(hdac->Instance==DAC2)
  {
  /* USER CODE BEGIN DAC2_MspInit 0 */

  /* USER CODE END DAC2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DAC2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC2 GPIO Configuration
    PA6     ------> DAC2_OUT1
    */
    GPIO_InitStruct.Pin = D2C1_OFFSET2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(D2C1_OFFSET2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN DAC2_MspInit 1 */

  /* USER CODE END DAC2_MspInit 1 */
  }
  else if(hdac->Instance==DAC3)
  {
  /* USER CODE BEGIN DAC3_MspInit 0 */

  /* USER CODE END DAC3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DAC3_CLK_ENABLE();
  /* USER CODE BEGIN DAC3_MspInit 1 */

  /* USER CODE END DAC3_MspInit 1 */
  }
  else if(hdac->Instance==DAC4)
  {
  /* USER CODE BEGIN DAC4_MspInit 0 */

  /* USER CODE END DAC4_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DAC4_CLK_ENABLE();
  /* USER CODE BEGIN DAC4_MspInit 1 */

  /* USER CODE END DAC4_MspInit 1 */
  }

}

/**
* @brief DAC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hdac: DAC handle pointer
* @retval None
*/
void HAL_DAC_MspDeInit(DAC_HandleTypeDef* hdac)
{
  if(hdac->Instance==DAC1)
  {
  /* USER CODE BEGIN DAC1_MspDeInit 0 */

  /* USER CODE END DAC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC1_CLK_DISABLE();

    /**DAC1 GPIO Configuration
    PA4     ------> DAC1_OUT1
    */
    HAL_GPIO_DeInit(D1C1_OFFSET_GPIO_Port, D1C1_OFFSET_Pin);

  /* USER CODE BEGIN DAC1_MspDeInit 1 */

  /* USER CODE END DAC1_MspDeInit 1 */
  }
  else if(hdac->Instance==DAC2)
  {
  /* USER CODE BEGIN DAC2_MspDeInit 0 */

  /* USER CODE END DAC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC2_CLK_DISABLE();

    /**DAC2 GPIO Configuration
    PA6     ------> DAC2_OUT1
    */
    HAL_GPIO_DeInit(D2C1_OFFSET2_GPIO_Port, D2C1_OFFSET2_Pin);

  /* USER CODE BEGIN DAC2_MspDeInit 1 */

  /* USER CODE END DAC2_MspDeInit 1 */
  }
  else if(hdac->Instance==DAC3)
  {
  /* USER CODE BEGIN DAC3_MspDeInit 0 */

  /* USER CODE END DAC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC3_CLK_DISABLE();
  /* USER CODE BEGIN DAC3_MspDeInit 1 */

  /* USER CODE END DAC3_MspDeInit 1 */
  }
  else if(hdac->Instance==DAC4)
  {
  /* USER CODE BEGIN DAC4_MspDeInit 0 */

  /* USER CODE END DAC4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC4_CLK_DISABLE();
  /* USER CODE BEGIN DAC4_MspDeInit 1 */

  /* USER CODE END DAC4_MspDeInit 1 */
  }

}

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(hi2c->Instance==I2C3)
  {
  /* USER CODE BEGIN I2C3_MspInit 0 */

  /* USER CODE END I2C3_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C3;
    PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**I2C3 GPIO Configuration
    PC8     ------> I2C3_SCL
    PC9     ------> I2C3_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();
  /* USER CODE BEGIN I2C3_MspInit 1 */

  /* USER CODE END I2C3_MspInit 1 */

  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C3)
  {
  /* USER CODE BEGIN I2C3_MspDeInit 0 */

  /* USER CODE END I2C3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C3_CLK_DISABLE();

    /**I2C3 GPIO Configuration
    PC8     ------> I2C3_SCL
    PC9     ------> I2C3_SDA
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

  /* USER CODE BEGIN I2C3_MspDeInit 1 */

  /* USER CODE END I2C3_MspDeInit 1 */
  }

}

/**
* @brief OPAMP MSP Initialization
* This function configures the hardware resources used in this example
* @param hopamp: OPAMP handle pointer
* @retval None
*/
void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef* hopamp)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hopamp->Instance==OPAMP1)
  {
  /* USER CODE BEGIN OPAMP1_MspInit 0 */

  /* USER CODE END OPAMP1_MspInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**OPAMP1 GPIO Configuration
    PA3     ------> OPAMP1_VINM0
    PA7     ------> OPAMP1_VINP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|O1P_O2P_DPO_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN OPAMP1_MspInit 1 */

  /* USER CODE END OPAMP1_MspInit 1 */
  }
  else if(hopamp->Instance==OPAMP2)
  {
  /* USER CODE BEGIN OPAMP2_MspInit 0 */

  /* USER CODE END OPAMP2_MspInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**OPAMP2 GPIO Configuration
    PA5     ------> OPAMP2_VINM0
    PA7     ------> OPAMP2_VINP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|O1P_O2P_DPO_IN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN OPAMP2_MspInit 1 */

  /* USER CODE END OPAMP2_MspInit 1 */
  }
  else if(hopamp->Instance==OPAMP3)
  {
  /* USER CODE BEGIN OPAMP3_MspInit 0 */

  /* USER CODE END OPAMP3_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**OPAMP3 GPIO Configuration
    PB2     ------> OPAMP3_VINM0
    PB13     ------> OPAMP3_VINP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|O6P_O3P_DPO_IN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN OPAMP3_MspInit 1 */

  /* USER CODE END OPAMP3_MspInit 1 */
  }
  else if(hopamp->Instance==OPAMP4)
  {
  /* USER CODE BEGIN OPAMP4_MspInit 0 */

  /* USER CODE END OPAMP4_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**OPAMP4 GPIO Configuration
    PB12     ------> OPAMP4_VOUT
    */
    GPIO_InitStruct.Pin = O4O_D4C1_BIAS1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(O4O_D4C1_BIAS1_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN OPAMP4_MspInit 1 */

  /* USER CODE END OPAMP4_MspInit 1 */
  }
  else if(hopamp->Instance==OPAMP5)
  {
  /* USER CODE BEGIN OPAMP5_MspInit 0 */

  /* USER CODE END OPAMP5_MspInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**OPAMP5 GPIO Configuration
    PA8     ------> OPAMP5_VOUT
    */
    GPIO_InitStruct.Pin = O5O_D4C2_IAS0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(O5O_D4C2_IAS0_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN OPAMP5_MspInit 1 */

  /* USER CODE END OPAMP5_MspInit 1 */
  }
  else if(hopamp->Instance==OPAMP6)
  {
  /* USER CODE BEGIN OPAMP6_MspInit 0 */

  /* USER CODE END OPAMP6_MspInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**OPAMP6 GPIO Configuration
    PA1     ------> OPAMP6_VINM0
    PB13     ------> OPAMP6_VINP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = O6P_O3P_DPO_IN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(O6P_O3P_DPO_IN2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN OPAMP6_MspInit 1 */

  /* USER CODE END OPAMP6_MspInit 1 */
  }

}

/**
* @brief OPAMP MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hopamp: OPAMP handle pointer
* @retval None
*/
void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef* hopamp)
{
  if(hopamp->Instance==OPAMP1)
  {
  /* USER CODE BEGIN OPAMP1_MspDeInit 0 */

  /* USER CODE END OPAMP1_MspDeInit 0 */

    /**OPAMP1 GPIO Configuration
    PA3     ------> OPAMP1_VINM0
    PA7     ------> OPAMP1_VINP
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3|O1P_O2P_DPO_IN_Pin);

  /* USER CODE BEGIN OPAMP1_MspDeInit 1 */

  /* USER CODE END OPAMP1_MspDeInit 1 */
  }
  else if(hopamp->Instance==OPAMP2)
  {
  /* USER CODE BEGIN OPAMP2_MspDeInit 0 */

  /* USER CODE END OPAMP2_MspDeInit 0 */

    /**OPAMP2 GPIO Configuration
    PA5     ------> OPAMP2_VINM0
    PA7     ------> OPAMP2_VINP
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|O1P_O2P_DPO_IN_Pin);

  /* USER CODE BEGIN OPAMP2_MspDeInit 1 */

  /* USER CODE END OPAMP2_MspDeInit 1 */
  }
  else if(hopamp->Instance==OPAMP3)
  {
  /* USER CODE BEGIN OPAMP3_MspDeInit 0 */

  /* USER CODE END OPAMP3_MspDeInit 0 */

    /**OPAMP3 GPIO Configuration
    PB2     ------> OPAMP3_VINM0
    PB13     ------> OPAMP3_VINP
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|O6P_O3P_DPO_IN2_Pin);

  /* USER CODE BEGIN OPAMP3_MspDeInit 1 */

  /* USER CODE END OPAMP3_MspDeInit 1 */
  }
  else if(hopamp->Instance==OPAMP4)
  {
  /* USER CODE BEGIN OPAMP4_MspDeInit 0 */

  /* USER CODE END OPAMP4_MspDeInit 0 */

    /**OPAMP4 GPIO Configuration
    PB12     ------> OPAMP4_VOUT
    */
    HAL_GPIO_DeInit(O4O_D4C1_BIAS1_GPIO_Port, O4O_D4C1_BIAS1_Pin);

  /* USER CODE BEGIN OPAMP4_MspDeInit 1 */

  /* USER CODE END OPAMP4_MspDeInit 1 */
  }
  else if(hopamp->Instance==OPAMP5)
  {
  /* USER CODE BEGIN OPAMP5_MspDeInit 0 */

  /* USER CODE END OPAMP5_MspDeInit 0 */

    /**OPAMP5 GPIO Configuration
    PA8     ------> OPAMP5_VOUT
    */
    HAL_GPIO_DeInit(O5O_D4C2_IAS0_GPIO_Port, O5O_D4C2_IAS0_Pin);

  /* USER CODE BEGIN OPAMP5_MspDeInit 1 */

  /* USER CODE END OPAMP5_MspDeInit 1 */
  }
  else if(hopamp->Instance==OPAMP6)
  {
  /* USER CODE BEGIN OPAMP6_MspDeInit 0 */

  /* USER CODE END OPAMP6_MspDeInit 0 */

    /**OPAMP6 GPIO Configuration
    PA1     ------> OPAMP6_VINM0
    PB13     ------> OPAMP6_VINP
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

    HAL_GPIO_DeInit(O6P_O3P_DPO_IN2_GPIO_Port, O6P_O3P_DPO_IN2_Pin);

  /* USER CODE BEGIN OPAMP6_MspDeInit 1 */

  /* USER CODE END OPAMP6_MspDeInit 1 */
  }

}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hspi->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB5     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = ST_SPI3_SCK_Pin|ST_SPI3_MOSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA1_Channel4;
    hdma_spi1_tx.Init.Request = DMA_REQUEST_SPI1_TX;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hspi,hdmatx,hdma_spi1_tx);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
  else if(hspi->Instance==SPI3)
  {
  /* USER CODE BEGIN SPI3_MspInit 0 */

  /* USER CODE END SPI3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI3_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**SPI3 GPIO Configuration
    PA15     ------> SPI3_NSS
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO
    PC12     ------> SPI3_MOSI
    */
    GPIO_InitStruct.Pin = FPGA_SPI3_NSS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(FPGA_SPI3_NSS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = FPGA_SPI3_SCK_Pin|FPGA_SPI3_MISO_Pin|FPGA_SPI3_MOSI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* SPI3 DMA Init */
    /* SPI3_TX Init */
    hdma_spi3_tx.Instance = DMA1_Channel8;
    hdma_spi3_tx.Init.Request = DMA_REQUEST_SPI3_TX;
    hdma_spi3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi3_tx.Init.Mode = DMA_NORMAL;
    hdma_spi3_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi3_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hspi,hdmatx,hdma_spi3_tx);

  /* USER CODE BEGIN SPI3_MspInit 1 */

  /* USER CODE END SPI3_MspInit 1 */
  }

}

/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
  if(hspi->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB5     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, ST_SPI3_SCK_Pin|ST_SPI3_MOSI_Pin);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(hspi->hdmatx);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
  else if(hspi->Instance==SPI3)
  {
  /* USER CODE BEGIN SPI3_MspDeInit 0 */

  /* USER CODE END SPI3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI3_CLK_DISABLE();

    /**SPI3 GPIO Configuration
    PA15     ------> SPI3_NSS
    PC10     ------> SPI3_SCK
    PC11     ------> SPI3_MISO
    PC12     ------> SPI3_MOSI
    */
    HAL_GPIO_DeInit(FPGA_SPI3_NSS_GPIO_Port, FPGA_SPI3_NSS_Pin);

    HAL_GPIO_DeInit(GPIOC, FPGA_SPI3_SCK_Pin|FPGA_SPI3_MISO_Pin|FPGA_SPI3_MOSI_Pin);

    /* SPI3 DMA DeInit */
    HAL_DMA_DeInit(hspi->hdmatx);
  /* USER CODE BEGIN SPI3_MspDeInit 1 */

  /* USER CODE END SPI3_MspDeInit 1 */
  }

}

/**
* @brief TIM_Encoder MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_encoder: TIM_Encoder handle pointer
* @retval None
*/
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_encoder)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim_encoder->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PC0     ------> TIM1_CH1
    PC1     ------> TIM1_CH2
    */
    GPIO_InitStruct.Pin = ENC1_P_Pin|ENC1_N_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
  else if(htim_encoder->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PC6     ------> TIM3_CH1
    PC7     ------> TIM3_CH2
    */
    GPIO_InitStruct.Pin = ENC3_P_Pin|ENC3_N_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
  else if(htim_encoder->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    */
    GPIO_InitStruct.Pin = ENC4_P_Pin|ENC4_N_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }

}

/**
* @brief TIM_PWM MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_pwm: TIM_PWM handle pointer
* @retval None
*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(htim_pwm->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspInit 0 */

  /* USER CODE END TIM15_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM15_CLK_ENABLE();
  /* USER CODE BEGIN TIM15_MspInit 1 */

  /* USER CODE END TIM15_MspInit 1 */
  }

}

/**
* @brief TIM_Base MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }
  else if(htim_base->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspInit 0 */

  /* USER CODE END TIM7_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();
  /* USER CODE BEGIN TIM7_MspInit 1 */

  /* USER CODE END TIM7_MspInit 1 */
  }
  else if(htim_base->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspInit 0 */

  /* USER CODE END TIM8_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM8_CLK_ENABLE();
  /* USER CODE BEGIN TIM8_MspInit 1 */

  /* USER CODE END TIM8_MspInit 1 */
  }
  else if(htim_base->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspInit 0 */

  /* USER CODE END TIM17_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM17_CLK_ENABLE();

    /* TIM17 DMA Init */
    /* TIM17_CH1 Init */
    hdma_tim17_ch1.Instance = DMA2_Channel1;
    hdma_tim17_ch1.Init.Request = DMA_REQUEST_TIM17_CH1;
    hdma_tim17_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim17_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim17_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim17_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_tim17_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_tim17_ch1.Init.Mode = DMA_NORMAL;
    hdma_tim17_ch1.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_tim17_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(htim_base,hdma[TIM_DMA_ID_CC1],hdma_tim17_ch1);

  /* USER CODE BEGIN TIM17_MspInit 1 */

  /* USER CODE END TIM17_MspInit 1 */
  }
  else if(htim_base->Instance==TIM20)
  {
  /* USER CODE BEGIN TIM20_MspInit 0 */

  /* USER CODE END TIM20_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM20_CLK_ENABLE();
  /* USER CODE BEGIN TIM20_MspInit 1 */

  /* USER CODE END TIM20_MspInit 1 */
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspPostInit 0 */

  /* USER CODE END TIM2_MspPostInit 0 */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM2 GPIO Configuration
    PB10     ------> TIM2_CH3
    PB11     ------> TIM2_CH4
    */
    GPIO_InitStruct.Pin = T2C3_REF1_Pin|T2C4_DC1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM2_MspPostInit 1 */

  /* USER CODE END TIM2_MspPostInit 1 */
  }
  else if(htim->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspPostInit 0 */

  /* USER CODE END TIM8_MspPostInit 0 */

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM8 GPIO Configuration
    PC13     ------> TIM8_CH4N
    */
    GPIO_InitStruct.Pin = T8C4N_ST_BRI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_TIM8;
    HAL_GPIO_Init(T8C4N_ST_BRI_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM8_MspPostInit 1 */

  /* USER CODE END TIM8_MspPostInit 1 */
  }
  else if(htim->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspPostInit 0 */

  /* USER CODE END TIM15_MspPostInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM15 GPIO Configuration
    PB14     ------> TIM15_CH1
    PB15     ------> TIM15_CH2
    */
    GPIO_InitStruct.Pin = T15C1_DC2_Pin|T15C2_REF2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM15_MspPostInit 1 */

  /* USER CODE END TIM15_MspPostInit 1 */
  }
  else if(htim->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspPostInit 0 */

  /* USER CODE END TIM17_MspPostInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM17 GPIO Configuration
    PB9     ------> TIM17_CH1
    */
    GPIO_InitStruct.Pin = T17C1_WS2812_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM17;
    HAL_GPIO_Init(T17C1_WS2812_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM17_MspPostInit 1 */

  /* USER CODE END TIM17_MspPostInit 1 */
  }
  else if(htim->Instance==TIM20)
  {
  /* USER CODE BEGIN TIM20_MspPostInit 0 */

  /* USER CODE END TIM20_MspPostInit 0 */

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM20 GPIO Configuration
    PC2     ------> TIM20_CH2
    */
    GPIO_InitStruct.Pin = T20C2_RUN_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_TIM20;
    HAL_GPIO_Init(T20C2_RUN_LED_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM20_MspPostInit 1 */

  /* USER CODE END TIM20_MspPostInit 1 */
  }

}
/**
* @brief TIM_Encoder MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_encoder: TIM_Encoder handle pointer
* @retval None
*/
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* htim_encoder)
{
  if(htim_encoder->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /**TIM1 GPIO Configuration
    PC0     ------> TIM1_CH1
    PC1     ------> TIM1_CH2
    */
    HAL_GPIO_DeInit(GPIOC, ENC1_P_Pin|ENC1_N_Pin);

  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
  else if(htim_encoder->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /**TIM3 GPIO Configuration
    PC6     ------> TIM3_CH1
    PC7     ------> TIM3_CH2
    */
    HAL_GPIO_DeInit(GPIOC, ENC3_P_Pin|ENC3_N_Pin);

  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
  else if(htim_encoder->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    */
    HAL_GPIO_DeInit(GPIOB, ENC4_P_Pin|ENC4_N_Pin);

  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }

}

/**
* @brief TIM_PWM MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_pwm: TIM_PWM handle pointer
* @retval None
*/
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
  if(htim_pwm->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(htim_pwm->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspDeInit 0 */

  /* USER CODE END TIM15_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM15_CLK_DISABLE();
  /* USER CODE BEGIN TIM15_MspDeInit 1 */

  /* USER CODE END TIM15_MspDeInit 1 */
  }

}

/**
* @brief TIM_Base MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspDeInit 0 */

  /* USER CODE END TIM7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM7_CLK_DISABLE();
  /* USER CODE BEGIN TIM7_MspDeInit 1 */

  /* USER CODE END TIM7_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspDeInit 0 */

  /* USER CODE END TIM8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM8_CLK_DISABLE();
  /* USER CODE BEGIN TIM8_MspDeInit 1 */

  /* USER CODE END TIM8_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspDeInit 0 */

  /* USER CODE END TIM17_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM17_CLK_DISABLE();

    /* TIM17 DMA DeInit */
    HAL_DMA_DeInit(htim_base->hdma[TIM_DMA_ID_CC1]);
  /* USER CODE BEGIN TIM17_MspDeInit 1 */

  /* USER CODE END TIM17_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM20)
  {
  /* USER CODE BEGIN TIM20_MspDeInit 0 */

  /* USER CODE END TIM20_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM20_CLK_DISABLE();
  /* USER CODE BEGIN TIM20_MspDeInit 1 */

  /* USER CODE END TIM20_MspDeInit 1 */
  }

}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel2;
    hdma_usart1_rx.Init.Request = DMA_REQUEST_USART1_RX;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel3;
    hdma_usart1_tx.Init.Request = DMA_REQUEST_USART1_TX;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(huart,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */

  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(huart->hdmarx);
    HAL_DMA_DeInit(huart->hdmatx);

    /* USART1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
