#pragma once

#include <thread>
#include "Player.h"
#include "Enemy.h"
#include "Rocket.h"
#include "World.h"
#include "Wall.h"
#include "Gold.h"


class Game
{
public:
	Game();
	~Game();
	void checkWall(World&, Wall*);
	void popWall(int, int);
	bool gameStatus();
	void startTheGame();
	static void timeInGame();
	void makeWalls();
	void makeCastle();
	bool checkEnemy(World&, Enemy*);
	void popEnemy(int, int);

private:
	int numberOfEnemies;
	int numberOfGold;
	World world;
	std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player);
	std::vector<Enemy*> enemies;
	std::vector<Wall*> walls;
	std::vector<Gold*> golds;
};

