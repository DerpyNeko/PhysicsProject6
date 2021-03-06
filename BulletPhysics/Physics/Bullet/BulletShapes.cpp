#include "BulletShapes.h"
#include "nConvert.h"

namespace nPhysics
{
	// Constructor for the iBulletShape
	iBulletShape::iBulletShape() : iShape(eShapeType::SHAPE_TYPE_SPHERE)
	{
	}

	// Sphere
	cBulletSphere::cBulletSphere(float radius) : iSphereShape(), iShape(eShapeType::SHAPE_TYPE_SPHERE)
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

	// Box
	cBulletBox::cBulletBox(const glm::vec3& boxHalfExtents) : iBoxShape(), iShape(eShapeType::SHAPE_TYPE_BOX)
	{
		mBulletShape = new btBoxShape(btVector3(nConvert::ToBullet(boxHalfExtents)));
	}

	cBulletBox::~cBulletBox()
	{
		delete mBulletShape;
		mBulletShape = 0;
	}

	// Capsule
	cBulletCapsule::cBulletCapsule(float radius, float height) : iCapsuleShape(), iShape(eShapeType::SHAPE_TYPE_CAPSULE)
	{
		mBulletShape = new btCapsuleShape(btScalar(radius), btScalar(height));
	}

	cBulletCapsule::~cBulletCapsule()
	{
		delete mBulletShape;
		mBulletShape = 0;
	}

	int cBulletCapsule::GetUpAxis()
	{
		return dynamic_cast<btCapsuleShape*>(mBulletShape)->getUpAxis();
	}

	float cBulletCapsule::GetRadius()
	{
		return dynamic_cast<btCapsuleShape*>(mBulletShape)->getRadius();
	}

	float cBulletCapsule::GetHalfHeight()
	{
		return dynamic_cast<btCapsuleShape*>(mBulletShape)->getHalfHeight();
	}

	// Cone
	cBulletCone::cBulletCone(float radius, float height) : iConeShape(), iShape(eShapeType::SHAPE_TYPE_CONE)
	{
		mBulletShape = new btConeShape(radius, height);
	}

	cBulletCone::~cBulletCone()
	{
		delete mBulletShape;
		mBulletShape = 0;
	}

	float cBulletCone::GetRadius()
	{
		return dynamic_cast<btConeShape*>(mBulletShape)->getRadius();
	}

	float cBulletCone::GetHeight()
	{
		return dynamic_cast<btConeShape*>(mBulletShape)->getHeight();
	}

	// Cylinder
	cBulletCylinder::cBulletCylinder(const glm::vec3& boxHalfExtents) : iCylinderShape(), iShape(eShapeType::SHAPE_TYPE_CYLINDER)
	{
		mBulletShape = new btCylinderShape(btVector3(nConvert::ToBullet(boxHalfExtents)));
	}

	cBulletCylinder::~cBulletCylinder()
	{
		delete mBulletShape;
		mBulletShape = 0;
	}

	float cBulletCylinder::GetRadius()
	{
		return dynamic_cast<btCylinderShape*>(mBulletShape)->getRadius();
	}
}
