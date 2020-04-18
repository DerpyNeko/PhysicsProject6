#include "cBulletHingeConstraint.h"
#include "nConvert.h"

namespace nPhysics
{
	cBulletHingeConstraint::cBulletHingeConstraint(const sHingeDef& def) : iConstraint(eConstraintType::HINGE_CONSTRAINT)
	{
		btBoxShape* hingeShape = new btBoxShape(btVector3(def.Width * 0.5f, def.Height * 0.5f, def.Thickness * 0.5f));

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(nConvert::ToBullet(def.Position));

		btScalar mass(def.Mass);
		btVector3 localInertia(0.0f, 0.0f, 0.0f);
		hingeShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, hingeShape, localInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setUserPointer(this);

		mConstraint = new btHingeConstraint(*mBody, btVector3(nConvert::ToBullet(def.Pivot)), btVector3(nConvert::ToBullet(def.Axis)));
	}

	cBulletHingeConstraint::~cBulletHingeConstraint()
	{
		delete mConstraint;
		mConstraint = 0;

		delete mBody->getMotionState();
		delete mBody;
		mBody = 0;
	}

	void cBulletHingeConstraint::GetTransform(glm::mat4& transformOut)
	{
		btTransform transform;
		mBody->getMotionState()->getWorldTransform(transform);
		nConvert::ToSimple(transform, transformOut);
	}

	int cBulletHingeConstraint::GetUniqueEntityId()
	{
		return mBody->getUserIndex();
	}

	void cBulletHingeConstraint::SetUniqueEntityId(int id)
	{
		mBody->setUserIndex(id);
	}

	void cBulletHingeConstraint::AddSelfToWorld(btDiscreteDynamicsWorld* world)
	{
		world->addRigidBody(mBody);
		world->addConstraint(mConstraint);
	}

	void cBulletHingeConstraint::RemoveSelfFromWorld(btDiscreteDynamicsWorld* world)
	{
		world->addRigidBody(mBody);
		world->addConstraint(mConstraint);
	}
}