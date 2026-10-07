#include "SandboxApp.h"

#include "Engine/Core/Log.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Input/KeyCodes.h"
#include "Engine/Render/Renderer.h"

#include <cmath>

SandboxApp::SandboxApp() {
    RE_INFO("SandboxApp created");
}

SandboxApp::~SandboxApp() {
    RE_INFO("SandboxApp destroyed");
}

void SandboxApp::OnUpdate(RealEngine::Timestep ts) {
    // Animate the clear colour so it is obvious the render loop is running.
    static float elapsed = 0.0f;
    elapsed += ts.GetSeconds();

    const float r = 0.5f + 0.5f * std::sin(elapsed * 1.0f);
    const float g = 0.5f + 0.5f * std::sin(elapsed * 1.3f + 2.0f);
    const float b = 0.5f + 0.5f * std::sin(elapsed * 1.7f + 4.0f);

    RealEngine::Renderer::SetClearColor(r, g, b, 1.0f);
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
