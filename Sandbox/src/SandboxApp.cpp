#include "SandboxApp.h"

#include "Engine/Core/Log.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Input/KeyCodes.h"
#include "Engine/Render/Buffer.h"
#include "Engine/Render/Renderer.h"
#include "Engine/Render/Shader.h"
#include "Engine/Render/VertexArray.h"

SandboxApp::SandboxApp() {
    RE_INFO("SandboxApp created");

    float vertices[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};

    // Create vertex buffer
    auto vertexBuffer = RealEngine::VertexBuffer::Create(vertices, sizeof(vertices));

    // Tell the engine what the vertex data looks like
    RealEngine::BufferLayout layout = {{RealEngine::ShaderDataType::Float2, "a_Position"}};

    vertexBuffer->SetLayout(layout);

    // Create VAO
    m_VertexArray = RealEngine::VertexArray::Create();

    // Attach VBO to VAO
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // Create shader
    const std::string vertexSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        out vec2 v_Pos;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
        }
    )";

    const std::string fragmentSource = R"(
        #version 460 core

        out vec4 FragColor;
        in vec2 v_Pos;

        void main()
        {
            FragColor = vec4(0.2, 0.3, 0.8, 1.0);
        }
    )";

    m_Shader = RealEngine::Shader::Create("Triangle", vertexSource, fragmentSource);

    RE_INFO("Triangle resources created");
}

SandboxApp::~SandboxApp() {
    RE_INFO("SandboxApp destroyed");
}

void SandboxApp::OnUpdate(RealEngine::Timestep ts) {
    m_VertexArray->Bind();
    m_Shader->Bind();

    RealEngine::Renderer::DrawArrays(3);
}

void SandboxApp::OnEvent(RealEngine::Event& e) {
    RealEngine::EventDispatcher dispatcher(e);

    dispatcher.Dispatch<RealEngine::KeyPressedEvent>([](RealEngine::KeyPressedEvent& event) {
        if (event.GetKeyCode() == RealEngine::Key::Escape) {
            RE_INFO("Escape pressed - requesting close");
            RealEngine::Application::Get().Close();
            return true;
        }

        return false;
    });
}
