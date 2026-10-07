#pragma once

namespace RealEngine {

// Time elapsed since the previous frame, in seconds. Kept as a distinct type so
// APIs that expect a duration cannot be accidentally passed a raw float.
class Timestep {
public:
    Timestep(float time = 0.0f) : m_Time(time) {}

    operator float() const { return m_Time; }

    float GetSeconds() const { return m_Time; }
    float GetMilliseconds() const { return m_Time * 1000.0f; }

private:
    float m_Time;
};

} // namespace RealEngine
