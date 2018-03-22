#pragma once

class IDestroyable {
	virtual void destroy() = 0;
	virtual void takeDamage() = 0;
};