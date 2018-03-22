#pragma once
#include <random>
#include <iostream>
#include <Windows.h>
#include <conio.h>

class World
{
public:
	static const int width = 20;
	static const int heigth = 20;
	char arr[heigth][width];

	void drawWorld();
	void makeWorld();
	void makeWalls();
	void makeCastle();
	void clearScreen();
	World();
	~World();
};

