#include "World.h"



World::World()
{
}



World::~World()
{
}


void World::drawWorld()
{
	Sleep(100);
	clearScreen();
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
	makeCastle();

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

	// count of horizontal / vertical walls
	int nHorizontalWalls = countDist(mt) + 7;
	int nVerticalWalls = countDist(mt) + 7;

	// create horizontal walls
	for (int i = 0; i < nHorizontalWalls; i++) {

		int xx = coordinateDist(mt);
		int yy = coordinateDist(mt);
		int distance = countDist(mt);

		for (int i = 0; i < distance; i++) {
			if (arr[xx + 1][yy] != '#' && xx < heigth - 1 && yy < width) {
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
			if (arr[xx][yy + 1] != '#' && distance != 0 && xx < heigth - 1 && yy < width) {
				arr[xx][yy++] = '#';
			}
		}

	}
}

void World::makeCastle()
{
	arr[17][1] = '#';
	arr[17][2] = '#';
	arr[18][2] = '#';
	arr[18][1] = 'G';
}

void World::clearScreen()
{
	{
		HANDLE                     hStdOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD                      count;
		DWORD                      cellCount;
		COORD                      homeCoords = { 0, 0 };

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;

		/* Get the number of cells in the current buffer */
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X *csbi.dwSize.Y;

		/* Fill the entire buffer with spaces */
		if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Move the cursor home */
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}
}
