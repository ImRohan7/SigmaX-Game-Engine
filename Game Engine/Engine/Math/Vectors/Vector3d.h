#pragma once
#include "iostream"
#include "../../Console/ConsolePrint.h"

class Vector3d {

public:
	static const Vector3d Zero;
	static const Vector3d Unit;
	
	Vector3d() : m_x(0.0f), m_y(0.0f), m_z(0.0f)
	{}

	Vector3d(float i_x, float i_y, float i_z)
		: m_x(i_x), m_y(i_y), m_z(i_z)
	{}

	//Get
	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }

	//Set
	void x(const float i_x) { m_x = i_x; }
	void y(const float i_y) { m_x = i_y; }
	void z(const float i_z) { m_x = i_z; }

	// Addition
	inline Vector3d operator+(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x + i_other.m_x;
		temp.m_y = m_y + i_other.m_y;
		temp.m_z = m_z + i_other.m_z;

		return temp;
	}

	// Substract
	inline Vector3d operator-(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x - i_other.m_x;
		temp.m_y = m_y - i_other.m_y;
		temp.m_z = m_z - i_other.m_z;

		return temp;
	}

	// Devide
	inline Vector3d operator/(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x / i_other.m_x;
		temp.m_y = m_y / i_other.m_y;
		temp.m_z = m_z / i_other.m_z;

		return temp;
	}

	// Multiply
	inline Vector3d operator*(const Vector3d &i_other) const
	{
		Vector3d temp;
		temp.m_x = m_x * i_other.m_x;
		temp.m_y = m_y * i_other.m_y;
		temp.m_z = m_z * i_other.m_z;

		return temp;
	}

	//Print
	void printVector() const
	{
		std::cout << m_x << std::endl;
		std::cout << m_y << std::endl;
		std::cout << m_z << std::endl;
	}

	// Normalise
	inline void coolDown()
	{
		if (m_x < 0) { m_x = -m_x; }
		if (m_y < 0) { m_y = -m_y; }
		if (m_z < 0) { m_z = -m_z; }
	}
	
	// dot
	inline float dot(const Vector3d &i_vec) const
	{
		float toReturn = m_x * i_vec.x() + m_y * i_vec.y() + m_z * i_vec.z();
		return toReturn;
	}

	// Get Normal As AXIS
	inline Vector3d getNormal() const
	{
		return Vector3d(-m_x, -m_y, -m_z);
	}

	// Negate
	inline void negate() 
	{
		m_x = -m_x;
		m_y = -m_y;
		m_z = -m_z;
	}

	// Print to Log
	inline void printVectorInLOG() const
	{
		DEBUG_PRINT("X:%f Y:%f Z:%f", m_x, m_y, m_z);
	}

private:
		float m_x, m_y, m_z;
};

