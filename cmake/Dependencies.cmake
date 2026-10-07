# ---------------------------------------------------------------------------
# Third-party dependency resolution.
#
# Strategy: prefer a library that is already installed on the system, otherwise
# fetch a pinned source release with FetchContent. This keeps the project
# buildable on both Windows and Linux with no vendored source in the tree.
# ---------------------------------------------------------------------------
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# ---------------------------------------------------------------------------
# GLFW - windowing, input and OpenGL context creation
# ---------------------------------------------------------------------------
find_package(glfw3 3.3 QUIET)
if(glfw3_FOUND AND RE_PREFER_SYSTEM_LIBS)
    message(STATUS "[RealEngine] Using system GLFW (${glfw3_VERSION})")
else()
    message(STATUS "[RealEngine] Fetching GLFW 3.4")
    set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
        GIT_SHALLOW    TRUE)
    FetchContent_MakeAvailable(glfw)
endif()

# ---------------------------------------------------------------------------
# GLM - header-only math
# ---------------------------------------------------------------------------
find_package(glm QUIET)
if(glm_FOUND AND RE_PREFER_SYSTEM_LIBS)
    message(STATUS "[RealEngine] Using system GLM")
else()
    message(STATUS "[RealEngine] Fetching GLM 1.0.1")
    set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)   # header-only usage
    set(GLM_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
    set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        1.0.1
        GIT_SHALLOW    TRUE)
    FetchContent_MakeAvailable(glm)
endif()

# ---------------------------------------------------------------------------
# spdlog - logging
# ---------------------------------------------------------------------------
find_package(spdlog QUIET)
if(spdlog_FOUND AND RE_PREFER_SYSTEM_LIBS)
    message(STATUS "[RealEngine] Using system spdlog")
else()
    message(STATUS "[RealEngine] Fetching spdlog 1.15.0")
    set(SPDLOG_BUILD_EXAMPLE OFF CACHE BOOL "" FORCE)
    set(SPDLOG_BUILD_TESTS   OFF CACHE BOOL "" FORCE)
    set(SPDLOG_BUILD_BENCH   OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.15.0
        GIT_SHALLOW    TRUE)
    FetchContent_MakeAvailable(spdlog)
endif()

# ---------------------------------------------------------------------------
# glad - OpenGL function loader (glad2)
#
# glad2 has no root CMakeLists; it exposes glad_add_library() from its cmake/
# directory, so we point FetchContent at that sub-directory. The generated
# target (glad_gl_core_46) is what the OpenGL backend links against. Swapping
# the API/profile/version here is the only change needed to target, e.g.,
# GL 3.3 core or GLES.
# ---------------------------------------------------------------------------
if(RE_RENDERER_OPENGL)
    message(STATUS "[RealEngine] Fetching glad (glad2)")
    FetchContent_Declare(glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        v2.0.8
        GIT_SHALLOW    TRUE
        SOURCE_SUBDIR  cmake)
    FetchContent_MakeAvailable(glad)
    glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE API gl:core=4.6)
endif()
