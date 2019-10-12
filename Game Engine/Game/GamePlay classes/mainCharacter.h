#pragma once
#include "Engine.h"

class mainCharacter : public GameObject
{

public:
	// overrides 
	// This will be called at the start of the game
	virtual void Begin() override
	{
		m_Id = 50;
	}

	// Called every frame
	virtual void Update() override
	{
		if (InputManager::getKeyDown(KeyId::D))
		{
			m_Physics->setVelocity(Vector2(5, 0));
		}
		else if(InputManager::getKeyDown(KeyId::A))
		{
			m_Physics->setVelocity(Vector2(-5, 0));
		}
		else if (InputManager::getKeyDown(KeyId::W))
		{
			m_Physics->setVelocity(Vector2(0, 5));
		}
		else if (InputManager::getKeyDown(KeyId::S))
		{
			m_Physics->setVelocity(Vector2(0, -5));
		}
	}

	// called while collision happens
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override
	{

	}

	unsigned int m_Id;
	mainCharacter(int id) : m_Id(id) {}

};