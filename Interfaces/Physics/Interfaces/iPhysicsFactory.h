#ifndef _iPhysicsFactory_HG_
#define _iPhysicsFactory_HG_

// Physics Factory that creates all of physics related objects

#include "Interfaces.h"

namespace nPhysics
{
	// Factory that creates world, rigid bodies and shapes
	class iPhysicsFactory
	{
	public:
		// Destructor
		virtual ~iPhysicsFactory() {}

		// Creates a physics world 
		virtual iPhysicsWorld* CreatePhysicsWorld() = 0;

		// Creates a rigid body with the definitions and shape 
		virtual iRigidBody* CreateRigidBody(const sRigidBodyDef& rbDef, iShape* shape) = 0;
		
		// Creates a sphere object to be added to a rigid body
		virtual iSphereShape* CreateSphereShape(float sphereRadius) = 0;

		// Creates a plane object to be added to a rigid body
		virtual iPlaneShape* CreatePlaneShape(const glm::vec3& planeNormal, float planeConstant) = 0;

		// Creates a box shape based on box half extends
		virtual iBoxShape* CreateBoxShape(const glm::vec3& boxHalfExtents) = 0;

		// Creates a plane shape based on the radius and height
		virtual iCapsuleShape* CreateCapsuleShape(float radius, float height) = 0;

		// Creates a cone
		virtual iConeShape* CreateConeShape(float radius, float height) = 0;

		// Creates a cylinder shape based on box half extends
		virtual iCylinderShape* CreateCylinderShape(const glm::vec3& boxHalfExtents) = 0;

		// Creates a 6DoF constraint based on definition
		virtual i6DoFConstraint* Create6DoFConstraint(const s6DoFDef& dofDef) = 0;

		// Creates a hinge constraint based on definition
		virtual iHingeConstraint* CreateHingeConstraint(const sHingeDef& hingeDef) = 0;

		// Creates a slider constraint based on definition
		virtual iSliderConstraint* CreateSliderConstraint(const sSliderDef& sliderDef) = 0;
	protected:
		iPhysicsFactory() {}
	private:
		// Constructors not used
		//iPhysicsFactory() = delete;
		iPhysicsFactory(const iPhysicsFactory& other) = delete;
		iPhysicsFactory& operator=(const iPhysicsFactory& other) = delete;
	};
}
#endif
