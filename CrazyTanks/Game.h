#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Rocket.h"
#include "World.h"
#include "Wall.h"
#include "Gold.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <thread>
#include <chrono>
#include <Windows.h>


class Game
{
public:
	Game();
	World world;
	//std::shared_ptr<World> world = std::shared_ptr<World>(new World);
	// i made shared_ptr because of logic that i delete later


	std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player);
	//std::vector<Enemy*> enemies;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Wall>> walls;
	std::vector<std::shared_ptr<Gold>> golds;

	bool gameStatus();
	int numberOfEnemies;
	int numberOfGold;
	void startTheGame();
	static void timeInGame();
	~Game();
};

