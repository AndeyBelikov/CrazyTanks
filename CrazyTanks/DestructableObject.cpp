#include "DestructableObject.h"



DestructableObject::DestructableObject()
{
}



DestructableObject::~DestructableObject()
{
}

void DestructableObject::destroy()
{
}

void DestructableObject::takeDamage()
{
	this->health--;
}

bool DestructableObject::isAlive()
{
	return this->health > 0 ? true : false;
}

int DestructableObject::getHealth()
{
	return health;
}

void DestructableObject::setHealth(int h)
{
	health = h;
}



