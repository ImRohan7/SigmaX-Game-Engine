#include "Intersection.h"

Vector2 Math::Intersection::getIntersectionPoint(Vector2 pa1, Vector2 pa2, Vector2 pb1, Vector2 pb2)
{
	Vector2 result;
	// line eq: Ax + By = C
	float A1 = pa2.y() - pa1.y(); // A = Y2 - Y1 getting from Y = mX + C ; m = (Y1-Y2)/(X1-X2)
	float B1 = pa1.x() - pa2.x(); // B = X1 - X2
	float C1 = A1 * pa1.x() + B1 * pa1.y();

	// Line 2
	float A2 = pb2.y() - pb1.y(); // A = Y2 - Y1
	float B2 = pb1.x() - pb2.x(); // B = X1 - X2
	float C2 = A2 * pb1.x() + B2 * pb1.y();

	// intersect eq
	float denominator = (A1 * B2) - (A2 * B1);
	
	result.x((B2 * C1 - B1 * C2) / denominator);
	result.y((A1 * C2 - A2 * C1) / denominator);


	return result;
}
