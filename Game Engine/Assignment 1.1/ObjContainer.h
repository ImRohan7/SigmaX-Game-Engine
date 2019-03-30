#pragma once
#pragma once
#include "ZombieController.h"
#include "Vector2D.h"

class ObjContainer {

public:
	ObjContainer * next;

	ZombieController* getController()
	{
		return mZombie;
	}

private:
	ZombieController * mZombie;
};