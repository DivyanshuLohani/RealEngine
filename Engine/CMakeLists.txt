# ---------------------------------------------------------------------------
# RealEngine - the engine static library
# ---------------------------------------------------------------------------

set(RE_ENGINE_SOURCES
    src/Engine/Core/Application.cpp
    src/Engine/Core/Log.cpp

    src/Engine/Window/Window.cpp
    src/Engine/Window/GLFWWindow.cpp
    src/Engine/Window/GLFWWindowCallbacks.cpp

    src/Engine/Render/RenderContext.cpp
    src/Engine/Render/Renderer.cpp

    src/Engine/Platform/OpenGL/OpenGLContext.cpp
    src/Engine/Platform/OpenGL/OpenGLRendererAPI.cpp
)

add_library(RealEngine STATIC ${RE_ENGINE_SOURCES})

# Public headers define the engine API; src/ holds private headers + the backend.
target_include_directories(RealEngine
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(RealEngine
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        glfw
        glad_gl_core_46)

# glad loads GL entry points via glfwGetProcAddress, so opengl32 is only needed
# on Windows for the GLFW/driver linkage.
if(WIN32)
    target_link_libraries(RealEngine PRIVATE opengl32)
endif()

target_compile_definitions(RealEngine PUBLIC
    $<$<BOOL:${RE_RENDERER_OPENGL}>:RE_RENDERER_OPENGL=1>)

re_set_warnings(RealEngine)
