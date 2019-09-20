#pragma once
#include "Vector2.h"
#include "MyString.h"
#include "SmartPtr.h"
#include "Matrix_4x4.h"

struct AABB
{
		Vector2 m_Center;
		Vector2 m_Extents;
};

class GameObject
{
	
public:
	GameObject() = delete;

	static SmartPtr<GameObject> Create(const Vector2 & i_pos, const char * i_string, const Vector2 & i_vel)
	{
		return SmartPtr<GameObject>(new GameObject(i_pos, i_string, i_vel));
	}
	
	// Set
	void SetPosition(const Vector2 &i_Position) { m_Position = i_Position; }
	void setVelocity(const Vector2 &i_Velocity) { m_Velocity = i_Velocity; }
	void SetRotation(const float &i_RotX) { m_RotationZ = i_RotX; }
	void Set_Mass(const float &iMass) { m_Masss = iMass; }
	inline void setAABB(const Vector2 &i_Dim) // should be moved to a private function for sure
	{
		m_AABB.m_Center = Vector2(0, i_Dim.y() / 2);	// x = 0; y = dim.y/2;
		m_AABB.m_Extents = Vector2(i_Dim.x() / 2, i_Dim.y() / 2);
	}

	// Get
	Vector2 GetPosition() const {
		return m_Position; 
	}
	Vector2 getVelocity() const { return m_Velocity;  }
	char* getName() const{ return m_Name.getName(); }
	int getNameLength() const { return m_Name.getLength(); }
	float getRotationZ() const { return m_RotationZ;  }
	float get_Mass() const { return m_Masss; }
	AABB getAABB() const { return m_AABB; }

	// Base To World
	Math::Matrix_4x4 getBaseToWorld() const
	{
		Math::Matrix_4x4 mRot = Math::Matrix_4x4::CreateZRotation(m_RotationZ);
		Vector3d tmp = Vector3d(m_Position.x(), m_Position.y(), 1.0f);
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

	// may be usefull while creating game
	inline void AdjustCharactersPerLevel(const int &iLevel,const float &iSpeed)
	{
		m_Velocity = Vector2(iSpeed / 5, 0); 
	}
	
	~GameObject() {}

	bool IsDynamic;	// whether to move while colliding
	bool ToUseDrag;	// to apply drag or not while calculating physics
	unsigned int tag; // useful for collision check or other stuff || Default is 0

private:
	MyString m_Name;
	Vector2 m_Position;
	Vector2 m_Velocity;
	float m_RotationZ;
	float m_Masss; // will be set while creating physics comp for now
	AABB m_AABB;

	GameObject(const Vector2 & i_pos, const char * i_string, const Vector2 & i_vel)
		: m_Position(i_pos), m_Velocity(i_vel), m_Name(i_string), m_RotationZ(0.0f), m_Masss(0.0f)
		,IsDynamic(true), ToUseDrag(true), tag(0)
	{}

};