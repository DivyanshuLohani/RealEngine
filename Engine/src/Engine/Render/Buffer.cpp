#include "Engine/Render/Buffer.h"

#include "Engine/Core/Assert.h"
#include "Engine/Platform/OpenGL/OpenGLBuffer.h"

namespace RealEngine {

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLVertexBuffer>(vertices, size);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLIndexBuffer>(indices, count);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

} // namespace RealEngine
