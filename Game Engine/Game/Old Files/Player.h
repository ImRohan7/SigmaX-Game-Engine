#pragma once
#include"Map.h"
#include "Math/Vectors/Vector2.h"

class Player
{
	public:
	
	Vector2 position;
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
