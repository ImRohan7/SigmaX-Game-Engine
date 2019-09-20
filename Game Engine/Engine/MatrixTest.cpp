#include "Vector3d.h"
#include "Vector4d.h"
#include "Vector2.h"
#include "Matrix_4x4.h"

namespace Math {

	static void test()
	{
		Vector3d V1(2, 3, 5);

	//Vector4d k(Vector3d::Unit, 9.0);

		Matrix_4x4 M1(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
		
		Matrix_4x4 m2(12,	6,	2,	4,
			13,	5,7,	8,
			9	,14	,10,	11,
			15,	16	,17	,3
		);
	//	Matrix_4x4 M1 = Matrix_4x4::CreateYRotation(80);
	
		Matrix_4x4 mx = m2.GetInverse();

		mx.print_Me();
		//m2.print_Me();
		m2.Invert();
		m2.print_Me();
		//Vector4d Test = Vector4d(5,10,15,20) * M1;

		//Matrix_4x4 m3 = M1 * 10.0;

		//Matrix_4x4 m3 = m2.GetInverse();

		//m3.print_Me();
		
		
		int stop;

	}

}