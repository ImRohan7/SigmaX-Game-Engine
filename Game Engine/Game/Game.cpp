#include "Game.h"
#include <vector>
#include "Math/Vectors/Vector3d.h"
#include "PointerManagment/SmartPtr.h"
#include "Delegates/Delegates.h"
#include "GamePlay classes/mainCharacter.h"
#include "GamePlay classes/Platform.h"
#include "MyString/MyString.h"

#define MAX_SPEED 6.0f		// the max difficulty ( Legendary Mode ;-p )
#define LVL_UP_TIME 5		// the time(in seconds) after increase the difficulty
#define INTENSITY 0.5f		// at what intesity we want to increase the difficulty

typedef SmartPtr<GameObject> OBJ;	

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

	static bool IsGameSetup = true;
	static bool IsEndSetup = false;

	mainCharacter* _player;
	Platform* _platform;
	Platform* _platform1;

//	mainCharacter* m2;

	bool Game::Init()
	{
		// strig test
		/*MyString m;
		MyString n("Heyya");
		MyString o(n);
		MyString a = "gaga";

		

		if (n == "Helyaa")
		{
			m = o;
		}*/
		/////////////////////////

		DEBUG_PRINT("Game Started");
		using namespace Engine;
		GameMode = Menu;

		LuaParser* lp = new LuaParser();

		_player = new mainCharacter(3);
		_platform = new Platform();
		_platform1 = new Platform();
	//	m2 = new mainCharacter(4);

		
		// add to level in order to run the engine behavior for object
		if (!LuaParser::createObject_and_addToScene(_player, "../Data_Files/player.lua"))
		{
			assert(false);
		}
		if (!LuaParser::createObject_and_addToScene(_platform, "../Data_Files/platform.lua"))
		{
			assert(false);
		}
		if (!LuaParser::createObject_and_addToScene(_platform1, "../Data_Files/platform.lua"))
		{
			assert(false);
		}
		
		_platform->m_Physics->DisableGravity();
		_platform->m_Physics->m_IsDynamic = false;
		_platform->m_Physics->m_IsAPlatform = true;
		_platform->m_Tag = "PF";

		_platform1->m_Physics->DisableGravity();
		_platform1->m_Physics->m_IsDynamic = false;
		_platform1->m_Physics->m_IsAPlatform = true;
		_platform1->m_Tag = "PF";

		Vector2 p = _platform->m_Physics->getPosition();
		_platform->m_Physics->SetPosition(Vector2(p.x() + 600, p.y()));
		
		delete lp;
		return true;
	}


	// Write all user's game logic here
	void Game::Update()
	{
		/*if(!m2->m_To)
			m2->m_Physics->setVelocity(Vector2(-5, 0));*/
		//m1->m_Physics->SetAngularVelocity(2.0f);/*
		
		GameMode = Engine::getMode();

		RunGame();

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