#include "Engine/Render/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RealEngine {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) {
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

    RecalculateViewMatrix();
}

void OrthographicCamera::SetPosition(const glm::vec3& position) {
    m_Position = position;
    RecalculateViewMatrix();
}

void OrthographicCamera::SetRotation(float rotation) {
    m_Rotation = rotation;
    RecalculateViewMatrix();
}

const glm::vec3& OrthographicCamera::GetPosition() const {
    return m_Position;
}

float OrthographicCamera::GetRotation() const {
    return m_Rotation;
}

const glm::mat4& OrthographicCamera::GetViewMatrix() const {
    return m_ViewMatrix;
}

const glm::mat4& OrthographicCamera::GetProjectionMatrix() const {
    return m_ProjectionMatrix;
}

const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const {
    return m_ViewProjectionMatrix;
}

void OrthographicCamera::RecalculateViewMatrix() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    m_ViewMatrix = glm::inverse(transform);

    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

} // namespace RealEngine
