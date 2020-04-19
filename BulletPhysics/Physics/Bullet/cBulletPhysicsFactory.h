#ifndef _cBulletPhysicsFactory_HG_
#define _cBulletPhysicsFactory_HG_

#include <Physics/Interfaces/iPhysicsFactory.h>

// Factory class that inherits from the iPhysicsFactory

namespace nPhysics
{
	class cBulletPhysicsFactory : public iPhysicsFactory
	{
	public:
		// Constructor
		cBulletPhysicsFactory();

		// Destructor
		virtual ~cBulletPhysicsFactory();

		// Creates the physics world
		virtual iPhysicsWorld* CreatePhysicsWorld();
		
		// Creates a rigid body based on definition and shape
		virtual iRigidBody* CreateRigidBody(const sRigidBodyDef& rbDef, iShape* shape);

		// Creates a sphere shape based on the radius
		virtual iSphereShape* CreateSphereShape(float sphereRadius);

		// Creates a plane shape based on the normal and constant
		virtual iPlaneShape* CreatePlaneShape(const glm::vec3& planeNormal, float planeConstant);

		// box
		virtual iBoxShape* CreateBoxShape(const glm::vec3& boxHalfExtents);

		// capsule
		virtual iCapsuleShape* CreateCapsuleShape(float radius, float height);

		// tetrahedron
		virtual iTetrahedronShape* CreateTetrahedronShape();

		// cylinder
		virtual iCylinderShape* CreateCylinderShape(const glm::vec3& boxHalfExtents);
	};
}

#endif
