#include "OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace RealEngine {

void OpenGLRendererAPI::Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    glViewport(static_cast<GLint>(x), static_cast<GLint>(y),
               static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void OpenGLRendererAPI::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace RealEngine
