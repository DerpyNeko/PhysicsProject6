#include "cBulletPhysicsWorld.h"
#include "nConvert.h"
#include <iostream>

namespace nPhysics
{
	cBulletPhysicsWorld::cBulletPhysicsWorld() : iPhysicsWorld()
	{
		mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

		mOverlappingPairCache = new btDbvtBroadphase();

		mSolver = new btSequentialImpulseConstraintSolver();

		mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mOverlappingPairCache, mSolver, mCollisionConfiguration);

		//mDynamicsWorld->setInternalTickCallback(TickCallBack, (void*)&mCollisionShapes);

		mDynamicsWorld->setGravity(btVector3(0.0f, 0.0f, -9.81f));
	}

	cBulletPhysicsWorld::~cBulletPhysicsWorld()
	{
		if (mDynamicsWorld)
		{
			delete mDynamicsWorld;
			mDynamicsWorld = 0;
		}

		if (mSolver)
		{
			delete mSolver;
			mSolver = 0;
		}

		if (mOverlappingPairCache)
		{
			delete mOverlappingPairCache;
			mOverlappingPairCache = 0;
		}

		if (mDispatcher)
		{
			delete mDispatcher;
			mDispatcher = 0;
		}

		if (mCollisionConfiguration)
		{
			delete mCollisionConfiguration;
			mCollisionConfiguration = 0;
		}
	}

	void cBulletPhysicsWorld::SetGravity(const glm::vec3& gravity)
	{
		mDynamicsWorld->setGravity(nConvert::ToBullet(gravity));
	}

	void cBulletPhysicsWorld::Update(float dt)
	{	
		mDynamicsWorld->stepSimulation(dt, 10, 1.f / 60.f);

		//mDynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
		//mDynamicsWorld->stepSimulation(dt, 10, 1.f / 240.0f);
		// TODO: Add collision check 

		//for (int i = 0; i < mDynamicsWorld->getCollisionObjectArray().size(); i++) 
		//{
		//	cCollisionBody* worldObj = (cCollisionBody*)mDynamicsWorld->getCollisionObjectArray()[i]->getUserPointer();

		//	if (worldObj->GetMass() != 0.0f) {
		//		btTransform testTrans = mDynamicsWorld->getCollisionObjectArray()[i]->getWorldTransform();
		//		glm::vec3 pos = ToGlm(testTrans.getOrigin());
		//		glm::vec3 rot = ToGlm(testTrans.getRotation());
		//		break;

		//	}
		//}

		//if (this->collisions.size() > 0) {
		//	for (int counter = 0; counter < collisions.size(); counter++) {
		//		cCollisionBody* kineMatObj = collisions[counter]->getKinematicBody();
		//		cCollisionBody* staticObj = collisions[counter]->getStaticBody();
		//		if (staticObj == NULL) {
		//			staticObj = collisions[counter]->getOtherKinematicBody(kineMatObj);
		//		}
		//		if (kineMatObj->getObjType() == OBJ_PLAYER) {
		//			kineMatObj->setIsColliding(true);
		//			if (staticObj->getObjType() == OBJ_TREASURE || staticObj->getObjType() == OBJ_FIRE) {
		//				std::vector<int> vecIds = kineMatObj->getVecCollidedBodies();
		//				vecIds.push_back(staticObj->getObjectId());
		//				kineMatObj->setVecCollidedBodies(vecIds);
		//			}
		//			if (staticObj->getObjType() == OBJ_ANGRY_AI || staticObj->getObjType() == OBJ_CURIOUS_AI || OBJ_FOLLOWER_AI) {
		//				std::vector<int> vecIds = kineMatObj->getVecCollidedBodies();
		//				vecIds.push_back(staticObj->getObjectId());
		//				kineMatObj->setVecCollidedBodies(vecIds);
		//			}
		//			//this->UpdateBoundingBox(kineMatObj);
		//		}
		//		else if (kineMatObj->getObjType() == OBJ_CAMERA) {
		//			kineMatObj->setIsColliding(true);
		//			std::vector<int> vecIds = kineMatObj->getVecCollidedBodies();
		//			vecIds.push_back(staticObj->getObjectId());
		//			kineMatObj->setVecCollidedBodies(vecIds);
		//			//this->UpdateBoundingBox(kineMatObj);
		//		}
		//	}
		//}
	}

	bool cBulletPhysicsWorld::AddBody(iRigidBody* rigidBody)
	{
		// 1) Null check
		if (rigidBody == 0) return false;

		cBulletRigidBody* rb = dynamic_cast<cBulletRigidBody*>(rigidBody);

		if (!rb) return false; 

		mDynamicsWorld->addRigidBody(rb->GetBulletBody());

		return true;
	}

	bool cBulletPhysicsWorld::RemoveBody(iRigidBody* rigidBody)
	{
		// 1) Null check
		if (!rigidBody) return false;

		// 2) Check if we currently have this rigid body.
		cBulletRigidBody* rb = dynamic_cast<cBulletRigidBody*>(rigidBody);

		if (!rb) return false;

		btRigidBody* bulletBtBody = rb->GetBulletBody();
		mDynamicsWorld->removeRigidBody(bulletBtBody);

		return true;
	}

	bool cBulletPhysicsWorld::AddConstraint(iConstraint* constraint)
	{
		// 1) Null check
		if (constraint == 0) return false;

		if (constraint->GetConstraintType() == eConstraintType::HINGE_CONSTRAINT)
		{
			cBulletHingeConstraint* hinge = dynamic_cast<cBulletHingeConstraint*>(constraint);

			if (!hinge) return false;

			hinge->AddSelfToWorld(mDynamicsWorld);

			return true;
		}
		else if (constraint->GetConstraintType() == eConstraintType::SIXDOF_CONSTRAINT)
		{
			cBullet6DoFConstraint* sixDoF = dynamic_cast<cBullet6DoFConstraint*>(constraint);

			if (!sixDoF) return false;

			sixDoF->AddSelfToWorld(mDynamicsWorld);

			return true;
		}
		else if (constraint->GetConstraintType() == eConstraintType::SLIDER_CONSTRAINT)
		{
			cBulletSliderConstraint* slider = dynamic_cast<cBulletSliderConstraint*>(constraint);

			if (!slider) return false;

			slider->AddSelfToWorld(mDynamicsWorld);

			return true;
		}

		return false;
	}

	bool cBulletPhysicsWorld::RemoveConstraint(iConstraint* constraint)
	{
		// 1) Null check
		if (!constraint) return false;

		if (constraint->GetConstraintType() == eConstraintType::HINGE_CONSTRAINT)
		{
			cBulletHingeConstraint* hinge = dynamic_cast<cBulletHingeConstraint*>(constraint);

			if (!hinge) return false;

			hinge->RemoveSelfFromWorld(mDynamicsWorld);

			return true;
		}
		else if (constraint->GetConstraintType() == eConstraintType::SIXDOF_CONSTRAINT)
		{
			cBullet6DoFConstraint* sixDoF = dynamic_cast<cBullet6DoFConstraint*>(constraint);

			if (!sixDoF) return false;

			sixDoF->RemoveSelfFromWorld(mDynamicsWorld);

			return true;
		}
		else if (constraint->GetConstraintType() == eConstraintType::SLIDER_CONSTRAINT)
		{
			cBulletSliderConstraint* slider = dynamic_cast<cBulletSliderConstraint*>(constraint);

			if (!slider) return false;

			slider->RemoveSelfFromWorld(mDynamicsWorld);

			return true;
		}

		return false;
	}


	//void cBulletPhysicsWorld::TickCallBack(btDynamicsWorld* dynamicsWorld, btScalar timeStep) {
	//	btAlignedObjectArray<cCollision*>& vecCollisions = *reinterpret_cast<btAlignedObjectArray<cCollision*>*>(dynamicsWorld->getWorldUserInfo());
	//	vecCollisions.clear();
	//	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	//	for (int i = 0; i < numManifolds; i++) {
	//		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
	//		cCollision* collision = new cCollision();
	//		const btCollisionObject* objA = contactManifold->getBody0();
	//		collision->mBodyA = (cBulletRigidBody*)(objA->getUserPointer());
	//		const btCollisionObject* objB = contactManifold->getBody1();
	//		collision->mBodyB = (cBulletRigidBody*)(objB->getUserPointer());

	//		if (collision->mBodyA->GetMass() == 0.0f && collision->mBodyB->GetMass() == 0.0f)
	//			continue;


	//		int numContacts = contactManifold->getNumContacts();
	//		for (int j = 0; j < numContacts; j++)
	//		{
	//			btManifoldPoint& pt = contactManifold->getContactPoint(j);
	//			if (pt.getDistance() < 0.f)
	//			{
	//				collision->contactPtA = pt.getPositionWorldOnA();
	//				collision->contactPtB = pt.getPositionWorldOnB();
	//				collision->normalOnB = pt.m_normalWorldOnB;
	//			}
	//		}

	//		if (numContacts > 0)
	//			vecCollisions.push_back(collision);
	//	}
	//}
}