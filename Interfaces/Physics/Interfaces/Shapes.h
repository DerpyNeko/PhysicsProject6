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
}
#endif
