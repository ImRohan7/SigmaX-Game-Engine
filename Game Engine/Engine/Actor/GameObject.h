#pragma once
#include "..//Math/Vectors/Vector3d.h"
#include "../Engine/MyString/MyString.h"
#include "../Engine/PointerManagment/SmartPtr.h"
#include "../Engine/Math/Matrix/Matrix_4x4.h"
#include "../Engine/Physics/PhysicsComponent.h"

struct AABB
{
		Vector2 m_Center;
		Vector2 m_Extents;
};

class GameObject
{
	
public:
	GameObject() :m_Physics(nullptr) {};

	
	// SET
	// =========================
	void setFromFile(const char* i_name)	
	{
		// TODO find a solution for name
		//	m_Name = i_string;

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

	virtual void Begin() {}	// This will be called at the start of the game
	
	virtual void Update() {} // Called every frame
	
	virtual void OnCollision(SmartPtr<GameObject> i_collidedObj) {} // called while collision happens
	

	// Other utilities
	// =================
	template<class T>
	bool TryCastTo(T*& i_targetClassObj)
	{
		if (i_targetClassObj = dynamic_cast<T*>(this))
			return true;
		else
			return false;
	}

	// to avoid undefined behavior when trying to delete a derived class object using base class pointer
	virtual ~GameObject() {}


	// Move to Matrix functionality
	// ============================

	// Base To World
	Math::Matrix_4x4 getBaseToWorld() const
	{
		Math::Matrix_4x4 mRot = Math::Matrix_4x4::CreateZRotation(m_Physics->getRotationZ());
		Vector3d tmp = Vector3d(m_Physics->getPosition().x(), m_Physics->getPosition().y(), 1.0f);
		Math::Matrix_4x4 mTrans = Math::Matrix_4x4::CreateTranslation(tmp);
		Math::Matrix_4x4 mBaseToWorld = mTrans.MultiplySSE(mRot); 
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
	PhysicsComponent * m_Physics;
	MyString m_Tag;	// useful for collision check or other stuff || Default is 0

private:
	MyString m_Name;
	AABB m_AABB;

	/*GameObject(const char* i_string)
		: m_Name(i_string)
	{}*/

};