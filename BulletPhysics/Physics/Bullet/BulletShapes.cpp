#include "BulletShapes.h"
#include "nConvert.h"

namespace nPhysics
{
	// Constructor for the iBulletShape
	iBulletShape::iBulletShape() : iShape(eShapeType::SHAPE_TYPE_SPHERE)
	{
	}

	// Sphere
	cBulletSphere::cBulletSphere(float radius) : iSphereShape(),
		iShape(eShapeType::SHAPE_TYPE_SPHERE)
	{
		mBulletShape = new btSphereShape(btScalar(radius));
	}

	cBulletSphere::~cBulletSphere()
	{
		delete mBulletShape;
		mBulletShape = 0;
	}

	float cBulletSphere::GetRadius()
	{
		return dynamic_cast<btSphereShape*>(mBulletShape)->getRadius();
	}

	// Plane
	cBulletPlane::cBulletPlane(const glm::vec3& normal, float constant) : iPlaneShape(),
		iShape(eShapeType::SHAPE_TYPE_PLANE)
	{
		mBulletShape = new btStaticPlaneShape(btVector3(nConvert::ToBullet(normal)), btScalar(constant));
	}

	cBulletPlane::~cBulletPlane()
	{
		delete mBulletShape;
		mBulletShape = 0;
	}

	float cBulletPlane::GetPlaneConstant()
	{
		return dynamic_cast<btStaticPlaneShape*>(mBulletShape)->getPlaneConstant();
	}

	glm::vec3 cBulletPlane::GetPlaneNormal()
	{
		return nConvert::ToSimple(dynamic_cast<btStaticPlaneShape*>(mBulletShape)->getPlaneNormal());
	}
}
