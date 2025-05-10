// #include "TLC5952.h"

// TLC5952_AllDataDef TLC5952Data = {0};

// /**
//  * @brief 初始化 TLC5952
//  */
// void TLC5952_Init(void)
// {
//     GPIO_InitTypeDef GPIO_InitStruct = {0};

//     __HAL_RCC_GPIOA_CLK_ENABLE();

//     GPIO_InitStruct.Pin = TLC5952_SIN_Pin | TLC5952_SCLK_Pin | TLC5952_LAT_Pin;
//     GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//     TLC5952_SIN_LOW();
//     TLC5952_SCLK_LOW();
//     TLC5952_LAT_LOW();
// }

// /**
//  * @brief 发送单个 bit
//  * @param bit 0 或 1
//  */
// void TLC5952_WriteBit(uint8_t bit)
// {
//     if (bit)
//         TLC5952_SIN_HIGH();
//     else
//         TLC5952_SIN_LOW();

//     TLC5952_SCLK_HIGH();
//     TLC5952_SCLK_LOW();
// }

// /**
//  * @brief 发送 24 位 LED 数据
//  */
// void TLC5952_WriteLED(void)
// {
//     TLC5952_WriteBit(0);
//     uint32_t *data = (uint32_t *)&TLC5952Data;
//     for (int8_t i = 23; i >= 0; i--)
//     {
//         uint8_t currentBit = (*data >> i) & 0x01;
//         TLC5952_WriteBit(currentBit);
//     }
//     TLC5952_LAT_HIGH();
//     TLC5952_LAT_LOW();
// }


// /**
//  * @brief 发送 24 位 控制 数据
//  */
// void TLC5952_WriteControl(void) {
//     TLC5952_WriteBit(1);
//     for (int i = 6; i >= 0; i--) {
//         TLC5952_WriteBit((TLC5952Data.red_brightness >> i) & 0x01);
//     }
//     for (int i = 6; i >= 0; i--) {
//         TLC5952_WriteBit((TLC5952Data.green_brightness >> i) & 0x01);
//     }
//     for (int i = 6; i >= 0; i--) {
//         TLC5952_WriteBit((TLC5952Data.blue_brightness >> i) & 0x01);
//     }
//     for (int i = 2; i >= 0; i--) {
//         TLC5952_WriteBit((TLC5952Data.detection_voltage_select >> i) & 0x01);
//     }
//     TLC5952_LAT_HIGH();
//     TLC5952_LAT_LOW();
// }

