#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/Event.h"
#include "Engine/Window/Window.h"

#include <string>

namespace RealEngine {

// Base class for a RealEngine application. Clients derive from it, override
// OnUpdate / OnEvent, and return an instance from CreateApplication().
class Application {
public:
    explicit Application(const std::string& name = "RealEngine App");
    virtual ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void Run();
    void Close();

    virtual void OnUpdate(Timestep ts) {}
    virtual void OnFixedUpdate(Timestep dt) {}
    virtual void OnEvent(Event& e);

    Window& GetWindow() { return *m_Window; }

    static Application& Get() { return *s_Instance; }

private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

    Scope<Window> m_Window;
    bool m_Running = true;
    bool m_Minimized = false;

    static Application* s_Instance;

    float m_PhysicsFrameRate = 60.0f; // Physics update rate in Hz
};

// Implemented by the client application (e.g. Sandbox).
Application* CreateApplication();

} // namespace RealEngine
