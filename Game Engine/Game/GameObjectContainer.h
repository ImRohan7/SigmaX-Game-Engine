#pragma once
#pragma once
#include "ZombieController.h"
#include "Vector2D.h"

class GameObjectContainer {

public:
	GameObjectContainer * next;

	ZombieController* getController()
	{
		return mZombie;
	}

private:
	ZombieController * mZombie;
};