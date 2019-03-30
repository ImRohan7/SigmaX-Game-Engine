#include "stdafx.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#endif // _DEBUG
#include "Engine.h"
#include "Game.h"
#include "GLib.h"
#include "LuaParser.h"
#include "MatrixTest.cpp"
//#include "Allocator.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	Math::test();

	//_crtBreakAlloc = 23;
	//Initializing Glib
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 1000, 720);
	
	if (bSuccess)
	{
		if (Engine::Init())
		{
			if (Game::Init())
			{
				// runs our Game until it’s done
				Engine::Run();
				Game::Shutdown(); 
			}
			Engine::Shutdown(); // Release Everything
		}
	}
	
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}