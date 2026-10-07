#pragma once

#include "Engine/Core/Base.h"

#include <glm/glm.hpp>

#include <string>

namespace RealEngine {

// Backend-agnostic shader program. Uniform setters are part of the public API so
// renderer code never needs to know which graphics API is underneath.
class Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetInt(const std::string& name, int value) = 0;
    virtual void SetFloat(const std::string& name, float value) = 0;
    virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
    virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
    virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

    virtual const std::string& GetName() const = 0;

    // Phase 2: static Ref<Shader> Create(const std::string& filepath);
    //          static Ref<Shader> Create(const std::string& name,
    //                                    const std::string& vertexSrc,
    //                                    const std::string& fragmentSrc);
};

} // namespace RealEngine
