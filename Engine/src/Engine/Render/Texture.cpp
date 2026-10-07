#include "Engine/Render/Texture.h"
#include "Engine/Core/Assert.h"
#include "Engine/Platform/OpenGL/OpenGLTexture.h"

namespace RealEngine {

Ref<Texture2D> Texture2D::Create(const std::string& path) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLTexture2D>(path);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
#ifdef RE_RENDERER_OPENGL
    return CreateRef<OpenGLTexture2D>(width, height);
#else
    RE_CORE_ASSERT(false, "No renderer backend available");
    return nullptr;
#endif
}

} // namespace RealEngine
