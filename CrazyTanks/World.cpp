#include "World.h"
#include "Items.h"

#include <Windows.h>
#include <conio.h>


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
		arr[0][i] = It::Border;

	// describe the lateral boundaries and mid
	for (int i = 1; i < heigth - 1; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				arr[i][j] = It::Border;
			else
				arr[i][j] = ' ';
		}
	}

	// describe the lower boundary
	for (int i = 0; i < width; i++)
		arr[width - 1][i] = It::Border;
}



void World::clearScreen()
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
