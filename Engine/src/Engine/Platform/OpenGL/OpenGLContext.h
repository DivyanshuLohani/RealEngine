#pragma once

#include "Render/RenderContext.h"

struct GLFWwindow;

namespace RealEngine {

// OpenGL implementation of RenderContext. Owns the current GL context for a
// GLFW window and loads the OpenGL entry points through glad.
class OpenGLContext : public RenderContext {
public:
    explicit OpenGLContext(GLFWwindow* windowHandle);
    ~OpenGLContext() override = default;

    void Init() override;
    void SwapBuffers() override;

private:
    GLFWwindow* m_WindowHandle;
};

} // namespace RealEngine
