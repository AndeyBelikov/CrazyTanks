#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Rocket.h"
#include "World.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>


class Game
{
public:
	Game();
	World world;
	//std::shared_ptr<World> world = std::shared_ptr<World>(new World);
	// i made shared_ptr because of logic that i delete later
	std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player);
	std::vector<Enemy*> enemies;

	bool gameStatus();
	int numberOfEnemies;
	void startTheGame();
	static void timeInGame();
	~Game();
};

