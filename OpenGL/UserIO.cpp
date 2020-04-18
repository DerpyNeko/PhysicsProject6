#include "globalOpenGLStuff.h"
#include "globalStuff.h"

// This has all the keyboard, mouse, and controller stuff
// No modifiers		Camera controls
// Shift			Camera rotations
// Ctrl				Model controls
// Alt				Light controls

bool xPos = false;
bool xNeg = false;
bool yPos = false;
bool yNeg = false;

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
}

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

	return;
}

void ProcessAsyncMouse(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	::g_pCamera->setMouseXY(x, y);

	const float MOUSE_SENSITIVITY = 0.1f;

	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && ::g_MouseIsInsideWindow)
	{
		::g_pCamera->Yaw_LeftRight(-::g_pCamera->getDeltaMouseX() * MOUSE_SENSITIVITY);
		::g_pCamera->Pitch_UpDown(::g_pCamera->getDeltaMouseY() * MOUSE_SENSITIVITY);
	}

	// Adjust the movement speed based on the wheel position
	if (::g_MouseIsInsideWindow)
	{
		::g_pCamera->movementSpeed = ::g_pCamera->getMouseWheel() * MOUSE_SENSITIVITY;
	}

	return;
}
