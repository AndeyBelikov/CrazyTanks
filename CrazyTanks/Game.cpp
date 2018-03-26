#include "Game.h"
#include "Items.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include <Windows.h>
#include <random>

Game::Game()
{
	this->numberOfEnemies = 4;
	this->numberOfGold = 1;

	for (int i = 0; i < numberOfEnemies; i++) {
		enemies.push_back(new Enemy);
	}

	for (int i = 0; i < numberOfGold; i++) {
		golds.push_back(new Gold);
	}
}



Game::~Game()
{
}



void Game::timeInGame()
{
	int time = 0;
	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "You are " << ++time << "sec in the game" << std::flush << std::endl;
	}
}



void Game::makeWalls()
{
	int minWallLength = 2;
	int maxWallLength = 4;
	int minWallCoord = 1;
	int maxWallCoord = 19;
	int sevenWalls = 7;

	std::random_device rd;
	std::mt19937 mt(rd());

	// countDist - random wall length
	std::uniform_int_distribution<int> countDist(minWallLength, maxWallLength);

	// coordinateDist - random wall coordinate
	std::uniform_int_distribution<int> coordinateDist(minWallCoord, maxWallCoord);

	// count of horizontal / vertical walls
	int nHorizontalWalls = countDist(mt) + sevenWalls;
	int nVerticalWalls = countDist(mt) + sevenWalls;

	// create horizontal walls
	for (int i = 0; i < nHorizontalWalls; i++) {

		int xx = coordinateDist(mt);
		int yy = coordinateDist(mt);
		int distance = countDist(mt);

		// add walls to the world and push them back into vector
		for (int i = 0; i < distance; i++) {
			if (world.arr[xx + 1][yy] != It::Border && xx < world.heigth - 1 &&
				yy < world.width && world.arr[xx + 1][yy] != It::Wall && distance != 0) {
				world.arr[xx++][yy] = It::Wall;
				walls.push_back(new Wall(xx, yy));
			}
		}
	}

	// create vertical walls
	for (int i = 0; i < nVerticalWalls; i++) {

		int xx = coordinateDist(mt);
		int yy = coordinateDist(mt);
		int distance = countDist(mt);

		// add walls to the world and push them back into vector
		for (int i = 0; i < distance; i++) {
			if (world.arr[xx][yy + 1] != It::Border && distance != 0 &&
				xx < world.heigth - 1 && yy < world.width && world.arr[xx][yy + 1] != It::Wall) {
				world.arr[xx][yy++] = It::Wall;
				walls.push_back(new Wall(xx, yy));
			}
		}

	}
}



void Game::makeCastle()
{
	int castleX = 17;	//castle X coordinate
	int castleY = 1;	// castle Y coordinate

	world.arr[castleX][castleY] = It::Wall;
	world.arr[castleX][castleY + 1] = It::Wall;
	world.arr[castleX + 1][castleY + 1] = It::Wall;
	world.arr[castleX + 1][castleY] = It::Gold;
}



bool Game::checkEnemy(World& world, Enemy* enemy)
{
	// return false if enemy is not alive anymore
	if (world.arr[enemy->y][enemy->x] == It::Field) {
		popEnemy(enemy->y, enemy->x);
		return false;
	}
	else {
		return true;
	}
}



void Game::popEnemy(int y, int x)
{
	// delete died enemies from the vector
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->y == y && enemies[i]->x == x)
			enemies.erase(enemies.begin() + i);
	}
}



void Game::startTheGame() {

	// initialize our timer
	std::thread thr(timeInGame);
	thr.detach();

	world.makeWorld();
	makeWalls();
	makeCastle();

	// placing players and opponents on the map
	player->placeInTheWorld(world.heigth, world.width, world);
	std::for_each(enemies.begin(), enemies.end(), [this](auto _val) {
		_val->placeInTheWorld(world.heigth, world.width, world);
	});

	// main game loop
	while (gameStatus()) {
		world.drawWorld();
		std::cout << "Your score: " << player->getScore() << std::endl;

		player->input(world);

		std::for_each(player->rockets.begin(), player->rockets.end(), [this](auto _val) mutable
		{
			player->logic(_val, world);
		});

		//for (int i = 0; i < enemies.size(); i++) {
		//	if (!enemies[i]->rockets.empty()) enemies[i]->logic(world);
		//}

		std::for_each(enemies.begin(), enemies.end(), [this](auto _val) mutable
		{
			if (checkEnemy(world, _val))
				_val->move(world);
		});

		std::for_each(walls.begin(), walls.end(), [this](auto _val) mutable
		{
			checkWall(world, _val);
		});

		player->move(world);
	}
}


// ckeck health of the wall. if its health = 0, delete it
void Game::checkWall(World& world, Wall* wall)
{
	if (world.arr[wall->y][wall->x] == It::Field && wall->isAlive()) {
		wall->takeDamage();
		world.arr[wall->y][wall->x] = It::Wall;
	}
	if (!wall->isAlive()) {
		world.arr[wall->y][wall->x] = It::Field;
		popWall(wall->y, wall->x);
	}
}


// delete a wall by its coordinates
void Game::popWall(int y, int x)
{
	for (int i = 0; i < walls.size(); i++) {
		if (walls[i]->y == y && walls[i]->x == x)
			walls.erase(walls.begin() + i);
	}
}


bool Game::gameStatus() {
	return (player->isAlive() && !enemies.empty() && !golds.empty()) ? true : false;
}
