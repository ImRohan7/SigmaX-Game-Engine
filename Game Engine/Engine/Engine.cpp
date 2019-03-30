#include "Engine.h"
#include <vector>

static bool Input = false;

namespace Engine {
	
	// TO DO: create a list for storing components
	static std::vector<PhysicsComponent*> _physicsComps;
	static std::vector<Renderable*> _renderables;

	// ptr stuff
	static std::vector<SmartPtr<GameObject>> _AllObjects;
	//static std::vector<WeakPtr<GameObject>> _Physics_Ptrs;

	static bool ToQuit = false;

	bool Engine::Init()
	{
		DEBUG_PRINT("Engine starting up");

		InputManager::InitService();

		return true;
	}

	void push_PhysicsComponentToList(PhysicsComponent * i_Obj)
	{
		_physicsComps.push_back(i_Obj);
	}

	void push_RendererToList(Renderable * i_obj)
	{
		_renderables.push_back(i_obj);
	}

	void push_ObjectToList(const SmartPtr<GameObject> i_Obj)
	{
		_AllObjects.push_back(i_Obj);
	}

	bool Engine::Shutdown()
	{
		SmartPtr<GameObject> toFreeG = _AllObjects.at(0);
		_AllObjects.pop_back();
		
		// relsease sprites
		Renderable * toFreeR = _renderables.at(0);
		_renderables.pop_back();
		delete toFreeR;

		PhysicsComponent * toFreeP = _physicsComps.at(0);
		_physicsComps.pop_back();
		delete toFreeP;

		//DEBUG_PRINT("Size: %d", _physicsComps.size());
		//DEBUG_PRINT("Engine shutting down");
		return true;
	}

	bool Engine::QuitRequested()
	{
		return ToQuit;
	}


	// ****  not using anymore 
	// Create Player 
	void create_Player(const Point2D i_pos)
	{
		SmartPtr<GameObject> player;// = GameObject::Create(i_pos);
		_AllObjects.push_back(player);

		// this(overload '->') should get a copy of smartPtr and deal with gameobject velocity
		player->setVelocity(Point2D::Unit);

		
		// create a physics component as well
		PhysicsComponent * pComp = new PhysicsComponent(player, 5.0f, Point2D::Unit);
		_physicsComps.push_back(pComp);

		float dt = Timer::calcLastFrameTime();
		dt /= 1000;
		pComp->updatePhysics(dt);

	}

	void Engine::Run()
	{
		bool bQuit = false;
		do
		{
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
	
			// Calculating Last Frame time
			float dt = Timer::calcLastFrameTime();
			dt /= 1000;

			// applying input actions
			// Update gameObjects based on user input
			Input::CheckInput(dt);
			
			//AI::Run(dt);          // Run AI 
								  // (also apply user input).
			// Applying Physics
			Physics::Run(dt);

			// Last but Not least Drawing
			Renderer::Draw();

			if (Engine::QuitRequested())
				break;

		} while (!bQuit);
	}

	void Physics::Run(float i_dt)
	{
		for (unsigned i = 0; i < _physicsComps.size(); i++)
			_physicsComps.at(i)->updatePhysics(i_dt);
	}

	void Renderer::Draw()
	{
		for (unsigned i = 0; i < _renderables.size(); i++)
			_renderables.at(i)->Draw();
	}

	void Input::CheckInput(float i_dt)
	{
		if (InputManager::getKeyDown(KeyId::D))
		{
			_physicsComps.at(0)->addForce(Point2D(3.0, 0), i_dt);
		}
		else if (InputManager::getKeyDown(KeyId::A))
		{
			_physicsComps.at(0)->addForce(Point2D(-3.0, 0), i_dt);
		}
		else if (InputManager::getKeyDown(KeyId::W))
		{
			_physicsComps.at(0)->addForce(Point2D(0, 2.0), i_dt);
		}
		else if (InputManager::getKeyDown(KeyId::S))
		{
			_physicsComps.at(0)->addForce(Point2D(0, -2.0), i_dt);
		}
		else if (InputManager::getKeyDown(KeyId::Q))
		{
			ToQuit = true;
		}
		else
		{
			_physicsComps.at(0)->removeForce(i_dt);
		}
	}
	
}