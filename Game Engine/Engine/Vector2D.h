#pragma once
#include "iostream"

class Vector2D
{

public:

	Vector2D() : m_x(0.0f), m_y(0.0f) {}

	// Constructor
	Vector2D(float i_x, float i_y)
	{
		m_x = i_x;
		m_y = i_y;
	}

	// get
	float x() const { return m_x; }
	float y() const { return m_y; }

	// set
	void x(float i_x) { m_x = i_x; }
	void y(float i_y) { m_y = i_y; }

	// Check Equals
	inline bool operator==(const Vector2D &i_other) const
	{
		if (m_x == i_other.x() && m_y == i_other.y())
		{
			return true;
		}
		return false;
	}

	// Addition
	inline Vector2D operator+(const Vector2D &i_other) const
	{
		Vector2D temp;
		temp.m_x = m_x + i_other.m_x;
		temp.m_y = m_y + i_other.m_y;

		return temp;
	}

	// Multiplication
	inline Vector2D operator*(const Vector2D &i_other) const
	{
		Vector2D temp;
		temp.m_x = m_x * i_other.m_x;
		temp.m_y = m_y * i_other.m_y;

		return temp;
	}

	// Substraction
	inline Vector2D operator-(const Vector2D &i_other) const
	{
		Vector2D temp;
		temp.m_x = m_x - i_other.m_x;
		temp.m_y = m_y - i_other.m_y;

		return temp;
	}

	//Devide
	inline Vector2D operator/(const Vector2D &i_other) const
	{
		Vector2D temp;
		temp.m_x = m_x / i_other.m_x;
		temp.m_y = m_y / i_other.m_y;

		return temp;
	}

	// Normalise
	inline void coolDown()
	{
		if (m_x < 0) { m_x = -m_x; }
		if (m_y < 0) { m_y = -m_y; }
	}

	// Negate
	inline void Negate()
	{
		m_x = -m_x;
		m_y = -m_y;
	}

	// Random
	inline void Rand_Shuffle(int i_min, int i_max)
	{
		m_x = (float)(rand() % i_max + i_min);
		m_y = (float)(rand() % i_max + i_min);
	}

	// Print
	void printVector() const
	{
		std::cout << m_x << std::endl;
		std::cout << m_y << std::endl;
	}

	static const Vector2D Zero;
	static const Vector2D Unit;
	static const Vector2D Unit_Negative;


private:
	float m_x, m_y;

};

