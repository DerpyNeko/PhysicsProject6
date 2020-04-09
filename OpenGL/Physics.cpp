#include "Physics.h"
#include <iostream>
#include <Windows.h>
#include "globalStuff.h"

nPhysics::iPhysicsFactory* gPhysicsFactory = 0;
nPhysics::iPhysicsWorld* physicsWorld = 0;

typedef nPhysics::iPhysicsFactory* (*f_CreateFactory)();

HINSTANCE hGetProcDll = 0;

bool InitPhysics()
{
	if (gPhysicsFactory)
	{
		std::cout << "Factory exists" << std::endl;
		return false;
	}

	hGetProcDll = LoadLibraryA("BulletPhysics.dll");
	//hGetProcDll = LoadLibraryA("SimplePhysics.dll");
	if (!hGetProcDll)
	{
		std::cout << "Error loading dll" << std::endl;
		return false;
	}

	f_CreateFactory CreateFactory = (f_CreateFactory)GetProcAddress(hGetProcDll, "CreatePhysicsFactory");

	if (!CreateFactory)
	{
		std::cout << "Error creating factory" << std::endl;
		return false;
	}

	gPhysicsFactory = CreateFactory();

	return true;
}

void DestroyAllObjects()
{
	size_t numSupers = g_MeshObjects.size();
	for (size_t c = 0; c < numSupers; c++)
	{
		delete g_MeshObjects[c];
	}

	g_MeshObjects.resize(0);

	if (gPhysicsFactory)
	{
		delete gPhysicsFactory;
		gPhysicsFactory = 0;
	}

	if (hGetProcDll)
	{
		FreeLibrary(hGetProcDll);
		hGetProcDll = 0;
	}
}
