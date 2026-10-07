# ---------------------------------------------------------------------------
# RealEngine - the engine static library
# ---------------------------------------------------------------------------

file(GLOB_RECURSE RE_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(RealEngine STATIC ${RE_ENGINE_SOURCES})

target_include_directories(RealEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Engine
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine
)

target_link_libraries(RealEngine
    PUBLIC
        glm::glm
        spdlog::spdlog
    PRIVATE
        glfw
        glad_gl_core_46
)

if(WIN32)
    target_link_libraries(RealEngine PRIVATE opengl32)
endif()

target_compile_definitions(RealEngine PUBLIC
    $<$<BOOL:${RE_RENDERER_OPENGL}>:RE_RENDERER_OPENGL=1>
)

re_set_warnings(RealEngine)
