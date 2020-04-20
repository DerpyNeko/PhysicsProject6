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
		sHingeDef() : Position(0.0f, 0.0f, 0.0f), Length(0.0f), Height(0.0f), Width(0.0f), Mass(0.0f), Pivot(0.0f, 0.0f, 0.0f), Axis(0.0f, 0.0f, 0.0f) {}

		glm::vec3 Position;
		float Length;
		float Height;
		float Width;
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
		s6DoFDef() : Position(0.0f, 0.0f, 0.0f), Mass(0.0f), Radius(0.0f), UpperLimit(0.0f, 0.0f, 0.0f), LowerLimit(0.0f, 0.0f, 0.0f) {}

		glm::vec3 Position;
		float Mass;
		float Radius;
		glm::vec3 UpperLimit;
		glm::vec3 LowerLimit;
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
		sSliderDef() : Position(0.0f, 0.0f, 0.0f), Length(0.0f), Height(0.0f), Width(0.0f), Mass(0.0f), UpperLimit(0.0f), LowerLimit(0.0f) {}

		glm::vec3 Position;
		float Length;
		float Height;
		float Width;
		float Mass;
		float UpperLimit;
		float LowerLimit;
	};

	// Slider constraint that is affect by force and has a transform
	class iSliderConstraint : public virtual iConstraint
	{
	public:
		// Destructor
		virtual ~iSliderConstraint() {}
	protected:
		iSliderConstraint() : iConstraint(eConstraintType::SLIDER_CONSTRAINT) {}
	private:
		iSliderConstraint(const iSliderConstraint& other) = delete;
		iSliderConstraint& operator=(const iSliderConstraint& other) = delete;
	};
}
#endif
