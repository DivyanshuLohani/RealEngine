#pragma once

#include "Engine/Core/Base.h"

namespace RealEngine {

// Low-level drawing device: viewport, clear state, and (from Phase 2) draw
// calls. One implementation exists per graphics backend. This is the seam that
// keeps the rest of the engine free of any OpenGL/Vulkan/D3D headers.
class RendererAPI {
public:
    enum class API {
        None = 0,
        OpenGL = 1,
        Vulkan = 2,
        Direct3D11 = 3
    };

    virtual ~RendererAPI() = default;

    virtual void Init() = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;
    virtual void Clear() = 0;

    // Phase 2 will add: DrawIndexed / DrawArrays / DrawLines.

    static API GetAPI() { return s_API; }
    static void SetAPI(API api) { s_API = api; }

private:
    static API s_API;
};

} // namespace RealEngine
