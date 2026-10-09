#include "Render/Buffer.h"

#include "Core/Assert.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace RealEngine {

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLVertexBuffer>(size);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

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
