#pragma once
#include "World.h"
#include "Direction.h"

class Rocket
{
public:	
	Rocket();
	~Rocket();
	int x;
	int y;
	char owner;
	Direction direction;
	Rocket(int, int, Direction, const char);
	void logic(World&);
};

