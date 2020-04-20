#include "cBulletSliderConstraint.h"
#include "nConvert.h"
#include "cBulletRigidBody.h"

namespace nPhysics
{
	cBulletSliderConstraint::cBulletSliderConstraint(const sSliderDef& def) : iConstraint(eConstraintType::SLIDER_CONSTRAINT)
	{
		btBoxShape* sliderShape = new btBoxShape(btVector3(def.Length * 0.5f, def.Height * 0.5f, def.Width * 0.5f));

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(nConvert::ToBullet(def.Position));

		transform.getBasis().setEulerZYX(0.0, 67.5, 0.0);

		btScalar mass(def.Mass);
		btVector3 localInertia(0.0f, 0.0f, 0.0f);
		sliderShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, sliderShape, localInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setUserPointer(this);

		mConstraint = new btSliderConstraint(*mBody, transform, false);

		mConstraint->setUpperLinLimit(btScalar(def.UpperLimit));		
		mConstraint->setLowerLinLimit(btScalar(def.LowerLimit));
	}

	cBulletSliderConstraint::~cBulletSliderConstraint()
	{
		delete mConstraint;
		mConstraint = 0;

		delete mBody->getMotionState();
		delete mBody;
		mBody = 0;
	}

	iRigidBody* cBulletSliderConstraint::GetRigidBody()
	{
		
		cBulletRigidBody* b = new cBulletRigidBody();
		b->SetBulletBody(mBody);
		iRigidBody* rb = b;
		return rb;
	}

	void cBulletSliderConstraint::GetTransform(glm::mat4& transformOut)
	{
		btTransform transform;
		mBody->getMotionState()->getWorldTransform(transform);
		nConvert::ToSimple(transform, transformOut);
	}

	int cBulletSliderConstraint::GetUniqueEntityId()
	{
		return mBody->getUserIndex();
	}

	void cBulletSliderConstraint::SetUniqueEntityId(int id)
	{
		mBody->setUserIndex(id);
	}

	void cBulletSliderConstraint::AddSelfToWorld(btDiscreteDynamicsWorld* world)
	{
		world->addRigidBody(mBody);
		world->addConstraint(mConstraint);
	}

	void cBulletSliderConstraint::RemoveSelfFromWorld(btDiscreteDynamicsWorld* world)
	{
		world->addRigidBody(mBody);
		world->addConstraint(mConstraint);
	}

	//void cBulletSliderConstraint::AddSelfToWorld(btSimpleDynamicsWorld* world)
	//{
	//	world->addRigidBody(mBody);
	//	world->addConstraint(mConstraint);
	//}

	//void cBulletSliderConstraint::RemoveSelfFromWorld(btSimpleDynamicsWorld* world)
	//{
	//	world->addRigidBody(mBody);
	//	world->addConstraint(mConstraint);
	//}
}