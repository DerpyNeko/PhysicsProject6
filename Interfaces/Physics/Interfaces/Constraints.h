#ifndef _Constraints_HG_
#define _Constraints_HG_

// Constraint interfaces that inherits from the base iConstraint interface

#include <glmMath.h>
#include "iConstraint.h"

namespace nPhysics
{
	// Definition of what information the hinge will have
	struct sHingeDef
	{
		glm::vec3 Position;
		float Width;
		float Height;
		float Thickness;
		float Mass;
		glm::vec3 Pivot;
		glm::vec3 Axis;
	};

	// Hinge constraint that is affect by force and has a transform
	class iHingeConstraint : public virtual iConstraint
	{
	public:
		// Destructor
		virtual ~iHingeConstraint() {}
	protected:
		iHingeConstraint() : iConstraint(eConstraintType::HINGE_CONSTRAINT) {}
	private:
		iHingeConstraint(const iHingeConstraint& other) = delete;
		iHingeConstraint& operator=(const iHingeConstraint& other) = delete;
	};

	// Definition of what information the 6DoF will have
	struct s6DoFDef
	{
		glm::vec3 Position;
		glm::vec3 UpperLimit;
		glm::vec3 LowerLimit;
		float Radius;
		float Mass;
	};

	// 6DoF constraint that is affect by force and has a transform
	class i6DoFConstraint : public virtual iConstraint
	{
	public:
		// Destructor
		virtual ~i6DoFConstraint() {}
	protected:
		i6DoFConstraint() : iConstraint(eConstraintType::SIXDOF_CONSTRAINT) {}
	private:
		i6DoFConstraint(const i6DoFConstraint& other) = delete;
		i6DoFConstraint& operator=(const i6DoFConstraint& other) = delete;
	};

	// Definition of what information the Slider will have
	struct sSliderDef
	{
		glm::vec3 Position;
		float Width;
		float Height;
		float Thickness;
		float Mass;
		glm::vec3 UpperLimit;
		glm::vec3 LowerLimit;
	};

	// Slider constraint that is affect by force and has a transform
	class iSliderConstraint : public virtual iConstraint
	{
	public:
		// Destructor
		virtual ~iSliderConstraint() {}
	protected:
		iSliderConstraint() : iConstraint(eConstraintType::SIXDOF_CONSTRAINT) {}
	private:
		iSliderConstraint(const iSliderConstraint& other) = delete;
		iSliderConstraint& operator=(const iSliderConstraint& other) = delete;
	};
}
#endif
