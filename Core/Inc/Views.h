#ifndef __VIEWS_H
#define __VIEWS_H

#include "main.h"
#include "st7789.h"
#include "ws2812.h"


/* Views */
extern uint8_t wave_buf[]; // 每段缓冲区
extern THEMEs THEME_DPO_1;
extern THEMEs THEME_DPO_2;
extern THEMEs THEME_AFG_1;
extern THEMEs THEME_AFG_2;
extern THEMEs THEME_CONFIG;
extern THEMEs THEME_SINGLE;
extern THEMEs THEME_TRIGMODE;

void THEME_CONVER_565(THEMEs *theme);
void DrawLine(uint16_t part_w, uint16_t h, uint8_t *buf, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint8_t H, uint8_t L) ;
void DrawWaveSegment(uint16_t start_x, uint16_t part_w, uint16_t h, uint16_t x_offset,uint8_t H_DPO1, uint8_t L_DPO1,uint8_t H_DPO2, uint8_t L_DPO2) ;
void ST7789_DrawWave() ;




#endif
