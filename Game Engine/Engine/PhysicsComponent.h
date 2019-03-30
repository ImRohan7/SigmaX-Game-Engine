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
	PhysicsComponent(const SmartPtr<GameObject> i_Obj, const float i_mass, const Point2D i_drag) :
		m_GameObject(i_Obj), m_Mass(i_mass), m_Drag(i_drag)
	{ }

	void updatePhysics(float DeltaTime);

	//set
	//void setGameObject(GameObject* i_go) { mGameObject = i_go; }
	void setMass(float iMass) { m_Mass = iMass; }
	void setDrag(Point2D iDrag) { m_Drag = iDrag; }

	void addForce(Point2D iForce, float DeltaTime);
	void removeForce(float i_dt);

	~PhysicsComponent();

private:
	WeakPtr<GameObject>  m_GameObject;
	
	float m_Mass;
	Point2D m_Drag;
	bool IsApplyingForce = false;
};