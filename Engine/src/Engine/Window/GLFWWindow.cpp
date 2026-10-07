#include "GLFWWindow.h"

#include "Engine/Core/Log.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Render/RenderContext.h"

#include <GLFW/glfw3.h>

#include <cstdlib>

namespace RealEngine {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
    RE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

GLFWWindow::GLFWWindow(const WindowProps& props) {
    Init(props);
}

GLFWWindow::~GLFWWindow() {
    Shutdown();
}

void GLFWWindow::Init(const WindowProps& props) {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    m_Data.VSync = props.VSync;

    RE_CORE_INFO("Creating window \"{0}\" ({1} x {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized) {
        glfwSetErrorCallback(GLFWErrorCallback);
        if (!glfwInit()) {
            RE_CORE_CRITICAL("Failed to initialise GLFW");
            std::abort();
        }
        s_GLFWInitialized = true;
    }

    // Request an OpenGL 4.6 core context.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
                                nullptr, nullptr);
    if (!m_Window) {
        RE_CORE_CRITICAL("Failed to create GLFW window");
        std::abort();
    }

    // Create and initialise the graphics context (loads OpenGL via glad).
    m_Context = RenderContext::Create(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(props.VSync);

    // ---------------------------------------------------------------------
    // Event callbacks -> engine events
    // ---------------------------------------------------------------------
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data.Width = static_cast<uint32_t>(width);
        data.Height = static_cast<uint32_t>(height);

        WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (focused) {
            WindowFocusEvent event;
            data.EventCallback(event);
        } else {
            WindowLostFocusEvent event;
            data.EventCallback(event);
        }
    });

    glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowMovedEvent event(xpos, ypos);
        data.EventCallback(event);
    });

    RegisterInputCallbacks();
}

void GLFWWindow::Shutdown() {
    // Tear down the context before the native window it targets.
    m_Context.reset();

    if (m_Window) {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    if (s_GLFWInitialized) {
        glfwTerminate();
        s_GLFWInitialized = false;
    }
}

void GLFWWindow::OnUpdate() {
    glfwPollEvents();
    m_Context->SwapBuffers();
}

void GLFWWindow::SetVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.VSync = enabled;
}

} // namespace RealEngine
