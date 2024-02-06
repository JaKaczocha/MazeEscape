/*
 * Character.h
 *
 *  Created on: 31 sty 2024
 *      Author: User
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "JoyStick.h"

class Character {
public:
	Character(uint16_t xPos, uint16_t yPos, uint16_t size);
	virtual ~Character();

	void move(); // dorobić buffor na sumowanie ruchu tak aby wartości poniżej 1 się ładnie sumowały i ruszały postacia przy zsumowaniu do 1
				// (powolny ruch nawet przy małym wychyleniu)

	uint16_t getXPos() const;
	uint16_t getYPos() const;
	int16_t getXSpeed() const;
	int16_t getYSpeed() const;
	uint16_t getSize() const;
	uint16_t getColisionNumber() const;

	
	
	JoyStick joyStick; // możesz raczej to poprawić umiejscowienie może jakis getter czy inny wzorzec

private:
	void setXPos(uint16_t xPos); //nie wiem czy potrzebuje tego 
	void setYPos(uint16_t yPos); //nie wiem czy potrzebuje tego

	bool getColision(int16_t xPos, int16_t yPos,uint16_t color);
	void updateSpeed();

	uint16_t xPos, yPos;
	int16_t xSpeed, ySpeed;
	uint16_t size;
	uint16_t colisionNumber;
	
};

#endif /* CHARACTER_H_ */
