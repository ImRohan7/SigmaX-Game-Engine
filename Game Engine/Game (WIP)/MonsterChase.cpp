#include <stdlib.h>

// WIP
// TO BUILD A GAME

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "stdafx.h"
#include "iostream"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Vector2D.h"
#include "assert.h"
#include "ConsolePrint.h"
#include "Unit_test_const.cpp"
#include "GameObject.h"
#include "PlayerController.h"
#include "ZombieController.h"
#include "HeapManagerProxy.h"
#include "assert.h"
#include "windows.h"
#include "Allocator.h"
#include "MyString.h"
#include <vector>
#include"FixedSizeAllocator.h"
#include <intrin.h>
#include <algorithm>

#pragma intrinsic(_BitScanForward)

int n,oldX,oldY;
Map map;

#if HEAP_DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#elif defined(HEAP_RELEASE)
#define LOG(x)
#endif

void monster_AI(Player*, Monster*, Map);
void printDetails(Player*, Monster*);
bool checkForLife(Player*, Map);
void addMonster(Monster*);

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG

//int main(int i_arg, char **)
//{
//	const size_t 		sizeHeap = 1024 * 1024;
//
//	// you may not need this if you don't use a descriptor pool
//	const unsigned int 	numDescriptors = 2048;
//
//	// Allocate memory for my test heap.
//	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//	assert(pHeapMemory);
//
//	// Create your HeapManager and FixedSizeAllocators.
//	InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
//
//	bool success = MemorySystem_UnitTest();
//	assert(success);
//
//	// Clean up your Memory System (HeapManager and FixedSizeAllocators)
//	DestroyMemorySystem();
//
//	HeapFree(GetProcessHeap(), 0, pHeapMemory);
//
//	// in a Debug build make sure we didn't leak any memory.
//#if defined(_DEBUG)
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG
//
//	return 0;
//}

//// this new [] / delete [] pair should run through your allocator
//	char * pNewTest = new char[1024];
//
//	delete[] pNewTest;
//
//	// we succeeded
//	return true;
//
//LOG("Starting");
//	
//	/*unsigned long index;
//	unsigned long mask;
//
//	unsigned char isNonzero;
//
//	std::cout << "Enter a positive integer as the mask: ";
//	std::cin >> mask;
//	mask = ~mask;
//	isNonzero = _BitScanForward(&index, mask);
//	if (isNonzero)
//	{
//		std::cout << "Mask: " << mask << " Index: " << index << std::endl;
//	}
//	else
//	{
//		std::cout << "No set bits found.  Mask is zero." << std::endl;
//	}*/
//
//		const size_t 		sizeHeap = 1024 * 1024;
//	
//		// you may not need this if you don't use a descriptor pool
//		const unsigned int 	numDescriptors = 2048;
//	
//		// Allocate memory for my test heap.
//		void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//		assert(pHeapMemory);
//	
//		// Create your HeapManager and FixedSizeAllocators.
//		bool x = InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
//
//		const size_t maxAllocations = 10 * 1024;
//		std::vector<void *> AllocatedAddresses;
//
//		long	numAllocs = 0;
//		long	numFrees = 0;
//		long	numCollects = 0;
//
//		size_t totalAllocated = 0;
//
//		// reserve space in AllocatedAddresses for the maximum number of allocation attempts
//		// prevents new returning null when std::vector expands the underlying array
//		AllocatedAddresses.reserve(10 * 1024);
//
//		// allocate memory of random sizes up to 1024 bytes from the heap manager
//		// until it runs out of memory
//	
//			const size_t		maxTestAllocationSize = 1024;
//
//			size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));
//
//			void * pPtr = malloc(sizeAlloc);
//
//
//		//int* Testk = new int();
//		//char* Test2 = new char();
//		////char* c = (char*)malloc(2);
//
//		//delete Testk;
//		//delete Test2;
//		////free(Testk);
//		////free(Test2);
//		////free(c);
//
//		int xnn = 88;
//		int mmmmll=0;

