#pragma once
#include "iostream"
#include "../..//Console/ConsolePrint.h"

class Vector2
{

public:
	static const Vector2 Zero;
	static const Vector2 Unit;
	static const Vector2 Unit_Negative;

	Vector2() : m_x(0.0f), m_y(0.0f) {}

	// Constructor
	Vector2(float i_x, float i_y)
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
	inline bool operator==(const Vector2 &i_other) const
	{
		if (m_x == i_other.x() && m_y == i_other.y())
		{
			return true;
		}
		return false;
	}

	// Check Equals with Float
	inline bool operator==(const float &i_float) const
	{
		if (m_x == i_float && m_y == i_float)
		{
			return true;
		}
		return false;
	}

	// Addition
	inline Vector2 operator+(const Vector2 &i_other) const
	{
		Vector2 temp;
		temp.m_x = m_x + i_other.m_x;
		temp.m_y = m_y + i_other.m_y;

		return temp;
	}

	// shorthand addition
	inline Vector2 operator+=(const Vector2 &i_other) const
	{
		Vector2 tmp = *this + i_other;
		return tmp;
	}

	// Multiplication
	inline Vector2 operator*(const Vector2 &i_other) const
	{
		Vector2 temp;
		temp.m_x = m_x * i_other.m_x;
		temp.m_y = m_y * i_other.m_y;

		return temp;
	}

	// Substraction
	inline Vector2 operator-(const Vector2 &i_other) const
	{
		Vector2 temp;
		temp.m_x = m_x - i_other.m_x;
		temp.m_y = m_y - i_other.m_y;

		return temp;
	}

	//Devide
	inline Vector2 operator/(const Vector2 &i_other) const
	{
		Vector2 temp;
		temp.m_x = m_x / i_other.m_x;
		temp.m_y = m_y / i_other.m_y;

		return temp;
	}

	// 
	inline Vector2 operator/(const float &i_value) const
	{
		Vector2 temp;
		temp.m_x = m_x / i_value;
		temp.m_y = m_y / i_value;

		return temp;
	}

	// 
	inline Vector2 operator*(const float &i_value) const
	{
		Vector2 temp;
		temp.m_x = m_x * i_value;
		temp.m_y = m_y * i_value;

		return temp;
	}

	// 
	inline Vector2 operator+(const float &i_value) const
	{
		Vector2 temp;
		temp.m_x = m_x + i_value;
		temp.m_y = m_y + i_value;

		return temp;
	}

	// Normalise
	inline void coolDown()
	{
		if (m_x < 0) { m_x = -m_x; }
		if (m_y < 0) { m_y = -m_y; }
	}

	// negative
	inline Vector2 operator-()
	{
		Negate();
		return *this;
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

	// dot
	inline float dot(const Vector2 &i_vec) const
	{
		float toReturn = m_x * i_vec.x() + m_y * i_vec.y();
		return toReturn;
	}

	// Get Normal As AXIS
	inline Vector2 getNormal() const
	{
		return Vector2(-m_x, -m_y);
	}

	// Print
	inline void printVector() const
	{
		DEBUG_PRINT("Vector2 :: X: %f  Y: %f", m_x, m_y);
	}

	// Print to Log
	inline void printVectorInLOG() const
	{
		DEBUG_PRINT("X:%f Y:%f", m_x, m_y);
	}

	inline void RoundTo2()
	{
		m_x = roundf(m_x * 100) / 100;
		m_y = roundf(m_y * 100) / 100;
	}

private:
	float m_x, m_y;

};

