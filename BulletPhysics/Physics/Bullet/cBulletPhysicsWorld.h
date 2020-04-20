#ifndef _cSimplePhysicsWorld_HG_
#define _cSimplePhysicsWorld_HG_

#include <Physics/Interfaces/iPhysicsWorld.h>
#include <Physics/Interfaces/iConstraint.h>
#include "cBulletRigidBody.h"
#include "BulletShapes.h"
#include "cBullet6DoFConstraint.h"
#include "cBulletHingeConstraint.h"
#include "cBulletSliderConstraint.h"
#include <vector>

// Physics world that simulates rigid bodies

namespace nPhysics
{
	// cWorld
	// 
	// A rigid body simulator.
	// 
	// Pointers to cRigidBody instances can be added and removed.
	// 
	// cWorld will operate on the contained cRigidBody's during timesteps
	// triggered by calls to cWorld::Update(dt)
	// 
	// cWorld does not own cRigidBody pointers, and will not
	// delete them when it is deleted.
	class cBulletPhysicsWorld : public iPhysicsWorld
	{
	public:
		// Constructor
		// Create a cWorld
		// The world is initially empty, containing no rigid bodies.
		cBulletPhysicsWorld();

		// Destructor
		// Does not delete any cRigidBody pointers.
		~cBulletPhysicsWorld();

		// GetGravity
		// Get the gravity acceleration vector.
		//void GetGravity(glm::vec3& gravityOut);

		// SetGravity
		// Set the gravity acceleration vector.
		// This will be applied to all rigid bodies during timesteps.
		virtual void SetGravity(const glm::vec3& gravity) override;

		// Update
		// A single trigger to perform a single timestep.
		// All rigid bodies will go through integration, collision
		// detection and reaction, and have their internal values updated.
		virtual void Update(float dt) override;

		// AddRigidBody
		// Add a rigid body to the world. 
		// Returns true if:
		//    There was an addition to the world.
		//    This particular rigid body was added to the world.
		//    (It must not have already been contained in the world)
		// Returns false if:
		//    There was no addition to the world.
		//    A null pointer is passed in.
		//    This particular rigid body is already in the world, hense not added again.
		virtual bool AddBody(iRigidBody* rigidBody) override;

		// RemoveRigidBody
		// Remove a rigid body from the world.
		// Returns true if:
		//    There was a removal from the world.
		//    This particular rigid body existed in the world and was removed.
		// Returns false if:
		//    There was no removal from the world.
		//    A null pointer was passed in.
		//    This particular rigid body was not in the world, hense not removed.
		virtual bool RemoveBody(iRigidBody* rigidBody) override;

		// AddConstraint
		// Add a constraint to the world. 
		// Returns true if:
		//    There was an addition to the world.
		//    This particular constraint was added to the world.
		//    (It must not have already been contained in the world)
		// Returns false if:
		//    There was no addition to the world.
		//    A null pointer is passed in.
		//    This particular constraint is already in the world, hense not added again.
		virtual bool AddConstraint(iConstraint* constraint) override;

		// RemoveConstraint
		// Remove a constraint from the world.
		// Returns true if:
		//    There was a removal from the world.
		//    This particular constraint existed in the world and was removed.
		// Returns false if:
		//    There was no removal from the world.
		//    A null pointer was passed in.
		//    This particular constraint was not in the world, hense not removed.
		virtual bool RemoveConstraint(iConstraint* constraint) override;
	protected:

		// IntegrateRigidBody
		// Performs a single numerical integration step.
		// Safe for null pointers.
		// Safe for static rigid bodies.
		//void IntegrateRigidBody(cBulletRigidBody* body, float dt);

		// Collide
		// Entry point for collision detection.
		// Returns the result of specific Collide[shapeA][ShapeB] methods.
		//bool Collide(cBulletRigidBody* bodyA, cBulletRigidBody* bodyB);

		// CollideSpherePlane
		// Handles collision detection and reaction between a sphere and a plane.
		// Returns true if a collision occured.
		// Returns false if no collision occured.
		//bool CollideSpherePlane(cBulletRigidBody* sphereBody, cBulletSphere* sphereShape,
		//	cBulletRigidBody* planeBody, cBulletPlane* planeShape);

		// CollideSphereSphere
		// Handles collision detection and reaction between two spheres.
		// Returns true if a collision occured.
		// Returns false if no collision occured.
		//bool CollideSphereSphere(cBulletRigidBody* bodyA, cBulletSphere* sphereA,
		//	cBulletRigidBody* bodyB, cBulletSphere* sphereB);

	private:
		// Bullet collision configuration
		btDefaultCollisionConfiguration* mCollisionConfiguration;

		// Bullet collision dispatcher
		btCollisionDispatcher* mDispatcher;

		// Bullet broadphase interface
		btBroadphaseInterface* mOverlappingPairCache;

		// Bullet sequential impulse constraint solver
		btSequentialImpulseConstraintSolver* mSolver;

		// Bullet discrete dynamic world
		btDiscreteDynamicsWorld* mDynamicsWorld;
		//btSimpleDynamicsWorld* mDynamicsWorld;

		btAlignedObjectArray<btCollisionShape*> mCollisionShapes;

		//void TickCallBack(btDynamicsWorld* dynamicWorld, btScalar timeStep);

		// Constructors not to be used.
		cBulletPhysicsWorld(const cBulletPhysicsWorld& other) = delete;
		cBulletPhysicsWorld& operator=(const cBulletPhysicsWorld& other) = delete;
	};
}
#endif
