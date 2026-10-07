#include "Window/Window.h"

#include "GLFWWindow.h"

namespace RealEngine {

Window* Window::Create(const WindowProps& props) {
    return new GLFWWindow(props);
}

} // namespace RealEngine
