#pragma once

#include "World.h"

class IMovable {
	virtual void move(World&) = 0;
};