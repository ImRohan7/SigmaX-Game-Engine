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
		Vector2 velX(5, 0);
		Vector2 velY(0, 5);
		if (m_Id == 3)
		{
			if (InputManager::getKeyDown(KeyId::D))
			{
				m_Physics->setVelocity(velX);
			}
			else if (InputManager::getKeyDown(KeyId::A))
			{
				m_Physics->setVelocity(-velX);
			}
			else if (InputManager::getKeyDown(KeyId::W))
			{
				m_Physics->setVelocity(velY);
			}
			else if (InputManager::getKeyDown(KeyId::S))
			{
				m_Physics->setVelocity(-velY);
			}
		}
	}

	// called while collision happens
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override
	{
		m_To = true;
		// create a casting function
		//mainCharacter* cd;
		//if (i_collidedObj->CastTo(cd))
		{
			// cast succedded
		}

		//int m = t->m_Gravity;
	}

	mainCharacter(int id) : m_Id(id), m_To(false) {}

public:
	bool m_To;
	unsigned int m_Id;

};