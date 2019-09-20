#include "Engine.h"
#include <vector>
#include "RendererManager.h"
#include "CollisionHandler.h"
#define FORCE 20.0f

static bool Input = false;

namespace Engine {
	
	// TO DO: create a list for storing components
	static std::vector<SmartPtr<GameObject>> _AllObjects;
	static std::vector<PhysicsComponent*> _physicsComps;
	static std::vector<Renderable*> _renderables;
	
	static bool ToQuit = false;
	static float ElapsedTime = 0.0f;
	static long int ElapsedSeconds = 0;
	static Modes m_Mode = Menu; // 0: Game, 1: Exir

	bool Engine::Init()
	{
		DEBUG_PRINT("Engine starting up");
		InputManager::InitService();
		
		return true;
	}
	int Engine::getElapsedTime() { return ElapsedSeconds; }
	Modes Engine::getMode() { return m_Mode; }
	void Engine::setMode(Modes m)
	{
		m_Mode = m;
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
			
		int size = _AllObjects.size();
		// relsease sprites
		for (unsigned i = 0; i < size; i++)
		{
			Renderable * toFreeR = _renderables.at(size-i-1);
			_renderables.pop_back();
			delete toFreeR;
		}

		for (unsigned i = 0; i < size; i++)
		{
			PhysicsComponent * toFreeP = _physicsComps.at(size - i - 1);
			_physicsComps.pop_back();
			delete toFreeP;
		}

		for (unsigned i = 0; i < size; i++)
		{
					SmartPtr<GameObject> toFreeG = _AllObjects.at(size - i - 1);
					_AllObjects.pop_back();
		}

		//DEBUG_PRINT("Size: %d", _physicsComps.size());
		//DEBUG_PRINT("Engine shutting down");
		return true;
	}


	void Engine::ClearAll()
	{
		int size = _AllObjects.size();
		// relsease sprites
		for (unsigned i = 0; i < size; i++)
		{
			Renderable * toFreeR = _renderables.at(size - i - 1);
			_renderables.pop_back();
			delete toFreeR;
		}

		for (unsigned i = 0; i < size; i++)
		{
			PhysicsComponent * toFreeP = _physicsComps.at(size - i - 1);
			_physicsComps.pop_back();
			delete toFreeP;
		}

		for (unsigned i = 0; i < size; i++)
		{
			SmartPtr<GameObject> toFreeG = _AllObjects.at(size - i - 1);
			_AllObjects.pop_back();
		}
	}

	bool Engine::QuitRequested()
	{
		return ToQuit;
	}


	// ****  not using anymore 
	// Create Player 
	void create_Player(const Vector2 i_pos)
	{
		SmartPtr<GameObject> player;// = GameObject::Create(i_pos);
		_AllObjects.push_back(player);

		// this(overload '->') should get a copy of smartPtr and deal with gameobject velocity
		player->setVelocity(Vector2::Unit);

		
		// create a physics component as well
		PhysicsComponent * pComp = new PhysicsComponent(player, 5.0f, Vector2::Unit);
		_physicsComps.push_back(pComp);

		float dt = Timer::calcLastFrameTime();
		dt /= 1000;
		pComp->updatePhysics(dt);

	}

	void Engine::Run()
	{
			bool bQuit = false;
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
	
			// Calculating Last Frame time
			float dt = Timer::calcLastFrameTime();
			dt /= 1000;
			ElapsedTime += dt;
			if (ElapsedTime > 100)
			{
				ElapsedTime = 0.0f;
				ElapsedSeconds++;
			}
			
		//	DEBUG_PRINT("Elapsed: %d", ElapsedSeconds);
			// applying input actions
			// Update gameObjects based on user input
			Input::CheckInput(dt);

			Engine::Physics::CollisionHandler cs;
			cs.HandleCollisions(_AllObjects, dt);

			//AI::Run(dt);          // Run AI 
			// Applying Physics
			Physics::Run(dt);

			// Last but Not least Drawing
			Renderer::Draw();
	}

	void Physics::Run(float i_dt)
	{
		for (unsigned i = 0; i < _physicsComps.size(); i++)
		{
			_physicsComps.at(i)->updatePhysics(i_dt);
		}
	}

	void Renderer::Draw()
	{
		RendererManager R;
		R.Draw();
	}

	void Input::CheckInput(float i_dt)
	{
		float force = 15.0f;
		// first (0th Object) is by default Player Controller
		switch (m_Mode)
		{
			
			case Menu:
				if (InputManager::getKeyDown(KeyId::S))
				{
					m_Mode = Play;
				}
				else if (InputManager::getKeyDown(KeyId::Q))
				{
					ToQuit = true;
				}
			break;

			case Play:
				
				if (InputManager::getKeyDown(KeyId::D))
				{
					_physicsComps.at(0)->addForce(Vector2(FORCE, 0), i_dt);
				}
				else if (InputManager::getKeyDown(KeyId::A))
				{
					_physicsComps.at(0)->addForce(Vector2(-FORCE, 0), i_dt);
				}
				else if (InputManager::getKeyDown(KeyId::W))
				{
					_physicsComps.at(0)->addForce(Vector2(0, FORCE), i_dt);
				}
				else if (InputManager::getKeyDown(KeyId::S))
				{
					_physicsComps.at(0)->addForce(Vector2(0, -FORCE), i_dt);
				}
				else if (InputManager::getKeyDown(KeyId::Q))
				{
					ToQuit = true;
				}
			break;

			case Endscreen:
				if (InputManager::getKeyDown(KeyId::Q))
				{
					ToQuit = true;
				}
			break;
		default:
			break;
		}
		
		
		
	}

	// ------------getters----------------

	// get physics component
	PhysicsComponent* Engine::getPlayer_PhysicsComponent()
	{
		return _physicsComps.at(0);
	}

	// get player object
	SmartPtr<GameObject> Engine::getPlayerObj()
	{
		return _AllObjects.at(0);
	}

	// get renderables
	std::vector<Renderable*> getRenderables()
	{
		return _renderables;
	}
}