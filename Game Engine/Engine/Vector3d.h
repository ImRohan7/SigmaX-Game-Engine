#pragma once
#include "iostream"

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
	
	// Negate
	inline void negate() 
	{
		m_x = -m_x;
		m_y = -m_y;
		m_z = -m_z;
	}

private:
		float m_x, m_y, m_z;
};

//const Vector3d Vector3d::Zero(0.0f, 0.0f, 0.0f);
//const Vector3d Vector3d::Unit(1.0f, 1.0f, 1.0f);