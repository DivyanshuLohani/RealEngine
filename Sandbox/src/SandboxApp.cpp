#include "SandboxApp.h"

SandboxApp::SandboxApp() {
    RE_INFO("SandboxApp created");

    float vertices[] = {
        // Position              // Color
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // Top right
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // Top left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom left
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // Bottom right
    };

    auto vertexBuffer = RealEngine::VertexBuffer::Create(vertices, sizeof(vertices));

    RealEngine::BufferLayout layout = {{RealEngine::ShaderDataType::Float3, "a_Position"},
                                       {RealEngine::ShaderDataType::Float3, "a_Color"}};

    vertexBuffer->SetLayout(layout);

    m_VertexArray = RealEngine::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};

    auto indexBuffer = RealEngine::IndexBuffer::Create(indices, 6);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    RE_TRACE("Vertex array created with {} vertices and {} indices",
             vertexBuffer->GetLayout().GetStride() / sizeof(float), indexBuffer->GetCount());

    // Create shader
    m_Shader = RealEngine::Shader::Create("Assets/Shaders/default.glsl");
    m_Shader->Bind();
    m_Shader->SetFloat2("u_resolution", {(float)RealEngine::Application::Get().GetWindow().GetWidth(),
                                         (float)RealEngine::Application::Get().GetWindow().GetHeight()});
    RE_INFO("Triangle resources created");
}

SandboxApp::~SandboxApp() {
    RE_INFO("SandboxApp destroyed");
}

void SandboxApp::OnUpdate(RealEngine::Timestep ts) {
    m_VertexArray->Bind();
    m_Shader->Bind();

    m_Shader->SetFloat("u_time", (float)RealEngine::Time::GetTime());

    RealEngine::Renderer::DrawIndexed(m_VertexArray->GetIndexBuffer()->GetCount());
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

    dispatcher.Dispatch<RealEngine::WindowCloseEvent>([](RealEngine::WindowCloseEvent& event) {
        RE_INFO("Window close event received - requesting close");
        RealEngine::Application::Get().Close();
        return true;
    });
}
