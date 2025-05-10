// #ifndef TLC5952_H
// #define TLC5952_H

// #include "main.h"

// #define TLC5952_SIN_HIGH()   HAL_GPIO_WritePin(TLC5952_SIN_GPIO_Port, TLC5952_SIN_Pin, GPIO_PIN_SET)
// #define TLC5952_SIN_LOW()    HAL_GPIO_WritePin(TLC5952_SIN_GPIO_Port, TLC5952_SIN_Pin, GPIO_PIN_RESET)

// #define TLC5952_SCLK_HIGH()  HAL_GPIO_WritePin(TLC5952_SCLK_GPIO_Port, TLC5952_SCLK_Pin, GPIO_PIN_SET)
// #define TLC5952_SCLK_LOW()   HAL_GPIO_WritePin(TLC5952_SCLK_GPIO_Port, TLC5952_SCLK_Pin, GPIO_PIN_RESET)

// #define TLC5952_LAT_HIGH()   HAL_GPIO_WritePin(TLC5952_LAT_GPIO_Port, TLC5952_LAT_Pin, GPIO_PIN_SET)
// #define TLC5952_LAT_LOW()    HAL_GPIO_WritePin(TLC5952_LAT_GPIO_Port, TLC5952_LAT_Pin, GPIO_PIN_RESET)

// typedef struct {
//     uint32_t led0  : 1;
//     uint32_t led1  : 1;
//     uint32_t led2  : 1;
//     uint32_t led3  : 1;
//     uint32_t led4  : 1;
//     uint32_t led5  : 1;
//     uint32_t led6  : 1;
//     uint32_t led7  : 1;
//     uint32_t led8  : 1;
//     uint32_t led9  : 1;
//     uint32_t led10 : 1;
//     uint32_t led11 : 1;
//     uint32_t led12 : 1;
//     uint32_t led13 : 1;
//     uint32_t led14 : 1;
//     uint32_t led15 : 1;
//     uint32_t led16 : 1;
//     uint32_t led17 : 1;
//     uint32_t led18 : 1;
//     uint32_t led19 : 1;
//     uint32_t led20 : 1;
//     uint32_t led21 : 1;
//     uint32_t led22 : 1;
//     uint32_t led23 : 1;
//     uint32_t red_brightness : 7;
//     uint32_t green_brightness : 7;
//     uint32_t blue_brightness : 7;
//     uint32_t detection_voltage_select : 3;
// } TLC5952_AllDataDef;

// extern TLC5952_AllDataDef allData;

// /**
//  * @brief 初始化 TLC5952
//  */
// void TLC5952_Init(void);

// /**
//  * @brief 发送单个 bit
//  * @param bit 0 或 1
//  */
// void TLC5952_WriteBit(uint8_t bit);

// /**
//  * @brief 发送 24 位 LED 数据
//  */
// void TLC5952_WriteLED(void);



// void TLC5952_WriteControl(void);



// #endif // TLC5952_H
