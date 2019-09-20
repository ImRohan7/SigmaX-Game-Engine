#include "CollisionHandler.h"
#include "ConsolePrint.h"
#include "Matrix_4x4.h"

namespace Engine {
	namespace Physics {

		
		void CollisionHandler::HandleCollisions(std::vector<SmartPtr<GameObject>> i_Collidables, float t_EndFrame)
		{
			const size_t count = i_Collidables.size();

			for (size_t i = 0; i < (count - 1); i++)
			{
				for (size_t j = i + 1; j < count; j++)
				{
					bool IsX = false;
					if (IsCollision(i_Collidables[i], i_Collidables[j], t_EndFrame, IsX))
					{
						// Do something here
						if (i == 0)
						{
							SmartPtr<GameObject> other = i_Collidables[j];
							other->tag;
							if (other->tag == 3)
							{
								DEBUG_PRINT("Game Over");
								Engine::setMode(Modes::Endscreen);
							}
						}
						ApplyResponse(i_Collidables[i], i_Collidables[j], IsX);
					}
				}
			}
		}

		bool CollisionHandler::IsCollision(SmartPtr<GameObject> i_A, SmartPtr<GameObject> i_B, float t_EndFrame, bool &IsX) const
		{
			SmartPtr<GameObject> A = i_A;
			SmartPtr<GameObject> B = i_B;
			Vector2 pos1 = A->GetPosition();
			Vector2 pos2 = B->GetPosition();

			AABB ObjA = A->getAABB();//setAABB(AA->getSpriteDimensions());
			AABB ObjB = B->getAABB();//setAABB(BB->getSpriteDimensions());

			Math::Matrix_4x4 WorldToA = A->getWorldToBase(); //getWorldToBase(A->GetPosition(), A->getRotationZ());
			Math::Matrix_4x4 AToWorld = A->getBaseToWorld(); // getBaseToWorld(A->GetPosition(), A->getRotationZ());

			Math::Matrix_4x4 WorldToB = B->getWorldToBase(); // getWorldToBase(B->GetPosition(), B->getRotationZ());
			Math::Matrix_4x4 BToWorld = B->getBaseToWorld(); // getBaseToWorld(B->GetPosition(), B->getRotationZ());

			// A TO B
			Math::Matrix_4x4 AToB = WorldToB.MultiplySSE(AToWorld);
			Vector4d ABBCenterInB = AToB * Vector4d(ObjA.m_Center.x(), ObjA.m_Center.y(), 0.0f, 1.0f);

			// Convert Extends
			Vector4d AExtXInB = AToB * Vector4d(ObjA.m_Extents.x(), 0.0f, 0.0f, 0.0f);
			Vector4d AExtYInB = AToB * Vector4d(0.0f, ObjA.m_Extents.y(), 0.0f, 0.0f);
			// Calculate Projections
			float AprojOnBX = fabs(AExtXInB.x()) + fabs(AExtYInB.x());
			float AprojOnBY = fabs(AExtXInB.y()) + fabs(AExtYInB.y());

			// Velocities
			Vector2 velA = A->getVelocity();
			Vector2 velB = B->getVelocity();
			Vector2 velARelToB = velA - velB;
			velARelToB.RoundTo2();
			Vector4d vel(Vector3d(velARelToB.x(), velARelToB.y(), 0.0f), 0.0f);
			Vector4d velAInB = WorldToB * vel;
		
	// X
			float tCloseX = 0;
			float tOpenX = 100;
			bool checkX = checkAxisCollision(AprojOnBX, velAInB.x(), ABBCenterInB.x(), ObjB.m_Center.x(), ObjB.m_Extents.x(), t_EndFrame, tCloseX, tOpenX);

			float tCloseY = 0;
			float tOpenY = 110;
			bool checkY = checkAxisCollision(AprojOnBY, velAInB.y(), ABBCenterInB.y(), ObjB.m_Center.y(), ObjB.m_Extents.y(), t_EndFrame, tCloseY, tOpenY);

			float tLatestclose;
			float tEarliestOpen;
			if (checkX && checkY)
			{
				// compare Tclose and Open
				//DEBUG_PRINT(" THERE IS A CHANCE ");
				IsX = tCloseY > tCloseX ? true : false;
				tLatestclose = tCloseY > tCloseX ? tCloseY : tCloseX;
				tEarliestOpen = tOpenX < tOpenY ? tOpenX : tOpenY;

				if (tLatestclose < tEarliestOpen)
				{
					//DEBUG_PRINT("Collision");
					return true;
				}
			}
			else
			{
				//DEBUG_PRINT(" NOT A CHANCE ");
				return false;
			}
		}

