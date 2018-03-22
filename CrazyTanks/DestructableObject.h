#pragma once
#include "Object.h"
#include "IDestroyable.h"

class DestructableObject :
	public Object,
	public IDestroyable
{
public:
	DestructableObject();
	~DestructableObject();
	void destroy() override;
	void takeDamage() override;
	bool isAlive();

	int health;
	//bool isAlive;
};

