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

		}
		
		// called while collision happens
		virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override
		{

		}


		unsigned int m_Id;
		mainCharacter(int id) : m_Id(id) {}


	};