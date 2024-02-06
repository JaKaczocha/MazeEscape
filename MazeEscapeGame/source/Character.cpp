/*
 * Character.cpp
 *
 *  Created on: 31 sty 2024
 *      Author: User
 */

#include <Character.h>
extern "C" {
#include "lcd.h"
}

#include <Cmath>


Character::Character(uint16_t x_Pos, uint16_t y_Pos, uint16_t charSize) :
	xPos(x_Pos), yPos(y_Pos), size(charSize), winStatus(false),colisionNumber(0)
{

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

void Character::move()
{
	updateSpeed();

	int16_t direction;
	
	for (int i = 0; i < std::abs(xSpeed); i++)
	{
		direction = (xSpeed > 0) ? 1 : -1;
		if(getColision(xPos + direction, yPos,0xFFE0,0x051d))
		{
			break;
		}
		xPos += direction;

		if (xPos >= LCD_WIDTH)
		{
			xPos = LCD_WIDTH - 1;
			break;
		}
	}
	

	for (int i = 0; i < std::abs(ySpeed); i++)
	{
		direction = (ySpeed > 0) ? 1 : -1;
		if(getColision(xPos, yPos + direction,0xFFE0,0x051d))
		{
			break;
		}
		yPos += direction;

		if (yPos >= LCD_WIDTH)
		{
			yPos = LCD_WIDTH - 1;
			break;
		}
	}
}



bool Character::getColision( int16_t futureX, int16_t futureY,uint16_t color, uint16_t winColor) {
	for (uint16_t i = futureX; i <= futureX+size; i++) {
		for (uint16_t j = futureY; j <= futureY+size; j++) {
			if(LCD_Get_Point(i,j) == color){
				colisionNumber++;
				return true;
			}
			if(LCD_Get_Point(i,j) == winColor){
				winStatus = true;
				return true;
			}
		}
	}
	return false;
}

void Character::updateSpeed()
{
	xSpeed = static_cast<int16_t>( ((joyStick.getJoyAxisX() - 32767 ) / 409) * 0.1 * -1 );
	ySpeed = static_cast<int16_t>( ((joyStick.getJoyAxisY() - 32767 ) / 511) * 0.1 );
}


uint16_t Character::getXPos() const
{
    return xPos;
}

uint16_t Character::getYPos() const 
{
	return yPos;
}

int16_t Character::getXSpeed() const 
{
	return xSpeed;
}

int16_t Character::getYSpeed() const 
{
	return ySpeed;
}

uint16_t Character::getSize() const
{
    return size;
}

uint16_t Character::getColisionNumber() const
{
    return colisionNumber;
}
bool Character::getWinStatus() const
{
	return winStatus;
}

void Character::setXPos(uint16_t xPos) 
{
	this->xPos = xPos;
}

void Character::setYPos(uint16_t yPos)
{
	this->yPos = yPos;
}
