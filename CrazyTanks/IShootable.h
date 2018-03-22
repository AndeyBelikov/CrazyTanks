#pragma once

#include "World.h"

class IShootable {
	virtual void shoot(World&) = 0;
};