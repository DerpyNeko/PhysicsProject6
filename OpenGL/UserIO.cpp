#include "globalOpenGLStuff.h"
#include "globalStuff.h"

// This has all the keyboard, mouse, and controller stuff
// No modifiers		Camera controls
// Shift			Camera rotations
// Ctrl				Model controls
// Alt				Light controls

int gLookAtModel = 2;

bool IsShiftDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) { return true; }
	// both are up
	return false;
}

bool IsCtrlDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) { return true; }
	// both are up
	return false;
}

bool IsAltDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)) { return true; }
	// both are up
	return false;
}

bool AreAllModifiersUp(GLFWwindow* window)
{
	if (IsShiftDown(window)) { return false; }
	if (IsCtrlDown(window)) { return false; }
	if (IsAltDown(window)) { return false; }
	// Yup, they are all UP
	return true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);	
	}
	
	// PADDLE COMMANDS
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		std::cout << "LEFT PRESS" << std::endl;
		_result = _system->playSound(soundArray[4], 0, false, &channelArray[0]);
		assert(!_result);
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		std::cout << "LEFT RELEASE" << std::endl;
		_result = _system->playSound(soundArray[5], 0, false, &channelArray[1]);
		assert(!_result);
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		std::cout << "RIGHT PRESS" << std::endl;
		_result = _system->playSound(soundArray[4], 0, false, &channelArray[0]);
		assert(!_result);
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		std::cout << "RIGHT RELEASE" << std::endl;
		_result = _system->playSound(soundArray[5], 0, false, &channelArray[1]);
		assert(!_result);
	}

	// LAUNCHER COMMAND
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		std::cout << "SPACE RELEASE" << std::endl;
		_result = _system->playSound(soundArray[3], 0, false, &channelArray[2]);
		assert(!_result);
	}

	return;
}

