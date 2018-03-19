#include "Enemy.h"



Enemy::Enemy()
{
	this->health = 1;
	this->numberOfSteps = 0;
	this->maxNumberOfSteps = 7;
}



Enemy::~Enemy()
{
}



void Enemy::logic(World& world)
{
	world.arr[y][x] = 'X';

	switch (this->direction) {
		case Direction::LEFT : {

			//if (numberOfSteps == maxNumberOfSteps - 2) {
			//	shoot(world);								// the enemy will fire every fifth move
			//}

			// add a bit of randomness
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			if (world.arr[y][x - 1] == ' ') {
				world.arr[y][x] = ' ';
				world.arr[y][x - 1] = 'X';
				x--;
				numberOfSteps++;
				break;
			}
			this->direction = makeRundomDir();
			break;
		}
		case Direction::RIGTH : {
			//if (numberOfSteps == maxNumberOfSteps - 2) {
			//	shoot(world);
			//}
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			if (world.arr[y][x + 1] == ' ') {
				world.arr[y][x] = ' ';
				world.arr[y][x + 1] = 'X';
				x++;
				numberOfSteps++;
				break;
			}
			this->direction = makeRundomDir();
			break;
		}
		case Direction::UP : {
			//if (numberOfSteps == maxNumberOfSteps - 2) {
			//	shoot(world);
			//}
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			if (world.arr[y - 1][x] == ' ') {
				world.arr[y][x] = ' ';
				world.arr[y - 1][x] = 'X';
				y--;
				numberOfSteps++;
				break;
			}
			this->direction = makeRundomDir();
			break;
		}
		case Direction::DOWN : {
			//if (numberOfSteps == maxNumberOfSteps - 2) {
			//	shoot(world);
			//}
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			if (world.arr[y + 1][x] == ' ') {
				world.arr[y][x] = ' ';
				world.arr[y + 1][x] = 'X';
				y++;
				numberOfSteps++;
				break;
			}
			this->direction = makeRundomDir();
			break;
		}
	}
}



void Enemy::placeInTheWorld(int height, int width)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 18);
	this->x = dist(mt);
	this->y = dist(mt);
	this->direction = makeRundomDir();
}



void Enemy::shoot(World& world)
{
	this->rockets.push_back(new Rocket(x, y, direction, 'X'));
}



Direction Enemy::makeRundomDir()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> randomDirection(0, 4);
	switch (randomDirection(mt))
	{
		case 0: {
			return Direction::UP;
			break;
		}
		case 1: {
			return Direction::DOWN;
			break;
		}
		case 2: {
			return Direction::LEFT;
			break;
		}
		case 3: {
			return Direction::RIGTH;
			break;
		}
		default : return Direction::UP;
	}
}
