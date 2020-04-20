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

		Json::Value jsonSuperDefs = jsonConfig["Entities"];
		if (!jsonSuperDefs.isArray())
		{
			return false;
		}

		int numDefs = jsonSuperDefs.size();
		for (int c = 0; c < numDefs; c++)
		{
			cMeshObject* object = new cMeshObject();

			nPhysics::iSphereShape* sphere;
			nPhysics::iPlaneShape* plane;
			nPhysics::iBoxShape* box;
			nPhysics::iCapsuleShape* capsule;
			nPhysics::iConeShape* cone;
			nPhysics::iCylinderShape* cylinder;

			nPhysics::sRigidBodyDef rbDef;
			nPhysics::s6DoFDef dofDef;
			nPhysics::sHingeDef hingeDef;
			nPhysics::sSliderDef sliderDef;

			glm::vec3 position = glm::vec3(0.0f);
			float mass = 0;

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
					object->setDiffuseColour(glm::vec3(t[0].asFloat(), t[1].asFloat(), t[2].asFloat()));
				}
				else
				{
					std::cout << "Color not loaded" << std::endl;
				}

				if (jsonSuperDef["Orientation"].isArray())
				{
					Json::Value t = jsonSuperDef["Orientation"];
					object->adjMeshOrientationEulerAngles(glm::vec3(t[0].asFloat(), t[1].asFloat(), t[2].asFloat()), true);
				}
				else
				{
					std::cout << "Orientation not loaded" << std::endl;
				}

				if (jsonSuperDef["Position"].isArray())
				{
					Json::Value t = jsonSuperDef["Position"];
					position = glm::vec3(t[0].asFloat(), t[1].asFloat(), t[2].asFloat());
				}
				else
				{
					std::cout << "Position not loaded" << std::endl;
				}

				if (jsonSuperDef["Mass"].isDouble())
				{
					mass = jsonSuperDef["Mass"].asFloat();
				}
				else
				{
					std::cout << "Mass not loaded" << std::endl;
				}

				if (jsonSuperDef["Shape"].isString())
				{
					rbDef.Position = position;
					rbDef.Mass = mass;

					if (jsonSuperDef["Velocity"].isArray())
					{
						Json::Value t = jsonSuperDef["Velocity"];
						rbDef.Velocity = glm::vec3(t[0].asFloat(), t[1].asFloat(), t[2].asFloat());
					}
					else
					{
						std::cout << "Velocity not loaded" << std::endl;
					}

					if (jsonSuperDef["Shape"].asString() == "Sphere")
					{
						if (jsonSuperDef["Radius"].isDouble())
						{
							object->setUniformScale(jsonSuperDef["Radius"].asFloat());
							sphere = gPhysicsFactory->CreateSphereShape(jsonSuperDef["Radius"].asFloat());
							object->rigidBody = gPhysicsFactory->CreateRigidBody(rbDef, sphere);
						}
						else
						{
							std::cout << "Sphere Radius not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Shape"].asString() == "Plane")
					{
						if (jsonSuperDef["Constant"].isDouble())
						{
							if (jsonSuperDef["Normal"].isArray())
							{
								Json::Value t = jsonSuperDef["Normal"];

								plane = gPhysicsFactory->CreatePlaneShape(glm::vec3(t[0].asFloat(), t[1].asFloat(), t[2].asFloat()),
									jsonSuperDef["Constant"].asFloat());

								object->rigidBody = gPhysicsFactory->CreateRigidBody(rbDef, plane);
							}
							else
							{
								std::cout << "Plane Normal not loaded" << std::endl;
							}
						}
						else
						{
							std::cout << "Plane Constant not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Shape"].asString() == "Box")
					{
						if (jsonSuperDef["HalfExtents"].isArray())
						{
							Json::Value h = jsonSuperDef["HalfExtents"];

							box = gPhysicsFactory->CreateBoxShape(glm::vec3(h[0].asFloat(), h[1].asFloat(), h[2].asFloat()));

							object->rigidBody = gPhysicsFactory->CreateRigidBody(rbDef, box);
						}
						else
						{
							std::cout << "Box HalfExtents not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Shape"].asString() == "Capsule")
					{
						if (jsonSuperDef["Radius"].isDouble())
						{
							if (jsonSuperDef["Height"].isDouble())
							{
								capsule = gPhysicsFactory->CreateCapsuleShape(jsonSuperDef["Radius"].asFloat(),
									jsonSuperDef["Height"].asFloat());

								object->rigidBody = gPhysicsFactory->CreateRigidBody(rbDef, capsule);
							}
							else
							{
								std::cout << "Capsule Height not loaded" << std::endl;
							}
						}
						else
						{
							std::cout << "Capsule Radius not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Shape"].asString() == "Cone")
					{
						if (jsonSuperDef["Radius"].isDouble())
						{
							if (jsonSuperDef["Height"].isDouble())
							{
								cone = gPhysicsFactory->CreateConeShape(jsonSuperDef["Radius"].asFloat(),
									jsonSuperDef["Height"].asFloat());

								object->rigidBody = gPhysicsFactory->CreateRigidBody(rbDef, cone);
							}
							else
							{
								std::cout << "Cone Height not loaded" << std::endl;
							}
						}
						else
						{
							std::cout << "Cone Radius not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Shape"].asString() == "Cylinder")
					{
						if (jsonSuperDef["HalfExtents"].isArray())
						{
							Json::Value h = jsonSuperDef["HalfExtents"];

							cylinder = gPhysicsFactory->CreateCylinderShape(glm::vec3(h[0].asFloat(), h[1].asFloat(), h[2].asFloat()));

							object->rigidBody = gPhysicsFactory->CreateRigidBody(rbDef, cylinder);
						}
						else
						{
							std::cout << "Box HalfExtents not loaded" << std::endl;
						}
					}
					physicsWorld->AddBody(object->rigidBody);
				}

				if (jsonSuperDef["Type"].isString())
				{
					if (jsonSuperDef["Type"].asString() == "Hinge")
					{
						hingeDef.Position = position;
						hingeDef.Mass = mass;

						if (jsonSuperDef["Length"].isDouble())
						{
							if (jsonSuperDef["Height"].isDouble())
							{
								if (jsonSuperDef["Width"].isDouble())
								{
									if (jsonSuperDef["Pivot"].isArray())
									{
										if (jsonSuperDef["Axis"].isArray())
										{
											hingeDef.Length = jsonSuperDef["Length"].asFloat();
											hingeDef.Height = jsonSuperDef["Height"].asFloat();
											hingeDef.Width = jsonSuperDef["Width"].asFloat();

											Json::Value p = jsonSuperDef["Pivot"];
											Json::Value a = jsonSuperDef["Axis"];
											hingeDef.Pivot = glm::vec3(p[0].asFloat(), p[1].asFloat(), p[2].asFloat());
											hingeDef.Axis = glm::vec3(a[0].asFloat(), a[1].asFloat(), a[2].asFloat());

											nPhysics::iHingeConstraint* h = gPhysicsFactory->CreateHingeConstraint(hingeDef);
											physicsWorld->AddConstraint(h);
											object->rigidBody = h->GetRigidBody();
										}
										else
										{
											std::cout << "Hinge Axis not loaded" << std::endl;
										}
									}
									else
									{
										std::cout << "Hinge Pivot not loaded" << std::endl;
									}
								}
								else
								{
									std::cout << "Hinge Width not loaded" << std::endl;
								}
							}
							else
							{
								std::cout << "Hinge Height not loaded" << std::endl;
							}
						}
						else
						{
							std::cout << "Hinge Length not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Type"].asString() == "6DoF")
					{
						dofDef.Position = position;
						dofDef.Mass = mass;

						if (jsonSuperDef["Radius"].isDouble())
						{
							if (jsonSuperDef["UpperLimit"].isArray())
							{
								if (jsonSuperDef["LowerLimit"].isArray())
								{
									dofDef.Radius = jsonSuperDef["Radius"].asFloat();

									Json::Value u = jsonSuperDef["UpperLimit"];
									Json::Value l = jsonSuperDef["LowerLimit"];
									dofDef.UpperLimit = glm::vec3(u[0].asFloat(), u[1].asFloat(), u[2].asFloat());
									dofDef.LowerLimit = glm::vec3(l[0].asFloat(), l[1].asFloat(), l[2].asFloat());

									nPhysics::i6DoFConstraint* d = gPhysicsFactory->Create6DoFConstraint(dofDef);
									physicsWorld->AddConstraint(d);
									object->rigidBody = d->GetRigidBody();
								}
								else
								{
									std::cout << "6DoF LowerLimit not loaded" << std::endl;
								}
							}
							else
							{
								std::cout << "6DoF UpperLimit not loaded" << std::endl;
							}
						}
						else
						{
							std::cout << "6DoF Radius not loaded" << std::endl;
						}
					}
					else if (jsonSuperDef["Type"].asString() == "Slider")
					{
						sliderDef.Position = position;
						sliderDef.Mass = mass;

						if (jsonSuperDef["Length"].isDouble())
						{
							if (jsonSuperDef["Height"].isDouble())
							{
								if (jsonSuperDef["Width"].isDouble())
								{
									if (jsonSuperDef["UpperLimit"].isDouble())
									{
										if (jsonSuperDef["LowerLimit"].isDouble())
										{
											sliderDef.Length = jsonSuperDef["Length"].asFloat();
											sliderDef.Height = jsonSuperDef["Height"].asFloat();
											sliderDef.Width = jsonSuperDef["Width"].asFloat();

											sliderDef.UpperLimit = jsonSuperDef["UpperLimit"].asFloat();
											sliderDef.LowerLimit = jsonSuperDef["LowerLimit"].asFloat();

											nPhysics::iSliderConstraint* s = gPhysicsFactory->CreateSliderConstraint(sliderDef);
											physicsWorld->AddConstraint(s);
											object->rigidBody = s->GetRigidBody();
										}
										else
										{
											std::cout << "Slider LowerLimit not loaded" << std::endl;
										}
									}
									else
									{
										std::cout << "Slider UpperLimit not loaded" << std::endl;
									}
								}
								else
								{
									std::cout << "Slider Width not loaded" << std::endl;
								}
							}
							else
							{
								std::cout << "Slider Height not loaded" << std::endl;
							}
						}
						else
						{
							std::cout << "Slider Length not loaded" << std::endl;
						}
					}
				}
			}
			else
			{
				std::cout << "Not an object" << std::endl;
			}

			object->bDontLight = true;
			g_MeshObjects.push_back(object);
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
