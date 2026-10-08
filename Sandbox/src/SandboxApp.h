#pragma once

#include <RealEngine.h>

class SandboxApp : public RealEngine::Application {
public:
    SandboxApp();
    ~SandboxApp() override;

    void OnUpdate(RealEngine::Timestep ts) override;
    void OnImGuiRender() override;
    void OnAppEvent(RealEngine::Event& e) override;

private:
    RealEngine::Ref<RealEngine::VertexArray> m_VertexArray;
    RealEngine::Ref<RealEngine::Shader> m_Shader;
    RealEngine::Ref<RealEngine::Texture2D> m_Texture;
    glm::mat4 m_transform;

    RealEngine::PrespectiveCamera m_Camera;
    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 3.0f};
    glm::vec3 m_CameraRotation = {0.0f, 0.0f, 0.0f};
    float m_CameraFOV = 45.0f;
    bool m_AutoAnimateCamera = false;

    float m_CameraMoveSpeed = 2.0f;
    float m_CameraRotateSpeed = 90.0f; // degrees per second
};
