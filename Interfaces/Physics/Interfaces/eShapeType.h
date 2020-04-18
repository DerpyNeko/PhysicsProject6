#ifndef _eShapeType_HG_
#define _eShapeType_HG_

// Enum of all current shapes in physics
// Matches with the shapes inheriting from iShape

namespace nPhysics
{
	enum class eShapeType
	{
		SHAPE_TYPE_PLANE = 0,
		SHAPE_TYPE_SPHERE = 1,
		SHAPE_TYPE_BOX = 2,
		SHAPE_TYPE_CAPSULE = 3,
		SHAPE_TYPE_TETRAHEDRON = 4
	};
}
#endif
