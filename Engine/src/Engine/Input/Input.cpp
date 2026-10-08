#include "Engine/Input/Input.h"

namespace RealEngine {

glm::vec2 Input::s_LastMousePosition = {0.0f, 0.0f};
glm::vec2 Input::s_MouseDelta = {0.0f, 0.0f};

bool Input::IsKeyPressed(KeyCode key) {
    return IsKeyPressedImpl(key);
}

bool Input::IsMouseButtonPressed(MouseCode button) {
    return IsMouseButtonPressedImpl(button);
}

glm::vec2 Input::GetMousePosition() {
    return GetMousePositionImpl();
}

float Input::GetMouseX() {
    return GetMousePosition().x;
}

float Input::GetMouseY() {
    return GetMousePosition().y;
}

glm::vec2 Input::GetMouseDelta() {
    return s_MouseDelta;
}

void Input::Update() {
    glm::vec2 currentPosition = GetMousePositionImpl();

    s_MouseDelta = currentPosition - s_LastMousePosition;

    s_LastMousePosition = currentPosition;
}

} // namespace RealEngine
