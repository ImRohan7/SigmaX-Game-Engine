#include "PhysicsComponent.h"
#include "assert.h"
#define TERMINAL_VEL 15.0f
#define ANG_TERMINAL_VEL 10.0f; // in case we add rotation acceleration or we need to clamp the angular vel

namespace
{
	float s_dt;

}
	// Updates position based on Linear and Angular velocity
void PhysicsComponent::updatePhysics(float dt)
{
	s_dt = dt;

	if (!m_IsAPlatform)
	{
		if (m_UseDrag)
			ApplyDrag(dt);

		// acceleration
		if(!m_IsOnGround)
		{
			m_Acceleration = m_gravitationalAcceleration;// +m_assistedAcceleration;
		}
		else
		{
			m_Acceleration.y(0.0);
		}

		// Linear Velocity
		{
			Vector2 newVel = m_Velocity + m_Acceleration * dt;
			Vector2 testVel = newVel;
			testVel.coolDown();

			// clamping to terminal
			if (testVel.x() > TERMINAL_VEL)
			{
				float xv = (newVel.x() < 0) ? -TERMINAL_VEL : TERMINAL_VEL;
				newVel.x(xv);
			}
			if (testVel.y() > TERMINAL_VEL)
			{
				float yv = (newVel.y() < 0) ? -TERMINAL_VEL : TERMINAL_VEL;
				newVel.y(yv);
			}

			//DEBUG_PRINT("VEL: %f", newVelocity.x());

			m_Velocity = (m_Velocity + newVel) / 2;

		}

		// Angular velocity
		{
			m_RotationZ = m_RotationZ + m_AngVelocity * dt;
		}

		// Position
		{
			m_Position = m_Position + m_Velocity * dt;
		}
	}
}

	// adds force  
	void PhysicsComponent::addForce(Vector2 iForce) {

		// a = f / m;
	//	m_assistedAcceleration = (iForce / m_Mass) * s_dt;
		//
		m_Velocity = m_Velocity + iForce;

	}

	// apply drag and updates velocity
	void PhysicsComponent::ApplyDrag(float dt) {

		Vector2 DragToAdd = Vector2::Zero;
		float vel_X = m_Velocity.x();
		float vel_Y = m_Velocity.y();

		// only when there is velocity (simulation is hecky)
		if (!(m_Velocity == Vector2::Zero))
		{
			// Calculate drag to apply based on velocity
			if (vel_X)	// only apply drag if velocity is greater than zero
			{
				DragToAdd = DragToAdd + ((vel_X > 0) ? Vector2(-m_Drag.x(), 0) : Vector2(m_Drag.x(), 0));
			}
			if (vel_Y)
			{
				DragToAdd = DragToAdd + ((vel_Y > 0) ? Vector2(0, -m_Drag.y()) : Vector2(0, m_Drag.y()));
			}
			DragToAdd = DragToAdd / m_Mass;

			m_Velocity = m_Velocity + (DragToAdd * dt);
		}
	}

	PhysicsComponent::~PhysicsComponent()
	{}

