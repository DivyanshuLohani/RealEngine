#pragma once

#include "Engine/Core/Base.h"

#include <string>

namespace RealEngine {

struct WindowProps {
    std::string Title;
    uint32_t Width;
    uint32_t Height;
    bool VSync;

    WindowProps(const std::string& title = "RealEngine", uint32_t width = 1280, uint32_t height = 720,
                bool vsync = true)
        : Title(title), Width(width), Height(height), VSync(vsync) {}
};

} // namespace RealEngine
