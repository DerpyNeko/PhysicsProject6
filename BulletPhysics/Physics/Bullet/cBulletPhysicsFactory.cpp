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

	iBoxShape* cBulletPhysicsFactory::CreateBoxShape(const glm::vec3& boxHalfExtents)
	{
		return new cBulletBox(boxHalfExtents);
	}

	iCapsuleShape* cBulletPhysicsFactory::CreateCapsuleShape(float radius, float height)
	{
		return new cBulletCapsule(radius, height);
	}

	iConeShape* cBulletPhysicsFactory::CreateConeShape(float radius, float height)
	{
		return new cBulletCone(radius, height);
	}

	iCylinderShape* cBulletPhysicsFactory::CreateCylinderShape(const glm::vec3& boxHalfExtents)
	{
		return new cBulletCylinder(boxHalfExtents);
	}

	i6DoFConstraint* cBulletPhysicsFactory::Create6DoFConstraint(const s6DoFDef& dofDef)
	{
		return new cBullet6DoFConstraint(dofDef);
	}

	iHingeConstraint* cBulletPhysicsFactory::CreateHingeConstraint(const sHingeDef& hingeDef)
	{
		return new cBulletHingeConstraint(hingeDef);
	}

	iSliderConstraint* cBulletPhysicsFactory::CreateSliderConstraint(const sSliderDef& sliderDef)
	{
		return new cBulletSliderConstraint(sliderDef);
	}
}