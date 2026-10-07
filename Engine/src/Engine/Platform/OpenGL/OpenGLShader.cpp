#include "Engine/Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace RealEngine {

OpenGLShader::OpenGLShader(const std::string& filepath) : m_RendererID(0) {
    std::ifstream file(filepath);

    if (!file.is_open())
        throw std::runtime_error("Could not open shader file: " + filepath);

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    // Find shader types
    const std::string typeToken = "#type";
    size_t pos = source.find(typeToken);

    if (pos == std::string::npos)
        throw std::runtime_error("Shader file missing #type declarations: " + filepath);

    std::unordered_map<GLenum, std::string> shaderSources;

    while (pos != std::string::npos) {
        size_t eol = source.find_first_of("\r\n", pos);
        size_t begin = pos + typeToken.size() + 1;

        std::string type = source.substr(begin, eol - begin);

        GLenum shaderType;

        if (type == "vertex")
            shaderType = GL_VERTEX_SHADER;
        else if (type == "fragment" || type == "pixel")
            shaderType = GL_FRAGMENT_SHADER;
        else
            throw std::runtime_error("Unknown shader type: " + type);

        size_t nextLine = source.find_first_not_of("\r\n", eol);
        pos = source.find(typeToken, nextLine);

        shaderSources[shaderType] =
            source.substr(nextLine, pos == std::string::npos ? source.size() - nextLine : pos - nextLine);
    }

    m_Name = filepath;

    const std::string& vertexSrc = shaderSources[GL_VERTEX_SHADER];
    const std::string& fragmentSrc = shaderSources[GL_FRAGMENT_SHADER];

    // Compile vertex shader
    GLuint vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);

    const char* vertexSource = vertexSrc.c_str();
    glad_glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glad_glCompileShader(vertexShader);

    GLint success;
    glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glad_glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);

        glad_glDeleteShader(vertexShader);

        throw std::runtime_error("Vertex shader compilation failed:\n" + std::string(infoLog));
    }

    // Compile fragment shader
    GLuint fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentSource = fragmentSrc.c_str();
    glad_glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glad_glCompileShader(fragmentShader);

    glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glad_glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);

        glad_glDeleteShader(vertexShader);
        glad_glDeleteShader(fragmentShader);

        throw std::runtime_error("Fragment shader compilation failed:\n" + std::string(infoLog));
    }

    // Create shader program
    m_RendererID = glad_glCreateProgram();

    glad_glAttachShader(m_RendererID, vertexShader);
    glad_glAttachShader(m_RendererID, fragmentShader);

    glad_glLinkProgram(m_RendererID);

    glad_glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glad_glGetProgramInfoLog(m_RendererID, 1024, nullptr, infoLog);

        glad_glDeleteShader(vertexShader);
        glad_glDeleteShader(fragmentShader);
        glad_glDeleteProgram(m_RendererID);
        m_RendererID = 0;

        throw std::runtime_error("Shader program linking failed:\n" + std::string(infoLog));
    }

    // Shaders are no longer needed after linking
    glad_glDeleteShader(vertexShader);
    glad_glDeleteShader(fragmentShader);
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    : m_RendererID(0), m_Name(name) {
    // Compile vertex shader
    GLuint vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);

    const char* vertexSource = vertexSrc.c_str();
    glad_glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glad_glCompileShader(vertexShader);

    GLint success;
    glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glad_glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);

        glad_glDeleteShader(vertexShader);

        throw std::runtime_error("Vertex shader compilation failed:\n" + std::string(infoLog));
    }

    // Compile fragment shader
    GLuint fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);

    const char* fragmentSource = fragmentSrc.c_str();
    glad_glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glad_glCompileShader(fragmentShader);

    glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glad_glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);

        glad_glDeleteShader(vertexShader);
        glad_glDeleteShader(fragmentShader);

        throw std::runtime_error("Fragment shader compilation failed:\n" + std::string(infoLog));
    }

    // Create program
    m_RendererID = glad_glCreateProgram();

    glad_glAttachShader(m_RendererID, vertexShader);
    glad_glAttachShader(m_RendererID, fragmentShader);

    glad_glLinkProgram(m_RendererID);

    glad_glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glad_glGetProgramInfoLog(m_RendererID, 1024, nullptr, infoLog);

        glad_glDeleteShader(vertexShader);
        glad_glDeleteShader(fragmentShader);
        glad_glDeleteProgram(m_RendererID);
        m_RendererID = 0;

        throw std::runtime_error("Shader program linking failed:\n" + std::string(infoLog));
    }

    glad_glDeleteShader(vertexShader);
    glad_glDeleteShader(fragmentShader);
}

OpenGLShader::~OpenGLShader() {
    glad_glDeleteProgram(m_RendererID);
}

} // namespace RealEngine