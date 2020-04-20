#ifndef _cBulletHingeConstraint_HG_
#define _cBulletHingeConstraint_HG_

#include "iBulletComponent.h"
#include <Physics/Interfaces/Constraints.h>
#include <Physics/Interfaces/iRigidBody.h>

// Hinge class that creates a hinge effect on a bullet object

namespace nPhysics
{
	class cBulletHingeConstraint : public iBulletComponent, public iHingeConstraint
	{
		friend class cPhysicsWorld;
	public:
		// Constructor
		cBulletHingeConstraint(const sHingeDef& def);

		// Destructor
		virtual ~cBulletHingeConstraint();

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
		btHingeConstraint* mConstraint;

		cBulletHingeConstraint() = delete;
		cBulletHingeConstraint(const cBulletHingeConstraint& other) = delete;
		cBulletHingeConstraint& operator =(const cBulletHingeConstraint& other) = delete;
	};
}

#endif
