#include "Views.h"


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

THEMEs THEME_TRIGMODE = {
  .MAIN = 0x0F0000,
  .WAKE = 0x000F00,
  .SHUT = 0x00000F,
};

THEMEs THEME_SINGLE = {
  .MAIN = 0x0F0000,
  .WAKE = 0x000F00,
  .SHUT = 0x000000,
};

THEMEs THEME_CONFIG = {0};

void THEME_CONVER_565(THEMEs *theme)
{
  theme->MAIN_565 = convert_24bit_to_16bit(theme->MAIN);
  theme->WAKE_565 = convert_24bit_to_16bit(theme->WAKE);
  theme->SHUT_565 = convert_24bit_to_16bit(theme->SHUT);
}



uint8_t wave_buf[141 * 204 * 2]={0}; // 每段缓冲区


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
    uint16_t part_w = w / 2;

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
    // DrawWaveSegment(2 * part_w, part_w, h, x + 2 * part_w, H_DPO1, L_DPO1, H_DPO2, L_DPO2);+

    ST7789_UnSelect();
}
