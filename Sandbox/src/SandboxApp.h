#pragma once

#include <RealEngine.h>

class SandboxApp : public RealEngine::Application {
public:
    SandboxApp();
    ~SandboxApp() override;

    void OnUpdate(RealEngine::Timestep ts) override;
    void OnEvent(RealEngine::Event& e) override;

private:
    RealEngine::Ref<RealEngine::VertexArray> m_VertexArray;
    RealEngine::Ref<RealEngine::Shader> m_Shader;
    RealEngine::Ref<RealEngine::Texture2D> m_Texture;
    glm::mat4 m_transform;
};
