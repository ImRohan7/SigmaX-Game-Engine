#include "Game.h"
#include <vector>
#include "LuaParser.h"
#include "Vector3d.h"
#include "SmartPtr.h"

namespace Game
{
	bool Game::Init()
	{
		DEBUG_PRINT("Game Started");

		Engine::LuaParser * lp = new Engine::LuaParser();
		SmartPtr<GameObject> Player = lp->createObject("../Data_Files/player.lua");
		
		delete lp;
		return true;
	}

	// Write all user's game logic here
	void Game::Update()
	{

	}

	bool Game::Shutdown()
	{
		DEBUG_PRINT("Game Shutting down");

		return true;
	}
}