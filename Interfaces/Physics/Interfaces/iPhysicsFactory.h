#ifndef _iPhysicsFactory_HG_
#define _iPhysicsFactory_HG_

// Physics Factory that creates all of physics related objects

#include "Shapes.h"
#include "iRigidBody.h"
#include "iPhysicsWorld.h"

namespace nPhysics
{
	// Factory that creates world, rigid bodies and shapes
	class iPhysicsFactory
	{
	public:
		// Destructor
		virtual ~iPhysicsFactory() {}

		// Creates a physics world 
		virtual iPhysicsWorld* CreatePhysicsWorld() = 0;

		// Creates a rigid body with the definitions and shape 
		virtual iRigidBody* CreateRigidBody(const sRigidBodyDef& rbDef, iShape* shape) = 0;
		
		// Creates a sphere object to be added to a rigid body
		virtual iSphereShape* CreateSphereShape(float sphereRadius) = 0;

		// Creates a plane object to be added to a rigid body
		virtual iPlaneShape* CreatePlaneShape(const glm::vec3& planeNormal, float planeConstant) = 0;
	protected:
		iPhysicsFactory() {}
	private:
		// Constructors not used
		//iPhysicsFactory() = delete;
		iPhysicsFactory(const iPhysicsFactory& other) = delete;
		iPhysicsFactory& operator=(const iPhysicsFactory& other) = delete;
	};
}
#endif
