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
}