#include "cBulletPhysicsWorld.h"
#include "nConvert.h"

namespace nPhysics
{
	cBulletPhysicsWorld::cBulletPhysicsWorld() : iPhysicsWorld()
	{
		mCollisionConfiguration = new btDefaultCollisionConfiguration();

		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

		mOverlappingPairCache = new btDbvtBroadphase();

		mSolver = new btSequentialImpulseConstraintSolver;

		mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mOverlappingPairCache, mSolver, mCollisionConfiguration);

		//mDynamicsWorld->setGravity(btVector3(0, -9.81, 0));
		mDynamicsWorld->setGravity(btVector3(0, 0, -9.81));
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
		mDynamicsWorld->stepSimulation(dt, 0, 1.f / 60.f);
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

	//void cBulletPhysicsWorld::IntegrateRigidBody(cBulletRigidBody* body, float dt)
	//{
	//	// 1) Static bodies are not to be integrated!
	//	if (!body) return;
	//	if (body->mMass == 0.0f) return;

	//	// 2) Update the body's previous position.
	//	body->mPreviousPosition = body->mPosition;

	//	// 3) Do some integrating!
	//	mIntegrator.RK4(body->mPosition, body->mVelocity, body->mAcceleration, mGravity, mDt);

	//	// 4) Apply some linear damping
	//	// TODO

	//}

	//bool cBulletPhysicsWorld::Collide(cBulletRigidBody* bodyA, cBulletRigidBody* bodyB)
	//{
	//	cBulletRigidBody* rbA = dynamic_cast<cBulletRigidBody*>(bodyA);
	//	cBulletRigidBody* rbB = dynamic_cast<cBulletRigidBody*>(bodyB);
	//	if (!rbA || !rbB) return false;

	//	// 1) Based on shape type, determine which specific collision handling method to use.
	//	// 2) Cast up the shapes, call the methods, return the result.

	//	eShapeType shapeA = rbA->mShape->GetShapeType();
	//	eShapeType shapeB = rbB->mShape->GetShapeType();

	//	if (shapeA == eShapeType::SHAPE_TYPE_SPHERE)
	//	{
	//		if (shapeB == eShapeType::SHAPE_TYPE_SPHERE)
	//		{
	//			// Both shapes are spheres
	//			return CollideSphereSphere(rbA, dynamic_cast<cBulletSphere*>(rbA->mShape), rbB, dynamic_cast<cBulletSphere*>(rbB->mShape));
	//		}
	//		else if (shapeB == eShapeType::SHAPE_TYPE_PLANE)
	//		{
	//			// First shape is a sphere, second is a plane
	//			return CollideSpherePlane(rbA, dynamic_cast<cBulletSphere*>(rbA->mShape), rbB, dynamic_cast<cBulletPlane*>(rbB->mShape));
	//		}
	//	}
	//	else if (shapeA == eShapeType::SHAPE_TYPE_PLANE)
	//	{
	//		if (shapeB == eShapeType::SHAPE_TYPE_SPHERE)
	//		{
	//			// First shape is a plane, second is a sphere
	//			return CollideSpherePlane(rbB, dynamic_cast<cBulletSphere*>(rbB->mShape), rbA, dynamic_cast<cBulletPlane*>(rbA->mShape));
	//		}
	//		else if (shapeB == eShapeType::SHAPE_TYPE_PLANE)
	//		{
	//			// Both shapes are planes
	//			return false;
	//		}
	//	}

	//	return false;
	//}

	//bool cBulletPhysicsWorld::CollideSpherePlane(cBulletRigidBody* sphereBody, cBulletSphere* sphereShape,
	//	cBulletRigidBody* planeBody, cBulletPlane* planeShape)
	//{
	//	// From our textbook, REAL-TIME COLLISION DETECTION, ERICSON
	//	// Use intersect_moving_sphere_plane(...inputs...outputs...)
	//	// to determine if:
	//	glm::vec3 q;
	//	float t = 0.0f;
	//	glm::vec3 c(sphereBody->mPreviousPosition);
	//	float r(sphereShape->mRadius);
	//	glm::vec3 v(sphereBody->mPosition - c);
	//	glm::vec3 n(planeShape->mNormal);
	//	float d = planeShape->GetPlaneConstant();
	//	int result = nCollide::intersect_moving_sphere_plane(c, r, v, n, d, t, q);

	//	// case A: The sphere did not collide during the timestep.
	//	// case A: Return false to indicate no collision happened.
	//	if (result == 0) return false;

	//	if (result == -1)
	//	{
	//		// TODO
	//		// case B: The sphere was already colliding at the beginning of the timestep.
	//		// case B: Do the timestep again for this sphere after applying an
	//		//         impulse that should separate it from the plane.
	//		// 1) From our textbook, use closest_point_on_plane(..inputs..) to determine the 
	//		//    penetration-depth of the sphere at the beginning of the timestep.
	//		//    (This penetration-depth is the distance the sphere must travel during
	//		//    the timestep in order to escape the plane.)
	//		// 2) Use the sphere's center and the closest point on the plane to define
	//		//    the direction of our impulse vector.

	//		// 3) Use (penetration-depth / DT) to define the magnitude of our impulse vector.
	//		//    (The impulse vector is now distance/time ...a velocity!)

