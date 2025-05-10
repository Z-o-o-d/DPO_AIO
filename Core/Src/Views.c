#include "Views.h"




void View_KingKong(void){
		ST7789_DrawTriangle(20, 210, 40, 200, 40, 220, WHITE);
		ST7789_DrawCircle(90, 210, 10, WHITE);
		ST7789_DrawRectangle(140, 200, 160, 220, WHITE);
	}


void View_DoubaoWelcome(void){
		ST7789_DrawImage(10, 10, 160, 160, (uint16_t *)doubao);
		ST7789_WriteString(0, 180, " !\"#$\%&\'\()", Han_Array32, WHITE, BLACK);
//		ST7789_WriteString(170, 180, "", Han_Array, WHITE, BLACK);
	}


	
	

void View_NIR(void){
	ST7789_DrawImage(10, 10, 160, 160, (uint16_t *)doubao);
	ST7789_WriteString(0, 180, " !\"#$\%&\'\()", Han_Array32, WHITE, BLACK);


}