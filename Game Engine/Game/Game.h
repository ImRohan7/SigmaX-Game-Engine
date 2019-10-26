#pragma once
#include "Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Luaparser/LuaParser.h"

namespace Game{

	void Update();
	bool Init();
	bool Shutdown();

	// ________GAME_PLAY___FUNCTIONS_________

	void setUpWalls(Engine::LuaParser* lp);
	void setUpObstacles(Engine::LuaParser* lp);
	void HandleWalls(); // Endless grasswall loop
	void HandleObstacles(); // Endless Obstacles loop with pos X and Y speed variation
	void Adjust_Level_Difficulty(); // adjust the level speed

	void SetUpGame();
	void RunGame();

	void setUpEndScreen();
	void RunEndScreen();
	


}

