/*
 * @Description: WS2812驱动头文件
 * @Author: Tomood
 * @Date: 2024-03-25 23:07:58
 * @LastEditTime: 2024-06-15 15:21:21
 * @FilePath: \ARGB-ligtcontroller\bsp\ws2812.h
 */
#ifndef __WS2812_H
#define __WS2812_H
#include "main.h"

/*灯参数宏*/
#define WS2812_NUM               19                            	     //WS2812串联个数
#define WS2812_DATA_LEN          24                           		 //WS2812数据长度(RGB888 = 24bit)
#define WS2812_BUF_SIZE          (WS2812_NUM + 1) * WS2812_DATA_LEN  //ws2812级联后需要的数组长度(需要增加复位码)

/*WS2812对应码元的定时器计数值 PWM周期：800 kHz*/
#define High_Code             148                        //1 码相对计数值
#define Low_Code              74                       //0 码相对计数值

/*生成PWM的定时器和通道定义*/
#define WS2812_TIM  htim17
#define WS2812_CHANNEL  TIM_CHANNEL_1 

extern TIM_HandleTypeDef WS2812_TIM;
extern uint16_t WS2812_Buf[WS2812_NUM + 1][WS2812_DATA_LEN];
// extern uint32_t rainbow_buf[];

//基础控制函数
void WS2812_Write_Data(uint32_t Color, uint8_t index);
void WS2812_Set_All(uint32_t Color);
void WS2812_Update(void);

// 将24位颜色值(0xGGRRBB)转换为16位颜色值(5-6-5格式)
static inline uint16_t convert_24bit_to_16bit(uint32_t color_24bit) {
    uint8_t g = (color_24bit >> 16) & 0xFF;  // R 在高位
    uint8_t r = (color_24bit >> 8) & 0xFF;
    uint8_t b = color_24bit & 0xFF;

    return ((r & 0xF8) << 8) |   // R[7:3] << 11
           ((g & 0xFC) << 3) |   // G[7:2] << 5
           (b >> 3);             // B[7:3]
}





uint32_t WS2812_rgb2color(uint8_t red, uint8_t green, uint8_t blue);

void WS2812_RunningHorse(uint8_t speed,uint8_t color_offset);

//灯控效果in while(1)





#endif
