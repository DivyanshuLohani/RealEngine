#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Render/Buffer.h"

#include <vector>

namespace RealEngine {

// Combines vertex buffers + a buffer layout into a drawable vertex
// specification (a VAO in OpenGL terms).
class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

    virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

    // Phase 2: static Ref<VertexArray> Create();
};

} // namespace RealEngine
