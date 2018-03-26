#include "Rocket.h"


Rocket::Rocket()
{

}



Rocket::Rocket(int x, int y, Direction dir)
{
	this->direction = dir;
	this->x = x;
	this->y = y;
}



Rocket::~Rocket()
{
}

