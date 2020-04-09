#ifndef _iRigidBody_HG_
#define _iRigidBody_HG_

// Rigid body that moves from physics

#include <glmMath.h>

namespace nPhysics
{
	// Definition of what information the rigid body will have
	struct sRigidBodyDef
	{
		// Constructor
		sRigidBodyDef() : Position(0.0f, 0.0f, 0.0f), Velocity(0.0f, 0.0f, 0.0f), Mass(1.0f) {}

		// Position of the rigid body
		glm::vec3 Position;
		
		// Linear velocity of the rigid body
		glm::vec3 Velocity;

		// Mass
		// Must be set to a non-negative value.
		// 0.f will result in a static rigid body.
		// A positive value will result in a dynamic rigid body.
		float Mass;
	};

	// Rigid body that is affect by force and has a transform
	class iRigidBody
	{
	public:
		// Destructor
		virtual ~iRigidBody() {}

		// Applies force to the rigid body
		virtual void ApplyForce(const glm::vec3& force) = 0;

		// Returns the position and rotation of the rigid body
		virtual void GetTransform(glm::mat4& transformOut) = 0;

		// Returns the position of the rigid body
		virtual glm::vec3 GetPosition() = 0;

	protected:
		iRigidBody() {}

	private:
		// Constructors not used
		//iRigidBody() = delete;
		iRigidBody(const iRigidBody& other) = delete;
		iRigidBody& operator=(const iRigidBody& other) = delete;
	};
}
#endif
