#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "fsl_power.h"

extern "C" {
#include "lcd.h"
#include "back.h"
}

#include "Map.h"
#include "JoyStick.h"


char sbuff[32];
uint16_t colCounter=0;
uint16_t coursorX=0, coursorY=0;



void setCursor(uint16_t x, uint16_t y, uint16_t size, uint16_t color) {
	LCD_Draw_FillRect(x,y,x+size,y+size, color);
}
bool getColision(uint16_t x, uint16_t y, uint16_t size, uint16_t color) {
	for (uint16_t i = x; i <= x+size; i++) {
		for (uint16_t j = y; j <= y+size; j++) {
			if(LCD_Get_Point(i,j) == color){
				return true;
			}
		}
	}
	return false;
}
/*
 * @brief Application entry point.
 */

int main(void) {


	/* Disable LDOGPADC power down */
	POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif
	JoyStick myJoyStick;
	myJoyStick.initialize(); // musi być przed LCD_Init

	LCD_Init(FLEXCOMM3_PERIPHERAL);

	while(1) {
		if(myJoyStick.isReady()) {
			coursorX=myJoyStick.getJoyAxisX()/409;
			coursorY=LCD_HEIGHT-(myJoyStick.getJoyAxisY()/511);
			if(coursorX >= LCD_WIDTH){
				coursorX = LCD_WIDTH-1;
			}
			if(coursorY >= LCD_HEIGHT){
				coursorY = LCD_HEIGHT-1;
			}
			LCD_Set_Bitmap((uint16_t*)back_160x128);
			if(getColision(coursorX, coursorY, 5, 0xFFE0)){
				colCounter++;
			}
			setCursor(coursorX, coursorY, 5, 0xF800);
			LCD_7seg( 10, 2, colCounter, 5, 0xF800);
			LCD_GramRefresh();
			myJoyStick.setReady(false);
		}
	}
	return 0 ;
}
