#include "Player.h"
#include "Game.h"

Player::Player()
{
	this->health = 3;
	this->score = 0;
	this->direction = Direction::STOP;
}



Player::~Player()
{
}



void Player::input(World& world)
{
	char ch;
	if (_kbhit()) {
		switch (ch = _getch())
		{
			case 32: {			// space
				//shoot(world);
				break;
			}
			case 72: {			
				this->direction = Direction::UP;
				break;
			}
			case 75: {	
				this->direction = Direction::LEFT;
				break;
			}
			case 77: {		
				this->direction = Direction::RIGTH;
				break;
			}
			case 80: {	
				this->direction = Direction::DOWN;
				break;
			}
		}
	}
}


// check next position. if # / X - stop moving
// else make next move

void Player::move(World &world)
{
	switch (direction) {
		case Direction::LEFT : {
			if (world.arr[y][x - 1] == '#' || world.arr[y][x - 1] == 'X') {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = ' ';
			x--;
			world.arr[y][x] = '0';
			break;
		}
		case Direction::RIGTH : {
			if (world.arr[y][x + 1] == '#' || world.arr[y][x + 1] == 'X') {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = ' ';
			x++;
			world.arr[y][x] = '0';
			break;
		}
		case Direction::UP : {
			if (world.arr[y - 1][x] == '#' || world.arr[y - 1][x] == 'X') {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = ' ';
			y--;
			world.arr[y][x] = '0';
			break;
		}
		case Direction::DOWN : {
			if (world.arr[y + 1][x] == '#' || world.arr[y + 1][x] == 'X') {
				direction = Direction::STOP;
				break;
			}
			world.arr[y][x] = ' ';
			y++;
			world.arr[y][x] = '0';
			break;
		}
	}

	// possible logic of a rocket

	//for (int i = 0; i < rockets.size(); i++) {
	//	switch (rockets[i]->direction) {
	//		case Direction::LEFT:
	//			
	//		case Direction::RIGTH:
	//			
	//		case Direction::UP:
	//			
	//		case Direction::DOWN:
	//			
	//	}
	//}
}



void Player::placeInTheWorld(int height, int width)
{
	this->x = height / 2;
	this->y = width - 3;
}



void Player::shoot(World& world)
{
	this->rockets.push_back(new Rocket(x, y, direction));
}



