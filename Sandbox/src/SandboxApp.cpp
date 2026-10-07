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

    float vertices[] = {
        // Position          // Color
        0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // Top    - Red
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Left   - Green
        0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Right  - Blue
    };

    // Create vertex buffer
    auto vertexBuffer = RealEngine::VertexBuffer::Create(vertices, sizeof(vertices));

    // Tell the engine what the vertex data looks like
    RealEngine::BufferLayout layout = {{RealEngine::ShaderDataType::Float3, "a_Position"},
                                       {RealEngine::ShaderDataType::Float3, "a_Color"}};

    vertexBuffer->SetLayout(layout);

    // Create VAO
    m_VertexArray = RealEngine::VertexArray::Create();

    // Attach VBO to VAO
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // Create shader
    const std::string vertexSource = R"(
        #version 460 core

        layout(location = 0) in vec2 a_Position;
        layout(location = 1) in vec3 a_Color;
        out vec3 v_color;

        void main()
        {
            gl_Position = vec4(a_Position, 0.0, 1.0);
            v_color = a_Color;
        }
    )";

    const std::string fragmentSource = R"(
        #version 460 core

        out vec4 FragColor;
        in vec3 v_color;

        void main()
        {
            FragColor = vec4(v_color, 1.0);
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
    RE_INFO("Event received: {0}", e.ToString());

    dispatcher.Dispatch<RealEngine::KeyPressedEvent>([](RealEngine::KeyPressedEvent& event) {
        RE_INFO("Key pressed: {0} )", event.GetKeyCode());
        if (event.GetKeyCode() == RealEngine::Key::Escape) {
            RE_INFO("Escape pressed - requesting close");
            RealEngine::Application::Get().Close();
            return true;
        }

        return false;
    });
}
