#pragma once

#include "Engine/Render/RenderContext.h"
#include "Engine/Window/Window.h"

struct GLFWwindow;

namespace RealEngine {

// GLFW-backed window. This is the only place (besides the input layer) that
// touches GLFW directly.
class GLFWWindow : public Window {
public:
    explicit GLFWWindow(const WindowProps& props);
    ~GLFWWindow() override;

    void OnUpdate() override;

    uint32_t GetWidth() const override { return m_Data.Width; }
    uint32_t GetHeight() const override { return m_Data.Height; }

    void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override { return m_Data.VSync; }

    void* GetNativeWindow() const override { return m_Window; }

private:
    void Init(const WindowProps& props);
    void Shutdown();

    // Keyboard / mouse callbacks (defined in GLFWWindowCallbacks.cpp).
    void RegisterInputCallbacks();

    GLFWwindow* m_Window = nullptr;
    Scope<RenderContext> m_Context;

    struct WindowData {
        std::string Title;
        uint32_t Width = 0;
        uint32_t Height = 0;
        bool VSync = true;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

} // namespace RealEngine
