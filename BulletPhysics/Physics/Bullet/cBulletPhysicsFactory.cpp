#include "cBulletPhysicsFactory.h"
#include "cBulletPhysicsWorld.h"
#include "cBulletRigidBody.h"
#include "BulletShapes.h"

namespace nPhysics
{
	cBulletPhysicsFactory::cBulletPhysicsFactory()
	{
	}

	cBulletPhysicsFactory::~cBulletPhysicsFactory()
	{
	}

	iPhysicsWorld* cBulletPhysicsFactory::CreatePhysicsWorld()
	{
		return new cBulletPhysicsWorld();
	}

	iRigidBody* cBulletPhysicsFactory::CreateRigidBody(const sRigidBodyDef& rbDef, iShape* shape)
	{
		return new cBulletRigidBody(rbDef, shape);
	}

	iSphereShape* cBulletPhysicsFactory::CreateSphereShape(float sphereRadius)
	{
		return new cBulletSphere(sphereRadius);
	}

	iPlaneShape* cBulletPhysicsFactory::CreatePlaneShape(const glm::vec3& planeNormal, float planeConstant)
	{
		return new cBulletPlane(planeNormal, planeConstant);
	}
}