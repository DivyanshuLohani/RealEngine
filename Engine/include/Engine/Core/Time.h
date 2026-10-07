#pragma once

#include "Core/Base.h"
#include "Core/Timestep.h"

namespace RealEngine {

class RE_API Time {
public:
    static float GetTime(); // Time in seconds since application started
    static Timestep GetDeltaTime() { return s_DeltaTime; }

private:
    static void Update(Timestep dt);

    static Timestep s_DeltaTime;

    friend class Application;
};

} // namespace RealEngine
