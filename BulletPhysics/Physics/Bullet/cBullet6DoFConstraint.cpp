#include "cBullet6DoFConstraint.h"
#include "nConvert.h"

namespace nPhysics
{
	cBullet6DoFConstraint::cBullet6DoFConstraint(const s6DoFDef& def) : iConstraint(eConstraintType::SIXDOF_CONSTRAINT)
	{
		btCollisionShape* dofShape = new btSphereShape(def.Radius);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(nConvert::ToBullet(def.Position));

		btScalar mass(def.Mass);
		btVector3 localInertia(0.0f, 0.0f, 0.0f);
		dofShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, dofShape, localInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setUserPointer(this);

		mConstraint = new btGeneric6DofConstraint(*mBody, transform, false);
		mConstraint->setLinearLowerLimit(nConvert::ToBullet(def.LowerLimit));
		mConstraint->setLinearUpperLimit(nConvert::ToBullet(def.UpperLimit));
	}

	cBullet6DoFConstraint::~cBullet6DoFConstraint()
	{
		delete mConstraint;
		mConstraint = 0;

		delete mBody->getMotionState();
		delete mBody;
		mBody = 0;
	}

	void cBullet6DoFConstraint::GetTransform(glm::mat4& transformOut)
	{
		btTransform transform;
		mBody->getMotionState()->getWorldTransform(transform);
		nConvert::ToSimple(transform, transformOut);
	}

	int cBullet6DoFConstraint::GetUniqueEntityId()
	{
		return mBody->getUserIndex();
	}

	void cBullet6DoFConstraint::SetUniqueEntityId(int id)
	{
		mBody->setUserIndex(id);
	}

	void cBullet6DoFConstraint::AddSelfToWorld(btDiscreteDynamicsWorld* world)
	{
		world->addRigidBody(mBody);
		world->addConstraint(mConstraint);
	}

	void cBullet6DoFConstraint::RemoveSelfFromWorld(btDiscreteDynamicsWorld* world)
	{
		world->addRigidBody(mBody);
		world->addConstraint(mConstraint);
	}
}