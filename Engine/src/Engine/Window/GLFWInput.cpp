#include "Engine/Input/Input.h"

#include "Engine/Core/Application.h"
#include "Engine/Window/Window.h"

#include <GLFW/glfw3.h>

namespace RealEngine {

static GLFWwindow* GetGLFWWindow() {
    return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
}

bool Input::IsKeyPressedImpl(KeyCode key) {
    GLFWwindow* window = GetGLFWWindow();

    int state = glfwGetKey(window, static_cast<int>(key));

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressedImpl(MouseCode button) {
    GLFWwindow* window = GetGLFWWindow();

    return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePositionImpl() {
    GLFWwindow* window = GetGLFWWindow();

    double x = 0.0;
    double y = 0.0;

    glfwGetCursorPos(window, &x, &y);

    return {static_cast<float>(x), static_cast<float>(y)};
}

} // namespace RealEngine
