#pragma once

#include "Engine/Core/Base.h"

#include <vector>

namespace RealEngine {

enum class TextureFormat {
    None = 0,
    RGBA8,
    RED_INTEGER,
    DEPTH24STENCIL8,
    Depth = DEPTH24STENCIL8
};

struct FramebufferTextureSpecification {
    TextureFormat Format = TextureFormat::None;

    FramebufferTextureSpecification() = default;
    FramebufferTextureSpecification(TextureFormat format) : Format(format) {}
};

struct FramebufferAttachmentSpecification {
    std::vector<FramebufferTextureSpecification> Attachments;

    FramebufferAttachmentSpecification() = default;
    FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
        : Attachments(attachments) {}
};

struct FramebufferSpecification {
    uint32_t Width = 0;
    uint32_t Height = 0;
    FramebufferAttachmentSpecification Attachments;
    uint32_t Samples = 1;
    bool SwapChainTarget = false;
};

// Render target used for post-processing passes (Phase 7).
class Framebuffer {
public:
    virtual ~Framebuffer() = default;

    virtual const FramebufferSpecification& GetSpecification() const = 0;
    virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void Resize(uint32_t width, uint32_t height) = 0;

    // Phase 7: static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
};

} // namespace RealEngine
