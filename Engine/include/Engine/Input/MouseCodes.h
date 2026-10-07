#pragma once

#include "Engine/Core/Base.h"

namespace RealEngine {

using MouseCode = uint16_t;

// Values mirror GLFW's mouse button indices.
namespace Mouse {

    enum : MouseCode {
        Button0 = 0, Button1, Button2, Button3,
        Button4, Button5, Button6, Button7,

        ButtonLast   = Button7,
        ButtonLeft   = Button0,
        ButtonRight  = Button1,
        ButtonMiddle = Button2
    };

} // namespace Mouse

} // namespace RealEngine
