#pragma once
#include "iostream"

class Point2D
{

public:
	static const Point2D Zero;
	static const Point2D Unit;
	static const Point2D Unit_Negative;

	Point2D() : m_x(0.0f), m_y(0.0f) {}

	// Constructor
	Point2D(float i_x, float i_y)
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
	inline bool operator==(const Point2D &i_other) const
	{
		if (m_x == i_other.x() && m_y == i_other.y())
		{
			return true;
		}
		return false;
	}

	// Addition
	inline Point2D operator+(const Point2D &i_other) const
	{
		Point2D temp;
		temp.m_x = m_x + i_other.m_x;
		temp.m_y = m_y + i_other.m_y;

		return temp;
	}

	// Multiplication
	inline Point2D operator*(const Point2D &i_other) const
	{
		Point2D temp;
		temp.m_x = m_x * i_other.m_x;
		temp.m_y = m_y * i_other.m_y;

		return temp;
	}

	// Substraction
	inline Point2D operator-(const Point2D &i_other) const
	{
		Point2D temp;
		temp.m_x = m_x - i_other.m_x;
		temp.m_y = m_y - i_other.m_y;

		return temp;
	}

	//Devide
	inline Point2D operator/(const Point2D &i_other) const
	{
		Point2D temp;
		temp.m_x = m_x / i_other.m_x;
		temp.m_y = m_y / i_other.m_y;

		return temp;
	}

	// 
	inline Point2D operator/(const float &i_value) const
	{
		Point2D temp;
		temp.m_x = m_x / i_value;
		temp.m_y = m_y / i_value;

		return temp;
	}

	// 
	inline Point2D operator*(const float &i_value) const
	{
		Point2D temp;
		temp.m_x = m_x * i_value;
		temp.m_y = m_y * i_value;

		return temp;
	}

	// 
	inline Point2D operator+(const float &i_value) const
	{
		Point2D temp;
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


private:
	float m_x, m_y;

};

