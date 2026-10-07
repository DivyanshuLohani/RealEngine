#include "Engine/Core/Application.h"

#include "Engine/Core/Assert.h"
#include "Engine/Core/Log.h"
#include "Engine/Render/Renderer.h"

#include <chrono>

namespace RealEngine {

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& name) {
    RE_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = Scope<Window>(Window::Create(WindowProps(name)));
    m_Window->SetEventCallback(RE_BIND_EVENT_FN(OnEvent));

    Renderer::Init();
    Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

    m_Window->SetVSync(true);
}

Application::~Application() {
    Renderer::Shutdown();
}

void Application::Run() {
    using Clock = std::chrono::high_resolution_clock;

    auto lastFrameTime = Clock::now();

    while (m_Running) {
        const auto now = Clock::now();
        const Timestep ts(std::chrono::duration<float>(now - lastFrameTime).count());
        lastFrameTime = now;

        const Timestep dt = 1 / m_PhysicsFrameRate;

        Renderer::Clear();

        if (!m_Minimized)
            OnUpdate(ts);

        if (!m_Minimized)
            OnFixedUpdate(dt);

        // Poll OS events and present the frame.
        m_Window->OnUpdate();
    }
}

void Application::Close() {
    m_Running = false;
}

bool Application::OnWindowClose(WindowCloseEvent& /*e*/) {
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e) {
    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
    return false;
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(RE_BIND_EVENT_FN(Application::OnWindowResize));
}

} // namespace RealEngine
