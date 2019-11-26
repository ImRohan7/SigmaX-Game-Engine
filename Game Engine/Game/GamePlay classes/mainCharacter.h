#pragma once
#include "SigmaEngine.h"

class mainCharacter : public GameObject
{
public:
	// Engine overrides 
	// This will be called at the start of the game
	virtual void Begin() override;

	// This will Called every frame
	virtual void Update() override;

	// called while collision occurs
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) override;

	// user defined functions
	// ===================================
	mainCharacter(int id) : m_Id(id), m_To(false), OnGround(true), health(200) {}

	void doJump();

	void TriggerDeath();

	int getHealth();

public:
	bool OnGround;
	bool m_To;
	unsigned int m_Id;
	int health;
};
