#ifndef _cBulletRigidBody_HG_
#define _cBulletRigidBody_HG_

// Rigid body created from the iRigidBody interface for simple physics

#include <Physics/Interfaces/iShape.h>
#include <Physics/Interfaces/iRigidBody.h>
#include "Bullet/btBulletCollisionCommon.h"

namespace nPhysics
{
	class cBulletPhysicsWorld;
	// cRigidBody
	//
	// Contains all values required for a rigid body simulation.
	// 
	// Shapes may be shared between rigid bodies.
	// Does not own the iShape* used to create it.
	// Will not delete the iShape* it contains when it is deleted.
	class cBulletRigidBody : public iRigidBody
	{
		// cWorld will be operating on cRigidBody values quite a bit
		// We will trust it to do everything correctly.
		friend class cBulletPhysicsWorld;
	public:
		// Constructor
		// All internal values are initialized according to the sRigidBodyDef
		// A valid iShape* is expected.
		cBulletRigidBody(const sRigidBodyDef& def, iShape* shape);

		// Destructor
		// Will not delete the contained iShape.
		~cBulletRigidBody();

		// GetTransform
		// Retrieve a rendering-friendly form of position + rotation
		void GetTransform(glm::mat4& transformOut);

		// ApplyForce
		// Apply an external force to this rigid body.
		// The force is applied center-mass, affecting the acceleration.
		void ApplyForce(const glm::vec3& force);

		// Returns the rigidbody of the bullet
		inline btRigidBody* GetBulletBody()
		{
			return mBody;
		}

		// GetPosition
		// Get the position of the rigid body
		glm::vec3 GetPosition();

		// TODO:
		// ApplyImpulse
		// Apply an impulse to the center-mass of this rigid body.
		// ApplyImpulse(const glm::vec3& impulse);

		// GetShape
		// Get this rigid body's shape.
		// Each rigid body must be created with a shape.
		inline iShape* GetShape() { return miShape; }

		// GetShapeType
		// Get the type of shape of this rigid body's shape.
		// Equivalent to GetShape()->GetShapeType()
		inline eShapeType GetShapeType() { return miShape->GetShapeType(); }

	private:
		// Motion state for the rigid body
		btDefaultMotionState* mMotionState;

		// The rigid body
		btRigidBody* mBody;

		// The shape in bullet
		btCollisionShape* mShape;

		// The shape in our code
		iShape* miShape;

		// Constructors not to be used.
		cBulletRigidBody() = delete;
		cBulletRigidBody(const cBulletRigidBody& other) = delete;
		cBulletRigidBody& operator=(const cBulletRigidBody& other) = delete;
	};
}
#endif
