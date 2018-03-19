#pragma once
#include "Tank.h"
#include "World.h"

class Enemy :
	public Tank
{
public:
	Enemy();
	~Enemy();
	Direction direction;
	int numberOfSteps;
	int maxNumberOfSteps;
	void logic(World&) override;
	void placeInTheWorld(int, int) override;
	void shoot(World&) override;
	Direction makeRundomDir();
};

