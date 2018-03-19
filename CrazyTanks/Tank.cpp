#include "Tank.h"


Tank::Tank()
{
}



Tank::~Tank()
{
}



bool Tank::isAlive()
{
	return this->health > 0 ? true : false;
}



void Tank::takeDamage()
{
	this->health--;
}


