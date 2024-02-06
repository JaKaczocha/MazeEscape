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
#include "Character.h"

char sbuff[32];
uint16_t colCounter=0;
uint16_t coursorX=0, coursorY=0;
bool debugON = true;


void setCursor(uint16_t x, uint16_t y, uint16_t size, uint16_t color) {
	LCD_Draw_FillRect(x,y,x+size,y+size, color);
}

bool getWin( int16_t futureX, int16_t futureY,uint16_t size, uint16_t color) {
	for (uint16_t i = futureX; i <= futureX+size; i++) {
		for (uint16_t j = futureY; j <= futureY+size; j++) {
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

	Character character(55,50,5);
	Map map(back_160x128,160,128);

	LCD_Init(FLEXCOMM3_PERIPHERAL);

	constexpr int bufferSize = 60;
	constexpr int floatBufferSize = 10;

	char buffer[bufferSize];
	char floatBuffer[floatBufferSize];

	while(1) {
		if(character.joyStick.isReady()) {
			character.move();

			coursorX= character.getXPos();
			coursorY= character.getYPos();

			LCD_Set_Bitmap(map.getMap());

			setCursor(coursorX, coursorY, 5, 0xF800);
			
			if(!character.getWinStatus())
			{
				colCounter= character.getColisionNumber();
			}
			
			LCD_7seg( 10, 2, colCounter, 5, 0xF800);

			// lcd debug
			if (debugON)
			{

			    snprintf(buffer, sizeof(buffer), "X:%3d Xspd:%2d cC:%d", coursorX, character.getXSpeed(),colCounter);
			    LCD_Puts(2, 5, buffer, 0xffffff);


			    snprintf(buffer, sizeof(buffer), "Y:%3d Yspd:%2d", coursorY, character.getYSpeed());
			    LCD_Puts(2, 15, buffer, 0xffffff);

			    snprintf(buffer, sizeof(buffer), "Xax:%5d Yax:%5d ",  character.joyStick.getJoyAxisX(),character.joyStick.getJoyAxisY());
			    LCD_Puts(2, 25, buffer, 0xffffff);
			}




			LCD_GramRefresh();


			character.joyStick.setReady(false);
		}
	}
	return 0 ;
}
