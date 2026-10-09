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
    RealEngine::Ref<RealEngine::Texture2D> m_Texture;

    float m_CameraMoveSpeed = 2.0f;
    float m_CameraRotateSpeed = 90.0f; // degrees per second

    // 2D Camera & Mode
    RealEngine::OrthographicCamera m_Camera2D;
    glm::vec3 m_Camera2DPosition = {0.0f, 0.0f, 0.0f};
    float m_Camera2DRotation = 0.0f;
    bool m_Render2D = true;
    float m_QuadRotation = 0.0f;
};
