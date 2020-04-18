#ifndef _eComponentType_HG_
#define _eComponentType_HG_

// Enum of all current constraints in physics
// Matches with the constraints in bullet

namespace nPhysics
{
	enum class eConstraintType
	{
		HINGE_CONSTRAINT = 0,
		SIXDOF_CONSTRAINT = 1,
		SLIDER_CONSTRAINT = 2
	};
}
#endif
