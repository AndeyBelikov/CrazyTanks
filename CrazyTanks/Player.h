#pragma once
#include "Tank.h"

class Player :
	public Tank
{
public:	
	Player();
	~Player();
	void popRocket(int, int) override;
	void input(World&);
	void move(World& world) override;
	void placeInTheWorld(int, int, World&) override;
	void shoot(World&) override;
	void logic(Rocket*, World&);
	int getScore();
private:
	int score;
};

