#include "Wall.h"


Wall::Wall()
{
}


Wall::Wall(int y, int x)
{
	this->y = y;
	this->x = x;
	setHealth(2);
}


Wall::~Wall()
{
}
