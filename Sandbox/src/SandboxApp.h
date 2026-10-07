#pragma once

#include "Engine/Core/Application.h"

// Minimal demo application: opens a window and animates the clear colour to
// prove the window + render loop + event system are all wired up.
class SandboxApp : public RealEngine::Application {
public:
    SandboxApp();
    ~SandboxApp() override;

    void OnUpdate(RealEngine::Timestep ts) override;
    void OnEvent(RealEngine::Event& e) override;
};
