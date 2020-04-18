#ifndef _cBullet6DofConstraint_HG_
#define _cBullet6DofConstraint_HG_

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "../Interfaces/iBulletComponent.h"
#include <Physics/Interfaces/Constraints.h>

// 6DoF class that puts restraints on a bullet object

namespace nPhysics
{
	class cBullet6DoFConstraint : public iBulletComponent, public i6DoFConstraint
	{
		friend class cPhysicsWorld;
	public:
		// Constructor
		cBullet6DoFConstraint(const s6DoFDef& def);

		// Destructor
		virtual ~cBullet6DoFConstraint();

		virtual void GetTransform(glm::mat4& transformOut) override;
		virtual int GetUniqueEntityId() override;
		virtual void SetUniqueEntityId(int id) override;

		virtual void AddSelfToWorld(btDiscreteDynamicsWorld* world) override;
		virtual void RemoveSelfFromWorld(btDiscreteDynamicsWorld* world) override;

	private:
		btRigidBody* mBody;
		btGeneric6DofConstraint* mConstraint;

		cBullet6DoFConstraint() = delete;
		cBullet6DoFConstraint(const cBullet6DoFConstraint& other) = delete;
		cBullet6DoFConstraint& operator =(const cBullet6DoFConstraint& other) = delete;
	};
}

#endif
