#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Input/KeyCodes.h"
#include "Engine/Input/MouseCodes.h"

#include <glm/vec2.hpp>

namespace RealEngine {

class Input {
public:
    static bool IsKeyPressed(KeyCode key);

    static bool IsMouseButtonPressed(MouseCode button);

    static glm::vec2 GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();
    static glm::vec2 GetMouseDelta();

    static void Update();

private:
    static bool IsKeyPressedImpl(KeyCode key);
    static bool IsMouseButtonPressedImpl(MouseCode button);

    static glm::vec2 GetMousePositionImpl();

    static glm::vec2 s_LastMousePosition;
    static glm::vec2 s_MouseDelta;
};

} // namespace RealEngine
