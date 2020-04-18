#ifndef _Shapes_HG_
#define _Shapes_HG_

// Shape interfaces that inherits from the base iShape interface

#include "iShape.h"
#include <glmMath.h>

namespace nPhysics
{
	// Sphere interface that has a radius
	class iSphereShape : public virtual iShape
	{
	public:
		// Destructor
		virtual ~iSphereShape() {}

		// Returns radius of the sphere
		virtual float GetRadius() = 0;

	protected:
		// Constructor
		iSphereShape() : iShape(eShapeType::SHAPE_TYPE_SPHERE) {}
	private:
		// Constructors not used
		iSphereShape(const iSphereShape& other) = delete;
		iSphereShape& operator=(const iSphereShape& other) = delete;
	};

	// Plane interface that has a normal and constant
	class iPlaneShape : public virtual iShape
	{
	public:
		// Destructor
		virtual ~iPlaneShape() { }
		
		// Returns the constant of the plane
		virtual float GetPlaneConstant() = 0;

		// Returns the normal of the plane
		virtual glm::vec3 GetPlaneNormal() = 0;

	protected:
		iPlaneShape() : iShape(eShapeType::SHAPE_TYPE_PLANE) {}

	private:
		// Constructors not used
		iPlaneShape(const iPlaneShape& other) = delete;
		iPlaneShape& operator=(const iPlaneShape& other) = delete;
	};

	// Box interface
	class iBoxShape : public virtual iShape
	{
	public:
		// Destructor
		virtual ~iBoxShape() { }

		virtual float GetWidth() = 0;
		virtual float GetLength() = 0;
		virtual float GetHeight() = 0;

	protected:
		iBoxShape() : iShape(eShapeType::SHAPE_TYPE_BOX) {}

	private:
		// Constructors not used
		iBoxShape(const iBoxShape& other) = delete;
		iBoxShape& operator=(const iBoxShape& other) = delete;
	};

	// Capsule interface
	class iCapsuleShape : public virtual iShape
	{
	public:
		// Destructor
		virtual ~iCapsuleShape() { }

		virtual int GetUpAxis() = 0;
		virtual float GetRadius() = 0;
		virtual float GetHalfHeight() = 0;

	protected:
		iCapsuleShape() : iShape(eShapeType::SHAPE_TYPE_CAPSULE) {}

	private:
		// Constructors not used
		iCapsuleShape(const iCapsuleShape& other) = delete;
		iCapsuleShape& operator=(const iCapsuleShape& other) = delete;
	};

	// Tetrahedron interface
	class iTetrahedronShape : public virtual iShape
	{
	public:
		// Destructor
		virtual ~iTetrahedronShape() { }

	protected:
		iTetrahedronShape() : iShape(eShapeType::SHAPE_TYPE_TETRAHEDRON) {}

	private:
		// Constructors not used
		iTetrahedronShape(const iTetrahedronShape& other) = delete;
		iTetrahedronShape& operator=(const iTetrahedronShape& other) = delete;
	};


}
#endif
