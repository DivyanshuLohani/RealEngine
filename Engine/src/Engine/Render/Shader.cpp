

#include "Render/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace RealEngine {

Ref<Shader> Shader::Create(const std::string& filepath) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLShader>(filepath);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

} // namespace RealEngine
