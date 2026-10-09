#include "SandboxApp.h"

SandboxApp::SandboxApp() : m_Camera2D(-1.6f, 1.6f, -0.9f, 0.9f) {
    RE_INFO("SandboxApp created");

    m_Texture = RealEngine::Texture2D::Create("Assets/Textures/wall.jpg");
}

SandboxApp::~SandboxApp() {
    m_Texture.reset();
    RE_INFO("SandboxApp destroyed");
}

void SandboxApp::OnUpdate(RealEngine::Timestep ts) {
    if (m_Render2D) {
        RealEngine::Renderer2D::ResetStats();

        // 2D Camera controls
        if (RealEngine::Input::IsKeyPressed(RealEngine::Key::A))
            m_Camera2DPosition.x -= m_CameraMoveSpeed * ts.GetSeconds();
        else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::D))
            m_Camera2DPosition.x += m_CameraMoveSpeed * ts.GetSeconds();

        if (RealEngine::Input::IsKeyPressed(RealEngine::Key::W))
            m_Camera2DPosition.y += m_CameraMoveSpeed * ts.GetSeconds();
        else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::S))
            m_Camera2DPosition.y -= m_CameraMoveSpeed * ts.GetSeconds();

        if (RealEngine::Input::IsKeyPressed(RealEngine::Key::Q))
            m_Camera2DRotation += m_CameraRotateSpeed * ts.GetSeconds();
        else if (RealEngine::Input::IsKeyPressed(RealEngine::Key::E))
            m_Camera2DRotation -= m_CameraRotateSpeed * ts.GetSeconds();

        m_Camera2D.SetPosition(m_Camera2DPosition);
        m_Camera2D.SetRotation(m_Camera2DRotation);

        m_QuadRotation += 50.0f * ts.GetSeconds();

        RealEngine::Renderer2D::BeginScene(m_Camera2D);

        // Solid color quads
        RealEngine::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        RealEngine::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});

        // Textured quad
        RealEngine::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {1.0f, 1.0f}, m_Texture, 1.0f);

        // Rotated quads (color & textured)
        RealEngine::Renderer2D::DrawRotatedQuad({-0.5f, 0.5f}, {0.5f, 0.5f}, glm::radians(m_QuadRotation),
                                                {0.3f, 0.8f, 0.2f, 1.0f});
        RealEngine::Renderer2D::DrawRotatedQuad({1.0f, 0.5f}, {0.6f, 0.6f}, glm::radians(-m_QuadRotation), m_Texture,
                                                2.0f, {1.0f, 0.8f, 0.8f, 1.0f});

        // Grid of quads to demonstrate batch accumulation
        for (float y = -2.0f; y < 10.0f; y += 0.4f) {
            for (float x = -2.0f; x < 20.0f; x += 0.4f) {
                glm::vec4 color = {(x + 2.0f) / 4.0f, 0.4f, (y + 2.0f) / 4.0f, 0.7f};
                RealEngine::Renderer2D::DrawQuad({x, y, -0.2f}, {0.35f, 0.35f}, color);
            }
        }

        RealEngine::Renderer2D::EndScene();
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
    ImGui::Checkbox("Use 2D Batch Renderer", &m_Render2D);

    if (m_Render2D) {
        ImGui::Separator();
        ImGui::Text("2D Renderer Statistics");
        auto stats = RealEngine::Renderer2D::GetStats();
        ImGui::Text("Draw Calls:   %u", stats.DrawCalls);
        ImGui::Text("Quad Count:   %u", stats.QuadCount);
        ImGui::Text("Vertex Count: %u", stats.GetTotalVertexCount());
        ImGui::Text("Index Count:  %u", stats.GetTotalIndexCount());

        ImGui::Separator();
        ImGui::Text("2D Camera Controls (WASD / QE)");
        ImGui::DragFloat2("Camera 2D Pos", &m_Camera2DPosition.x, 0.05f);
        ImGui::DragFloat("Camera 2D Rot", &m_Camera2DRotation, 1.0f, -360.0f, 360.0f, "%.1f deg");

        if (ImGui::Button("Reset 2D Camera")) {
            m_Camera2DPosition = {0.0f, 0.0f, 0.0f};
            m_Camera2DRotation = 0.0f;
        }
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
