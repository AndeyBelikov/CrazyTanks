#pragma once
#include "World.h"
#include "Direction.h"
#include "DestructableObject.h"

class Rocket :
	public DestructableObject
{
public:	
	Rocket();
	~Rocket();
	int x;
	int y;
	Direction direction;
	Rocket(int, int, Direction);
	void logic(World&);
};

