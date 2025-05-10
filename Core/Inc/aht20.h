#ifndef __DHT20_H__
#define __DHT20_H__

#include "main.h"
#define AHT20_I2C_PORT hi2c3

// 初始化AHT20
void AHT20_Init();

// 获取温度和湿度
void AHT20_Read(float *Temperature, float *Humidity);

#endif
