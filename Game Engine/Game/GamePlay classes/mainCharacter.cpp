#include "mainCharacter.h"

namespace {
	Vector2 maxvel(7, 13);
}

void mainCharacter::Begin()
{
	//m_Id = 50;
}

// Called every frame
void mainCharacter::Update()
{
	Vector2 velX(2, 0);
	Vector2 velY(0, 3);
	Vector2 velToAdd(0, 0);

	if (m_Id == 3)
	{
		if (InputManager::getKeyDown(KeyId::D))
		{
			velToAdd = velX;
		}
		else if (InputManager::getKeyDown(KeyId::Space))
		{
			m_Physics->setVelocity(velY);
			DEBUG_PRINT("space");
		}
		else if (InputManager::getKeyDown(KeyId::A))
		{
			velToAdd = -velX;
		}
		else if (InputManager::getKeyDown(KeyId::W) && OnGround)
		{
			velToAdd = velY;
			if (OnGround)
			{
			}
		}
		else if (InputManager::getKeyDown(KeyId::S))
		{
			velToAdd = -velY;
			OnGround = true;
		}

		Vector2 cur = m_Physics->getVelocity();
		if (cur + velToAdd < maxvel  )
		{
			m_Physics->setVelocity(cur+velToAdd);
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