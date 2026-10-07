#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>

// ---------------------------------------------------------------------------
// Platform detection
// ---------------------------------------------------------------------------
#if defined(_WIN32)
    #define RE_PLATFORM_WINDOWS 1
#elif defined(__linux__)
    #define RE_PLATFORM_LINUX 1
#elif defined(__APPLE__)
    #define RE_PLATFORM_MACOS 1
#else
    #error "RealEngine: unsupported platform"
#endif

// ---------------------------------------------------------------------------
// Import/export decoration (meaningful once the engine is built as a DLL).
// ---------------------------------------------------------------------------
#if defined(RE_PLATFORM_WINDOWS) && defined(RE_BUILD_SHARED)
    #define RE_API __declspec(dllexport)
#else
    #define RE_API
#endif

// ---------------------------------------------------------------------------
// Utility macros
// ---------------------------------------------------------------------------
#define BIT(x) (1u << (x))

#define RE_BIND_EVENT_FN(fn)                                    \
    [this](auto&&... args) -> decltype(auto) {                  \
        return this->fn(std::forward<decltype(args)>(args)...); \
    }

namespace RealEngine {

// Unique ownership
template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Shared ownership
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace RealEngine
