#pragma once
#include "iostream"
#include "Vector3d.h"

class Vector4d {

public:
	static const Vector4d Zero;
	static const Vector4d Unit;

	Vector4d() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f)
	{}

	Vector4d(float i_x, float i_y, float i_z, float i_w)
		: m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w)
	{}

	Vector4d(const Vector3d & i_Vec, float i_4):
		m_x(i_Vec.x()), m_y(i_Vec.y()), m_z(i_Vec.z()), m_w(i_4)
	{}

	//Get
	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }
	float w() const { return m_w; }

	//Set
	void x(const float i_x) { m_x = i_x; }
	void y(const float i_y) { m_x = i_y; }
	void z(const float i_z) { m_x = i_z; }
	void w(const float i_w) { m_w = i_w; }

	// Addition
	Vector4d operator+(const Vector4d &i_other) const;

	// Substravtion
	Vector4d operator-(const Vector4d &i_other) const;

	// Devide
	Vector4d operator/(const Vector4d &i_other) const;
	
	// Multiply
	Vector4d operator*(const Vector4d &i_other) const;

	//Print
	void printVector() const;

	// Normalise
	inline void coolDown();
	
	// Negate
	inline void negate();

private:
	float m_x, m_y, m_z, m_w;
};

//const Vector4d Vector4d::Zero(Vector3d::Zero, 0.0f);
//const Vector4d Vector4d::Unit(Vector3d::Unit, 1.0f);

inline Vector4d Vector4d::operator+(const Vector4d &i_other) const
{
	Vector4d temp;
	temp.m_x = m_x + i_other.m_x;
	temp.m_y = m_y + i_other.m_y;
	temp.m_z = m_z + i_other.m_z;
	temp.m_w = m_z + i_other.m_w;

	return temp;
}

inline Vector4d Vector4d::operator-(const Vector4d &i_other) const
{
	Vector4d temp;
	temp.m_x = m_x - i_other.m_x;
	temp.m_y = m_y - i_other.m_y;
	temp.m_z = m_z - i_other.m_z;
	temp.m_w = m_w - i_other.m_w;

	return temp;
}

inline Vector4d Vector4d::operator/(const Vector4d &i_other) const
{
	Vector4d temp;
	temp.m_x = m_x / i_other.m_x;
	temp.m_y = m_y / i_other.m_y;
	temp.m_z = m_z / i_other.m_z;
	temp.m_w = m_w / i_other.m_w;

	return temp;
}

inline Vector4d Vector4d::operator*(const Vector4d &i_other) const
{
	Vector4d temp;
	temp.m_x = m_x * i_other.m_x;
	temp.m_y = m_y * i_other.m_y;
	temp.m_z = m_z * i_other.m_z;
	temp.m_w = m_w * i_other.m_w;

	return temp;
}

inline void Vector4d::printVector() const
{
	std::cout << m_x << std::endl;
	std::cout << m_y << std::endl;
	std::cout << m_z << std::endl;
}

inline void Vector4d::coolDown()
{
	if (m_x < 0) { m_x = -m_x; }
	if (m_y < 0) { m_y = -m_y; }
	if (m_z < 0) { m_z = -m_z; }
	if (m_w < 0) { m_w = -m_w; }
}

inline void Vector4d::negate()
{
	m_x = -m_x;
	m_y = -m_y;
	m_z = -m_z;
	m_w = -m_w;
}

