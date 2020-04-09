#ifndef _nLoad_HG_
#define _nLoad_HG_

#include "../json/json.h"
#include <Physics/Interfaces/iRigidBody.h>

namespace nLoad
{
	inline bool FileExists(const char* fileName)
	{
		struct stat buffer;
		return (stat(fileName, &buffer) == 0);
	}

	bool LoadConfig(const char* filename);
	bool ReadJsonFile(const char* fileName, Json::Value& jsonOut);
}
#endif