		bool CollisionHandler::checkAxisCollision(
			float srcProj,
			float relVel,
			float srcCenterinDest,
			float BBdestCenter,
			float destExtent,
			float t_EndFrame,
			float &i_tCLose,
			float &i_tOpen
		) const
		{
			// B's extents + A's proj onto B
			float expanded_B = destExtent + srcProj;
			// for simplification 
			float leftEdge = BBdestCenter - expanded_B;	// left side of B
			float rightEdge = BBdestCenter + expanded_B; // right side of B

			// Check for Edge:  velocity is 0
			if (relVel == 0)
			{
				//  We don't give a sh** about collision if A is not even in the boundary of B
				if (srcCenterinDest < leftEdge || srcCenterinDest > rightEdge )
				{
					return false;
				}
				else // else it's collision for this axis
				{
					return true;
				}
			}
			else
			{
				float distClose = leftEdge - srcCenterinDest;
				float distOpen = rightEdge - srcCenterinDest;

				float TClose = distClose / relVel;
				float TOpen = distOpen / relVel;
				
				// Check for Edge:: if TOpen < tClose
				if (TOpen < TClose)
				{
					std::swap(TOpen, TClose);
				}
				// Check for Edge:: if TClose < tFrameEnd
				if (TClose > t_EndFrame)	// ie Collisions might happen in next frame
				{
					return false;
				}
				// Check for Edge:: if TOpen < 0
				if (TOpen < 0)					// ie collisions happened in some previous frame
				{
					return false;
				}
				else   // Update times
				{
					i_tCLose = TClose;
					i_tOpen = TOpen;
					return true;

				}

			}
		}

		void CollisionHandler::ApplyResponse(SmartPtr<GameObject> A, SmartPtr<GameObject> B, bool IsX) const
		{
			// get stuff
			Vector2 v1 = A->getVelocity();
			Vector2 v2 = B->getVelocity();
			
			float m1 = A->get_Mass();
			float m2 = B->get_Mass();
		
		// Only move if their body is Dynamic
			if (!A->IsDynamic)
				m1 = m2 * 5;
			if (!B->IsDynamic)
				m2 = m1 * 5;

			float mTotal = m1 + m2;

			Vector2 v1n = v1 * ((m1 - m2) / mTotal) + v2 * (2 * m2 / mTotal);
			Vector2 v2n = v2 * ((m2 - m1) / mTotal) + v1 * (2 * m1 / mTotal);

			// Find the Normal
			Math::Matrix_4x4 BtoWorld = B->getBaseToWorld();
			Vector4d BXinworld = BtoWorld * Vector4d(1.0f, 0, 0, 0);
			Vector4d BYinworld = BtoWorld * Vector4d(0, 1.0f, 0, 0);

			Vector2 normal(BYinworld.x(), BYinworld.y());
			if (IsX)
			{
				normal = Vector2(BXinworld.x(), BXinworld.y());
			}

			// refl = ori - 2(ori . norm) * norm
			Vector2 refVel1 = v1n - (normal *(v1n.dot(normal) * 2));

			if (A->IsDynamic)
			{
				A->setVelocity(v1n);
			}
			if (B->IsDynamic)
			{
				B->setVelocity(refVel1);
			}
		}
	}
}