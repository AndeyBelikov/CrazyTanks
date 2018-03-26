#include "Player.h"
#include "Items.h"

#include <conio.h>



Player::Player()
{
	setHealth(3);
	this->score = 0;
	this->direction = Direction::STOP;
}



Player::~Player()
{
}



// destroy the rocket by its coordinates
void Player::popRocket(int y, int x)
{
	for (int i = 0; i < rockets.size(); i++) {
		if (rockets[i]->y == y && rockets[i]->x == x)
			rockets.erase(rockets.begin() + i);
	}
}




void Player::input(World& world)
{
	// key codes
	const int space = 32;
	const int up = 72;
	const int left = 75;
	const int right = 77;
	const int down = 80;
	char ch;

	if (_kbhit()) {
		switch (ch = _getch())
		{
			case space: {
				shoot(world);
				break;
			}
			case up: {
				this->direction = Direction::UP;
				this->rocketDir = Direction::UP;
				break;
			}
			case left: {
				this->direction = Direction::LEFT;
				this->rocketDir = Direction::LEFT;
				break;
			}
			case right: {
				this->direction = Direction::RIGTH;
				this->rocketDir = Direction::RIGTH;
				break;
			}
			case down: {	
				this->direction = Direction::DOWN;
				this->rocketDir = Direction::DOWN;
				break;
			}
		}
	}
}



