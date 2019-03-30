#pragma once

#include "Point2D.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ConsolePrint.h"
#include "Timer.h" 
#include "PhysicsComponent.h"
#include "GLib.h"
#include "assert.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SmartPtr.h"

namespace Engine {

	bool Init();
	bool Shutdown();

	void Run();

	// Physics component to enable physics
	void push_PhysicsComponentToList(PhysicsComponent*);

	//Renderable componenet to draw sprites
	void push_RendererToList(Renderable*);

	void push_ObjectToList(const SmartPtr<GameObject>);

	bool QuitRequested();

	void create_Player(const Point2D i_pos);

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