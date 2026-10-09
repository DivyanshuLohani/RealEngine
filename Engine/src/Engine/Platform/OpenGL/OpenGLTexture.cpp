#include "OpenGLTexture.h"

#include "Core/Assert.h"
#include "Core/Log.h"

#include <glad/gl.h>
#include <stb_image.h>

namespace RealEngine {

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path), m_Width(0), m_Height(0), m_RendererID(0) {

    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(true);

    RE_CORE_TRACE("Loading texture: {} )", path);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        RE_ERROR("Failed to load texture: {}", path);
        return;
    }

    m_Width = static_cast<uint32_t>(width);
    m_Height = static_cast<uint32_t>(height);

    GLenum internalFormat = GL_RGB8;
    GLenum dataFormat = GL_RGB;

    if (channels == 4) {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    } else if (channels == 3) {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    } else {
        RE_ERROR("Unsupported texture format: {} ({} channels)", path, channels);

        stbi_image_free(data);
        return;
    }

    m_InternalFormat = internalFormat;
    m_DataFormat = dataFormat;

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload texture data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height), m_RendererID(0), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA) {

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size) {
    uint32_t bpp = (m_DataFormat == GL_RGBA) ? 4 : 3;
    RE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

OpenGLTexture2D::~OpenGLTexture2D() {
    RE_CORE_TRACE("Destroying texture ID: {}", m_RendererID);

    if (m_RendererID != 0) {
        glDeleteTextures(1, &m_RendererID);
        m_RendererID = 0;
    }
}

void OpenGLTexture2D::Bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void OpenGLTexture2D::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace RealEngine
