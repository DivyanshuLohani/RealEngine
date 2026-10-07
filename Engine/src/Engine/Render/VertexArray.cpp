#include "Engine/Render/VertexArray.h"
#include "Engine/Platform/OpenGL/OpenGLVertexArray.h"

namespace RealEngine {

Ref<VertexArray> VertexArray::Create() {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLVertexArray>();
#else
    return nullptr;
#endif
}

} // namespace RealEngine
