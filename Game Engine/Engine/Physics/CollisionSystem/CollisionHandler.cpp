#include "CollisionHandler.h"
#include "..//..//Console/ConsolePrint.h"
#include "../..//Math/Matrix/Matrix_4x4.h"
#include "../..//Delegates/Delegates.h"

namespace Engine {
	namespace Physics {
		// function declaration
	

		std::vector<std::pair<SmartPtr<GameObject>, SmartPtr<GameObject>>> _groundPair;

		typedef Delegate<SmartPtr<GameObject>> CollisionTriggerEvent;
		
		void CollisionHandler::HandleCollisions(std::vector<SmartPtr<GameObject>> i_Collidables, float t_EndFrame)
		{
			const size_t count = i_Collidables.size();
			bool tmp = false;
			
			verifyGroundStatus(t_EndFrame, tmp);
			
			for (size_t i = 0; i < (count - 1); i++)
			{
				for (size_t j = i + 1; j < count; j++)
				{
					bool IsX = false;
					if (IsCollision(i_Collidables[i], i_Collidables[j], t_EndFrame, IsX))
					{
						// Do something here
						GameObject* A = i_Collidables[i].getObj();
						GameObject* B = i_Collidables[j].getObj();

						// invoke collision triggers
						{
							// invoke oncollision method
							CollisionTriggerEvent _x1 = CollisionTriggerEvent::Create
								<GameObject, & GameObject::OnCollision>(A);

							CollisionTriggerEvent _x2 = CollisionTriggerEvent::Create
								<GameObject, & GameObject::OnCollision>(B);

							// fire
							_x1.ExecuteIfBound(i_Collidables[j]);
							_x2.ExecuteIfBound(i_Collidables[i]);

						}
						
						if (A->m_Physics->m_IsAPlatform || B->m_Physics->m_IsAPlatform)
						{
							if (A->m_Physics->m_IsAPlatform && B->m_Physics->m_IsAPlatform)
							{
								// do nothing they are static
							}
							else if (A->m_Physics->m_IsAPlatform) // A platform
							{
								handleGroundCollision(i_Collidables[j], i_Collidables[i]);
							}
							else	// B Platform
							{
								handleGroundCollision(i_Collidables[i], i_Collidables[j]);
							}
						}
						else 
						{
							A->m_Physics->m_IsOnGround = false;
							B->m_Physics->m_IsOnGround = false;
							// apply response
							ApplyResponse(i_Collidables[i], i_Collidables[j], IsX);
						}
					}
				}
			}
		}

		void CollisionHandler::handleGroundCollision(SmartPtr<GameObject> obj, SmartPtr<GameObject> _pf)
		{
			// set the IsGround value
			
			// insert to _groundpair	// 0: Object 1: Platform
			if (!obj->m_Physics->m_IsOnGround)
			{
				obj->m_Physics->m_IsOnGround = true;	
				_groundPair.push_back(std::make_pair(obj, _pf));
			}

			// handle velocity
			Vector2 vel = obj->m_Physics->getVelocity();
			// avoid ground collision
			if(vel.y()<0)
				obj->m_Physics->setVelocity(Vector2(vel.x(), 0.0f));

		}


		void CollisionHandler::verifyGroundStatus(float t_EndFrame, bool IsX)
		{
			std::vector<int> toErase;

			for(int i=0; i<_groundPair.size(); i++)
			{
				SmartPtr<GameObject> obj = _groundPair.at(i).first;
				SmartPtr<GameObject> pf = _groundPair.at(i).second;
				
				if (!IsCollision(obj, pf, t_EndFrame, IsX))
				{
					obj->m_Physics->m_IsOnGround = false;
					toErase.push_back(i);
				}
			}

			// erase
			int mod = 0;
			for (auto x : toErase)
			{
				_groundPair.erase(_groundPair.begin()+ (x-mod));
				mod++;
			}

			toErase.clear();
		}

		bool CollisionHandler::IsCollision(SmartPtr<GameObject> i_A, SmartPtr<GameObject> i_B, float t_EndFrame, bool &IsX) const
		{
			SmartPtr<GameObject> A = i_A;
			SmartPtr<GameObject> B = i_B;
			Vector2 pos1 = A->m_Physics->getPosition();
			Vector2 pos2 = B->m_Physics->getPosition();

			// getting the local dimensions
			AABB ObjA = A->getAABB();
			AABB ObjB = B->getAABB();

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
			Vector2 velA = A->m_Physics->getVelocity();
			Vector2 velB = B->m_Physics->getVelocity();
			Vector2 velARelToB = velA - velB;
			velARelToB.RoundTo2();
			Vector4d vel(Vector3d(velARelToB.x(), velARelToB.y(), 0.0f), 0.0f);
			Vector4d velAInB = WorldToB * vel;
		
	// X
			float tCloseX = 0;
			float tOpenX = 100;
			bool checkX = checkAxisCollision(AprojOnBX, velAInB.x(), ABBCenterInB.x(), ObjB.m_Center.x(), ObjB.m_Extents.x(), t_EndFrame, tCloseX, tOpenX);
	// Y
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

			// Check for Edge::  velocity is 0
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
					// In this case Obj B is approching obj A in the opposite direction
					// from what we assumed (Normal situation A--> <--B)
					// ie. Right to Left (B--> <--A)
					std::swap(TOpen, TClose); // so we just swap to adjust
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
			Vector2 v1 = A->m_Physics->getVelocity();
			Vector2 v2 = B->m_Physics->getVelocity();
			
			float m1 = A->m_Physics->getMass();
			float m2 = B->m_Physics->getMass();
		
		// Only move if their body is Dynamic
			if (!A->m_Physics->m_IsDynamic)
				m1 = m2 * 5;
			if (!B->m_Physics->m_IsDynamic)
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
			Vector2 refVel2 = v2n - (normal *(v2n.dot(normal) * 2));
			Vector2 refVel1 = v1n - (normal * (v1n.dot(normal) * 2));

			// update if it's dynamica
			if (A->m_Physics->m_IsDynamic)
			{
				if (B->m_Physics->m_IsAPlatform)
				{
					Vector2 deduct_gravity(v1n.x(),0); // y zero
					A->m_Physics->DisableGravity();
					A->m_Physics->setVelocity(deduct_gravity);
				}
				else
				{
					A->m_Physics->setVelocity(v1n);
				}
			}
			if (B->m_Physics->m_IsDynamic)
			{
				if (A->m_Physics->m_IsAPlatform)
				{
					Vector2 deduct_gravity(refVel2.x(), 0); // y zero
					A->m_Physics->DisableGravity();
					B->m_Physics->setVelocity(deduct_gravity);
				}
				else
				{
					B->m_Physics->setVelocity(refVel2);
				}
			}
		}
	}
}