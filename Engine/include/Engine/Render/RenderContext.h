#pragma once

#include "Engine/Core/Base.h"

namespace RealEngine {

// Owns the graphics context / swap chain associated with a window. Backend
// specific; created via the factory below so callers stay backend agnostic.
class RenderContext {
public:
    virtual ~RenderContext() = default;

    // Makes the context current and initialises the function loader.
    virtual void Init() = 0;

    // Presents the rendered back buffer to the window.
    virtual void SwapBuffers() = 0;

    // windowHandle is a native window pointer (GLFWwindow*).
    static Scope<RenderContext> Create(void* windowHandle);
};

} // namespace RealEngine
