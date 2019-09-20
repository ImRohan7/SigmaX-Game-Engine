#include "Game.h"
#include <vector>
#include "Vector3d.h"
#include "SmartPtr.h"
#include "Delegates.h"
#define MAX_SPEED 6.0f		// the max difficulty ( Legendary Mode ;-p )
#define LVL_UP_TIME 5		// the time(in seconds) after increase the difficulty
#define INTENSITY 0.5f		// at what intesity we want to increase the difficulty

typedef SmartPtr<GameObject> OBJ;	// 

namespace Game
{
	// game variables
//	static OBJ _playerCar;
	static std::vector<OBJ> _grassWalls;	// walls have tag = 2
	static std::vector<OBJ> _obStcales;    // Obstacles have tag = 3 

	static Engine::Modes GameMode;
	static int timeTracker = 0;

// level and speed
	static int Level = 1;
	static float Bottom = -400;
	static float top = 400;
	static float levelSpeed = -2.0;
	static float LeftEdge = -225;
	static float RightEdge = 225;

	static bool IsGameSetup = false;
	static bool IsEndSetup = false;

	bool Game::Init()
	{
		DEBUG_PRINT("Game Started");
		using namespace Engine;
		GameMode = Menu;
		
		LuaParser * lp = new LuaParser();
		SmartPtr<GameObject> Menu = lp->createObject("../Data_Files/title.lua");
		
		delete lp;
		return true;
	}


	// Write all user's game logic here
	void Game::Update()
	{
		GameMode = Engine::getMode();

		switch (GameMode)
		{
		case Engine::Modes::Menu:

			break;

		case Engine::Modes::Play:	// Do Gameplay Stuff
			RunGame();
			break;

		case Engine::Modes::Endscreen:	// Display Score based on Level
			RunEndScreen();
			break;
		default:
			break;
		}
		
	}

	bool Game::Shutdown()
	{
		DEBUG_PRINT("Game Shutting down");
		int size = static_cast<int>(_grassWalls.size());

		for (unsigned int i = 0; i < size; i++)
		{
			SmartPtr<GameObject> toFreeG = _grassWalls.at(size - i - 1);
			_grassWalls.pop_back();
		}

		
		return true;
	}


	// ________GAME_PLAY___FUNCTIONS_________

	void Game::SetUpGame()	// Game Setup
	{
		IsGameSetup = true;

		Engine::LuaParser * lp = new Engine::LuaParser();
		SmartPtr<GameObject> Car = lp->createObject("../Data_Files/car.lua");

		setUpWalls(lp);		// set up Environment
		setUpObstacles(lp);		// And Obstacles

		delete lp;
	}

	void Game::RunGame()	// Run Game
	{
		if (!IsGameSetup)
		{
			Engine::ClearAll();
			SetUpGame();
		}
		Adjust_Level_Difficulty();
		HandleWalls();
		HandleObstacles();
	}

	void Game::setUpEndScreen()	// Setup End Screen
	{
		IsEndSetup = true;

		Engine::LuaParser * lp = new Engine::LuaParser();
		if (Level >= 0 && Level < 2)
		{
			SmartPtr<GameObject> endScreen = lp->createObject("../Data_Files/end.lua");
			endScreen->IsDynamic = false;
		}
		else if (Level > 1 && Level < 4)
		{
			SmartPtr<GameObject> endScreen = lp->createObject("../Data_Files/end0.lua");
			endScreen->IsDynamic = false;
		}
		else if (Level >= 4   && Level < 7)
		{
			SmartPtr<GameObject> endScreen = lp->createObject("../Data_Files/end1.lua");
			endScreen->IsDynamic = false;
		}
		else
		{
			SmartPtr<GameObject> endScreen = lp->createObject("../Data_Files/end2.lua");
			endScreen->IsDynamic = false;
		}
		

		delete lp;
	}

	void Game::RunEndScreen()	// Display End Screen
	{
		if (!IsEndSetup)
		{
			Engine::ClearAll();
			setUpEndScreen();
		}
		switch (Level)
		{
		default:

			break;
		}
	}

	void Game::setUpWalls(Engine::LuaParser * ilp)
	{
		ilp = new Engine::LuaParser();

		SmartPtr<GameObject> grassLeft = ilp->createObject("../Data_Files/grassLeft.lua");
		SmartPtr<GameObject> grassRight = ilp->createObject("../Data_Files/grassRight.lua");
		SmartPtr<GameObject> grassLeft1 = ilp->createObject("../Data_Files/grassLeft.lua");
		SmartPtr<GameObject> grassRight1 = ilp->createObject("../Data_Files/grassRight.lua");

		grassLeft1->SetPosition(Vector2(-450,top));
		grassRight1->SetPosition(Vector2(450,top));

		_grassWalls.push_back(grassLeft);
		_grassWalls.push_back(grassRight);
		_grassWalls.push_back(grassLeft1);
		_grassWalls.push_back(grassRight1);

		for (OBJ wall : _grassWalls)
		{
			wall->IsDynamic = false;
			wall->ToUseDrag = false;
			wall->tag = 2;	//	in collision check if tag == 2 -> player doesn't die
		}
	}

	void Game::setUpObstacles(Engine::LuaParser * ilp)
	{
		SmartPtr<GameObject> block = ilp->createObject("../Data_Files/block.lua");
		SmartPtr<GameObject> rock = ilp->createObject("../Data_Files/obstacle.lua");
		SmartPtr<GameObject> block1 = ilp->createObject("../Data_Files/block.lua");
		SmartPtr<GameObject> rock1 = ilp->createObject("../Data_Files/obstacle.lua");

		block1->SetPosition(Vector2(225,top + 500));
		rock1->SetPosition(Vector2(50, top + 300));

		_obStcales.push_back(block);
		_obStcales.push_back(rock);
		_obStcales.push_back(block1);
		_obStcales.push_back(rock1);

		for (OBJ ocl : _obStcales)
		{
			ocl->ToUseDrag = false;
			ocl->IsDynamic = false;
			ocl->tag = 3;
		}
	}

	void Game::HandleWalls()
	{
		for(OBJ wall : _grassWalls)
		{
			wall->setVelocity(Vector2(0.0f, levelSpeed));
			Vector2 pos = wall->GetPosition();
			if (pos.y() < Bottom - 800)
			{
				wall->SetPosition(Vector2(pos.x(), top));
			}
		}	
	}

	// Endless Obstacles loop with pos X and Y speed variation
	void Game::HandleObstacles()
	{
		for (OBJ obs : _obStcales)
		{
			obs->setVelocity(Vector2(0.0f, levelSpeed));
			Vector2 pos = obs->GetPosition();
			if (pos.y() < Bottom - 150)
			{
				int Xpos = rand() % 450 + LeftEdge;
				obs->SetPosition(Vector2(Xpos, top));
			}
		}
	}

	// // adjust the level speed
	void Game::Adjust_Level_Difficulty()
	{
		int tLatest = Engine::getElapsedTime();
		if (timeTracker + LVL_UP_TIME < tLatest )
		{
			timeTracker = tLatest;
			if (levelSpeed > -MAX_SPEED)
			{
				levelSpeed += -INTENSITY;
			}
			
			Level++;
		}
	}

}