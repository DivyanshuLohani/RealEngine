#include "Core/Time.h"

#include <chrono>

namespace RealEngine {

static const auto s_StartTime = std::chrono::high_resolution_clock::now();

Timestep Time::s_DeltaTime = 0.0f;

float Time::GetTime() {
    const auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(now - s_StartTime).count();
}

void Time::Update(Timestep dt) {
    s_DeltaTime = dt;
}

} // namespace RealEngine
