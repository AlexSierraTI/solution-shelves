#include "sspch.h"
#include "Engine/Core/Input.h"

#include "Engine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace SolutionShelves
{
	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	glm::vec2 Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
	float Input::GetMouseX()
	{
		auto mousePos = GetMousePosition();
		return mousePos.x;
	}
	float Input::GetMouseY()
	{
		auto mousePos = GetMousePosition();
		return mousePos.y;
	}
}
