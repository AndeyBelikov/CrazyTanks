#pragma once

#include "World.h"
#include "Direction.h"
#include "Rocket.h"
#include "DestructableObject.h"
#include <vector>
#include "IMovable.h"
#include "IShootable.h"


class Tank :
	public DestructableObject,
	public IMovable,
	public IShootable
{

public:
	virtual void placeInTheWorld(int, int) = 0;
	virtual void shoot(World&) = 0;
	virtual void move(World&) = 0;
	std::vector<Rocket*> rockets;
	Direction direction;
	Tank();
	virtual ~Tank();
};

