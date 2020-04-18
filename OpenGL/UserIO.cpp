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
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//playerVelocity->vy = 3.0f;
		yPos = true;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && yPos == true)
	{
		//playerVelocity->vy = 0.0f;
		yPos = false;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	// "backwards"
	{
		//playerVelocity->vy = -3.0f;
		yNeg = true;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && yNeg == true)
	{
		//playerVelocity->vy = 0.0f;
		yNeg = false;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	// "left"
	{
		//playerVelocity->vx = 3.0f;
		xPos = true;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && xPos)	// "left"
	{
		//playerVelocity->vx = 0.0f;
		xPos = false;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// "right"
	{
		//playerVelocity->vx = -3.0f;
		xNeg = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE && xNeg)	// "right"
	{
		//playerVelocity->vx = 0.0f;
		xNeg = false;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
	}

	return;
}

void ProcessAsyncKeys(GLFWwindow* window)
{

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
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	// "right"
	{
		::g_pCamera->MoveLeftRight_X(+10);
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
