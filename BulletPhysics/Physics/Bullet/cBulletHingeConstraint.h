#ifndef _cBulletHingeConstraint_HG_
#define _cBulletHingeConstraint_HG_

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "../Interfaces/iBulletComponent.h"
#include  <Physics/Interfaces/Constraints.h>

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

		virtual void GetTransform(glm::mat4& transformOut) override;
		virtual int GetUniqueEntityId() override;
		virtual void SetUniqueEntityId(int id) override;

		virtual void AddSelfToWorld(btDiscreteDynamicsWorld* world) override;
		virtual void RemoveSelfFromWorld(btDiscreteDynamicsWorld* world) override;
		
	private:
		btRigidBody* mBody;
		btHingeConstraint* mConstraint;

		cBulletHingeConstraint() = delete;
		cBulletHingeConstraint(const cBulletHingeConstraint& other) = delete;
		cBulletHingeConstraint& operator =(const cBulletHingeConstraint& other) = delete;
	};
}

#endif
