#include "SandboxApp.h"

SandboxApp::SandboxApp()
    : m_Camera(45.0f,
               (float)RealEngine::Application::Get().GetWindow().GetWidth() /
                   (float)RealEngine::Application::Get().GetWindow().GetHeight(),
               0.1f, 100.0f) {
    RE_INFO("SandboxApp created");
    float vertices[] = {// Front face (+Z)
                        // Position              Color             UV
                        -0.5f, -0.5f, 0.5f, 1, 0, 0, 0, 0, 0.5f, -0.5f, 0.5f, 0, 1, 0, 1, 0, 0.5f, 0.5f, 0.5f, 0, 0, 1,
                        1, 1, -0.5f, 0.5f, 0.5f, 1, 1, 0, 0, 1,

                        // Back face (-Z)
                        -0.5f, -0.5f, -0.5f, 1, 0, 0, 1, 0, -0.5f, 0.5f, -0.5f, 0, 1, 0, 1, 1, 0.5f, 0.5f, -0.5f, 0, 0,
                        1, 0, 1, 0.5f, -0.5f, -0.5f, 1, 1, 0, 0, 0,

                        // Left face (-X)
                        -0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 0, -0.5f, -0.5f, 0.5f, 0, 1, 0, 1, 0, -0.5f, 0.5f, 0.5f, 0, 0,
                        1, 1, 1, -0.5f, 0.5f, -0.5f, 1, 1, 0, 0, 1,

                        // Right face (+X)
                        0.5f, -0.5f, 0.5f, 1, 0, 0, 0, 0, 0.5f, -0.5f, -0.5f, 0, 1, 0, 1, 0, 0.5f, 0.5f, -0.5f, 0, 0, 1,
                        1, 1, 0.5f, 0.5f, 0.5f, 1, 1, 0, 0, 1,

                        // Top face (+Y)
                        -0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 0, 0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0, 0.5f, 0.5f, -0.5f, 0, 0, 1,
                        1, 1, -0.5f, 0.5f, -0.5f, 1, 1, 0, 0, 1,

                        // Bottom face (-Y)
                        -0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 0, 0.5f, -0.5f, -0.5f, 0, 1, 0, 1, 0, 0.5f, -0.5f, 0.5f, 0, 0,
                        1, 1, 1, -0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1};

    auto vertexBuffer = RealEngine::VertexBuffer::Create(vertices, sizeof(vertices));

    RealEngine::BufferLayout layout = {{RealEngine::ShaderDataType::Float3, "a_Position"},
                                       {RealEngine::ShaderDataType::Float3, "a_Color"},
                                       {RealEngine::ShaderDataType::Float2, "a_TexCoord"}};

    vertexBuffer->SetLayout(layout);

    m_VertexArray = RealEngine::VertexArray::Create();
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[] = {// Front
                          0, 1, 2, 2, 3, 0,

                          // Back
                          4, 5, 6, 6, 7, 4,

                          // Left
                          8, 9, 10, 10, 11, 8,

                          // Right
                          12, 13, 14, 14, 15, 12,

                          // Top
                          16, 17, 18, 18, 19, 16,

                          // Bottom
                          20, 21, 22, 22, 23, 20};

    auto indexBuffer = RealEngine::IndexBuffer::Create(indices, 2 * sizeof(indices) / sizeof(uint32_t));
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

    if (m_AutoAnimateCamera) {
        float time = static_cast<float>(RealEngine::Time::GetTime());
        m_CameraPosition.x = std::sin(time) * 2.0f;
        m_CameraPosition.z = std::cos(time) * 2.0f;
        m_CameraRotation.y = -glm::degrees(time);
    }

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    m_Texture->Bind(0);
    m_Shader->SetInt("u_Texture", 0);

    m_Shader->SetMat4("u_Transform", m_transform);
    m_Shader->SetMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

    RealEngine::Renderer::DrawIndexed(m_VertexArray->GetIndexBuffer()->GetCount());

    // Camera Movement
    if (RealEngine::Input::IsKeyPressed(RealEngine::Key::W)) {
        m_CameraPosition += m_Camera.GetForwardDirection() * m_CameraMoveSpeed * ts.GetSeconds();
    } else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::S)) {
        m_CameraPosition -= m_Camera.GetForwardDirection() * m_CameraMoveSpeed * ts.GetSeconds();
    } else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::A)) {
        m_CameraPosition -= m_Camera.GetRightDirection() * m_CameraMoveSpeed * ts.GetSeconds();
    } else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::D)) {
        m_CameraPosition += m_Camera.GetRightDirection() * m_CameraMoveSpeed * ts.GetSeconds();
    } else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::Q)) {
        m_CameraPosition -= m_Camera.GetUpDirection() * m_CameraMoveSpeed * ts.GetSeconds();
    } else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::E)) {
        m_CameraPosition += m_Camera.GetUpDirection() * m_CameraMoveSpeed * ts.GetSeconds();
    }
    if (RealEngine::Input::IsMouseButtonPressed(RealEngine::Mouse::ButtonLeft)) {
        glm::vec2 mouseDelta = RealEngine::Input::GetMouseDelta();

        m_CameraRotation.y += mouseDelta.x * m_CameraRotateSpeed * ts.GetSeconds();
        m_CameraRotation.x -= mouseDelta.y * m_CameraRotateSpeed * ts.GetSeconds();
    }
}

void SandboxApp::OnImGuiRender() {
    ImGui::Begin("Demo / Settings");
    ImGui::Text("Application runtime: %.2f s", RealEngine::Time::GetTime());
    ImGui::Text("Frametime: %.3f ms (%.1f FPS)", RealEngine::Time::GetDeltaTime().GetMilliseconds(),
                1.0f / (RealEngine::Time::GetDeltaTime().GetSeconds() > 0.0f
                            ? RealEngine::Time::GetDeltaTime().GetSeconds()
                            : 0.001f));

    ImGui::Separator();
    ImGui::Text("Perspective Camera Controls");
    ImGui::Checkbox("Auto Orbit Camera", &m_AutoAnimateCamera);

    if (ImGui::SliderFloat("FOV", &m_CameraFOV, 10.0f, 120.0f)) {
        float aspect = (float)RealEngine::Application::Get().GetWindow().GetWidth() /
                       (float)RealEngine::Application::Get().GetWindow().GetHeight();
        m_Camera.SetProjection(m_CameraFOV, aspect, 0.1f, 100.0f);
    }

    ImGui::DragFloat3("Position", &m_CameraPosition.x, 0.05f);
    ImGui::DragFloat3("Rotation (Pitch/Yaw/Roll)", &m_CameraRotation.x, 1.0f, -180.0f, 180.0f, "%.1f deg");
    ImGui::DragFloat("Move Speed", &m_CameraMoveSpeed, 0.1f, 0.1f, 10.0f);
    ImGui::DragFloat("Rotate Speed", &m_CameraRotateSpeed, 1);

    if (ImGui::Button("Reset Camera")) {
        m_CameraPosition = {0.0f, 0.0f, 3.0f};
        m_CameraRotation = {0.0f, 0.0f, 0.0f};
        m_CameraFOV = 45.0f;
        m_AutoAnimateCamera = false;
        float aspect = (float)RealEngine::Application::Get().GetWindow().GetWidth() /
                       (float)RealEngine::Application::Get().GetWindow().GetHeight();
        m_Camera.SetProjection(m_CameraFOV, aspect, 0.1f, 100.0f);
    }

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
