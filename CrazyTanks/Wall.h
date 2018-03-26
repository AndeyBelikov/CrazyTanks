#pragma once
#include "DestructableObject.h"

class Wall :
	public DestructableObject
{
public:
	Wall();
	Wall(int, int);
	~Wall();
};

