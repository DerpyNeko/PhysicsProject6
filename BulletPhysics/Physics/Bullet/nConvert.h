#ifndef _nConvert_HG_
#define _nConvert_HG_

// Utility class that converts to and from glm::vec3 and btVector3 as well as convert btTransform to glm::mat4

#include "Bullet/LinearMath/btVector3.h"
#include "Bullet/LinearMath/btTransform.h"
#include <glmMath.h>

namespace nPhysics
{
	// Has its own special namespace
	namespace nConvert
	{
		// Converts btVector3 to glm::vec3, returns new glm::vec3
		inline glm::vec3 ToSimple(const btVector3& vec)
		{
			return glm::vec3(vec.x(), vec.y(), vec.z());
		}

		// Converts btVector3 to glm::vec3, returns the glm::vec3 in vecOut variable
		inline void ToSimple(const btVector3& vecIn, glm::vec3& vecOut)
		{
			vecOut.x = vecIn.x();
			vecOut.y = vecIn.y();
			vecOut.z = vecIn.z();
		}

		// Converts glm::vec3 to btVector3, returns new btVector3
		inline btVector3 ToBullet(const glm::vec3& vec)
		{
			return btVector3(vec.x, vec.y, vec.z);
		}

		// Converts glm::vec3 to btVector3, returns the btVector3 in vecOut variable
		inline void ToBullet(const glm::vec3& vecIn, btVector3& vecOut)
		{
			vecOut.setValue(vecIn.x, vecIn.y, vecIn.z);
		}

		// Converts btTransform to glm::mat4, returns new glm::mat4
		inline glm::mat4 ToSimple(const btTransform& transform)
		{
			glm::mat4 mat;
			transform.getOpenGLMatrix(&mat[0][0]);
			return mat;
		}

		// Converts btTransform to glm::mat4, returns the glm::mat4 in mat variable
		inline void ToSimple(const btTransform& transform, glm::mat4& mat)
		{
			transform.getOpenGLMatrix(&mat[0][0]);
		}
	}
}
#endif