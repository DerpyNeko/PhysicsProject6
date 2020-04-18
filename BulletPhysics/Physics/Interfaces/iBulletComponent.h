#include <BulletDynamics\Featherstone\btMultiBodyDynamicsWorld.h>

#ifndef _iBulletComponent_HG_
#define _iBulletComponent_HG_

// Used to add/remove constraints

namespace nPhysics
{
	class iBulletComponent
	{
	public:
		// Adds the constraint to the world
		virtual void AddSelfToWorld(btDiscreteDynamicsWorld* world) = 0;

		// Removes the constraint from the world
		virtual void RemoveSelfFromWorld(btDiscreteDynamicsWorld* world) = 0;
	};
}
#endif
