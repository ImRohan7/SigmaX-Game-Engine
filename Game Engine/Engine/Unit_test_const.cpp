#include "Vector2D.h"
#include "iostream"
bool unitTest_const();

bool unitTest_const()
{
	Vector2D A(21, 11);
	Vector2D B(10, 11);

	int x = A.x();

	B = A - B;
	A = A + B;
	B = A * B;

	std::cout << "B :" << B.x();


	return true;



}