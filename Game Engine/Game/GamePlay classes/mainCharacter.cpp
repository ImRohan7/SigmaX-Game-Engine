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

			//	Vector2 a = m_Physics->getVelocity() + velX;
		//	m_Physics->addForce(Vector2(0.4f, 0));
			m_Physics->setVelocity(velX);
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
			
			DEBUG_PRINT("A");
		}
		else if (InputManager::getKeyDown(KeyId::W) && OnGround)
		{
			m_Physics->addForce(Vector2(0, 0.2f));
			if (OnGround)
			{
			//	m_Physics->addForce(Vector2(0, -100));
			//	OnGround = false;
			}
		}
		else if (InputManager::getKeyDown(KeyId::S))
		{
			m_Physics->setVelocity(-velY);
			OnGround = true;
		}
	}
	
}

// called while collision happens
void mainCharacter::OnCollision(SmartPtr<GameObject> i_collidedObj)
{
	m_To = true;
	// create a casting function
	mainCharacter* cd;
	if (i_collidedObj->TryCastTo(cd))
	{
		// cast succedded
	}

	// ground check
	if (i_collidedObj->m_Tag == "PF")
	{
		//OnGround = true;
	}

	//int m = t->m_Gravity;
}
void mainCharacter::doJump()
{

}

void mainCharacter::TriggerDeath()
{

}
int mainCharacter::getHealth()
{
	return 100;
}