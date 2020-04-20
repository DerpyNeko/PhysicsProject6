#include "cBulletRigidBody.h"
#include "Bullet/BulletDynamics/Dynamics/btRigidBody.h"
#include "nConvert.h"
#include "BulletShapes.h"

namespace nPhysics
{
	cBulletRigidBody::cBulletRigidBody(const sRigidBodyDef& rbDef, iShape* shape)
		: miShape(shape)
	{
		btCollisionShape* colShape = 0;

		if (shape->GetShapeType() == eShapeType::SHAPE_TYPE_SPHERE)
		{
			cBulletSphere* sphere = dynamic_cast<cBulletSphere*>(shape);
			colShape = new btSphereShape(btScalar(sphere->GetRadius()));
		}
		else if (shape->GetShapeType() == eShapeType::SHAPE_TYPE_PLANE)
		{
			cBulletPlane* plane = dynamic_cast<cBulletPlane*>(shape);
			colShape = new btStaticPlaneShape(btVector3(nConvert::ToBullet(plane->GetPlaneNormal())), btScalar(plane->GetPlaneConstant()));
		}

		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(rbDef.Mass);
		bool isDynamic = (mass != 0.0f);

		btVector3 localInertia(0, 0, 0);

		if (isDynamic)
		{
			colShape->calculateLocalInertia(mass, localInertia);
		}

		startTransform.setOrigin(nConvert::ToBullet(rbDef.Position));
		mMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, mMotionState, colShape, localInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setLinearVelocity(nConvert::ToBullet(rbDef.Velocity));
	}

	cBulletRigidBody::~cBulletRigidBody()
	{
		delete mBody;
		mBody = 0;
		delete mMotionState;
		mMotionState = 0;
	}

	void cBulletRigidBody::ApplyForce(const glm::vec3& force)
	{
		mBody->activate();
		mBody->applyCentralForce(nConvert::ToBullet(force));
	}

	void cBulletRigidBody::GetTransform(glm::mat4& transformOut)
	{
		btTransform transform;
		mMotionState->getWorldTransform(transform);
		nConvert::ToSimple(transform, transformOut);
	}

	glm::vec3 cBulletRigidBody::GetPosition()
	{
		return nConvert::ToSimple(mBody->getWorldTransform().getOrigin());
	}

	//cBulletRigidBody* cCollision::GetKinematicBody() 
	//{
	//	if (mBodyA->GetMass() != 0.0f)
	//		return mBodyA;
	//	else if (mBodyB->GetMass() != 0.0f)
	//		return mBodyB;
	//	else
	//		return NULL;
	//};

	//cBulletRigidBody* cCollision::GetStaticBody()
	//{
	//	if (mBodyA->GetMass() != 0.0f)
	//		return mBodyA;
	//	else if (mBodyB->GetMass() != 0.0f)
	//		return mBodyB;
	//	else
	//		return NULL;
	//};

	//btVector3 cCollision::GetNewPosition() {
	//	btVector3 playerPos;
	//	btVector3 contactPoint;
	//	glm::vec3 orientation;
	//	glm::vec3 oldPosition;

	//	if (mBodyA->GetMass() != 0.0f) {
	//		playerPos = nConvert::ToBullet(mBodyA->GetPosition());
	//		oldPosition = mBodyA->GetPreviousPosition();
	//		contactPoint = this->mContactPtB;
	//	}
	//	else if (mBodyB->GetMass() != 0.0f) {
	//		playerPos = nConvert::ToBullet(B->getPosition());
	//		oldPosition = mBodyB->GetPreviousPosition();
	//		contactPoint = this->mContactPtA;
	//	}
	//	contactPoint.setY(0.0f);

	//	float distance = glm::distance(ToGlm(playerPos), oldPosition);
	//	glm::vec3 dispDir = ToGlm(playerPos) - oldPosition;
	//	dispDir = glm::normalize(dispDir);
	//	btVector3 disp = (distance * 0.95) * ToBullet(dispDir);
	//	playerPos = ToBullet(oldPosition) + disp;

	//	return playerPos;
	//};
}