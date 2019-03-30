#include "stdafx.h"
#include "Map.h"


Map::Map()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			mapStatus[i][j] = 0;
		}
	}
}

Map::~Map()
{

}
