#include "nLoad.h"
#include "../json/json.h"
#include <iostream>
#include <fstream>
#include "cMeshObject.h"
#include "Physics.h"
#include "globalStuff.h"

namespace nLoad
{
	bool LoadConfig(const char* fileName)
	{
		Json::Value jsonConfig;
		if (!ReadJsonFile(fileName, jsonConfig))
		{
			return false;
		}

		Json::Value jsonSuperDefs = jsonConfig["ObjectDefs"];
		if (!jsonSuperDefs.isArray())
		{
			return false;
		}

		int numDefs = jsonSuperDefs.size();
		for (int c = 0; c < numDefs; c++)
		{
			cMeshObject* object = new cMeshObject();
			nPhysics::sRigidBodyDef def;
			nPhysics::iSphereShape* sphere;
			nPhysics::iPlaneShape* plane;

			Json::Value jsonSuperDef = jsonSuperDefs[c];

			if (jsonSuperDef.isObject())
			{
				if (jsonSuperDef["Mesh"].isString())
				{
					object->meshName = jsonSuperDef["Mesh"].asString();
				}
				else
				{
					std::cout << "Mesh not loaded" << std::endl;
				}

				if (jsonSuperDef["Name"].isString())
				{
					object->friendlyName = jsonSuperDef["Name"].asString();
				}
				else
				{
					std::cout << "Name not loaded" << std::endl;
				}

				if (jsonSuperDef["Color"].isArray())
				{
					Json::Value t = jsonSuperDef["Color"];
					object->setDiffuseColour(glm::vec3(t[0].asDouble(), t[1].asDouble(), t[2].asDouble()));
				}
				else
				{
					std::cout << "Color not loaded" << std::endl;
				}

				if (jsonSuperDef["Mass"].isDouble())
				{
					def.Mass = jsonSuperDef["Mass"].asFloat();
				}
				else
				{
					std::cout << "Mass not loaded" << std::endl;
				}

				if (jsonSuperDef["Position"].isArray())
				{
					Json::Value t = jsonSuperDef["Position"];
					def.Position = glm::vec3(t[0].asDouble(), t[1].asDouble(), t[2].asDouble());
				}
				else
				{
					std::cout << "Position not loaded" << std::endl;

				}

				if (jsonSuperDef["Orientation"].isArray())
				{
					Json::Value t = jsonSuperDef["Orientation"];
					object->adjMeshOrientationEulerAngles(glm::vec3(t[0].asDouble(), t[1].asDouble(), t[2].asDouble()), true);
				}
				else
				{
					std::cout << "Orientation not loaded" << std::endl;
				}

				if (jsonSuperDef["Velocity"].isArray())
				{
					Json::Value t = jsonSuperDef["Velocity"];
					def.Velocity = glm::vec3(t[0].asFloat(), t[1].asDouble(), t[2].asDouble());
				}
				else
				{
					std::cout << "Velocity not loaded" << std::endl;
				}

				if (jsonSuperDef["Shape"].isString())
				{
					if (jsonSuperDef["Shape"].asString() == "Sphere")
					{
						if (jsonSuperDef["Radius"].isDouble())
						{
							object->setUniformScale(jsonSuperDef["Radius"].asFloat());
							sphere = gPhysicsFactory->CreateSphereShape(jsonSuperDef["Radius"].asFloat());
							object->rigidBody = gPhysicsFactory->CreateRigidBody(def, sphere);
						}
					}
					else
					{
						if (jsonSuperDef["Constant"].isDouble())
						{
							if (jsonSuperDef["Normal"].isArray())
							{
								Json::Value t = jsonSuperDef["Normal"];

								plane = gPhysicsFactory->CreatePlaneShape(glm::vec3(t[0].asFloat(), t[1].asFloat(), t[2].asFloat()),
									jsonSuperDef["Constant"].asFloat());

								object->rigidBody = gPhysicsFactory->CreateRigidBody(def, plane);
								object->bDontLight = true;
							}
						}
					}
				}
			}
			else
			{
				std::cout << "Not an object" << std::endl;
			}

			g_MeshObjects.push_back(object);
			physicsWorld->AddBody(object->rigidBody);
		}

		return true;
	}

	bool ReadJsonFile(const char* fileName, Json::Value& jsonOut)
	{
		if (!FileExists(fileName))
		{
			return false;
		}

		std::ifstream jsonFile(fileName, std::ifstream::binary);
		Json::CharReaderBuilder charReaderBuilder;
		std::string errs;
		return Json::parseFromStream(charReaderBuilder, jsonFile, &jsonOut, &errs);
	}
}