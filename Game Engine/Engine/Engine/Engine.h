#pragma once

#include "../Math/Vectors/Vector2.h"
#include "../Actor/GameObject.h"
#include "../Input/InputManager.h"
#include "../Console/ConsolePrint.h"
#include "../Timer/Timer.h" 
#include "../Physics/PhysicsComponent.h"
#include "GLib.h"
#include "assert.h"
#include "../Input/InputManager.h"
#include "../Renderer/Renderer.h"
#include "../PointerManagment/SmartPtr.h"
#include <vector>
#include "../Math/Matrix/Matrix_4x4.h"

namespace Engine {
	
	enum Modes { Menu, Play, Endscreen };

	bool Init_Objects(); // run init method of objects

	bool Init();
	bool Shutdown();

	void Run();

	// Physics component to enable physics
	void push_PhysicsComponentToList(PhysicsComponent*);

	//Renderable componenet to draw sprites
	void push_RendererToList(Renderable*);

	
	void push_ObjectToList(const SmartPtr<GameObject>);

	bool QuitRequested();

	

	std::vector<Renderable*> getRenderables();

	PhysicsComponent* getPlayer_PhysicsComponent();
	SmartPtr<GameObject> getPlayerObj();

	int getElapsedTime();
	Modes getMode();
	void setMode(Modes m);

	void ClearAll();

	namespace Physics {
		void Run(float i_dt);
	}

	namespace Renderer {
		void Draw();
	}

	namespace Input {
		void CheckInput(float dt);
	}
}