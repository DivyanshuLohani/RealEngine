#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Render/RendererAPI.h"

#include <glm/glm.hpp>

namespace RealEngine {

// High-level rendering facade used by application code. Delegates to the active
// RendererAPI backend, so game code never talks to a specific graphics API.
class Renderer {
public:
    static void Init();
    static void Shutdown();

    static void BeginFrame();
    static void EndFrame();

    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    static void SetClearColor(float r, float g, float b, float a = 1.0f);
    static void SetClearColor(const glm::vec4& color);

    static void DrawArrays(uint32_t vertexCount);
    static void DrawIndexed(uint32_t indexCount);

    static void Clear();

    static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
    static Scope<RendererAPI> s_RendererAPI;
};

} // namespace RealEngine
