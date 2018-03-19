#include "World.h"



World::World()
{
}



World::~World()
{
}


void World::drawWorld()
{
	system("cls");
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++)
			std::cout << arr[i][j];
		std::cout << std::endl;
	}
}



void World::makeWorld()
{
	// describe the upper boundary
	for (int i = 0; i < width; i++)
		arr[0][i] = '#';

	// describe the lateral boundaries and mid
	for (int i = 1; i < heigth - 1; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				arr[i][j] = '#';
			else
				arr[i][j] = ' ';
		}
	}

	// describe the lower boundary
	for (int i = 0; i < width; i++)
		arr[width - 1][i] = '#';

	makeWalls();

	// describe the player position
	arr[heigth - 3][width / 2] = '0';
}



void World::makeWalls()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	// countDist - random wall length
	std::uniform_int_distribution<int> countDist(2, 4);

	// coordinateDist - random wall coordinate
	std::uniform_int_distribution<int> coordinateDist(1, 19);

	// count of horizontal / vertical alls
	int nHorizontalWalls = countDist(mt) + 7;
	int nVerticalWalls = countDist(mt) + 7;

	// create horizontal walls
	for (int i = 0; i < nHorizontalWalls; i++) {

		int xx = coordinateDist(mt);
		int yy = coordinateDist(mt);
		int distance = countDist(mt);

		for (int i = 0; i < distance; i++) {
			if (arr[xx + 1][yy] != '#' && xx < heigth && yy < width) {
				arr[xx++][yy] = '#';
			}
		}

	}

	// create vertical walls
	for (int i = 0; i < nVerticalWalls; i++) {

		int xx = coordinateDist(mt);
		int yy = coordinateDist(mt);
		int distance = countDist(mt);

		for (int i = 0; i < distance; i++) {
			if (arr[xx][yy + 1] != '#' && distance != 0 && xx < heigth && yy < width) {
				arr[xx][yy++] = '#';
			}
		}

	}
}
