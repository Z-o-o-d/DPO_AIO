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

#include "FT6336.h"

extern I2C_HandleTypeDef FT6336_I2C_PORT;

TouchPoints_HandleTypeDef TouchPoints;

HAL_StatusTypeDef FT6336_WriteRegister(uint8_t RegAddress, uint8_t *pData, uint16_t Size)
{
    return HAL_I2C_Mem_Write(&FT6336_I2C_PORT, FT6X36_ADDR, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef FT6336_ReadRegister(uint8_t RegAddress, uint8_t *pData, uint16_t Size)
{
    return HAL_I2C_Mem_Read(&FT6336_I2C_PORT, FT6X36_ADDR, RegAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

void FT6336_Init(void)
{
    FT6336_RST_L;
    HAL_Delay(10);
    FT6336_RST_H;
    HAL_Delay(50);

    //    // 设置 DEVICE_MODE 为 0x00（正常模式）
    //    FT6336_WriteRegister(0x00, 0x00,1);
    //
    //    // 设置 ID_G_MODE 为 0x00（启用中断输出）
    //    FT6336_WriteRegister(0xA4, 0x00,1);

    uint8_t id = 0;
    FT6336_ReadRegister(FT6336_FOCALTECH_ID, &id, 1);
    HAL_Delay(1000);

    // used to debug IIC
    //    for (uint8_t addr = 0x08; addr < 0x78; ++addr) {  // I2C 地址范围是 0x08 到 0x77
    //           if (HAL_I2C_Mem_Read(&FT6336_I2C_PORT, addr << 1, 0x00, I2C_MEMADD_SIZE_8BIT, &id, 1, 100) == HAL_OK) {
    //                // 如果扫描到设备并且读取成功，进入处理函数
    //                HAL_Delay(100);
    //            }
    //            HAL_Delay(10);
    //        }
    //    HAL_I2C_Mem_Read(&FT6336_I2C_PORT, 0xA0, 0x00, I2C_MEMADD_SIZE_8BIT, &id, 1, HAL_MAX_DELAY);
    //    HAL_Delay(1000);
    // used to debug IIC
}

static void AdjustTouchCoordinates(uint16_t *x, uint16_t *y)
{
    uint16_t rawX = *x;
    uint16_t rawY = *y;

    // 根据触摸屏和屏幕方向进行调整，以下为常见几种情况

    // 情况 1：触摸屏 X 和 Y 坐标需要互换
    //    *x = rawY;
    //    *y = rawX;

    // 情况 2：X 或 Y 坐标需要翻转
    //    *x = SCREEN_WIDTH - rawX;
    //    *y = SCREEN_HEIGHT - rawY;

    // 情况 3：坐标需要缩放到屏幕分辨率
    // 假设触摸屏的分辨率为 TOUCH_WIDTH 和 TOUCH_HEIGHT
    // #define TOUCH_WIDTH  LCD_W  // 替换为触摸屏的实际分辨率
    // #define TOUCH_HEIGHT LCD_H
    //
    //     *x = (*x * SCREEN_WIDTH) / TOUCH_WIDTH;
    //     *y = (*y * SCREEN_HEIGHT) / TOUCH_HEIGHT;

    // 情况 X：特殊处理
    *x = rawY;
    *y = SCREEN_HEIGHT - rawX;
}

void FT6336_GetTouchPoint(TouchPoints_HandleTypeDef *touchPoints)
{
    uint8_t touchStatus = 0;
    
    #ifdef DUAL_TOUCH
    uint8_t touchData[8]; // 存储两个点的坐标数据 (每个点4个字节)
    #else
    uint8_t touchData[4]; // 存储一个点的坐标数据 (4个字节)
    #endif


    // 读取触摸状态寄存器
    FT6336_ReadRegister(FT6336_TD_STATUS, &touchStatus, 1);
    uint8_t touchCount = touchStatus & 0x0F; // 获取触摸点数量

    if (touchCount > 0)
    {
        // 读取第一个触摸点的坐标 (4个字节)
        FT6336_ReadRegister(FT6336_P1_XH, touchData, 4);
        touchPoints->point1_x = ((touchData[0] & 0x0F) << 8) | touchData[1];
        touchPoints->point1_y = ((touchData[2] & 0x0F) << 8) | touchData[3];
        AdjustTouchCoordinates(&touchPoints->point1_x, &touchPoints->point1_y); // 调整第一个触摸点坐标

        #ifdef DUAL_TOUCH
        // 如果有第二个触摸点，读取第二个触摸点的坐标 (4个字节)
        
        if (touchCount > 1)
        {
            // 读取第二个触摸点的坐标 (4个字节)
            FT6336_ReadRegister(FT6336_P2_XH, &touchData[4], 4);
            touchPoints->point2_x = ((touchData[4] & 0x0F) << 8) | touchData[5];
            touchPoints->point2_y = ((touchData[6] & 0x0F) << 8) | touchData[7];
            AdjustTouchCoordinates(&touchPoints->point2_x, &touchPoints->point2_y); // 调整第二个触摸点坐标
        }
        #endif
    }
    else
    {
        // 如果没有触摸点，设置坐标为无效值
        touchPoints->point1_x = 0xFFFF;
        touchPoints->point1_y = 0xFFFF;
        #ifdef DUAL_TOUCH
        // 如果有第二个触摸点，读取第二个触摸点的坐标 (4个字节)
        touchPoints->point2_x = 0xFFFF;
        touchPoints->point2_y = 0xFFFF;
        #endif
    }
}
