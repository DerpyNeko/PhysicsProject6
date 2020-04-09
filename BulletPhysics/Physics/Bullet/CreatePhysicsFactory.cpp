#include "CreatePhysicsFactory.h"
#include "cBulletPhysicsFactory.h"

EXTERN_DLL_EXPORT nPhysics::iPhysicsFactory* CreatePhysicsFactory()
{
	return new nPhysics::cBulletPhysicsFactory();
}