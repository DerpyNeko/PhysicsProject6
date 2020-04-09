//     ___                 ___ _     
//    / _ \ _ __  ___ _ _ / __| |    
//   | (_) | '_ \/ -_) ' \ (_ | |__  
//    \___/| .__/\___|_||_\___|____| 
//         |_|                       
//

#include "globalOpenGLStuff.h"
#include "globalStuff.h"

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "cShaderManager.h"
#include "DebugRenderer/cDebugRenderer.h"
#include "cLightHelper.h"

#include "Physics.h"
#include "nLoad.h"

cDebugRenderer* g_pDebugRendererACTUAL = NULL;
iDebugRenderer* g_pDebugRenderer = NULL;

cShaderManager* pShaderManager = NULL;		// "Heap" variable
cVAOMeshManager* g_pVAOMeshManager = NULL;
cBasicTextureManager* g_pTextureManager = NULL;

cCamera* g_pCamera = NULL;
std::vector<cMeshObject*> g_MeshObjects;
std::vector<sLight*> g_Lights;

int g_ModelIndex = 0;
bool g_bDrawDebugLightSpheres = false;

cMeshObject* findObjectByFriendlyName(std::string theNameToFind);

bool InitPhysics();
bool nLoad::LoadConfig(const char* fileName);

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(900, 920, "Physics Project 6", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	// Mouse callbacks
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	// Create the shader manager...
	pShaderManager = new cShaderManager();
	pShaderManager->setBasePath("assets/shaders/");

	cShaderManager::cShader vertexShader;
	cShaderManager::cShader fragmentShader;

	vertexShader.fileName = "vertex01.glsl";
	vertexShader.shaderType = cShaderManager::cShader::VERTEX_SHADER;

	fragmentShader.fileName = "fragment01.glsl";
	fragmentShader.shaderType = cShaderManager::cShader::FRAGMENT_SHADER;

	if (pShaderManager->createProgramFromFile("BasicUberShader", vertexShader, fragmentShader))
	{
		std::cout << "Compiled shaders OK." << std::endl;
	}
	else
	{
		std::cout << "OH NO! Compile error" << std::endl;
		std::cout << pShaderManager->getLastError() << std::endl;
	}

	// Load the uniform location values (some of them, anyway)
	cShaderManager::cShaderProgram* pSP = ::pShaderManager->pGetShaderProgramFromFriendlyName("BasicUberShader");
	pSP->LoadUniformLocation("texture00");
	pSP->LoadUniformLocation("texture01");
	pSP->LoadUniformLocation("texture02");
	pSP->LoadUniformLocation("texture03");
	pSP->LoadUniformLocation("texture04");
	pSP->LoadUniformLocation("texture05");
	pSP->LoadUniformLocation("texture06");
	pSP->LoadUniformLocation("texture07");
	pSP->LoadUniformLocation("texBlendWeights[0]");
	pSP->LoadUniformLocation("texBlendWeights[1]");

	GLuint program = pShaderManager->getIDFromFriendlyName("BasicUberShader");

	::g_pVAOMeshManager = new cVAOMeshManager();
	::g_pTextureManager = new cBasicTextureManager();

	// Loading the uniform variables here (rather than the inner draw loop)
	GLint objectColour_UniLoc = glGetUniformLocation(program, "objectColour");

	GLint matModel_location = glGetUniformLocation(program, "matModel");
	GLint matView_location = glGetUniformLocation(program, "matView");
	GLint matProj_location = glGetUniformLocation(program, "matProj");
	GLint eyeLocation_location = glGetUniformLocation(program, "eyeLocation");

	// Note that this point is to the +interface+ but we're creating the actual object
	::g_pDebugRendererACTUAL = new cDebugRenderer();
	::g_pDebugRenderer = (iDebugRenderer*)::g_pDebugRendererACTUAL;

	if (!::g_pDebugRendererACTUAL->initialize())
	{
		std::cout << "Warning: couldn't init the debug renderer." << std::endl;
		std::cout << "\t" << ::g_pDebugRendererACTUAL->getLastError() << std::endl;
	}
	else
	{
		std::cout << "Debug renderer is OK" << std::endl;
	}

	// Camera creation
	::g_pCamera = new cCamera();
	g_pCamera->eye = { 12.0f, 60.0f, 0.0f };
	g_pCamera->setCameraAt(glm::vec3(0.0f, -0.8f, 0.221f));

	LoadModelTypes(::g_pVAOMeshManager, program);
	//LoadModelsIntoScene(::g_vec_pObjectsToDraw);

	/***************************************************/
	if (!InitPhysics())
	{
		std::cout << "Error loading physics" << std::endl;
	}

	if (!gPhysicsFactory)
	{
		std::cout << "No super factory" << std::endl;
	}

	physicsWorld = gPhysicsFactory->CreatePhysicsWorld();

	nLoad::LoadConfig("assets/json/objects.json");

	std::vector<cMeshObject*> vec_pTransparentObject;
	std::vector<cMeshObject*> vec_pSolidObject;

	for (cMeshObject* m : g_MeshObjects)
	{
		if (m->materialDiffuse.a < 1.0f)
		{
			vec_pTransparentObject.push_back(m);
		}
		else
		{
			vec_pSolidObject.push_back(m);
		}
	}

	CreateLights(program);

	cLightHelper* pLightHelper = new cLightHelper();

	// Get the current time to start with
	double lastTime = glfwGetTime();

	// Draw the "scene" (run the program)
	while (!glfwWindowShouldClose(window))
	{

		// Switch to the shader we want
		::pShaderManager->useShaderProgram("BasicUberShader");

		float ratio;
		int width, height;

		glm::mat4x4 matProjection = glm::mat4(1.0f);
		glm::mat4x4	matView = glm::mat4(1.0f);

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH);			// Enables the KEEPING of the depth information
		glEnable(GL_DEPTH_TEST);	// When drawing, checked the existing depth
		glEnable(GL_CULL_FACE);		// Discared "back facing" triangles

		// Colour and depth buffers are TWO DIFF THINGS.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// FOV, Aspect ratio, Near clipping plane, Far clipping plane
		matProjection = glm::perspective(0.6f, ratio, 0.1f, 10000.0f);

		matView = glm::lookAt(::g_pCamera->eye, ::g_pCamera->getAtInWorldSpace(), ::g_pCamera->getUpVector());

		glUniform3f(eyeLocation_location, ::g_pCamera->eye.x, ::g_pCamera->eye.y, ::g_pCamera->eye.z);

		glUniformMatrix4fv(matView_location, 1, GL_FALSE, glm::value_ptr(matView));
		glUniformMatrix4fv(matProj_location, 1, GL_FALSE, glm::value_ptr(matProjection));

		for (sLight* light : g_Lights)
		{
			glUniform4f(light->position_UniLoc, light->position.x,
				light->position.y, light->position.z, 1.0f);

			glUniform4f(light->diffuse_UniLoc, light->diffuse.x,
				light->diffuse.y, light->diffuse.z, 1.0f);

			glUniform4f(light->param2_UniLoc, 1.0f, 0.0f, 0.0f, 0.0f);

			glUniform4f(light->atten_UniLoc, light->atten.x,
				light->atten.y, light->atten.z, light->atten.w);

			//cMeshObject* pDebugSphere = findObjectByFriendlyName("DebugSphere");
			//pDebugSphere->bIsVisible = true;
			//pDebugSphere->bDontLight = true;

			//glm::vec4 oldDiffuse = pDebugSphere->materialDiffuse;
			//glm::vec3 oldScale = pDebugSphere->nonUniformScale;

			//pDebugSphere->setDiffuseColour(glm::vec3(255.0f / 255.0f, 105.0f / 255.0f, 180.0f / 255.0f));
			//pDebugSphere->bUseVertexColour = false;
			//pDebugSphere->rigidBody->GetPosition() = glm::vec3(light->position);
			//glm::mat4 matBall(1.0f);

			//pDebugSphere->materialDiffuse = oldDiffuse;
			//DrawObject(pDebugSphere, matBall, program);
		}//for ( sLight* light : g_Lights

		{
			// Draw the skybox first 
			cMeshObject* pSkyBox = findObjectByFriendlyName("SkyBoxObject");
			pSkyBox->rigidBody->GetPosition() = g_pCamera->eye;
			pSkyBox->bIsVisible = true;
			pSkyBox->bIsWireFrame = false;

			// Bind the cube map texture to the cube map in the shader
			GLuint cityTextureUNIT_ID = 30;			// Texture unit go from 0 to 79
			glActiveTexture(cityTextureUNIT_ID + GL_TEXTURE0);	// GL_TEXTURE0 = 33984

			int cubeMapTextureID = ::g_pTextureManager->getTextureIDFromName("CityCubeMap");

			// Cube map is now bound to texture unit 30
			//glBindTexture( GL_TEXTURE_2D, cubeMapTextureID );
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID);

			//uniform samplerCube textureSkyBox;
			GLint skyBoxCubeMap_UniLoc = glGetUniformLocation(program, "textureSkyBox");
			glUniform1i(skyBoxCubeMap_UniLoc, cityTextureUNIT_ID);

			//uniform bool useSkyBoxTexture;
			GLint useSkyBoxTexture_UniLoc = glGetUniformLocation(program, "useSkyBoxTexture");
			glUniform1f(useSkyBoxTexture_UniLoc, (float)GL_TRUE);

			glm::mat4 matIdentity = glm::mat4(1.0f);
			DrawObject(pSkyBox, matIdentity, program);

			pSkyBox->bIsVisible = false;
			glUniform1f(useSkyBoxTexture_UniLoc, (float)GL_FALSE);
		}

		// Draw all the solid objects in the "scene"
		for (unsigned int objIndex = 0; objIndex != (unsigned int)vec_pSolidObject.size(); objIndex++)
		{
			cMeshObject* pCurrentMesh = vec_pSolidObject[objIndex];

			glm::mat4x4 matModel = glm::mat4(1.0f);

			DrawObject(pCurrentMesh, matModel, program);
		}

		// Draw all the transparent objects in the "scene"
		for (unsigned int objIndex = 0; objIndex != (unsigned int)vec_pTransparentObject.size(); objIndex++)
		{
			cMeshObject* pCurrentMesh = vec_pTransparentObject[objIndex];

			glm::mat4x4 matModel = glm::mat4(1.0f);

			DrawObject(pCurrentMesh, matModel, program);
		}

		//glm::vec3 position = g_MeshObjects.at(gLookAtModel)->rigidBody->GetPosition() - g_pCamera->eye;
		//g_pCamera->setCameraAt(glm::normalize(position));

		// High res timer (likely in ms or ns)
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		physicsWorld->Update(deltaTime);

		//::g_pDebugRendererACTUAL->RenderDebugObjects(matView, matProjection, deltaTime);

		glfwSwapBuffers(window);		// Shows what we drew

		glfwPollEvents();

		ProcessAsyncKeys(window);

		ProcessAsyncMouse(window);

		lastTime = currentTime;

	}//while (!glfwWindowShouldClose(window))

	// Delete stuff
	delete pShaderManager;
	delete ::g_pVAOMeshManager;
	delete ::g_pTextureManager;

	delete ::g_pDebugRenderer;
	delete ::g_pCamera;

	DestroyAllObjects();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

cMeshObject* findObjectByFriendlyName(std::string theNameToFind)
{
	for (unsigned int index = 0; index != g_MeshObjects.size(); index++)
	{
		if (g_MeshObjects[index]->friendlyName == theNameToFind)
		{
			return g_MeshObjects[index];
		}
	}

	return NULL;
}
