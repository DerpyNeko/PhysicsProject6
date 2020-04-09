#include "globalOpenGLStuff.h"
#include "globalStuff.h"

// Loading models was moved into this function
void LoadModelTypes(cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID)
{
	sModelDrawInfo sphereInfo;
	sphereInfo.meshFileName = "Sphere_n_uv.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInfo, shaderProgramID);

	sModelDrawInfo sphereInvertedNormalsInfo;
	sphereInvertedNormalsInfo.meshFileName = "Sphere_n_uv_INVERTED_NORMALS.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInvertedNormalsInfo, shaderProgramID);

	// cubes
	{
	sModelDrawInfo cube1Info;
	cube1Info.meshFileName = "Cube_1x1.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube1Info, shaderProgramID);

	sModelDrawInfo cube2Info;
	cube2Info.meshFileName = "Cube_1x2.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube2Info, shaderProgramID);

	sModelDrawInfo cube3Info;
	cube3Info.meshFileName = "Cube_1x5.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube3Info, shaderProgramID);

	sModelDrawInfo cube4Info;
	cube4Info.meshFileName = "Cube_1x7.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube4Info, shaderProgramID);

	sModelDrawInfo cube5Info;
	cube5Info.meshFileName = "Cube_1x27.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube5Info, shaderProgramID);

	sModelDrawInfo cube6Info;
	cube6Info.meshFileName = "Cube_1x35.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube6Info, shaderProgramID);

	sModelDrawInfo cube7Info;
	cube7Info.meshFileName = "Cube_2x2.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube7Info, shaderProgramID);

	sModelDrawInfo cube8Info;
	cube8Info.meshFileName = "Cube_2x7.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube8Info, shaderProgramID);

	sModelDrawInfo cube9Info;
	cube9Info.meshFileName = "Cube_2x28.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube9Info, shaderProgramID);

	sModelDrawInfo cube10Info;
	cube10Info.meshFileName = "Cube_27x36.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube10Info, shaderProgramID);
	}

	// hemispheres
	{
	sModelDrawInfo hemiSphere1Info;
	hemiSphere1Info.meshFileName = "HemiSphere_1x1.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(hemiSphere1Info, shaderProgramID);

	sModelDrawInfo hemiSphere2Info;
	hemiSphere2Info.meshFileName = "HemiSphere_1x2.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(hemiSphere2Info, shaderProgramID);
	}

	// triangles
	{
	sModelDrawInfo triangle1Info;
	triangle1Info.meshFileName = "Triangle_1x1.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle1Info, shaderProgramID);

	sModelDrawInfo triangle2Info;
	triangle2Info.meshFileName = "Triangle_1x2.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle2Info, shaderProgramID);

	sModelDrawInfo triangle3Info;
	triangle3Info.meshFileName = "Triangle_1x4.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle3Info, shaderProgramID);

	sModelDrawInfo triangle4Info;
	triangle4Info.meshFileName = "Triangle_1x6.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle4Info, shaderProgramID);

	sModelDrawInfo triangle5Info;
	triangle5Info.meshFileName = "Triangle_2x2.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle5Info, shaderProgramID);

	sModelDrawInfo triangle6Info;
	triangle6Info.meshFileName = "Triangle_2x3.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle6Info, shaderProgramID);

	sModelDrawInfo triangle7Info;
	triangle7Info.meshFileName = "Triangle_2x4.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle7Info, shaderProgramID);

	sModelDrawInfo triangle8Info;
	triangle8Info.meshFileName = "Triangle_2x6.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle8Info, shaderProgramID);

	sModelDrawInfo triangle9Info;
	triangle9Info.meshFileName = "Triangle_2x8.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle9Info, shaderProgramID);

	sModelDrawInfo triangle10Info;
	triangle10Info.meshFileName = "Triangle_2x13.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle10Info, shaderProgramID);

	sModelDrawInfo triangle11Info;
	triangle11Info.meshFileName = "Triangle_4x4.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle11Info, shaderProgramID);

	sModelDrawInfo triangle12Info;
	triangle12Info.meshFileName = "Triangle_5x5.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(triangle12Info, shaderProgramID);

	}

	// bumper
	{
		sModelDrawInfo bumperInfo;
		bumperInfo.meshFileName = "cylinder.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(bumperInfo, shaderProgramID);
	}

	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;

	// Load the textures, too
	::g_pTextureManager->SetBasePath("assets/textures");
	::g_pTextureManager->Create2DTextureFromBMPFile("SandTexture.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("DarkCube.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("LightCube.bmp", true);
	::g_pTextureManager->Create2DTextureFromBMPFile("GreyCube.bmp", true);


	// Load the cube map
	::g_pTextureManager->SetBasePath("assets/textures/cubemaps");
	std::string errorString;
	if (::g_pTextureManager->CreateCubeTextureFromBMPFiles("CityCubeMap",
		"TropicalSunnyDayLeft2048.bmp", "TropicalSunnyDayRight2048.bmp",		// Alternate these
		"TropicalSunnyDayDown2048.bmp", "TropicalSunnyDayUp2048.bmp", 			// Rotate these 90 degrees
		"TropicalSunnyDayFront2048.bmp", "TropicalSunnyDayBack2048.bmp", true, errorString))
	{
		std::cout << "Loaded the city cube map OK" << std::endl;
	}
	else
	{
		std::cout << "Error: city cube map DIDN't load. On no!" << std::endl;
	}

	return;
}

// Loads the models we are drawing into the vector
void LoadModelsIntoScene(std::vector<cMeshObject*>& vec_pObjectsToDraw)
{
	// pPlayer object
	//{
	//	for (int x = 0; x < 11; x = x + 10)
	//	{
	//		for (int z = 0; z < 11; z = z + 10)
	//		{
	//			cMeshObject* pPlayer = new cMeshObject();
	//			pPlayer->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
	//			pPlayer->setUniformScale(0.15f);
	//			pPlayer->setSpecularPower(100.0f);
	//			pPlayer->position = glm::vec3((float)x, 1.0f, (float)z);
	//			std::cout << "Starting Position: " << pPlayer->position.x << ", " << pPlayer->position.y << ", " << pPlayer->position.z << std::endl;

	//			pPlayer->meshName = "player.ply";
	//			pPlayer->bIsVisible = true;

	//			vec_pObjectsToDraw.push_back(pPlayer);
	//			//g_Players.push_back(pPlayer);

	//			cMeshObject* pBullet = new cMeshObject();

	//			pBullet->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
	//			pBullet->setSpecularPower(100.0f);
	//			pBullet->position = glm::vec3((float)x, 1.0f, (float)z);
	//			pBullet->setUniformScale(0.1f);
	//			pBullet->meshName = "hitsphere.ply";
	//			pBullet->bIsVisible = true;

	//			pBullet->pDebugRenderer = ::g_pDebugRenderer;
	//			vec_pObjectsToDraw.push_back(pBullet);
	//			//g_Bullets.push_back(pBullet);	
	//			
	//			//cMeshObject* pHitBox = new cMeshObject();

	//			//pHitBox->setDiffuseColour(glm::vec3(0.0f, 0.0f, 1.0f));
	//			//pHitBox->setSpecularPower(100.0f);
	//			//pHitBox->position = glm::vec3((float)x, 1.0f, (float)z);
	//			//pHitBox->setUniformScale(0.15f);
	//			//pHitBox->meshName = "hitsphere.ply";
	//			//pHitBox->bIsVisible = true;

	//			//pHitBox->pDebugRenderer = ::g_pDebugRenderer;
	//			//vec_pObjectsToDraw.push_back(pHitBox);
	//			//g_HitBoxes.push_back(pHitBox);
	//		}
	//	}
	//}

	// skybox
	//{
	//	// (could also be a cube, or whatever)
	//	cMeshObject* pSkyBoxObject = new cMeshObject();
	//	pSkyBoxObject->setDiffuseColour(glm::vec3(1.0f, 105.0f / 255.0f, 180.0f / 255.0f));
	//	pSkyBoxObject->bUseVertexColour = false;
	//	pSkyBoxObject->friendlyName = "SkyBoxObject";
	//	float scale = 5000.0f;
	//	pSkyBoxObject->nonUniformScale = glm::vec3(scale, scale, scale);
	//	pSkyBoxObject->meshName = "Sphere_n_uv_INVERTED_NORMALS.ply";
	//	// Invisible until I need to draw it
	//	pSkyBoxObject->bIsVisible = false;

	//	vec_pObjectsToDraw.push_back(pSkyBoxObject);
	//}

	// cube - light texture
	//{
	//	cMeshObject* pCube = new cMeshObject();

	//	pCube->setDiffuseColour(glm::vec3(0.1f, 0.1f, 0.1f));
	//	pCube->setUniformScale(1.0f);
	//	pCube->setSpecularPower(100.0f);

	//	pCube->friendlyName = "CubeLight";
	//	pCube->meshName = "cube_n_uv.ply";
	//	pCube->bIsVisible = false;

	//	//sTextureInfo lightTexture;
	//	//lightTexture.name = "LightCube.bmp";
	//	//lightTexture.strength = 1.0f;
	//	//pCube->vecTextures.push_back(lightTexture);

	//	pCube->pDebugRenderer = ::g_pDebugRenderer;
	//	vec_pObjectsToDraw.push_back(pCube);
	//}

	// cube - dark texture
	//{
	//	cMeshObject* pCube = new cMeshObject();

	//	pCube->setDiffuseColour(glm::vec3(0.1f, 0.1f, 0.1f));
	//	pCube->setUniformScale(1.0f);
	//	pCube->setSpecularPower(100.0f);

	//	pCube->friendlyName = "CubeDark";
	//	pCube->meshName = "cube_n_uv.ply";
	//	pCube->bIsVisible = false;

	//	sTextureInfo darkTexture;
	//	darkTexture.name = "GreyCube.bmp";
	//	darkTexture.strength = 1.0f;
	//	pCube->vecTextures.push_back(darkTexture);

	//	pCube->pDebugRenderer = ::g_pDebugRenderer;
	//	vec_pObjectsToDraw.push_back(pCube);
	//}

	//{	// This sphere is the tiny little debug sphere
	//	cMeshObject* pDebugSphere = new cMeshObject();
	//	pDebugSphere->meshName = "Sphere_n_uv.ply";
	//	pDebugSphere->friendlyName = "DebugSphere";
	//	pDebugSphere->position = glm::vec3(0.0f, 0.0f, 0.0f);
	//	pDebugSphere->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
	//	pDebugSphere->setUniformScale(0.1f);

	//	pDebugSphere->bIsWireFrame = true;
	//	pDebugSphere->bIsVisible = false;

	//	pDebugSphere->pDebugRenderer = ::g_pDebugRenderer;
	//	vec_pObjectsToDraw.push_back(pDebugSphere);
	//}

	return;
}