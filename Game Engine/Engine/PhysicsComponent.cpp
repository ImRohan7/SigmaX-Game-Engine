#include "PhysicsComponent.h"
#include "assert.h"
#define TERMINAL_VEL 25.0f


// Constrictor
void PhysicsComponent::updatePhysics(float dt)
{
	SmartPtr<GameObject> _object = m_GameObject.AquireOwnership();

	if (_object->ToUseDrag)
		ApplyDrag(_object, dt);

	// Last but not the least
	updatePosition(_object,dt);
}

// updates position based on velocity
void PhysicsComponent::updatePosition(SmartPtr<GameObject> _Object,const float dt)
{
	// pos3 = pos2 + (v2 + v3)/2 * dt;
	Vector2 newPos = _Object->GetPosition() + _Object->getVelocity() * dt;
	_Object->SetPosition(newPos);
}

// adds force and updates velocity	// Will be used while OnButtonPress to move object 
void PhysicsComponent::addForce(Vector2 iForce, float dt) {

	SmartPtr<GameObject> _tempObject = m_GameObject.AquireOwnership();
	Vector2 _prevVelocity = _tempObject->getVelocity();
	
	// a = f / m;
	Vector2 Acceleration = iForce / m_Mass;
	// v = v0 + at;
	Vector2 newVelocity = _tempObject->getVelocity() + (Acceleration * dt);
	Vector2 TestVel = newVelocity;
	// Terminal Velocity limit
	TestVel.coolDown();	

	if (TestVel.x() > TERMINAL_VEL)
	{
		float xv = (newVelocity.x() < 0) ? -TERMINAL_VEL : TERMINAL_VEL;
		newVelocity.x(xv);
	}
	if (TestVel.y() > TERMINAL_VEL)
	{
		float yv = (newVelocity.y() < 0) ? -TERMINAL_VEL : TERMINAL_VEL;
		newVelocity.y(yv);
	}
	DEBUG_PRINT("VEL: %f", newVelocity.x());
	
	_tempObject->setVelocity((_prevVelocity + newVelocity)/2);
	IsApplyingForce = true;
}

// apply drag and updates velocity
void PhysicsComponent::ApplyDrag(SmartPtr<GameObject> _Object, float dt) {
	
	Vector2 DragToAdd = Vector2::Zero;
	float vel_X = _Object->getVelocity().x();
	float vel_Y = _Object->getVelocity().y();

	if (!(_Object->getVelocity() == Vector2::Zero))
	{
		// Calculate drag to apply based on velocity
		if (vel_X)	// only apply drag if velocity is greater than zero
		{
			DragToAdd = DragToAdd + ((vel_X > 0) ? Vector2(-m_Drag.x(),0) : Vector2(m_Drag.x(),0));
		}
		if (vel_Y)
		{
			DragToAdd = DragToAdd + ((vel_Y > 0) ? Vector2(0,-m_Drag.y()) : Vector2(0,m_Drag.x()));
		}
		DragToAdd = DragToAdd / m_Mass;

		Vector2 newVelocity = _Object->getVelocity() + (DragToAdd * dt);
		_Object->setVelocity(newVelocity);
	}
}

PhysicsComponent::~PhysicsComponent()
{}
