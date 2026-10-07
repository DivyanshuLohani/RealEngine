#pragma once

#include "Core/Base.h"

#include <ostream>
#include <string>

namespace RealEngine {

// ---------------------------------------------------------------------------
// Event types. Add new ones here as the engine grows.
// ---------------------------------------------------------------------------
enum class EventType {
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum EventCategory {
    EventCategoryNone = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

// Generates the static + virtual type identification for a concrete event.
#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType GetStaticType() {                                                                                 \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    EventType GetEventType() const override {                                                                          \
        return GetStaticType();                                                                                        \
    }                                                                                                                  \
    const char* GetName() const override {                                                                             \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    int GetCategoryFlags() const override {                                                                            \
        return category;                                                                                               \
    }

class Event {
public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }
};

// Dispatches an event to the first matching handler.
class EventDispatcher {
public:
    EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T, typename F> bool Dispatch(const F& func) {
        if (m_Event.GetEventType() == T::GetStaticType()) {
            m_Event.Handled |= func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }

private:
    Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    return os << e.ToString();
}

} // namespace RealEngine
