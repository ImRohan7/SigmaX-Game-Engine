//#include <stdlib.h>
//
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#endif // _DEBUG
//
//#include "stdafx.h"
//#include "iostream"
//#include "Player.h"
//#include "Monster.h"
//#include "Map.h"
//#include "time.h"
//#include "Vector2D.h"
//#include "assert.h"
//#include "ConsolePrint.h"
//#include "Unit_test_const.cpp"
//#include "Vector3d.h"
//#include "GameObject.h"
//#include "PlayerController.h"
//#include "ZombieController.h"
//#include "HeapManagerProxy.h"
//#include "assert.h"
//#include "windows.h"
//#include "Allocator.h"
//#include "MyString.h"
//
//int n,oldX,oldY;
//Map map;
//
//
//#if HEAP_DEBUG == 1
//#define LOG(x) std::cout << x << std::endl
//#elif defined(HEAP_RELEASE)
//#define LOG(x)
//#endif
//
//
//void monster_AI(Player*, Monster*, Map);
//void printDetails(Player*, Monster*);
//bool checkForLife(Player*, Map);
//void addMonster(Monster*);
////
////int main()
////{
////	LOG("Starting");
////
////	Vector2D test;
////	test.Negate();
////
////	GameObject Player;
////	std::cout << Player.getNameLength();
////	std::cout << Player.getName();
////
////#ifdef _DEBUG
////	_CrtDumpMemoryLeaks();
////#endif // DEBUG
////
////	DEBUG_PRINT("Memory Cleared !");
////	
////	return 0;
////
////}
//
//void printDetails(Player* P, Monster* m)
//{
//	std::cout << P->name;
//	std::cout << " is at (" << P->position.x() << "," << P->position.y() << ")" << std::endl;
//
//	Monster* print = m;
//	
//	while (print != NULL) {
//		std::cout << "Monster " << print->name << " is at (" << print->position.x() << "," << print->position.y() << ") LifeTime: " << print->lifetime << std::endl;
//		print = print->next;
//	}
//}
//
//void monster_AI(Player* p,Monster* head,Map mp)
//{
//	Monster* current = head;
//	Monster* previous = head;
//	
//	if (head->lifetime >= 20) 
//	{
//		head->lifetime = 2;
//	}
//
//	while (current != NULL)
//	{
//		oldX = current->position.x();
//		oldY = current->position.y();
//
//		if (current->lifetime <= 5)
//		{
//			current->position = ( p->position / Vector2D(2, 2)) + Vector2D(rand() % 8 + 0, rand() % 8 + 0);
//		}
//
//		if (current->lifetime > 5 && current->lifetime <= 13)
//		{
//			current->position = (p->position / Vector2D(2, 2))/ Vector2D(3,3) + Vector2D(rand() % 8 + 0, rand() % 10 + 0);		
//		}
//
//		if (current->lifetime > 13 && current->lifetime < 20)
//		{
//			current->position = p->position  + Vector2D(rand() % 2 + 1, rand() % 2 + 1);	
//		}
//
//		if (current->lifetime >= 20)
//		{
//			// monster gets destroyed
//			if (current != head && current->next != NULL)
//			{
//				std::cout << std::endl << "INN" << std::endl;					
//				Monster* temp = current;
//				previous->next = current->next;
//				current = current->next;
//				std::cout << "Done";				
//				std::cout << std::endl << temp->name << " Just Died ! RRIIIPP"<<std::endl;
//
//				DEBUG_PRINT("Monster Destroyed -> Name : %s ", temp->name);
//
//				delete temp;
//			}
//		}
//
//		mp.updateMap_Monster(oldX, oldY, current->position.x(), current->position.y());
//		current->updateMonsterPos(current->position.x(), current->position.y());
//		
//		previous = current;
//		current = current->next;
//	}	
//}
//
//void addMonster(Monster* head)
//{
//	Monster* temp = head;
//	
//	while (temp->next != NULL) {		
//		temp = temp->next;
//	}
//
//	Monster* m = new Monster();
//	std::cout <<std::endl<< "...New Monster Spawning...*_@_#_@_*"<<std::endl;
//	m->createMonster();
//	map.placeOnMap_Monster(m->position.x(), m->position.y());
//	temp->next = m;
//
//	DEBUG_PRINT("Monster Created -> Name : %s",m->name );
//
//	/*if (m->next == NULL) {
//		std::cout << endl << "Successss";
//	}*/
//}
//
//bool checkForLife(Player* p, Map m)
//{
//	if (m.mapStatus[p->position.x()][p->position.y()] == 2) 
//	{
//		return true; 
//	}
//
//	else
//	{
//		return false;
//	}
//}