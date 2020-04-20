#ifndef _cBulletPhysicsFactory_HG_
#define _cBulletPhysicsFactory_HG_

#include <Physics/Interfaces/iPhysicsFactory.h>
#include <Physics/Interfaces/Constraints.h>

// Factory class that inherits from the iPhysicsFactory

namespace nPhysics
{
	class cBulletPhysicsFactory : public iPhysicsFactory
	{
	public:
		// Constructor
		cBulletPhysicsFactory();

		// Destructor
		virtual ~cBulletPhysicsFactory();

		// Creates the physics world
		virtual iPhysicsWorld* CreatePhysicsWorld() override;
		
		// Creates a rigid body based on definition and shape
		virtual iRigidBody* CreateRigidBody(const sRigidBodyDef& rbDef, iShape* shape) override;

		// Creates a sphere shape based on the radius
		virtual iSphereShape* CreateSphereShape(float sphereRadius) override;

		// Creates a plane shape based on the normal and constant
		virtual iPlaneShape* CreatePlaneShape(const glm::vec3& planeNormal, float planeConstant) override;

		// Creates a box shape based on box half extends
		virtual iBoxShape* CreateBoxShape(const glm::vec3& boxHalfExtents) override;

		// Creates a plane shape based on the radius and height
		virtual iCapsuleShape* CreateCapsuleShape(float radius, float height) override;

		// Creates a cone based on the radius and height
		virtual iConeShape* CreateConeShape(float radius, float height) override;

		// Creates a cylinder shape based on box half extends
		virtual iCylinderShape* CreateCylinderShape(const glm::vec3& boxHalfExtents) override;

		// Creates a 6DoF constraint based on definition
		virtual i6DoFConstraint* Create6DoFConstraint(const s6DoFDef& dofDef) override;

		// Creates a hinge constraint based on definition
		virtual iHingeConstraint* CreateHingeConstraint(const sHingeDef& hingeDef) override;

		// Creates a slider constraint based on definition
		virtual iSliderConstraint* CreateSliderConstraint(const sSliderDef& sliderDef) override;
	};
}

#endif
