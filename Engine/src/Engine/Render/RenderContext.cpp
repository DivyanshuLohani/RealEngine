#include "Render/RenderContext.h"

#include "Core/Assert.h"
#include "Platform/OpenGL/OpenGLContext.h"

struct GLFWwindow;

namespace RealEngine {

// Backend selection point. Adding a new backend means adding a branch here (or,
// later, a runtime/plug-in based factory) - nothing else in the engine changes.
Scope<RenderContext> RenderContext::Create(void* windowHandle) {
#ifdef RE_RENDERER_OPENGL
    return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(windowHandle));
#else
    (void)windowHandle;
    RE_CORE_ASSERT(false, "No renderer backend selected at build time");
    return nullptr;
#endif
}

} // namespace RealEngine
