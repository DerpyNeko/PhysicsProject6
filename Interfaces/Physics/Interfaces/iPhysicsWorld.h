#ifndef _iPhysicsWorld_HG_
#define _iPhysicsWorld_HG_

// A "world" interface that contains all of the physic objects

#include <glmMath.h>
#include "iRigidBody.h"
#include "iConstraint.h"

namespace nPhysics
{
	// An interface that contains all rigidbodies and handles the physics in the update
	class iPhysicsWorld
	{
	public:
		// Destructor
		virtual ~iPhysicsWorld() {}

		// Handles the movement of physics object while the program is running
		virtual void Update(float dt) = 0;

		// Takes a vector and sets it as the gravity
		virtual void SetGravity(const glm::vec3& gravity) = 0;

		// Adds a rigid body to be affected by physics
		virtual bool AddBody(iRigidBody* body) = 0;

		// Removes a rigid body, will no longer be affect by physics
		virtual bool RemoveBody(iRigidBody* body) = 0;

		// Adds a constraint to be affected by physics
		virtual bool AddConstraint(iConstraint* constraint) = 0;

		// Removes a constraint, will no longer be affect by physics
		virtual bool RemoveConstraint(iConstraint* constraint) = 0;

	protected:
		iPhysicsWorld() {}

	private:
		// Constructors not used
		//iPhysicsWorld() = delete;
		iPhysicsWorld(const iPhysicsWorld& other) = delete;
		iPhysicsWorld& operator=(const iPhysicsWorld& other) = delete;
	};
}
#endif
