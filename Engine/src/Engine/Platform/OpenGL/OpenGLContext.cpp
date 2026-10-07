#include "OpenGLContext.h"

#include "Engine/Core/Assert.h"
#include "Engine/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace RealEngine {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    RE_CORE_ASSERT(m_WindowHandle, "OpenGLContext: window handle is null");
}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);

    // gladLoadGL takes a GLADloadfunc, which matches glfwGetProcAddress exactly.
    const int status = gladLoadGL(glfwGetProcAddress);
    RE_CORE_ASSERT(status, "Failed to initialise GLAD");

    RE_CORE_INFO("OpenGL context created");
    RE_CORE_INFO("  Vendor:   {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    RE_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    RE_CORE_INFO("  Version:  {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}

} // namespace RealEngine