void ProcessAsyncKeys(GLFWwindow* window)
{
	const float MOVE_SPEED_SLOW = 0.05f;
	const float MOVE_SPEED_FAST = 1.0f;
	const float CAMERA_TURN_SPEED = 0.1f;

	float cameraMoveSpeed = ::g_pCamera->movementSpeed;
	float moveSpeed = MOVE_SPEED_SLOW;

	// If no keys are down, move the camera
	if (AreAllModifiersUp(window))
	{
		// PADDLE COMMANDS
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			cMeshObject* pObject = findObjectByFriendlyName("Paddle 1");
			pObject->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
		{
			cMeshObject* pObject = findObjectByFriendlyName("Paddle 1");
			pObject->setDiffuseColour(glm::vec3(0.0f, 0.3f, 0.4f));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			cMeshObject* pObject = findObjectByFriendlyName("Paddle 2");
			pObject->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
		{
			cMeshObject* pObject = findObjectByFriendlyName("Paddle 2");
			pObject->setDiffuseColour(glm::vec3(0.0f, 0.3f, 0.4f));
		}

		// LAUNCHER COMMAND
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			_result = _system->playSound(soundArray[2], 0, false, &channelArray[0]);
			assert(!_result);
		}



		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			::g_pCamera->MoveForward_Z(+10);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// "backwards"
		{
			::g_pCamera->MoveForward_Z(-10);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// "left"
		{
			::g_pCamera->MoveLeftRight_X(-10);
			glm::vec3 position = g_MeshObjects.at(gLookAtModel)->rigidBody->GetPosition() - g_pCamera->eye;
			g_pCamera->setCameraAt(glm::normalize(position));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// "right"
		{
			::g_pCamera->MoveLeftRight_X(+10);
			glm::vec3 position = g_MeshObjects.at(gLookAtModel)->rigidBody->GetPosition() - g_pCamera->eye;
			g_pCamera->setCameraAt(glm::normalize(position));
		}
	}//if(AreAllModifiersUp(window)

	// Control (ctrl) key down? Move light
	if (IsCtrlDown(window))
	{

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//			g_CameraEye.z += cameraSpeed;
			::g_pCamera->MoveForward_Z(+cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// "backwards"
		{
			//			g_CameraEye.z -= cameraSpeed;
			::g_pCamera->MoveForward_Z(-cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// "left"
		{
			//			g_CameraEye.x -= cameraSpeed;
			::g_pCamera->MoveLeftRight_X(-cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// "right"
		{
			//			g_CameraEye.x += cameraSpeed;
			::g_pCamera->MoveLeftRight_X(+cameraMoveSpeed);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	// "up"
		{
			::g_pCamera->MoveUpDown_Y(-cameraMoveSpeed);
			//::g_pCamera->Roll_CW_CCW( +cameraMoveSpeed );
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	// "down"
		{
			//			g_CameraEye.y -= cameraSpeed;
			::g_pCamera->MoveUpDown_Y(+cameraMoveSpeed);
			//::g_pCamera->Roll_CW_CCW( -cameraMoveSpeed );
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)	// "down"
		{
			glm::vec3 at = ::g_pCamera->getCameraDirection();
			std::cout << ::g_pCamera->eye.x << " " << ::g_pCamera->eye.y << " " << ::g_pCamera->eye.z << " AT: " << at.x << " " << at.y << " " << at.z;
		}


	}//if(!IsShiftDown(window) )	


	const float MIN_LIGHT_BRIGHTNESS = 0.001f;

	// Control (alt) key down? Move light
	if (IsAltDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W)) { g_Lights[g_LightIndex]->position.z += moveSpeed; }
		if (glfwGetKey(window, GLFW_KEY_S)) { g_Lights[g_LightIndex]->position.z -= moveSpeed; }
		if (glfwGetKey(window, GLFW_KEY_A)) { g_Lights[g_LightIndex]->position.x += moveSpeed; }
		if (glfwGetKey(window, GLFW_KEY_D)) { g_Lights[g_LightIndex]->position.x -= moveSpeed; }
		if (glfwGetKey(window, GLFW_KEY_Q)) { g_Lights[g_LightIndex]->position.y += moveSpeed; }
		if (glfwGetKey(window, GLFW_KEY_E)) { g_Lights[g_LightIndex]->position.y -= moveSpeed; }

		if (glfwGetKey(window, GLFW_KEY_1))
		{	// Const
			g_Lights[g_LightIndex]->atten.x *= 0.99f;		// Decrease by 1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_2))
		{	// Const
			g_Lights[g_LightIndex]->atten.x *= 1.01f;		// Increase by 1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_3))
		{	// Linear
			g_Lights[g_LightIndex]->atten.y *= 0.99f;		// Decrease by 1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_4))
		{	// Linear
			g_Lights[g_LightIndex]->atten.y *= 1.01f;		// Increase by 1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_5))
		{	// Quadratic
			g_Lights[g_LightIndex]->atten.z *= 0.99f;		// Decrease by 0.1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_6))
		{	// Quadratic
			g_Lights[g_LightIndex]->atten.z *= 1.01f;		// Increase by 0.1 percent
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			std::cout << "Light[" << g_LightIndex << "] Position: " << g_Lights[g_LightIndex]->position.x
				<< ", " << g_Lights[g_LightIndex]->position.y << ", " << g_Lights[g_LightIndex]->position.z
				<< " Attenuation: " << g_Lights[g_LightIndex]->atten.x << ", " << g_Lights[g_LightIndex]->atten.y
				<< ", " << g_Lights[g_LightIndex]->atten.z << std::endl;
		}

	}//if(!IsShiftDown(window) )

	return;
}

bool g_MouseIsInsideWindow = false;

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		::g_MouseIsInsideWindow = true;
	}
	else
	{
		::g_MouseIsInsideWindow = false;
	}
	return;
}//cursor_enter_callback(...

// Mouse (cursor) callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	return;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// A regular mouse wheel returns the y value
	::g_pCamera->setMouseWheelDelta(yoffset);

	//	std::cout << "Mouse wheel: " << yoffset << std::endl;

	return;
}

void ProcessAsyncMouse(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	::g_pCamera->setMouseXY(x, y);

	const float MOUSE_SENSITIVITY = 0.1f;

	//	std::cout << ::g_pFlyCamera->getMouseX() << ", " << ::g_pFlyCamera->getMouseY() << std::endl;

		// Mouse left (primary?) button pressed? 
		// AND the mouse is inside the window...
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		&& ::g_MouseIsInsideWindow)
	{
		// Mouse button is down so turn the camera
		::g_pCamera->Yaw_LeftRight(-::g_pCamera->getDeltaMouseX() * MOUSE_SENSITIVITY);

		::g_pCamera->Pitch_UpDown(::g_pCamera->getDeltaMouseY() * MOUSE_SENSITIVITY);

	}

	// Adjust the mouse speed
	if (::g_MouseIsInsideWindow)
	{
		const float MOUSE_WHEEL_SENSITIVITY = 0.1f;

		// Adjust the movement speed based on the wheel position
		::g_pCamera->movementSpeed = ::g_pCamera->getMouseWheel() * MOUSE_WHEEL_SENSITIVITY;
	}

	return;
}//ProcessAsyncMouse(...
