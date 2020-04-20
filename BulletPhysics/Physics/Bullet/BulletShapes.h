#ifndef _BulletShapes_HG_
#define _BulletShapes_HG_

// Fleshed out classes of shapes from the interface

#include <Physics/Interfaces/Shapes.h>
#include "Bullet/btBulletDynamicsCommon.h"

namespace nPhysics
{
	// Interface class that contains the bullet information
	class iBulletShape : public virtual iShape
	{
	public:
		// Destructor
		virtual ~iBulletShape() {}

		// Returns the shape of the bullet object
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}

	protected:
		// Constructor
		iBulletShape();

		// Bullet object
		btCollisionShape* mBulletShape;
	};

	// Physics world that will apply physics on the rigid bodies
	class cBulletPhysicsWorld;

	// Sphere class, contains a radius
	class cBulletSphere : public iSphereShape, public iBulletShape
	{
		friend class cSimplePhysicsWorld;

	public:
		// Constructor, takes a radius
		cBulletSphere(float radius);
		
		// Destructor
		virtual ~cBulletSphere();

		// Returns the radius of the sphere
		virtual float GetRadius();
	};

	// Plane class, contains a constant and normal
	class cBulletPlane : public iPlaneShape, public iBulletShape
	{
		friend class cBulletPhysicsWorld;

	public:
		// Constructor, takes in a normal and a constant
		cBulletPlane(const glm::vec3& normal, float constant);
		
		// Destructor
		virtual ~cBulletPlane();

		// Returns the constant of the plane
		virtual float GetPlaneConstant();

		// Returns the normal of the plane
		virtual glm::vec3 GetPlaneNormal();
	};

	// Box class
	class cBulletBox : public iBoxShape, public iBulletShape
	{
		friend class cSimplePhysicsWorld;

	public:
		cBulletBox(const glm::vec3& boxHalfExtents);

		virtual ~cBulletBox();
	};

	// Capsule class
	class cBulletCapsule : public iCapsuleShape, public iBulletShape
	{
		friend class cSimplePhysicsWorld;

	public:
		cBulletCapsule(float radius, float height);

		virtual ~cBulletCapsule();

		virtual int GetUpAxis() override;
		virtual float GetRadius() override;
		virtual float GetHalfHeight() override;
	};

	// Cone class
	class cBulletCone : public iConeShape, public iBulletShape
	{
		friend class cSimplePhysicsWorld;

	public:
		cBulletCone(float radius, float height);

		virtual ~cBulletCone();

		virtual float GetRadius() override;
		virtual float GetHeight() override;
	};

	// Cylinder class
	class cBulletCylinder : public iCylinderShape, public iBulletShape
	{
		friend class cSimplePhysicsWorld;

	public:
		// Constructor, takes a radius
		cBulletCylinder(const glm::vec3& boxHalfExtents);

		// Destructor
		virtual ~cBulletCylinder();

		// Returns the radius of the sphere
		virtual float GetRadius() override;
	};

}
#endif
