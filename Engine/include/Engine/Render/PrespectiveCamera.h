#pragma once

#include <glm/glm.hpp>

namespace RealEngine {

class PrespectiveCamera {
public:
    PrespectiveCamera(float fov, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);

    void SetProjection(float fov, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec3& GetRotation() const { return m_Rotation; }

    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    glm::vec3 GetForwardDirection() const;
    glm::vec3 GetRightDirection() const;
    glm::vec3 GetUpDirection() const;

private:
    void RecalculateViewMatrix();

private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Rotation = {0.0f, 0.0f, 0.0f}; // Pitch (X), Yaw (Y), Roll (Z) in degrees
};

} // namespace RealEngine
