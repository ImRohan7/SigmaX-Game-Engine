#include "Game.h"
#include <vector>
#include "Vector3d.h"
#include "SmartPtr.h"
#include "Delegates.h"
#include "GamePlay classes/mainCharacter.h"

#define MAX_SPEED 6.0f		// the max difficulty ( Legendary Mode ;-p )
#define LVL_UP_TIME 5		// the time(in seconds) after increase the difficulty
#define INTENSITY 0.5f		// at what intesity we want to increase the difficulty

typedef SmartPtr<GameObject> OBJ;	// 

namespace Game
{
	// game variables

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

	mainCharacter* m1;

	bool Game::Init()
	{
		DEBUG_PRINT("Game Started");
		using namespace Engine;
		GameMode = Menu;

		LuaParser* lp = new LuaParser();

		m1 = new mainCharacter(3);
		// add to level in order to run the engine behavior for object
		if (!LuaParser::createObject_and_addToScene(m1, "../Data_Files/player.lua"))
		{
			assert(false);
		}
		
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
		
			break;
		default:
			break;
		}
		
	}

	bool Game::Shutdown()
	{
		DEBUG_PRINT("Game Shutting down");
	// clear stuff
		return true;
	}


	// ________GAME_PLAY___FUNCTIONS_________

	void Game::SetUpGame()	// Game Setup
	{
		IsGameSetup = true;

	}

	void Game::RunGame()	// Run Game
	{
		if (!IsGameSetup)
		{
			Engine::ClearAll();
			SetUpGame();
		}
	//	Adjust_Level_Difficulty();
	//	HandleWalls();
	//	HandleObstacles();
	}

}