	//		// 4) Apply the impulse vector to sphere velocity.
	//		// 5) Reset the sphere position.
	//		// 6) Re-do the integration for the timestep.
	//		// 7) Return true to indicate a collision has happened.
	//	}

	//	if (t > 1.0f)
	//	{
	//		return false;
	//	}

	//	// case C: The sphere collided during the timestep.
	//	// case C: Rewind to the point of impact, reflect, then replay.
	//	
	//	// 1) Use the outputs from the Ericson function to determine
	//	//    and set the sphere position to the point of impact.
	//	sphereBody->mPosition = sphereBody->mPreviousPosition + v * t;

	//	// 2) Reflect the sphere's velocity about the plane's normal vector.
	//	sphereBody->mVelocity = glm::reflect(sphereBody->mVelocity, n);

	//	glm::vec3 nComponent = glm::proj(sphereBody->mVelocity, n);

	//	// 3) Apply some energy loss (to the velocity) in the direction
	//	//    of the plane's normal vector.
	//	sphereBody->mVelocity -= nComponent * 0.2f;
	//	sphereBody->mPosition = (c + v * t);

	//	// 4) Re-integrate the sphere with its new velocity over the remaining
	//	//    portion of the timestep.
	//	mIntegrator.RK4(sphereBody->mPosition, sphereBody->mVelocity,
	//		sphereBody->mAcceleration, mGravity, mDt * (1.f - t));
	//	// 5) Return true to indicate a collision has happened.
	//	return true;
	//}

	//bool cBulletPhysicsWorld::CollideSphereSphere(cBulletRigidBody* bodyA, cBulletSphere* sphereA,
	//	cBulletRigidBody* bodyB, cBulletSphere* sphereB)
	//{
	//	// From our textbook, REAL-TIME COLLISION DETECTION, ERICSON
	//	// Use intersect_moving_sphere_sphere(...inputs...outputs...)
	//	// to determine if:
	//	glm::vec3 cA = bodyA->mPreviousPosition;
	//	glm::vec3 vA = bodyA->mPosition - bodyA->mPreviousPosition;
	//	float rA = sphereA->mRadius;
	//	glm::vec3 cB = bodyB->mPreviousPosition;
	//	glm::vec3 vB = bodyB->mPosition - bodyB->mPreviousPosition;
	//	float rB = sphereB->mRadius;

	//	float t = 0.f;
	//	int result = nCollide::intersect_moving_sphere_sphere(cA, rA, vA, cB, rB, vB, t);
	//
	//	// case A: The spheres don't collide during the timestep.
	//	// case A: Return false to indicate no collision happened.
	//	if (result == 0) return false;

	//	if (result == -1)
	//	{
	//		// TODO:
	//		// case B: The spheres were already colliding at the beginning of the timestep.
	//		// case B: Do the timestep again for these spheres after applying an impulse that should separate them.
	//		// 1) Determine the penetration-depth of the spheres at the beginning of the timestep.
	//		//    (This penetration-depth is the distance the spheres must travel during
	//		//    the timestep in order to separate.)
	//		// 2) Use the sphere's centers to define the direction of our impulse vector.
	//		// 3) Use (penetration-depth / DT) to define the magnitude of our impulse vector.
	//		//    (The impulse vector is now distance/time ...a velocity!)
	//		// 4) Apply a portion of the impulse vector to sphereA's velocity.
	//		// 5) Apply a portion of the impulse vector to sphereB's velocity.
	//		//    (Be sure to apply the impulse in opposing directions.)
	//		// 6) Reset the spheres' positions.
	//		// 7) Re-do the integration for the timestep.
	//		// 8) Return true to indicate a collision has happened.

	//		return false;
	//	}

	//	// case C: The spheres collided during the timestep.
	//	// case C: 
	//	// 1) Use the outputs from the Ericson function to determine
	//	//    and set the spheres positions to the point of impact.
	//	bodyA->mPosition = bodyA->mPreviousPosition + vA * t;
	//	bodyB->mPosition = bodyB->mPreviousPosition + vB * t;

	//	// 2) Use the inelastic collision response equations from
	//	//    Wikepedia to set their velocities post-impact.
	//	float ma = bodyA->mMass;
	//	float mb = bodyB->mMass;
	//	float mt = ma + mb;
	//	glm::vec3 va = bodyA->mVelocity;
	//	glm::vec3 vb = bodyB->mVelocity;
	//	float c = 0.2f;

	//	bodyA->mVelocity = (c * mb * (vb - va) + ma * va + mb * vb) / mt;
	//	bodyB->mVelocity = (c * ma * (va - vb) + ma * va + mb * vb) / mt;

	//	// 3) Re-integrate the spheres with their new velocities
	//	//    over the remaining portion of the timestep.
	//	mIntegrator.RK4(bodyA->mPosition, bodyA->mVelocity, bodyA->mAcceleration, mGravity, mDt * (1.0f - t));
	//	mIntegrator.RK4(bodyB->mPosition, bodyB->mVelocity, bodyB->mAcceleration, mGravity, mDt * (1.0f - t));

	//	// 4) Return true to indicate a collision has happened.
	//	return true;
	//}
}