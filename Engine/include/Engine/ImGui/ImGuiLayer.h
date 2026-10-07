#pragma once

#include "Core/Base.h"

namespace RealEngine {

class RE_API ImGuiLayer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void Init();
    void Shutdown();

    void Begin();
    void End();

    void SetBlockEvents(bool block) { m_BlockEvents = block; }

private:
    bool m_BlockEvents = true;
};

} // namespace RealEngine
