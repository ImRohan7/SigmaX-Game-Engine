#pragma once
#include "Vector2.h"
#include "MyString.h"
#include "SmartPtr.h"
#include "Matrix_4x4.h"
#include "PhysicsComponent.h"

struct AABB
{
		Vector2 m_Center;
		Vector2 m_Extents;
};

class GameObject
{
	
public:
	GameObject() :m_Name("d"), m_Physics(nullptr), m_tag(0)
	{ }

	//// noy using this anymore
	//static SmartPtr<GameObject> Create(const Vector2 & i_pos, const char * i_string, const Vector2 & i_vel)
	//{
	//	return SmartPtr<GameObject>(new GameObject(i_pos, i_string, i_vel));
	//}


	// SET
	// =========================
	void setFromFile(const char* i_name)	
	{
		// TODO find a solution for name
		//	m_Name = i_string;

		m_tag = 0;
	}

	inline void setAABB(const Vector2 &i_Dim) // should be moved to a private function for sure
	{
		m_AABB.m_Center = Vector2(0, i_Dim.y() / 2);	// x = 0; y = dim.y/2;
		m_AABB.m_Extents = Vector2(i_Dim.x() / 2, i_Dim.y() / 2);
	}

	// GET
	// ====================
	char* getName() const{ return m_Name.getName(); }
	int getNameLength() const { return m_Name.getLength(); }
	AABB getAABB() const { return m_AABB; }

	
	// Virtual methods for derived classes
	//====================================

	// This will be called at the start of the game
	virtual void Begin() {}
	// Called every frame
	virtual void Update() {}
	// called while collision happens
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) {}

	// Other
	// =================
	template<class T>
	bool TryCastTo(T*& i_targetClassObj)
	{
		if (i_targetClassObj = dynamic_cast<T*>(this))
			return true;
		else
			return false;
	}

	~GameObject() {}


	// Move to Matrix functionality
	// ============================

	// Base To World
	Math::Matrix_4x4 getBaseToWorld() const
	{
		Math::Matrix_4x4 mRot = Math::Matrix_4x4::CreateZRotation(m_Physics->getRotationZ());
		Vector3d tmp = Vector3d(m_Physics->getPosition().x(), m_Physics->getPosition().y(), 1.0f);
		Math::Matrix_4x4 mTrans = Math::Matrix_4x4::CreateTranslation(tmp);
		Math::Matrix_4x4 mBaseToWorld = mTrans.MultiplySSE(mRot); //mTrans * mRot;
		return mBaseToWorld;
	}

	// World To Base
	Math::Matrix_4x4 getWorldToBase() const
	{
		Math::Matrix_4x4 temp = getBaseToWorld();
		Math::Matrix_4x4 worldToBase = temp.getInverseSSE(); // temp.GetInverse();

		return worldToBase;
	}


public:	
	unsigned int m_tag; // useful for collision check or other stuff || Default is 0
	PhysicsComponent * m_Physics;

private:
	MyString m_Name;
	AABB m_AABB;

	/*GameObject(const char* i_string)
		: m_Name(i_string)
	{}*/

};