#pragma once
#include"Map.h"
#include "Vector2D.h"

class Player
{
	public:
	
	Vector2D position;
	char *name;

	void updatePlayerPos(const int &x1,const int &y1)
	{
		position.x(x1);
		position.y(y1);

		if (position.x() > 20) { position.x(0); }
		if (position.y() > 20) { position.y(0); }
		if (position.x() < 0) { position.x(20); }
		if (position.y() < 0) { position.x(20); }
	}
	
	Player();
	~Player();
};
