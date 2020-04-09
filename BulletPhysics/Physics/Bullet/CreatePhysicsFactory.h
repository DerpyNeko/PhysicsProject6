#ifndef _CreatePhysicsFactory_HG_
#define _CreatePhysicsFactory_HG_

// Creates the dll file for SimplePhysics

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

#include <Physics/Interfaces/iPhysicsFactory.h>

EXTERN_DLL_EXPORT nPhysics::iPhysicsFactory* CreatePhysicsFactory();

#endif
