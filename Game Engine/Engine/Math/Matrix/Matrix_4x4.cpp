#include "Matrix_4x4.h"
#include <cmath> 
#include "../..//Console/ConsolePrint.h"
#include <assert.h>

#define PI 3.14159265
#define	D ( PI / 180.0 )				// for radian to degree
namespace Math {
	Matrix_4x4::Matrix_4x4()
	{
#ifdef HEAP_DEBUG = 1
		m_11 = NAN;		// check with assert to amek sure not to use any matrix without intializing 
#endif // DEBUG
	}

	Matrix_4x4::Matrix_4x4(
		float i_11, float i_12, float i_13, float i_14,
		float i_21, float i_22, float i_23, float i_24,
		float i_31, float i_32, float i_33, float i_34,
		float i_41, float i_42, float i_43, float i_44
	) :
		m_11(i_11), m_12(i_12), m_13(i_13), m_14(i_14),
		m_21(i_21), m_22(i_22), m_23(i_23), m_24(i_24),
		m_31(i_31), m_32(i_32), m_33(i_33), m_34(i_34),
		m_41(i_41), m_42(i_42), m_43(i_43), m_44(i_44)
	{}

	// Print
	void Matrix_4x4::print_Me(void) const
	{
		assert(!isnan(m_11));
		DEBUG_PRINT("%f	 %f  %f  %f\n\t %f	 %f  %f  %f\n\t "
			"%f	 %f  %f  %f\n\t %f	 %f  %f  %f\n",
			m_11, m_12, m_13, m_14, m_21, m_22, m_23, m_24,
			m_31, m_32, m_33, m_34, m_41, m_42, m_43, m_44
		);
	}

