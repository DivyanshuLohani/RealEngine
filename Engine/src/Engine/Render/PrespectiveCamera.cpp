#include "Render/PrespectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RealEngine {

PrespectiveCamera::PrespectiveCamera(float fov, float aspectRatio, float nearClip, float farClip) {
    SetProjection(fov, aspectRatio, nearClip, farClip);
    RecalculateViewMatrix();
}

void PrespectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip) {
    m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PrespectiveCamera::SetPosition(const glm::vec3& position) {
    m_Position = position;
    RecalculateViewMatrix();
}

void PrespectiveCamera::SetRotation(const glm::vec3& rotation) {
    m_Rotation = rotation;
    RecalculateViewMatrix();
}

void PrespectiveCamera::RecalculateViewMatrix() {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                         glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                         glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * rotation;

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

glm::vec3 PrespectiveCamera::GetForwardDirection() const {
    return glm::normalize(glm::vec3(glm::inverse(m_ViewMatrix)[2]));
}

glm::vec3 PrespectiveCamera::GetRightDirection() const {
    return glm::normalize(glm::vec3(glm::inverse(m_ViewMatrix)[0]));
}

glm::vec3 PrespectiveCamera::GetUpDirection() const {
    return glm::normalize(glm::vec3(glm::inverse(m_ViewMatrix)[1]));
}

} // namespace RealEngine
