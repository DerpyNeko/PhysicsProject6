#ifndef _globalStuff_HG_
#define _globalStuff_HG_

#include "globalOpenGLStuff.h"

#include <glmMath.h>

#include <string>
#include <iostream>
#include <vector>

#include "sPlyVertex.h"
#include "sPlyTriangle.h"
#include "cMeshObject.h"
#include "sModelDrawInfo.h"
#include "cVAOMeshManager.h"

#include "cLightManager.h"
#include "cCamera.h"
#include "TextureManager/cBasicTextureManager.h"

#include "Error/CErrorLog.h"
#include "DebugRenderer/iDebugRenderer.h"

#include "fmod.hpp"

extern bool isFireProjectile;

extern iDebugRenderer* g_pDebugRenderer;
extern cCamera* g_pCamera;
extern cVAOMeshManager* g_pVAOMeshManager;

extern std::vector< cMeshObject* > g_MeshObjects;
extern int g_ModelIndex;
extern int gLookAtModel;

extern cBasicTextureManager* g_pTextureManager;

extern std::vector<sLight*> g_Lights;
extern int g_LightIndex;
extern bool g_bDrawDebugLightSpheres;

void CreateLights(GLint program);
void LoadModelTypes(cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID);
void LoadModelsIntoScene(std::vector<cMeshObject*> &vec_pObjectsToDraw);
void DrawObject(cMeshObject* pCurrentMesh, glm::mat4x4 &matModel, GLuint shaderProgramID);
cMeshObject* findObjectByFriendlyName(std::string theNameToFind);

extern FMOD_RESULT _result;
extern FMOD::System* _system;
extern FMOD::Sound* soundArray[];
extern FMOD::Channel* channelArray[];

#endif	// _globalStuff_HG_
