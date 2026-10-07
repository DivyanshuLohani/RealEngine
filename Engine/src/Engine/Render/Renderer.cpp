#include "Render/Renderer.h"

#include "Core/Assert.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace RealEngine {

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
Scope<RendererAPI> Renderer::s_RendererAPI = nullptr;

void Renderer::Init() {
    RE_CORE_ASSERT(!s_RendererAPI, "Renderer is already initialised");

#ifdef RE_RENDERER_OPENGL
    s_RendererAPI = CreateScope<OpenGLRendererAPI>();
    RendererAPI::SetAPI(RendererAPI::API::OpenGL);
#else
    RE_CORE_ASSERT(false, "No renderer backend selected at build time");
#endif

    s_RendererAPI->Init();
}

void Renderer::Shutdown() {
    s_RendererAPI.reset();
}

void Renderer::BeginFrame() {}

void Renderer::EndFrame() {}

void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    s_RendererAPI->SetViewport(x, y, width, height);
}

void Renderer::SetClearColor(float r, float g, float b, float a) {
    s_RendererAPI->SetClearColor(r, g, b, a);
}

void Renderer::SetClearColor(const glm::vec4& color) {
    s_RendererAPI->SetClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::DrawArrays(uint32_t vertexCount) {
    s_RendererAPI->DrawArrays(vertexCount);
}

void Renderer::DrawIndexed(uint32_t indexCount) {
    s_RendererAPI->DrawIndexed(indexCount, 0);
}

void Renderer::DrawArrays(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) {
    vertexArray->Bind();
    s_RendererAPI->DrawArrays(vertexCount);
}

void Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
    vertexArray->Bind();
    s_RendererAPI->DrawIndexed(indexCount, 0);
}

void Renderer::Clear() {
    s_RendererAPI->Clear();
}

} // namespace RealEngine
