#include "mainCharacter.h"

void mainCharacter::Begin()
{
	//m_Id = 50;
}

// Called every frame
void mainCharacter::Update()
{
	Vector2 velX(5, 0);
	Vector2 velY(0, 5);
	if (m_Id == 3)
	{
		if (InputManager::getKeyDown(KeyId::D))
		{
			m_Physics->setVelocity(velX);
			//m_Physics->setVelocity(velX);
			DEBUG_PRINT("D");
		}
		else if (InputManager::getKeyDown(KeyId::Space))
		{
			m_Physics->setVelocity(velY);
			DEBUG_PRINT("space");
		}
		else if (InputManager::getKeyDown(KeyId::A))
		{
			m_Physics->setVelocity(-velX);
			m_Physics->addForce(Vector2(0,10));
			DEBUG_PRINT("A");
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
void mainCharacter::OnCollision(SmartPtr<GameObject> i_collidedObj)
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