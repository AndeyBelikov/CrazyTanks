#include "Enemy.h"
#include "Items.h"



Enemy::Enemy()
{
	setHealth(1);
	this->numberOfSteps = 0;
	this->maxNumberOfSteps = 7;
}



Enemy::~Enemy()
{
}



void Enemy::move(World& world)
{
	switch (this->direction) {
		case Direction::LEFT : {
			if (world.arr[y][x] == It::Field) break;
			// the enemy will fire every fifth move
			if (numberOfSteps == maxNumberOfSteps - 2) {
				this->rocketDir = Direction::LEFT;
				shoot(world);								
			}
			// add a bit of random in future moving
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			// next move
			if (world.arr[y][x - 1] == It::Field) {
				world.arr[y][x] = It::Field;
				world.arr[y][x - 1] = It::Enemy;
				x--;
				numberOfSteps++;
				break;
			}
			// change enemy direction
			this->direction = makeRundomDir();
			break;
		}

		case Direction::RIGTH : {
			if (world.arr[y][x] == It::Field) break;
			// the enemy will fire every fifth move
			if (numberOfSteps == maxNumberOfSteps - 2) {
				this->rocketDir = Direction::RIGTH;
				shoot(world);
			}
			// add a bit of random in future moving
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			// next move
			if (world.arr[y][x + 1] == It::Field) {
				world.arr[y][x] = It::Field;
				world.arr[y][x + 1] = It::Enemy;
				x++;
				numberOfSteps++;
				break;
			}
			// change enemy direction
			this->direction = makeRundomDir();
			break;
		}

		case Direction::UP : {
			if (world.arr[y][x] == It::Field) break;
			// the enemy will fire every fifth move
			if (numberOfSteps == maxNumberOfSteps - 2) {
				this->rocketDir = Direction::UP;
				shoot(world);
			}
			// add a bit of random in future moving
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			// next move
			if (world.arr[y - 1][x] == It::Field) {
				world.arr[y][x] = It::Field;
				world.arr[y - 1][x] = It::Enemy;
				y--;
				numberOfSteps++;
				break;
			}
			// change enemy direction
			this->direction = makeRundomDir();
			break;
		}

		case Direction::DOWN : {
			if (world.arr[y][x] == It::Field) break;
			// the enemy will fire every fifth move
			if (numberOfSteps == maxNumberOfSteps - 2) {
				this->rocketDir = Direction::DOWN;
				shoot(world);
			}
			// add a bit of random in future moving
			if (numberOfSteps > maxNumberOfSteps) {
				this->direction = makeRundomDir();
				numberOfSteps = 0;
				break;
			}
			// next move
			if (world.arr[y + 1][x] == It::Field) {
				world.arr[y][x] = It::Field;
				world.arr[y + 1][x] = It::Enemy;
				y++;
				numberOfSteps++;
				break;
			}
			// change enemy direction
			this->direction = makeRundomDir();
			break;
		}
	}
}



void Enemy::placeInTheWorld(int height, int width, World& world)
{
	int minCoordinate = 1;
	int maxCoordinate = 18;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(minCoordinate, maxCoordinate);

	this->x = dist(mt);
	this->y = dist(mt);
	this->direction = makeRundomDir();

	world.arr[y][x] = It::Enemy;
}



void Enemy::shoot(World& world)
{
	this->rockets.push_back(new Rocket(x, y, rocketDir));
}



