#pragma once
#include "Tank.h"

class Enemy :
	public Tank
{
public:
	Enemy();
	~Enemy();
	void move(World&) override;
	void placeInTheWorld(int, int, World&) override;
	void shoot(World&) override;
	void logic(World&);
	void popRocket(int, int) override;
	Direction makeRundomDir();

private:
	int numberOfSteps = 0;
	int maxNumberOfSteps = 0;
};

