#include "Engine/Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/gl.h>

namespace RealEngine {

OpenGLVertexArray::OpenGLVertexArray() {
    glad_glGenVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
    glad_glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const {
    glad_glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const {
    glad_glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
    m_VertexBuffers.push_back(vertexBuffer);

    Bind();
    vertexBuffer->Bind();

    const auto& layout = vertexBuffer->GetLayout();

    uint32_t index = 0;

    for (const auto& element : layout) {
        glad_glEnableVertexAttribArray(index);

        glad_glVertexAttribPointer(index, element.GetComponentCount(), GL_FLOAT,
                                   element.Normalized ? GL_TRUE : GL_FALSE, static_cast<GLsizei>(layout.GetStride()),
                                   reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));

        index++;
    }
}

void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
    Bind();

    indexBuffer->Bind();

    m_IndexBuffer = indexBuffer;
}

const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const {
    return m_VertexBuffers;
}

const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const {
    return m_IndexBuffer;
}

} // namespace RealEngine
