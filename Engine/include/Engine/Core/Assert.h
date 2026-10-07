#pragma once

#include "Core/Log.h"

#include <csignal>

// ---------------------------------------------------------------------------
// Assertions: enabled in Debug builds only (NDEBUG is defined for Release).
// ---------------------------------------------------------------------------
#if defined(RE_PLATFORM_WINDOWS)
#define RE_DEBUGBREAK() __debugbreak()
#else
#define RE_DEBUGBREAK() std::raise(SIGTRAP)
#endif

#if !defined(NDEBUG)
#define RE_ENABLE_ASSERTS
#endif

#ifdef RE_ENABLE_ASSERTS
#define RE_ASSERT(x, ...)                                                                                              \
    do {                                                                                                               \
        if (!(x)) {                                                                                                    \
            RE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                            \
            RE_DEBUGBREAK();                                                                                           \
        }                                                                                                              \
    } while (0)

#define RE_CORE_ASSERT(x, ...)                                                                                         \
    do {                                                                                                               \
        if (!(x)) {                                                                                                    \
            RE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                       \
            RE_DEBUGBREAK();                                                                                           \
        }                                                                                                              \
    } while (0)
#else
#define RE_ASSERT(x, ...)
#define RE_CORE_ASSERT(x, ...)
#endif
