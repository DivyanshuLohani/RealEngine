#include "Core/Application.h"

#include "Core/Assert.h"
#include "Core/Log.h"
#include "Core/Time.h"
#include "ImGui/ImGuiLayer.h"
#include "Render/Renderer.h"

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

    m_ImGuiLayer = CreateScope<ImGuiLayer>();
    m_ImGuiLayer->Init();
}

Application::~Application() {
    m_ImGuiLayer->Shutdown();
    Renderer::Shutdown();
}

void Application::Run() {
    using Clock = std::chrono::high_resolution_clock;

    auto lastFrameTime = Clock::now();

    while (m_Running) {
        const auto now = Clock::now();
        const Timestep ts(std::chrono::duration<float>(now - lastFrameTime).count());
        lastFrameTime = now;

        Time::Update(ts);

        const Timestep dt = 1 / m_PhysicsFrameRate;

        Renderer::Clear();

        if (!m_Minimized)
            OnUpdate(ts);

        if (!m_Minimized)
            OnFixedUpdate(dt);

        m_ImGuiLayer->Begin();
        OnImGuiRender();
        m_ImGuiLayer->End();

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
#ifndef RE_DISABLE_TERMINATE_ON_CLOSE
    dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));
#endif
    dispatcher.Dispatch<WindowResizeEvent>(RE_BIND_EVENT_FN(Application::OnWindowResize));

    if (!e.Handled) {
        OnAppEvent(e);
    }
}

} // namespace RealEngine
