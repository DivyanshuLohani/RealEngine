#pragma once

// Include this header in exactly one translation unit of the client application
// (typically main.cpp). It provides the program entry point.

#include "Core/Application.h"
#include "Core/Log.h"

int main(int /*argc*/, char** /*argv*/) {
    RealEngine::Log::Init();
    RE_CORE_INFO("RealEngine initialising...");

    RealEngine::Application* app = RealEngine::CreateApplication();
    app->Run();
    delete app;

    RE_CORE_INFO("RealEngine shut down cleanly");
    return 0;
}
