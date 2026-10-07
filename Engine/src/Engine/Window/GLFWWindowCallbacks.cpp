#include "GLFWWindow.h"

#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace RealEngine {

void GLFWWindow::RegisterInputCallbacks() {
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(static_cast<KeyCode>(key), false);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(static_cast<KeyCode>(key));
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(static_cast<KeyCode>(key), true);
            data.EventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        KeyTypedEvent event(static_cast<KeyCode>(keycode));
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int /*mods*/) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(static_cast<MouseCode>(button));
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
            data.EventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
        data.EventCallback(event);
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
        data.EventCallback(event);
    });
}

} // namespace RealEngine
