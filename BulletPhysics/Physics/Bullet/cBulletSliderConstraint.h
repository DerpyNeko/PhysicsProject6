#ifndef _cBulletSliderConstraint_HG_
#define _cBulletSliderConstraint_HG_

#include "iBulletComponent.h"
#include <Physics/Interfaces/Constraints.h>
#include <Physics/Interfaces/iRigidBody.h>

// Slider class that puts restraints on a bullet object

namespace nPhysics
{
	class cBulletSliderConstraint : public iBulletComponent, public iSliderConstraint
	{
		friend class cPhysicsWorld;
	public:
		// Constructor
		cBulletSliderConstraint(const sSliderDef& def);

		// Destructor
		virtual ~cBulletSliderConstraint();

		virtual iRigidBody* GetRigidBody() override;
		virtual void GetTransform(glm::mat4& transformOut) override;
		virtual int GetUniqueEntityId() override;
		virtual void SetUniqueEntityId(int id) override;

		virtual void AddSelfToWorld(btDiscreteDynamicsWorld* world) override;
		virtual void RemoveSelfFromWorld(btDiscreteDynamicsWorld* world) override;

		//virtual void AddSelfToWorld(btSimpleDynamicsWorld* world);
		//virtual void RemoveSelfFromWorld(btSimpleDynamicsWorld* world);


	private:
		btRigidBody* mBody;
		btSliderConstraint* mConstraint;

		cBulletSliderConstraint() = delete;
		cBulletSliderConstraint(const cBulletSliderConstraint& other) = delete;
		cBulletSliderConstraint& operator =(const cBulletSliderConstraint& other) = delete;
	};
}

#endif
