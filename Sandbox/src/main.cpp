#include <Core/EntryPoint.h>

#include "SandboxApp.h"

// Entry point: the engine's EntryPoint.h provides main(), which calls this.
RealEngine::Application* RealEngine::CreateApplication() {
    return new SandboxApp();
}
