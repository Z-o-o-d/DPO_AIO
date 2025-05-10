// -------------------------------
// Created by 33974 on 2024/12/27.
//  @Project : STM32F4_4SPI
//  @Time    : 2024 - 12-27 00:10
//  @FileName:
//  @Software: Clion 2024
//  @System  : Windows 11 23H2
//  @Author  : 33974
//  @Contact : ${EMAIL}
// -------------------------------

#ifndef __FT6336_H
#define __FT6336_H

#include "main.h"
#include "stm32g4xx_hal.h"

#define FT6X36_ADDR 0x38 << 1 // 设备I2C地址（7位地址，需要左移1位）
#define SCREEN_WIDTH 320      // 替换为实际屏幕宽度
#define SCREEN_HEIGHT 240     // 替换为实际屏幕高度

#define FT6336_I2C_PORT hi2c3

// 定义一个结构体，其中包含两个独立的触摸点 (point1 和 point2)
typedef struct
{
  uint16_t point1_x; // 第一个触摸点的 X 坐标
  uint16_t point1_y; // 第一个触摸点的 Y 坐标
  uint16_t point2_x; // 第二个触摸点的 X 坐标
  uint16_t point2_y; // 第二个触摸点的 Y 坐标
} TouchPoints_HandleTypeDef;

#define FT6336_DEV_MODE 0x00
#define FT6336_GEST_ID 0x01
#define FT6336_TD_STATUS 0x02
#define FT6336_P1_XH 0x03
#define FT6336_P1_XL 0x04
#define FT6336_P1_YH 0x05
#define FT6336_P1_YL 0x06
#define FT6336_P1_WEIGHT 0x07
#define FT6336_P1_MISC 0x08
#define FT6336_P2_XH 0x09
#define FT6336_P2_XL 0x0A
#define FT6336_P2_YH 0x0B
#define FT6336_P2_YL 0x0C
#define FT6336_P2_WEIGHT 0x0D
#define FT6336_P2_MISC 0x0E
#define FT6336_TH_GROUP 0x80
#define FT6336_TH_DIFF 0x85
#define FT6336_CTRL 0x86
#define FT6336_TIMEENTERM 0x87
#define FT6336_PERIODACTIVE 0x88
#define FT6336_PERIODMONITOR 0x89
#define FT6336_RADIAN_VALUE 0x91
#define FT6336_OFFSET_LEFT_RIGHT 0x92
#define FT6336_OFFSET_UP_DOWN 0x93
#define FT6336_DISTANCE_LEFT_RIGHT 0x94
#define FT6336_DISTANCE_UP_DOWN 0x95
#define FT6336_DISTANCE_ZOOM 0x96
#define FT6336_LIB_VER_H 0xA1
#define FT6336_LIB_VER_L 0xA2
#define FT6336_CIPHER 0xA3
#define FT6336_G_MODE 0xA4
#define FT6336_PWR_MODE 0xA5
#define FT6336_FIRMID 0xA6
#define FT6336_FOCALTECH_ID 0xA8
#define FT6336_RELEASE_CODE_ID 0xAF
#define FT6336_STATE 0xBC

#define FT6336_RST_L \
  HAL_GPIO_WritePin(FT6336_RST_GPIO_Port, FT6336_RST_Pin, GPIO_PIN_RESET)
#define FT6336_RST_H \
  HAL_GPIO_WritePin(FT6336_RST_GPIO_Port, FT6336_RST_Pin, GPIO_PIN_SET)

extern TouchPoints_HandleTypeDef TouchPoints;

void FT6336_Init();
void FT6336_GetTouchPoint(TouchPoints_HandleTypeDef *touchPoints);

// void ReadTouchData();

#endif
