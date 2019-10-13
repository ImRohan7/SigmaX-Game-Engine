#pragma once
#include "ConsolePrint.h"
#include "WeakPtr.h"
#include "SmartPtr.h"
#include "Vector2.h"

static int ComponentsExisting = 0;

class PhysicsComponent
{

public:
	PhysicsComponent() = delete; // not required

	// Contsructor
	PhysicsComponent(const Vector2& i_pos, const Vector2& i_vel, const float i_mass, const Vector2 i_drag) :
		m_Position(i_pos), m_Velocity(i_vel), m_Mass(i_mass), m_Drag(i_drag),
		m_RotationZ(0), m_Acceleration(Vector2::Zero), m_ToUseDrag(true), m_IsDynamic(true)
	{ }

	
	// ADD / UPDATE
	// ===============
	void addForce(Vector2 iForce);

	// For ENGINE ONLY
	// ===============
	void updatePhysics(float DeltaTime);


	// SET
	//===============
	void SetPosition(const Vector2& i_Position) { m_Position = i_Position; }
	void setMass(float iMass) {
		m_Mass = iMass; 
	}
	void setDrag(Vector2 iDrag) { m_Drag = iDrag; }
	void setVelocity(const Vector2& i_Velocity) { m_Velocity = i_Velocity; }
	void setAcceleration(const Vector2& i_acc) { m_Acceleration = i_acc; }
	void SetRotation(const float& i_RotX) { m_RotationZ = i_RotX; }


	// GET
	// ================
	Vector2 getPosition() const { return m_Position; }
	float getMass() const { return m_Mass; }
	Vector2 getDrag() const { return m_Drag; }
	Vector2 getVelocity() const { return m_Velocity; }
	Vector2 getAcceleration() const { return m_Acceleration; }
	float getRotationZ() const { return m_RotationZ; }
	
	
	~PhysicsComponent();

public:
	bool m_ToUseDrag;	// to apply drag or not while calculating physics
	bool m_IsDynamic;	// whether to move while colliding

private:
	// We don't need to store Weakptr to GameObject mow
	// It is not possible now as well

	Vector2 m_Position;
	float m_Mass;
	Vector2 m_Drag;
	Vector2 m_Velocity;
	Vector2 m_Acceleration;
	float m_RotationZ;

	void ApplyDrag(float i_dt);

};