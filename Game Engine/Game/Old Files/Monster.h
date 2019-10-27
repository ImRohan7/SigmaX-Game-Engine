#pragma once
#include"stdlib.h"
#include"time.h"
#include"iostream"
#include "Math/Vectors/Vector2.h"
#include "Map.h"
#include "Mystring/MyString.h"
#include "assert.h"

class Monster
{
public:

	Monster* next;
	Vector2 position;

	int lifetime;
	char* name;
		
		void createMonster() 
		{
			/*int randX, randY;
			char temp[50];

			std::cout << "Enter the Name for Monster :";
			std::cin >> temp;

			assert(temp!=NULL);

			name = new char[m_countLength(temp) + 1];
			memcpy(name, temp, m_countLength(temp) + 1);

			lifetime = rand() % 10 + 0;
			srand(time(NULL));
			randX = rand() % 19 + 0;
			randY = rand() % 19 + 0;

			position.x(randX);
			position.y(randY);*/
		}

		void updateMonsterPos(const int &x1,const int &y1)
		{
			position.x(x1);
			position.y(y1);

			if (position.x() > 20) { position.x(0); }
			if (position.y() > 20) { position.y(0); }
			if (position.x() < 0) { position.x(20); }
			if (position.y() < 0) { position.x(20); }

			lifetime++;
		}

		Monster();
		~Monster();
};
