#pragma once
#include "Point2D.h"
#include "MyString.h"
#include "SmartPtr.h"

class GameObject
{

public:
	GameObject() = delete;

	static SmartPtr<GameObject> Create(const Point2D & i_pos, const char * i_string, const Point2D & i_vel)
	{
		return SmartPtr<GameObject>(new GameObject(i_pos, i_string, i_vel));
	}
	
	// Get
	Point2D GetPosition() const {
		return m_Position; 
	}
	Point2D velocity() const { return m_Velocity;  }
	char* getName() { return m_Name.getName(); }
	int getNameLength() { return m_Name.getLength(); }

	// Set
	void SetPosition(const Point2D &i_Position) {	m_Position = i_Position; }
	void setVelocity(const Point2D &i_Velocity) {
		m_Velocity = i_Velocity;
	}

	~GameObject() {}

private:
	MyString m_Name;
	Point2D m_Position;
	Point2D m_Velocity;

	GameObject(const Point2D & i_pos, const char * i_string, const Point2D & i_vel)
		: m_Position(i_pos), m_Velocity(i_vel), m_Name(i_string)
	{}
};