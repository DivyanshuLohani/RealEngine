#include "SandboxApp.h"

SandboxApp::SandboxApp() {
    RE_INFO("SandboxApp created");
    float vertices[] = {// Position             Color              UV
                        0.5f,  0.5f,  0.0f, 1, 0, 0, 1, 1, -0.5f, 0.5f,  0.0f, 0, 1, 0, 0, 1,
                        -0.5f, -0.5f, 0.0f, 0, 0, 1, 0, 0, 0.5f,  -0.5f, 0.0f, 1, 1, 0, 1, 0};

    auto vertexBuffer = RealEngine::VertexBuffer::Create(vertices, sizeof(vertices));

    RealEngine::BufferLayout layout = {{RealEngine::ShaderDataType::Float3, "a_Position"},
                                       {RealEngine::ShaderDataType::Float3, "a_Color"},
                                       {RealEngine::ShaderDataType::Float2, "a_TexCoord"}};

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

    m_Texture = RealEngine::Texture2D::Create("Assets/Textures/wall.jpg");

    m_transform = RealEngine::CreateTransform({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
}

SandboxApp::~SandboxApp() {
    RE_INFO("SandboxApp destroyed");
}

void SandboxApp::OnUpdate(RealEngine::Timestep ts) {
    m_VertexArray->Bind();
    m_Shader->Bind();

    float time = static_cast<float>(RealEngine::Time::GetTime());

    m_Texture->Bind(0);
    m_Shader->SetInt("u_Texture", 0);

    // Circular movement
    float x = std::sin(time) * 0.5f;
    float y = std::cos(time) * 0.5f;

    m_transform = RealEngine::CreateTransform({x, y, 0.0f}, {0.0f, 0.0f, time}, {1.0f, 1.0f, 1.0f});

    m_Shader->SetMat4("u_Transform", m_transform);

    RealEngine::Renderer::DrawIndexed(m_VertexArray->GetIndexBuffer()->GetCount());
}

void SandboxApp::OnImGuiRender() {
    ImGui::Begin("Demo / Settings");
    ImGui::Text("Application runtime: %.2f s", RealEngine::Time::GetTime());
    ImGui::Text("Frametime: %.3f ms (%.1f FPS)", RealEngine::Time::GetDeltaTime().GetMilliseconds(),
                1.0f / (RealEngine::Time::GetDeltaTime().GetSeconds() > 0.0f
                            ? RealEngine::Time::GetDeltaTime().GetSeconds()
                            : 0.001f));
    ImGui::End();
}

void SandboxApp::OnAppEvent(RealEngine::Event& e) {
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