//	Player *P2 = new(NEW_ALIGN_DEFAULT) Player();
//	//int *k = new int[3];
//	
//	delete P2;
//	//delete k;
//
//
//
//// testing interface
//
//	Vector3d test1(3.44f, -5.66f, 7.9f);
//	Vector3d A1(7.3f, 9.5f, 2.2f);
//	Vector3d B1(8.0f,9.66f,4.7f);
//
//	GameObject man(test1);
//	GameObject A(A1);
//	GameObject B(B1);
//
//	PlayerController pc;
//	pc.SetGameObject(&man);
//	pc.UpdateGameObject();
//
//	Vector3d test = man.GetPosition();
//	test.printVector();
//
//	ZombieController bot1, bot2;
//	bot1.SetGameObject(&A);
//	bot1.SetFocusObject(&man);
//	bot2.SetGameObject(&B);
//
//	bot1.UpdateGameObject();
//	bot2.UpdateGameObject();
//
//	test = A.GetPosition();
//	test.printVector();
//
//	test = B.GetPosition();
//	test.printVector();
//
//
//
//	Vector3d m;
//
//
//	float x = Vector3d::Zero.x();
//	Vector3d C = Vector3d::Zero;
//	
////	Zero.z(3.3);
//
//	std::cout << C.x() << std::endl << C.y() << std::endl << C.z();
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
////	Game begins here
////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Player *P = new Player() ;	
//	
//	DEBUG_PRINT("Player %s Created Successfully", P->name);
//
//	Monster* head=NULL;
//
//	char input,c;
//	bool ifDead = false;
//	int randX = 0;
//	int randY = 0;
//
//	map.placeOnMap_Player(P->position.x(),P->position.y());
//
//	std::cout << "\nMonsters have maximum lifetime of 20" <<std::endl << "Enter the number of monsters you want to start with: ";
//	std::cin >> n;
//
//	assert(n!=0);
//	for(int i = 0 ; i < n ; i++)
//	{
//		Monster* temp = new Monster();
//		temp->createMonster();
//		map.placeOnMap_Monster(temp->position.x(), temp->position.y());
//		temp->next = NULL;
//
//		if (head == NULL) 
//		{
//			head = temp;
//		}
//
//		else 
//		{
//			Monster* temp1 = head;
//			while (temp1->next != NULL)
//			{
//				temp1 = temp1->next;
//			}
//			temp1->next = temp;
//		}
//	}
//
//// Creating the list
//
//	/*head->createMonster();
//	map.placeOnMap_Monster(head->position.x(), head->position.y());
//	head->next = list;
//	list->createMonster();
//	map.placeOnMap_Monster(list->position.x(), list->position.y());
//
//	for (int i = 2; i < n; i++) 
//	{
//		list->next = new Monster();
//		list = list->next;
//		list->createMonster();
//		map.placeOnMap_Monster(list->position.x(), list->position.y());
//	}*/
//	
//// Gameplay Loop
//		do {
//
//			assert(head!=NULL);
//
//			printDetails(P, head);
//	
//			std::cout << "Where you wanna go now ?\n";
//			std::cout << "W - UP		S - DOWN		A - LEFT		D - RIGHT \n";
//			std::cout << "Press Q to quit \n"<<std::endl;
//			std::cin >> input;
//	
//			switch (input)
//			{
//			default:
//				std::cout << "Wrong Choice !"<< std::endl;
//				break;
//	
//			case 'W': case 'w' :
//				P->position = P->position + Vector2D(0, -1);
//
//				P->updatePlayerPos(P->position.x(), P->position.y());
//				ifDead = checkForLife(P, map);
//				if (ifDead == true)
//				{
//					std::cout << "Player died\n Press any key to quit";
//					std::cin >> c;
//					input = 'Q';
//					break;
//				}
//				
//				map.updateMap_Player(P->position.x(), P->position.y() + 1, P->position.x(), P->position.y());
//				monster_AI(P, head, map);
//				break;
//	
//			case 'S' : case 's':
//				P->position = P->position + Vector2D(0,1);
//
//				P->updatePlayerPos(P->position.x(), P->position.y() );
//				ifDead = checkForLife(P, map);
//				if (ifDead == true)
//				{
//					std::cout << "Player died\n Press any key to quit";
//					std::cin >> c;
//					input = 'Q';
//					break;
//				}
//				map.updateMap_Player(P->position.x(), P->position.y() - 1, P->position.x(), P->position.y());
//				monster_AI(P, head, map);
//				break;
//	
//			case 'A': case 'a':
//				P->position = P->position + Vector2D(-1, 0);
//
//				P->updatePlayerPos(P->position.x(), P->position.y());
//				ifDead = checkForLife(P, map);
//				if (ifDead == true)
//				{
//					std::cout << "Player died\n Press any key to quit";
//					std::cin >> c;
//					input = 'Q';
//					break;
//				}
//				map.updateMap_Player(P->position.x() + 1, P->position.y(), P->position.x(), P->position.y());
//				monster_AI(P, head, map);
//				break;
//	
//			case 'D': case 'd':
//				addMonster(head);
//
//				P->position = P->position + Vector2D(1, 0);
//
//				P->updatePlayerPos(P->position.x(), P->position.y());
//				ifDead = checkForLife(P, map);
//				if (ifDead == true)
//				{
//					std::cout << "Player died\n Press any key to quit";
//					std::cin >> c;
//					input = 'Q';
//					break;
//				}
//				map.updateMap_Player(P->position.x() - 1, P->position.y(), P->position.x(), P->position.y());
//				monster_AI(P, head, map);
//				break;
//				
//			}
//		} while (input != 'Q');
//	
//////For displaying the map Visually
////		/*std::cout << "\t\t MAP " << endl;
////		for (int i = 0; i < 20; i++)
////		{
////			for (int j = 0; j < 20; j++)
////			{				
////				std::cout<<map.mapStatus[i][j]<<" ";
////			}
////			std::cout << endl;
////		}*/
////		
////	} while (input != 'Q');
//
//	delete P;
//	while (head != NULL) {
//		Monster* temp = NULL;
//		temp = head;
//		head = head->next;
//		delete temp;
//	}
//	
//#ifdef _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif // DEBUG
//
//	DEBUG_PRINT("Memory Cleared !");
//	
//	return 0;
//
//}
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