	// Identity
	Matrix_4x4 Matrix_4x4::CreateIdentity(void)
	{
		return Matrix_4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	Matrix_4x4 Matrix_4x4::CreateXRotation(float i_Degree)
	{
		float Radians = i_Degree * D;
		return Matrix_4x4(
			1, 0, 0, 0,
			0, cos(Radians), -sin(Radians), 0,
			0, sin(Radians), cos(Radians), 0,
			0, 0, 0, 1
		);
	}

	Matrix_4x4 Matrix_4x4::CreateYRotation(float i_degree)
	{
		float Radians = i_degree * D;
		return Matrix_4x4(
			cos(Radians), 0, sin(Radians), 0,
			0, 1, 0, 0,
			-sin(Radians), 0, cos(Radians), 0,
			0, 0, 0, 1
		);
	}

	Matrix_4x4 Matrix_4x4::CreateZRotation(float i_Degree)
	{
		float Radians = i_Degree * D;
		return Matrix_4x4(
			cos(Radians), -sin(Radians), 0, 0,
			sin(Radians), cos(Radians), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
		//return toReturn;		<< Why this isn't working
	}

	Matrix_4x4 Matrix_4x4::CreateTranslation(Vector3d i_trans)
	{
		return Matrix_4x4::CreateTranslation(i_trans.x(), i_trans.y(), i_trans.z());
	}

	Matrix_4x4 Matrix_4x4::CreateTranslation(float i_TransX, float i_TransY, float i_TransZ)
	{
		return Matrix_4x4(
			1, 0, 0, i_TransX,
			0, 1, 0, i_TransY,
			0, 0, 1, i_TransZ,
			0, 0, 0, 1
		);
	}

	Matrix_4x4 Matrix_4x4::CreateScale(Vector3d i_Scale)
	{
		return Matrix_4x4::CreateScale(i_Scale.x(), i_Scale.y(), i_Scale.z());
	}

	Matrix_4x4 Matrix_4x4::CreateScale(float i_ScaleX, float i_ScaleY, float i_SccaleZ)
	{
		return Matrix_4x4(
			i_ScaleX, 0, 0, 0,
			0, i_ScaleY, 0, 0,
			0, 0, i_SccaleZ, 0,
			0, 0, 0, 1
			);
	}

	void Matrix_4x4::Transpose(void)	// transpose this
	{
		*this = this->GetTranspose();
	}

	Matrix_4x4 Matrix_4x4::GetTranspose(void) const		//  return transpose of this
	{
		Matrix_4x4 temp = *this;

		temp.m_21 = m_12;
		temp.m_31 = m_13;
		temp.m_41 = m_14;

		temp.m_12 = m_21;
		temp.m_32 = m_23;
		temp.m_42 = m_24;

		temp.m_13 = m_31;
		temp.m_23 = m_32;
		temp.m_43 = m_34;

		temp.m_14 = m_41;
		temp.m_24 = m_42;
		temp.m_34 = m_43;
		
		return temp;
	}

	void Matrix_4x4::Invert(void)
	{
		*this = this->GetInverse();
	}

	Matrix_4x4 Matrix_4x4::MultiplySSE(const Matrix_4x4 & i_other) const
	{
		// get Rows
		__m128 _row1 = _mm_load_ps(&i_other.m_11);
		__m128 _row2 = _mm_load_ps(&i_other.m_21);
		__m128 _row3 = _mm_load_ps(&i_other.m_31);
		__m128 _row4 = _mm_load_ps(&i_other.m_41);


		__m128 capture;
		Matrix_4x4 toReturn;
		
		// calculate rows
		// m_11 * i_other.row1
		capture = _mm_mul_ps(_mm_load1_ps(&m_11), _row1);
		// m_12 * i_other.row2
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_12), _row2));
		// m_13 * i_other.row3
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_13), _row3));
		// m_14 * i_other.row4
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_14), _row4));

		// Store First Row
		_mm_storel_pi(reinterpret_cast<__m64 *>(&toReturn.m_11), capture);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&toReturn.m_13), capture);

		capture = _mm_mul_ps(_mm_load1_ps(&m_21), _row1);
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_22), _row2));
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_23), _row3));
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_24), _row4));

		// Store Second Row
		_mm_storel_pi(reinterpret_cast<__m64 *>(&toReturn.m_21), capture);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&toReturn.m_23), capture);

		capture = _mm_mul_ps(_mm_load1_ps(&m_31), _row1);
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_32), _row2));
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_33), _row3));
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_34), _row4));

		// Store Third Row
		_mm_storel_pi(reinterpret_cast<__m64 *>(&toReturn.m_31), capture);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&toReturn.m_33), capture);

		capture = _mm_mul_ps(_mm_load1_ps(&m_41), _row1);
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_42), _row2));
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_43), _row3));
		capture = _mm_add_ps(capture, _mm_mul_ps(_mm_load1_ps(&m_44), _row4));

		// Store Fourth Row
		_mm_storel_pi(reinterpret_cast<__m64 *>(&toReturn.m_41), capture);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&toReturn.m_43), capture);

		return toReturn;
	}

	/*Matrix_4x4 Matrix_4x4::MultiplySSE(const Matrix_4x4 & i_other) const
	{
		return ((*this) * i_other);
	}*/

	Matrix_4x4 Matrix_4x4::GetInverse() const
	{

		float sub[17]; // 0 = NULL

		sub[1] = m_22 * m_33 * m_44
			+ m_23 * m_34 * m_42
			+ m_24 * m_32 * m_43
			- m_24 * m_33 * m_42
			- m_22 * m_34 * m_43
			- m_23 * m_32 * m_44;

		sub[2] = m_21 * m_33 * m_44
			+ m_23 * m_34 * m_41
			+ m_24 * m_31 * m_43
			- m_21 * m_34 * m_43
			- m_23 * m_31 * m_44
			- m_24 * m_33 * m_41;

		sub[3] = m_21 * m_32 * m_44
			+ m_22 * m_34 * m_41
			+ m_24 * m_31 * m_42
			- m_24 * m_32 * m_41
			- m_22 * m_31 * m_44
			- m_21 * m_34 * m_42;

		sub[4] = m_21 * m_32 * m_43
			+ m_22 * m_33 * m_41
			+ m_23 * m_31 * m_42
			- m_23 * m_32 * m_41
			- m_22 * m_31 * m_43
			- m_21 * m_33 * m_42;

		sub[5] = m_12 * m_33 * m_44
			+ m_13 * m_34 * m_42
			+ m_14 * m_32 * m_43
			- m_14 * m_33 * m_42
			- m_13 * m_32 * m_44
			- m_12 * m_34 * m_43;

		sub[6] = m_11 * m_33 * m_44
			+ m_13 * m_34 * m_41
			+ m_14 * m_31 * m_43
			- m_14 * m_33 * m_41
			- m_13 * m_31 * m_44
			- m_11 * m_34 * m_43;

		sub[7] = m_11 * m_32 * m_44
			+ m_12 * m_34 * m_41
			+ m_14 * m_31 * m_42
			- m_14 * m_32 * m_41
			- m_12 * m_31 * m_44
			- m_11 * m_34 * m_42;

		sub[8] = m_11 * m_32 * m_43
			+ m_12 * m_33 * m_41
			+ m_13 * m_31 * m_42
			- m_13 * m_32 * m_41
			- m_12 * m_31 * m_43
			- m_11 * m_33 * m_42;

		sub[9] = m_12 * m_23 * m_44
			+ m_13 * m_24 * m_42
			+ m_14 * m_22 * m_43
			- m_14 * m_23 * m_42
			- m_13 * m_22 * m_44
			- m_12 * m_24 * m_43;

		sub[10] = m_11 * m_23 * m_44
			+ m_13 * m_24 * m_41
			+ m_14 * m_21 * m_43
			- m_14 * m_23 * m_41
			- m_13 * m_21 * m_44
			- m_11 * m_24 * m_43;

		sub[11] = m_11 * m_22 * m_44
			+ m_12 * m_24 * m_41
			+ m_14 * m_21 * m_42
			- m_14 * m_22 * m_41
			- m_12 * m_21 * m_44
			- m_11 * m_24 * m_42;

		sub[12] = m_11 * m_22 * m_43
			+ m_12 * m_23 * m_41
			+ m_13 * m_21 * m_42
			- m_13 * m_22 * m_41
			- m_12 * m_21 * m_43
			- m_11 * m_23 * m_42;

		sub[13] = m_12 * m_23 * m_34
			+ m_13 * m_24 * m_32
			+ m_14 * m_22 * m_33
			- m_14 * m_23 * m_32
			- m_13 * m_22 * m_34
			- m_12 * m_24 * m_33;

		sub[14] = m_11 * m_23 * m_34
			+ m_13 * m_24 * m_31
			+ m_14 * m_21 * m_33
			- m_14 * m_23 * m_31
			- m_13 * m_21 * m_34
			- m_11 * m_24 * m_33;

		sub[15] = m_11 * m_22 * m_34
			+ m_12 * m_24 * m_31
			+ m_14 * m_21 * m_32
			- m_14 * m_22 * m_31
			- m_12 * m_21 * m_34
			- m_11 * m_24 * m_32;

		sub[16] = m_11 * m_22 * m_33
			+ m_12 * m_23 * m_31
			+ m_13 * m_21 * m_32
			- m_13 * m_22 * m_31
			- m_12 * m_21 * m_33
			- m_11 * m_23 * m_32;


		float detrminant = m_11 * sub[1] - m_21 * sub[5]
			+ m_31 * sub[9] - m_41 * sub[13];

		if (detrminant == 0)
		{
			DEBUG_PRINT("Can't find Inverse. Determinant is 0.");
			return Matrix_4x4();
		}
		else
		{
			float invOfDet = 1 / detrminant;

			Matrix_4x4 temp(sub[1], -sub[5], sub[9], -sub[13],
				-sub[2], sub[6], -sub[10], sub[14],
				sub[3], -sub[7], sub[11], -sub[15],
				-sub[4], sub[8], -sub[12], sub[16]);

			// Inverse  = [ 1/det(A) ] * adj(A);
			Matrix_4x4 Inverse = temp * invOfDet;

			return Inverse;
		}
	}

	/*Matrix_4x4 Matrix_4x4::getInverseSSE() const
	{
		return ((*this).GetInverse());
	}*/


	Matrix_4x4 Matrix_4x4::getInverseSSE() const
	{
		__m128 tmp = { 0.0f };
		__m128 _row0, _row1, _row2, _row3;
		__m128 _minor0, _minor1, _minor2, _minor3;

		tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, reinterpret_cast<const __m64 *>(&m_11)), reinterpret_cast<const __m64 *>(&m_21));
		_row1 = _mm_loadh_pi(_mm_loadl_pi(tmp, reinterpret_cast<const __m64 *>(&m_31)), reinterpret_cast<const __m64 *>(&m_41));
		_row0 = _mm_shuffle_ps(tmp, _row1, 0x88);
		_row1 = _mm_shuffle_ps(_row1, tmp, 0xDD);
		tmp = _mm_loadh_pi(_mm_loadl_pi(tmp, reinterpret_cast<const __m64 *>(&m_13)), reinterpret_cast<const __m64 *>(&m_23));
		_row3 = _mm_loadh_pi(_mm_loadl_pi(tmp, reinterpret_cast<const __m64 *>(&m_33)), reinterpret_cast<const __m64 *>(&m_43));
		_row2 = _mm_shuffle_ps(tmp, _row3, 0x88);
		_row3 = _mm_shuffle_ps(_row3, tmp, 0xDD);

		// -----------------------------------------------
		tmp = _mm_mul_ps(_row2, _row3);
		tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
		_minor0 = _mm_mul_ps(_row1, tmp);
		_minor1 = _mm_mul_ps(_row0, tmp);
		tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
		_minor0 = _mm_sub_ps(_mm_mul_ps(_row1, tmp), _minor0);
		_minor1 = _mm_sub_ps(_mm_mul_ps(_row0, tmp), _minor1);
		_minor1 = _mm_shuffle_ps(_minor1, _minor1, 0x4E);

		// -----------------------------------------------
		tmp = _mm_mul_ps(_row1, _row2);
		tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
		_minor0 = _mm_add_ps(_mm_mul_ps(_row3, tmp), _minor0);
		_minor3 = _mm_mul_ps(_row0, tmp);
		tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
		_minor0 = _mm_sub_ps(_minor0, _mm_mul_ps(_row3, tmp));
		_minor3 = _mm_sub_ps(_mm_mul_ps(_row0, tmp), _minor3);
		_minor3 = _mm_shuffle_ps(_minor3, _minor3, 0x4E);

		// -----------------------------------------------
		tmp = _mm_mul_ps(_mm_shuffle_ps(_row1, _row1, 0x4E), _row3);
		tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
		_row2 = _mm_shuffle_ps(_row2, _row2, 0x4E);
		_minor0 = _mm_add_ps(_mm_mul_ps(_row2, tmp), _minor0);
		_minor2 = _mm_mul_ps(_row0, tmp);
		tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
		_minor0 = _mm_sub_ps(_minor0, _mm_mul_ps(_row2, tmp));
		_minor2 = _mm_sub_ps(_mm_mul_ps(_row0, tmp), _minor2);
		_minor2 = _mm_shuffle_ps(_minor2, _minor2, 0x4E);

		// -----------------------------------------------
		tmp = _mm_mul_ps(_row0, _row1);
		tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
		_minor2 = _mm_add_ps(_mm_mul_ps(_row3, tmp), _minor2);
		_minor3 = _mm_sub_ps(_mm_mul_ps(_row2, tmp), _minor3);
		tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
		_minor2 = _mm_sub_ps(_mm_mul_ps(_row3, tmp), _minor2);
		_minor3 = _mm_sub_ps(_minor3, _mm_mul_ps(_row2, tmp));

		// -----------------------------------------------
		tmp = _mm_mul_ps(_row0, _row3);
		tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
		_minor1 = _mm_sub_ps(_minor1, _mm_mul_ps(_row2, tmp));
		_minor2 = _mm_add_ps(_mm_mul_ps(_row1, tmp), _minor2);
		tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
		_minor1 = _mm_add_ps(_mm_mul_ps(_row2, tmp), _minor1);
		_minor2 = _mm_sub_ps(_minor2, _mm_mul_ps(_row1, tmp));

		// -----------------------------------------------
		tmp = _mm_mul_ps(_row0, _row2);
		tmp = _mm_shuffle_ps(tmp, tmp, 0xB1);
		_minor1 = _mm_add_ps(_mm_mul_ps(_row3, tmp), _minor1);
		_minor3 = _mm_sub_ps(_minor3, _mm_mul_ps(_row1, tmp));
		tmp = _mm_shuffle_ps(tmp, tmp, 0x4E);
		_minor1 = _mm_sub_ps(_minor1, _mm_mul_ps(_row3, tmp));
		_minor3 = _mm_add_ps(_mm_mul_ps(_row1, tmp), _minor3);

		// Calculate determinant
		__m128 det;

		det = _mm_mul_ps(_row0, _minor0);
		det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
		det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
		tmp = _mm_rcp_ss(det);
		det = _mm_sub_ss(_mm_add_ss(tmp, tmp), _mm_mul_ss(det, _mm_mul_ss(tmp, tmp)));
		det = _mm_shuffle_ps(det, det, 0x00);

		_minor0 = _mm_mul_ps(det, _minor0);
		Matrix_4x4 ToReturn;
		_mm_storel_pi(reinterpret_cast<__m64 *>(&ToReturn.m_11), _minor0);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&ToReturn.m_13), _minor0);

		_minor1 = _mm_mul_ps(det, _minor1);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&ToReturn.m_21), _minor1);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&ToReturn.m_23), _minor1);

		_minor2 = _mm_mul_ps(det, _minor2);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&ToReturn.m_31), _minor2);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&ToReturn.m_33), _minor2);

		_minor3 = _mm_mul_ps(det, _minor3);
		_mm_storel_pi(reinterpret_cast<__m64 *>(&ToReturn.m_41), _minor3);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(&ToReturn.m_43), _minor3);
		return ToReturn;
	}


	// * with float
	Matrix_4x4 Matrix_4x4::operator*(const float & i_float) const
	{
		Matrix_4x4 temp;

		temp.m_11 = m_11 * i_float;
		temp.m_12 = m_12 * i_float;
		temp.m_13 = m_13 * i_float;
		temp.m_14 = m_14 * i_float;
		temp.m_21 = m_21 * i_float;
		temp.m_22 = m_22 * i_float;
		temp.m_23 = m_23 * i_float;
		temp.m_24 = m_24 * i_float;
		temp.m_31 = m_31 * i_float;
		temp.m_32 = m_32 * i_float;
		temp.m_33 = m_33 * i_float;
		temp.m_34 = m_34 * i_float;
		temp.m_41 = m_41 * i_float;
		temp.m_42 = m_42 * i_float;
		temp.m_43 = m_43 * i_float;
		temp.m_44 = m_44 * i_float;

		return temp;
	}

	Matrix_4x4 Matrix_4x4::operator*(const Matrix_4x4 & i_Oth) const
	{
		float sub[17];

		sub[1] = m_11 * i_Oth.m_11 + m_12 * i_Oth.m_21 + m_13 * i_Oth.m_31 + m_14 * i_Oth.m_41;
		sub[2] = m_11 * i_Oth.m_12 + m_12 * i_Oth.m_22 + m_13 * i_Oth.m_32 + m_14 * i_Oth.m_42;
		sub[3] = m_11 * i_Oth.m_13 + m_12 * i_Oth.m_23 + m_13 * i_Oth.m_33 + m_14 * i_Oth.m_43;
		sub[4] = m_11 * i_Oth.m_14 + m_12 * i_Oth.m_24 + m_13 * i_Oth.m_34 + m_14 * i_Oth.m_44;

		sub[5] = m_21 * i_Oth.m_11 + m_22 * i_Oth.m_21 + m_23 * i_Oth.m_31 + m_24 * i_Oth.m_41;
		sub[6] = m_21 * i_Oth.m_12 + m_22 * i_Oth.m_22 + m_23 * i_Oth.m_32 + m_24 * i_Oth.m_42;
		sub[7] = m_21 * i_Oth.m_13 + m_22 * i_Oth.m_23 + m_23 * i_Oth.m_33 + m_24 * i_Oth.m_43;
		sub[8] = m_21 * i_Oth.m_14 + m_22 * i_Oth.m_24 + m_23 * i_Oth.m_34 + m_24 * i_Oth.m_44;

		sub[9] =  m_31 * i_Oth.m_11 + m_32 * i_Oth.m_21 + m_33 * i_Oth.m_31 + m_34 * i_Oth.m_41;
		sub[10] = m_31 * i_Oth.m_12 + m_32 * i_Oth.m_22 + m_33 * i_Oth.m_32 + m_34 * i_Oth.m_42;
		sub[11] = m_31 * i_Oth.m_13 + m_32 * i_Oth.m_23 + m_33 * i_Oth.m_33 + m_34 * i_Oth.m_43;
		sub[12] = m_31 * i_Oth.m_14 + m_32 * i_Oth.m_24 + m_33 * i_Oth.m_34 + m_34 * i_Oth.m_44;

		sub[13] = m_41 * i_Oth.m_11 + m_42 * i_Oth.m_21 + m_43 * i_Oth.m_31 + m_44 * i_Oth.m_41;
		sub[14] = m_41 * i_Oth.m_12 + m_42 * i_Oth.m_22 + m_43 * i_Oth.m_32 + m_44 * i_Oth.m_42;
		sub[15] = m_41 * i_Oth.m_13 + m_42 * i_Oth.m_23 + m_43 * i_Oth.m_33 + m_44 * i_Oth.m_43;
		sub[16] = m_41 * i_Oth.m_14 + m_42 * i_Oth.m_24 + m_43 * i_Oth.m_34 + m_44 * i_Oth.m_44;

		return Matrix_4x4(sub[1],  sub[2], sub[3],  sub[4],
			 sub[5], sub[6],  sub[7], sub[8],
			sub[9],  sub[10], sub[11],  sub[12],
			 sub[13], sub[14],  sub[15], sub[16]);
	}

	// Multiply Vector Left
	Vector4d Matrix_4x4::MultiplyLeft(const Vector4d & i_Oth) const
	{
		float x = i_Oth.x() * m_11 + i_Oth.y() * m_21 + i_Oth.z() * m_31 + i_Oth.w() * m_41;
		float y = i_Oth.x() * m_12 + i_Oth.y() * m_22 + i_Oth.z() * m_32 + i_Oth.w() * m_42;
		float z = i_Oth.x() * m_13 + i_Oth.y() * m_23 + i_Oth.z() * m_33 + i_Oth.w() * m_43;
		float w = i_Oth.x() * m_14 + i_Oth.y() * m_24 + i_Oth.z() * m_34 + i_Oth.w() * m_44;

		return Vector4d(x, y, z, w);
	}

	Vector4d Matrix_4x4::MultiplyRight(const Vector4d & i_Oth) const
	{
		float x = m_11 * i_Oth.x() + m_12 * i_Oth.y() + m_13 * i_Oth.z() + m_14 * i_Oth.w();
		float y = m_21 * i_Oth.x() + m_22 * i_Oth.y() + m_23 * i_Oth.z() + m_24 * i_Oth.w();
		float z = m_31 * i_Oth.x() + m_32 * i_Oth.y() + m_33 * i_Oth.z() + m_34 * i_Oth.w();
		float w = m_41 * i_Oth.x() + m_42 * i_Oth.y() + m_43 * i_Oth.z() + m_44 * i_Oth.w();

		return Vector4d(x, y, z, w);
	}

}