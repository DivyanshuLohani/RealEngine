#pragma once

#include "Engine/Render/Shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

namespace RealEngine {

class OpenGLShader : public Shader {
private:
    GLuint m_RendererID = 0;
    std::string m_Name;

public:
    OpenGLShader(const std::string& filepath);

    OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

    ~OpenGLShader() override;

    void Bind() const override { glad_glUseProgram(m_RendererID); }

    void Unbind() const override { glad_glUseProgram(0); }

    void SetInt(const std::string& name, int value) override {
        glad_glUniform1i(glad_glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void SetFloat(const std::string& name, float value) override {
        glad_glUniform1f(glad_glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void SetFloat2(const std::string& name, const glm::vec2& value) override {
        glad_glUniform2f(glad_glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y);
    }

    void SetFloat3(const std::string& name, const glm::vec3& value) override {
        glad_glUniform3f(glad_glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z);
    }

    void SetFloat4(const std::string& name, const glm::vec4& value) override {
        glad_glUniform4f(glad_glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void SetMat3(const std::string& name, const glm::mat3& value) override {
        glad_glUniformMatrix3fv(glad_glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    void SetMat4(const std::string& name, const glm::mat4& value) override {
        glad_glUniformMatrix4fv(glad_glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

    const std::string& GetName() const override { return m_Name; }
};

} // namespace RealEngine
