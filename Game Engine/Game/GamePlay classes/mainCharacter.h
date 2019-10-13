#pragma once
#include "Engine.h"
#include "Platform.h"

class mainCharacter : public GameObject
{

public:
	// overrides 
	// This will be called at the start of the game
	virtual void Begin() override
	{
		//m_Id = 50;
	}

	// Called every frame
	virtual void Update() override
	{
		Vector2 vel(15, 0);
		if (m_Id == 3)
		{
			if (InputManager::getKeyDown(KeyId::D))
			{
				m_Physics->setVelocity(vel);
			}
			else if (InputManager::getKeyDown(KeyId::A))
			{
				m_Physics->setVelocity(vel);
			}
			else if (InputManager::getKeyDown(KeyId::W))
			{
				m_Physics->setVelocity(vel);
			}
			else if (InputManager::getKeyDown(KeyId::S))
			{
				m_Physics->setVelocity(vel);
			}
		}
	}

	// called while collision happens
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override
	{
		// create a casting function
		//mainCharacter* cd;
		//if (i_collidedObj->CastTo(cd))
		{
			// cast succedded
		}

		//int m = t->m_Gravity;
	}

	unsigned int m_Id;
	mainCharacter(int id) : m_Id(id) {}

};