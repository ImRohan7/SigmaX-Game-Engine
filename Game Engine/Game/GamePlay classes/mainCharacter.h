#pragma once
#include "Engine.h"
#include "Platform.h"

class mainCharacter : public GameObject
{

public:
	// Engine overrides 
	// This will be called at the start of the game
	virtual void Begin() override;

	// Called every frame
	virtual void Update() override;

	// called while collision occurs
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override;


	// user functions
	mainCharacter(int id) : m_Id(id), m_To(false) {}

	void doJump();

public:
	bool m_To;
	unsigned int m_Id;

};