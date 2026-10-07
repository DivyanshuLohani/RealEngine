cmake_minimum_required(VERSION 3.20)

project(RealEngine
    VERSION 0.1.0
    DESCRIPTION "A cross-platform game engine with a pluggable rendering backend"
    LANGUAGES C CXX)

# ---------------------------------------------------------------------------
# Global settings
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# Predictable output folders (bin/ and lib/ inside the build tree).
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(RE_BUILD_SANDBOX       "Build the Sandbox demo application" ON)
option(RE_PREFER_SYSTEM_LIBS  "Prefer libraries already installed on the system" ON)

set(RE_RENDERER_BACKEND "OpenGL" CACHE STRING "Rendering backend to compile in")
set_property(CACHE RE_RENDERER_BACKEND PROPERTY STRINGS OpenGL)

if(RE_RENDERER_BACKEND STREQUAL "OpenGL")
    set(RE_RENDERER_OPENGL ON)
else()
    message(FATAL_ERROR "Unsupported RE_RENDERER_BACKEND '${RE_RENDERER_BACKEND}'. Only 'OpenGL' is implemented so far.")
endif()

# ---------------------------------------------------------------------------
# Helpers + third-party dependencies
# ---------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CompilerWarnings)
include(Dependencies)

# ---------------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------------
add_subdirectory(Engine)

if(RE_BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif()

message(STATUS "----------------------------------------------------------------")
message(STATUS "RealEngine ${PROJECT_VERSION} configured")
message(STATUS "  Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Renderer backend : ${RE_RENDERER_BACKEND}")
message(STATUS "  Build sandbox    : ${RE_BUILD_SANDBOX}")
message(STATUS "----------------------------------------------------------------")