void Enemy::logic(World &world)
{
	for (int i = 0; i < this->rockets.size(); i++) {
		switch (direction) {
		case Direction::LEFT: {
			// if first/second next player coordinate is a field
			if (world.arr[rockets[i]->y][rockets[i]->x - 1] == It::Field &&
				world.arr[rockets[i]->y][rockets[i]->x - 2] == It::Field) {
				world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x - 2] = It::Rocket;
				rockets[i]->x = rockets[i]->x - 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[rockets[i]->y][rockets[i]->x - 1] == It::Border ||
				world.arr[rockets[i]->y][rockets[i]->x - 2] == It::Border) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[rockets[i]->y][rockets[i]->x - 1] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x - 1] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
			}
			// if first/second next player coordinate is a wall
			else if (world.arr[rockets[i]->y][rockets[i]->x - 2] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x - 2] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y][rockets[i]->x - 1] == It::Enemy ||
				world.arr[rockets[i]->y][rockets[i]->x - 1] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x - 1] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y][rockets[i]->x - 2] == It::Enemy ||
				world.arr[rockets[i]->y][rockets[i]->x - 2] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x - 2] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			break;
		}

		case Direction::RIGTH: {
			// if first/second next player coordinate is a field
			if (world.arr[rockets[i]->y][rockets[i]->x + 1] == It::Field &&
				world.arr[rockets[i]->y][rockets[i]->x + 2] == It::Field) {
				world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x + 2] = It::Rocket;
				rockets[i]->x = rockets[i]->x + 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[rockets[i]->y][rockets[i]->x + 1] == It::Border ||
				world.arr[rockets[i]->y][rockets[i]->x + 2] == It::Border) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[rockets[i]->y][rockets[i]->x + 1] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x + 1] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
			}
			// if first/second next player coordinate is a wall
			else if (world.arr[rockets[i]->y][rockets[i]->x + 2] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x + 2] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y][rockets[i]->x + 1] == It::Enemy ||
				world.arr[rockets[i]->y][rockets[i]->x + 1] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x + 1] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y][rockets[i]->x + 2] == It::Enemy ||
				world.arr[rockets[i]->y][rockets[i]->x + 2] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y][rockets[i]->x + 2] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			break;
		}

		case Direction::UP: {
			// if first/second next player coordinate is a field
			if (world.arr[rockets[i]->y - 1][rockets[i]->x] == It::Field &&
				world.arr[rockets[i]->y - 2][rockets[i]->x] == It::Field) {
				world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y - 2][rockets[i]->x] = It::Rocket;
				rockets[i]->y = rockets[i]->y - 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[rockets[i]->y - 1][rockets[i]->x] == It::Border ||
				world.arr[rockets[i]->y - 2][rockets[i]->x] == It::Border) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[rockets[i]->y - 1][rockets[i]->x] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y - 1][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
			}
			// if first/second next player coordinate is a wall
			else if (world.arr[rockets[i]->y - 2][rockets[i]->x] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y - 2][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y - 1][rockets[i]->x] == It::Enemy ||
				world.arr[rockets[i]->y - 1][rockets[i]->x] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y - 1][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y - 2][rockets[i]->x] == It::Enemy ||
				world.arr[rockets[i]->y - 2][rockets[i]->x] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y - 2][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			break;
		}

		case Direction::DOWN: {
			// if first/second next player coordinate is a field
			if (world.arr[rockets[i]->y + 1][rockets[i]->x] == It::Field &&
				world.arr[rockets[i]->y + 2][rockets[i]->x] == It::Field) {
				world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y + 2][rockets[i]->x] = It::Rocket;
				rockets[i]->y = rockets[i]->y + 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[rockets[i]->y + 1][rockets[i]->x] == It::Border ||
				world.arr[rockets[i]->y + 2][rockets[i]->x] == It::Border) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[rockets[i]->y + 1][rockets[i]->x] == It::Wall) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y + 1][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
			}
			// if first/second next player coordinate is a wall
			else if (world.arr[rockets[i]->y + 2][rockets[i]->x] == It::Wall) {
				popRocket(rockets[i]->y, rockets[i]->x);
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y + 2][rockets[i]->x] = It::Field;
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y + 1][rockets[i]->x] == It::Enemy ||
				world.arr[rockets[i]->y + 1][rockets[i]->x] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y + 1][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[rockets[i]->y + 2][rockets[i]->x] == It::Enemy ||
				world.arr[rockets[i]->y + 2][rockets[i]->x] == It::Rocket) {
				if (world.arr[rockets[i]->y][rockets[i]->x] != It::Player)
					world.arr[rockets[i]->y][rockets[i]->x] = It::Field;
				world.arr[rockets[i]->y + 2][rockets[i]->x] = It::Field;
				popRocket(rockets[i]->y, rockets[i]->x);
				break;
			}
			break;
		}
		}
	}
}


// delete rocket by its coordinates
void Enemy::popRocket(int y, int x)
{
	for (int i = 0; i < rockets.size(); i++) {
		if (rockets[i]->y == y && rockets[i]->x == x)
			rockets.erase(rockets.begin() + i);
	}
}


// return random direction
Direction Enemy::makeRundomDir()
{
	int minRandN = 0;
	int maxRandN = 4;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> randomDirection(minRandN, maxRandN);

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
