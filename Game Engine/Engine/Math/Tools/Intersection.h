#pragma once
#include "../Vectors/Vector2.h"

namespace Math{

	class Intersection {
	public:
		
		/* Get Intersection Point of two Lines
		@Param pa1: Line 1, point 1
		@Param pa2: Line 1, point 2
		@Param pb1: Line 2, point 1
		@Param pb2: Line 2, point 2
		*/
		static Vector2 getIntersectionPoint(Vector2 pa1, Vector2 pa2, Vector2 pb1, Vector2 pb2);
		
		static Vector2 getIntersectionPoint(Vector2 points[4])
		{
			return getIntersectionPoint(points[0], points[1], points[2], points[3]);
		}


	};

}