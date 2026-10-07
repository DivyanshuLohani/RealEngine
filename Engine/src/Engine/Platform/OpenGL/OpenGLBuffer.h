#pragma once

#include "Engine/Render/Buffer.h"

namespace RealEngine {

class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(const void* vertices, uint32_t size);
    ~OpenGLVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    void SetLayout(const BufferLayout& layout) override;
    const BufferLayout& GetLayout() const override;

private:
    uint32_t m_RendererID = 0;
    BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    uint32_t GetCount() const override { return m_Count; }

private:
    uint32_t m_RendererID = 0;
    uint32_t m_Count = 0;
};

} // namespace RealEngine
