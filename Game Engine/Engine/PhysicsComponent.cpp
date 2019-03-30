#include "PhysicsComponent.h"
#include "assert.h"

// Constrictor
void PhysicsComponent::updatePhysics(float dt)
{

	if (IsApplyingForce)
	{
		// pos3 = pos2 + (v2 + v3)/2 * dt;
		SmartPtr<GameObject> _tempObject = m_GameObject.AquireOwnership();

		Point2D newPos = _tempObject->GetPosition() + _tempObject->velocity() * dt;
		//d
		_tempObject->SetPosition(newPos);
	}
	// Apply natural drag to stop
	//else
	{
		
	}
	/*
	f = f - m * 9.8 - drag;
	f = appliedF - m * g;	
	*/
	
}

void PhysicsComponent::addForce(Point2D iForce, float dt) {

	SmartPtr<GameObject> _tempObject = m_GameObject.AquireOwnership();
	Point2D _prevVelocity = _tempObject->velocity();
	
	// a = f / m;
	Point2D Acceleration = iForce / m_Mass;
	// v = v0 + at;
	Point2D newVelocity = _tempObject->velocity() + (Acceleration * dt);

	
	// TODO: Make sure note more than terminal velocity
	// V = (v0 + v1) / 2

	_tempObject->setVelocity((_prevVelocity + newVelocity)/2);
	IsApplyingForce = true;
}

void PhysicsComponent::removeForce(float dt) {
	
	SmartPtr<GameObject> _tempObject = m_GameObject.AquireOwnership();
	// Add Natural Drag
	Point2D DragToAdd = Point2D::Zero;
	float vel_X = _tempObject->velocity().x();
	float vel_Y = _tempObject->velocity().y();

	if (!(_tempObject->velocity() == Point2D::Zero))
	{
		// Calculate drag to apply based on velocity
		
		if (vel_X)
		{
			DragToAdd = DragToAdd + ((vel_X > 0) ? Point2D(-m_Drag.x(),0) : Point2D(m_Drag.x(),0));
		}
		if (vel_Y)
		{
			DragToAdd = DragToAdd + ((vel_Y > 0) ? Point2D(0,-m_Drag.y()) : Point2D(0,m_Drag.x()));
		}
		DragToAdd = DragToAdd / m_Mass;

		Point2D newVelocity = _tempObject->velocity() + (DragToAdd * dt);
		
		_tempObject->setVelocity(newVelocity);
	}
}

PhysicsComponent::~PhysicsComponent()
{
	//assert(m_GameObject);
	//delete m_GameObject;
}
