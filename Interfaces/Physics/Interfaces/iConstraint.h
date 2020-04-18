#ifndef _iConstraint_HG_
#define _iConstraint_HG_

#include <glmMath.h>
#include "eConstraintType.h"

namespace nPhysics
{
	class iConstraint
	{
	public:
		virtual void GetTransform(glm::mat4& transformOut) = 0;

		virtual int GetUniqueEntityId() = 0;
		virtual void SetUniqueEntityId(int id) = 0;

		// Returns eShapeType of the shape that called it
		inline eConstraintType GetConstraintType() const { return mConstraintType; }

	protected:
		iConstraint(eConstraintType constraintType) : mConstraintType(constraintType) {}

	private:
		eConstraintType mConstraintType;
	};
}
#endif
