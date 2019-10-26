#pragma once
#include "../..//Actor/GameObject.h"
#include <iostream>
#include "../..//Engine/Engine.h"

namespace Engine {
	namespace Physics {

		/*struct AABB
		{
			Vector2 m_Center;
			Vector2 m_Extents;
		};*/


		class CollisionHandler
		{
			public:
				void HandleCollisions(std::vector<SmartPtr<GameObject>>, float t_EndFrame);

				//  cheks the collision for angular no frame-to-frame
		//		bool checkAngularSeperationXY(float i_srcProj, Vector4d i_srcCenterInDest ,AABB i_AABBdest );
				
				// checks collision
				bool IsCollision(SmartPtr<GameObject> i_A, SmartPtr<GameObject> i_B, float t_EndFrame, bool &IsX) const;

				// the ground collisions objects [0] object, [1] platform
				void handleGroundCollision(SmartPtr<GameObject> i_O, SmartPtr<GameObject> i_P);

				// modify the ground status from the pair by checking if they are still colliding
				void verifyGroundStatus(float t_EndFrame, bool IsX);

				// check Axis collision and updates the time variables
				bool checkAxisCollision(
					float srcProj,
					float relVel,
					float srcCenterinDest,
					float BBdestCenter,
					float destExtent,
					float t_EndFrame,
					float &tCLose,
					float &tOpen
				) const;

				void ApplyResponse(SmartPtr<GameObject> A, SmartPtr<GameObject> B, bool IsX) const;

				void OnEnter(bool dos);
		};
	}
}
