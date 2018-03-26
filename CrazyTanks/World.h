#pragma once
#include <random>
#include <iostream>

class World
{
public:
	static const int width = 20;
	static const int heigth = 20;
	char arr[heigth][width];

	void drawWorld();
	void makeWorld();
	void clearScreen();
	World();
	~World();
};

