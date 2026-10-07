#pragma once

#include "Render/RendererAPI.h"
#include <cstdint>

namespace RealEngine {

// OpenGL implementation of the low-level renderer API.
class OpenGLRendererAPI : public RendererAPI {
public:
    void Init() override;
    void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    void SetClearColor(float r, float g, float b, float a) override;
    void DrawArrays(uint32_t vertexCount) override;
    void DrawIndexed(uint32_t indexCount, uint32_t indexType = 0) override;
    void Clear() override;
};

} // namespace RealEngine
