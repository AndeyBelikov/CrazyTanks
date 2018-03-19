#include "Rocket.h"


Rocket::Rocket()
{

}



Rocket::Rocket(int x, int y, Direction dir, const char ch)
{
	this->owner = ch;
	this->x = x;
	this->y = y;
	this->direction = dir;
}



Rocket::~Rocket()
{
}


// future possible logic of a rocket (not done yet)
void Rocket::logic(World& world)
{
	switch (direction) {
		case Direction::LEFT: {

			break;
		}
		case Direction::RIGTH: {

			break;
		}
		case Direction::UP: {

			break;
		}
		case Direction::DOWN: {

			break;
		}
	}
}
