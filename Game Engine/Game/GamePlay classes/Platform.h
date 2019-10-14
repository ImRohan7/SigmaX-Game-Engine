#pragma once
#include "Engine.h"

class Platform : public GameObject
{

public:
	// overrides 
	// This will be called at the start of the game
	virtual void Begin() override
	{
		
	}

	// Called every frame
	virtual void Update() override
	{
		
	}

	// called while collision happens
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override
	{
		
	}

	unsigned int m_testVar;
	
};