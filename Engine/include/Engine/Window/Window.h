#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Events/Event.h"
#include "Engine/Window/WindowProps.h"

#include <functional>

namespace RealEngine {

// Platform-agnostic window. The GLFW implementation lives in
// src/Engine/Window/GLFWWindow.cpp - nothing above this interface includes GLFW.
class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    // Polls OS events and presents the back buffer.
    virtual void OnUpdate() = 0;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    // Native window handle (e.g. GLFWwindow*) for the render context.
    virtual void* GetNativeWindow() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};

} // namespace RealEngine