// move player tank in the world
void Player::move(World &world)
{
	switch (direction) {
		case Direction::LEFT : {
			if (world.arr[y][x - 1] == It::Border ||
				world.arr[y][x - 1] == It::Enemy ||
				world.arr[y][x - 1] == It::Wall ||
				world.arr[y][x - 1] == It::Gold) {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = It::Field;	// update previous player coord
			x--;
			world.arr[y][x] = It::Player;	// update next player coord
			break;
		}
		case Direction::RIGTH : {
			if (world.arr[y][x + 1] == It::Border ||
				world.arr[y][x + 1] == It::Enemy ||
				world.arr[y][x + 1] == It::Wall ||
				world.arr[y][x + 1] == It::Gold) {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = It::Field;	// update previous player coord
			x++;
			world.arr[y][x] = It::Player;	// update next player coord
			break;
		}
		case Direction::UP : {
			if (world.arr[y - 1][x] == It::Border ||
				world.arr[y - 1][x] == It::Enemy ||
				world.arr[y - 1][x] == It::Wall ||
				world.arr[y - 1][x] == It::Gold) {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = It::Field;	// update previous player coord
			y--;
			world.arr[y][x] = It::Player;	// update next player coord
			break;
		}
		case Direction::DOWN : {
			if (world.arr[y + 1][x] == It::Border ||
				world.arr[y + 1][x] == It::Enemy ||
				world.arr[y + 1][x] == It::Wall ||
				world.arr[y + 1][x] == It::Gold) {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = It::Field;	// update previous player coord
			y++;
			world.arr[y][x] = It::Player;	// update next player coord
			break;
		}
	}
}



void Player::placeInTheWorld(int heigth, int width, World& world)
{
	int playerX = heigth / 2;
	int playerY = width - 3;

	this->x = playerX;
	this->y = playerY;
	world.arr[playerY][playerX] = It::Player;
}



void Player::shoot(World& world)
{
	this->rockets.push_back(new Rocket(x, y, rocketDir));
}



void Player::logic(Rocket* roc, World& world)
{
	switch (roc->direction) {
		case Direction::LEFT: {
			// if first/second next player coordinate is a field
			if (world.arr[roc->y][roc->x - 1] == It::Field &&
				world.arr[roc->y][roc->x - 2] == It::Field) {
				world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x - 2] = It::Rocket;
				roc->x = roc->x - 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[roc->y][roc->x - 1] == It::Border ||
				world.arr[roc->y][roc->x - 2] == It::Border) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[roc->y][roc->x - 1] == It::Wall ||
				world.arr[roc->y][roc->x - 2] == It::Wall) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x - 1] == It::Wall ?
					world.arr[roc->y][roc->x - 1] = It::Field :
					world.arr[roc->y][roc->x - 2] = It::Field;
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[roc->y][roc->x - 1] == It::Enemy ||
				world.arr[roc->y][roc->x - 1] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x - 1] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[roc->y][roc->x - 2] == It::Enemy ||
				world.arr[roc->y][roc->x - 2] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x - 2] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			break;
		}

		case Direction::RIGTH: {
			// if first/second next player coordinate is a field
			if (world.arr[roc->y][roc->x + 1] == It::Field &&
				world.arr[roc->y][roc->x + 2] == It::Field) {
				world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x + 2] = It::Rocket;
				roc->x = roc->x + 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[roc->y][roc->x + 1] == It::Border ||
				world.arr[roc->y][roc->x + 2] == It::Border) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[roc->y][roc->x + 1] == It::Wall ||
				world.arr[roc->y][roc->x + 2] == It::Wall) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x + 1] == It::Wall ?
					world.arr[roc->y][roc->x + 1] = It::Field :
					world.arr[roc->y][roc->x + 2] = It::Field;
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[roc->y][roc->x + 1] == It::Enemy ||
				world.arr[roc->y][roc->x + 1] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x + 1] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[roc->y][roc->x + 2] == It::Enemy ||
				world.arr[roc->y][roc->x + 2] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y][roc->x + 2] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			break;
		}

		case Direction::UP: {
			// if first/second next player coordinate is a field
			if (world.arr[roc->y - 1][roc->x] == It::Field &&
				world.arr[roc->y - 2][roc->x] == It::Field) {
				world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y - 2][roc->x] = It::Rocket;
				roc->y = roc->y - 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[roc->y - 1][roc->x] == It::Border ||
				world.arr[roc->y - 2][roc->x] == It::Border) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[roc->y - 1][roc->x] == It::Wall ||
				world.arr[roc->y - 2][roc->x] == It::Wall) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y - 1][roc->x] == It::Wall ?
					world.arr[roc->y - 1][roc->x] = It::Field :
					world.arr[roc->y - 2][roc->x] = It::Field;
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[roc->y - 1][roc->x] == It::Enemy ||
				world.arr[roc->y - 1][roc->x] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y - 1][roc->x] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[roc->y - 2][roc->x] == It::Enemy ||
				world.arr[roc->y - 2][roc->x] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y - 2][roc->x] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			break;
		}

		case Direction::DOWN: {
			// if first/second next player coordinate is a field
			if (world.arr[roc->y + 1][roc->x] == It::Field &&
				world.arr[roc->y + 2][roc->x] == It::Field) {
				world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y + 2][roc->x] = It::Rocket;
				roc->y = roc->y + 2;
				break;
			}
			// if first/second next player coordinate is a border
			if (world.arr[roc->y + 1][roc->x] == It::Border ||
				world.arr[roc->y + 2][roc->x] == It::Border) {
				popRocket(roc->y, roc->x);
				if(world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				break;
			}
			// if first/second next player coordinate is a wall
			if (world.arr[roc->y + 1][roc->x] == It::Wall ||
				world.arr[roc->y + 2][roc->x] == It::Wall) {
				popRocket(roc->y, roc->x);
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y + 1][roc->x] == It::Wall ?
					world.arr[roc->y + 1][roc->x] = It::Field :
					world.arr[roc->y + 2][roc->x] = It::Field;
				break;
			}
			// if first next player coordinate is an enemy or a rocket
			if (world.arr[roc->y + 1][roc->x] == It::Enemy ||
				world.arr[roc->y + 1][roc->x] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y + 1][roc->x] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			// if second next player coordinate is an enemy or a rocket
			if (world.arr[roc->y + 2][roc->x] == It::Enemy ||
				world.arr[roc->y + 2][roc->x] == It::Rocket) {
				if (world.arr[roc->y][roc->x] != It::Player) 
					world.arr[roc->y][roc->x] = It::Field;
				world.arr[roc->y + 2][roc->x] = It::Field;
				score += 10;
				popRocket(roc->y, roc->x);
				break;
			}
			break;
		}
	}
}

int Player::getScore()
{
	return score;
}



