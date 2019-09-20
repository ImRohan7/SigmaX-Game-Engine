#pragma once
#include "GameObject.h"
#include "ConsolePrint.h"
#include "WeakPtr.h"
#include "SmartPtr.h"

static int ComponentsExisting = 0;

class PhysicsComponent
{

public:
	PhysicsComponent() = delete;

	// Contsructor
	PhysicsComponent(const SmartPtr<GameObject> i_Obj, const float i_mass, const Vector2 i_drag) :
		m_GameObject(i_Obj), m_Mass(i_mass), m_Drag(i_drag)
	{ }

	void updatePhysics(float DeltaTime);
	
	//set
	//void setGameObject(GameObject* i_go) { mGameObject = i_go; }
	void setMass(float iMass) { m_Mass = iMass; }
	void setDrag(Vector2 iDrag) { m_Drag = iDrag; }

	void addForce(Vector2 iForce, float DeltaTime);
	void setDragStatus(bool i_state)
	{
		IsApplyingForce = i_state;
	}

	~PhysicsComponent();

private:
	WeakPtr<GameObject>  m_GameObject;
	
	float m_Mass;
	Vector2 m_Drag;
	bool IsApplyingForce = false;


	void updatePosition(SmartPtr<GameObject> _Object,const float DeltaTime);
	void ApplyDrag(SmartPtr<GameObject> _Object, float i_dt);

};