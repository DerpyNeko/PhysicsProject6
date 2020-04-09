#ifndef _iShape_HG_
#define _iShape_HG_

// Base interface for actual shapes

#include "eShapeType.h"

namespace nPhysics
{
	// Base interface for shapes, has eShapeType to specify what shape it is
	class iShape
	{
	public:
		// Destructor
		virtual ~iShape() {}

		// Returns eShapeType of the shape that called it
		inline eShapeType GetShapeType() const { return mShapeType; }

	protected:
		// Constructor
		// To be called by subclasses and passed the corresponding shape of the subclass
		iShape(eShapeType shapeType) : mShapeType(shapeType) {}

	private:
		eShapeType mShapeType;

		// Constructors to not be used
		iShape() = delete;
		iShape(const iShape& other) = delete;
		iShape& operator=(const iShape& other) = delete;
	};
}
#endif
