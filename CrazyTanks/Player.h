#pragma once
#include "Tank.h"
#include <conio.h>

class Player :
	public Tank
{
public:	
	Player();
	~Player();
	int score;
	Direction direction;
	void input(World&);
	void logic(World& world) override;
	void placeInTheWorld(int, int) override;
	void shoot(World&) override;

};

