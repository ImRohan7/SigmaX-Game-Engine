#pragma once
#include "../..//Math/Vectors/Vector3d.h"
#include "../..//Math/Vectors/Vector4d.h"
#include <xmmintrin.h>
#include <intrin.h>

namespace Math {

	class Matrix_4x4
	{

	public:
		Matrix_4x4();

		// Constructor
		Matrix_4x4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44
		);

		// Copy Constructor & Assignment Operator DO I NEED THIS ??
		//Matrix_4x4(const Matrix_4x4 & i_Oth);	
		//Matrix_4x4 & operator=(const Matrix_4x4 & i_oth);

		// Quick Useful Matrix creators
		static Matrix_4x4 CreateIdentity(void);
		static Matrix_4x4 CreateXRotation(float i_RotationRadians);
		static Matrix_4x4 CreateYRotation(float i_RotationRadians);
		static Matrix_4x4 CreateZRotation(float i_RotationRadians);

		static Matrix_4x4 CreateTranslation(Vector3d i_Trans);
		static Matrix_4x4 CreateTranslation(float i_TransX, float i_TransY, float i_TransZ);
		static Matrix_4x4 CreateScale(Vector3d i_Scale);
		static Matrix_4x4 CreateScale(float i_ScaleX, float i_ScaleY, float i_SccaleZ);

		// Inverse
		void Invert(void);
		Matrix_4x4 GetInverse(void) const; // return inverse of this instance
		Matrix_4x4 getInverseSSE(void) const; // SSE Version

		// Transpose
		void Transpose(void);
		Matrix_4x4 GetTranspose(void) const; // return Transpose of this instance

		// operator * with similar type
		Matrix_4x4 operator*(const Matrix_4x4 & i_Oth) const;
		Matrix_4x4 MultiplySSE(const Matrix_4x4 & rhs) const;  // SSE Version


		// float * M
		Matrix_4x4 operator*(const float & i_float) const;

		// operator * with vector4d [Row]
		// V * M
		Vector4d MultiplyLeft(const Vector4d & i_Oth) const;

		// operator * with Vector4d [column] ?
		// M * V
		Vector4d MultiplyRight(const Vector4d & i_Oth) const;

		// Print Matrix for debugging purpose
		void print_Me(void) const;

	private:
		union {
			float mat[16];
			__m128 m_row[4]; // 4 X 32
			struct
			{
				float m_11, m_12, m_13, m_14;//m_11, m_12, m_13, m_14
				float m_21, m_22, m_23, m_24;//m_21, m_22, m_23, m_24
				float m_31, m_32, m_33, m_34;//m_31, m_32, m_33, m_34
				float m_41, m_42, m_43, m_44;//m_41, m_42, m_43, m_44
			};
		};
	};

	// V4 = M * V ie. Right , Column Vector 
	inline Vector4d operator* (const Matrix_4x4 & i_mtx, const Vector4d & i_vec)
	{
		Vector4d toReturn = i_mtx.MultiplyRight(i_vec);
		return toReturn;
	}
	// V4 = V * M ie. Left , Row Vector
	inline Vector4d operator* (const Vector4d & i_vec, const Matrix_4x4 & i_mtx)
	{
		Vector4d toReturn = i_mtx.MultiplyLeft(i_vec);
		return toReturn;
	}
}