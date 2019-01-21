#pragma once
#include "Vector2D.h"
#include "MyString.h"

class GameObject
{

public:
	GameObject() {};

	GameObject(Vector2D i_pos) : m_Position(i_pos)
	{}
	

	// Get
	Vector2D GetPosition() const { return m_Position; }
	char* getName() { return m_Name.getName(); }
	int getNameLength() { return m_Name.getLength(); }

	// Set
	void SetPosition(const Vector2D &i_Position) {	m_Position = i_Position;	}

	~GameObject() {}

private:
	MyString m_Name;
	Vector2D m_Position;
};