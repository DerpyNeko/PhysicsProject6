#ifndef _Physics_HG_
#define _Physics_HG_

#include <Physics/Interfaces/iPhysicsFactory.h>

extern nPhysics::iPhysicsFactory* gPhysicsFactory;
extern nPhysics::iPhysicsWorld* physicsWorld;

bool InitPhysics();
void DestroyAllObjects();
#endif
