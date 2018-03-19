#pragma once

#include "World.h"
#include "Direction.h"
#include "Rocket.h"
#include <vector>


class Tank
{

public:
	bool isAlive();
	void takeDamage();
	virtual void logic(World&) = 0;
	virtual void placeInTheWorld(int, int) = 0;
	virtual void shoot(World&) = 0;
	std::vector<Rocket*> rockets;
	int health;
	int x;
	int y;
	Direction direction;
	Tank();
	virtual ~Tank();
};

