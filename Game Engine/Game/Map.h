#pragma once
class Map
{
public:
	int mapStatus[20][20]; //0 = empty 1 = player 2 = monster

	Map();
	~Map();

	inline void updateMap_Player(int x1, int y1, int x2, int y2)
	{
			mapStatus[x1][y1] = 0;
			mapStatus[x2][y2] = 1;
	}

	inline void updateMap_Monster(int x1, int y1, int x2, int y2)
	{
		mapStatus[x1][y1] = 0;
		mapStatus[x2][y2] = 2;
	}

	inline void placeOnMap_Player(const int &x,const int &y) 
	{
		mapStatus[x][y] =1;
	}

	inline void placeOnMap_Monster(int x, int y)
	{
		mapStatus[x][y] = 2;
	}
};