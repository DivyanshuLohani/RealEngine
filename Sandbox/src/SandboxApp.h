#pragma once

#include "Engine/Core/Application.h"
#include "Engine/Render/Shader.h"
#include "Engine/Render/VertexArray.h"

class SandboxApp : public RealEngine::Application {
public:
    SandboxApp();
    ~SandboxApp() override;

    void OnUpdate(RealEngine::Timestep ts) override;
    void OnEvent(RealEngine::Event& e) override;

private:
    RealEngine::Ref<RealEngine::VertexArray> m_VertexArray;
    RealEngine::Ref<RealEngine::Shader> m_Shader;
};
