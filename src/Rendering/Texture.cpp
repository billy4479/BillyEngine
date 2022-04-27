#include "Texture.hpp"

#include <glad/gl.h>

#include <filesystem>
#include <utility>

#include "Assets/Image.hpp"
#include "Core/Logger.hpp"

namespace BillyEngine {
Texture::Proprieties Texture::Proprieties::FromImage(Ref<Image> image) {
    Texture::Proprieties props;
    props.Size = image->GetSize();
    props.Format = image->GetChannels() == 4 ? Texture::TexFormat::RGBA
                                             : Texture::TexFormat::RGB;
    props.Data = image;

    return props;
}

Ref<Texture> Texture::Create(const Proprieties& props) {
    return Ref<Texture>(new Texture(props));
}

Texture::~Texture() { glDeleteTextures(1, &m_Texture); }

void Texture::Bind(u32 slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

template <typename T>
static constexpr decltype(auto) GetGLValue(T v) {
    if constexpr (std::is_same_v<T, Texture::Filtering>) {
        switch (v) {
            case Texture::Filtering::Linear:
                return GL_LINEAR;
            case Texture::Filtering::Nearest:
                return GL_NEAREST;

            case Texture::Filtering::LinearMipmapLinear:
                return GL_LINEAR_MIPMAP_LINEAR;
            case Texture::Filtering::LinearMipmapNearest:
                return GL_LINEAR_MIPMAP_NEAREST;
            case Texture::Filtering::NearestMipmapLinear:
                return GL_NEAREST_MIPMAP_LINEAR;
            case Texture::Filtering::NearestMipmapNearest:
                return GL_NEAREST_MIPMAP_NEAREST;
        }
    } else if constexpr (std::is_same_v<T, Texture::WrappingMode>) {
        switch (v) {
            case Texture::WrappingMode::Repeat:
                return GL_REPEAT;
            case Texture::WrappingMode::MirroredRepeat:
                return GL_MIRRORED_REPEAT;
            case Texture::WrappingMode::ClampToBorder:
                return GL_CLAMP_TO_BORDER;
            case Texture::WrappingMode::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
        }
    } else if constexpr (std::is_same_v<T, Texture::TexFormat>) {
        switch (v) {
            case Texture::TexFormat::RGB:
                return std::pair<u32, u32>{GL_RGB, GL_RGB8};
            case Texture::TexFormat::RGBA:
                return std::pair<u32, u32>{GL_RGBA, GL_RGBA8};
        }
    }
    VERIFY_NOT_REACHED();
}

static constexpr bool IsMipmap(Texture::Filtering v) {
    switch (v) {
        case Texture::Filtering::Linear:
        case Texture::Filtering::Nearest:
            return false;

        case Texture::Filtering::LinearMipmapLinear:
        case Texture::Filtering::LinearMipmapNearest:
        case Texture::Filtering::NearestMipmapLinear:
        case Texture::Filtering::NearestMipmapNearest:
            return true;
    }

    VERIFY_NOT_REACHED();
}

Texture::Texture(const Proprieties& props) : m_Proprieties(props) {
    const auto [format, internalFormat] = GetGLValue(props.Format);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
    BE_LOG_GL_CALL("glGenTextures(1, {})", m_Texture);

    BE_LOG_GL_CALL("glTextureStorage2D({}, 1, {}, {}, {})", m_Texture,
                   internalFormat, props.Size.x, props.Size.y);
    glTextureStorage2D(m_Texture, 1, internalFormat, props.Size.x,
                       props.Size.y);

    assert(!IsMipmap(props.MagnificationFilter));  // Make sure that we don't
                                                   // use mipmaps here
    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_MAG_FILTER, {})",
                   m_Texture, props.MagnificationFilter);
    glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER,
                        GetGLValue(props.MagnificationFilter));

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_MIN_FILTER, {})",
                   m_Texture, props.MinificationFilter);
    glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER,
                        GetGLValue(props.MinificationFilter));

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_WRAP_T, {})", m_Texture,
                   props.Wrapping);
    glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T,
                        GetGLValue(props.Wrapping));

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_WRAP_S, {})", m_Texture,
                   props.Wrapping);
    glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S,
                        GetGLValue(props.Wrapping));

    if (props.Data != nullptr) SetData(props.Data->GetData());
}

void Texture::SetData(const u8* data) {
    const auto [format, internalFormat] = GetGLValue(m_Proprieties.Format);

    BE_LOG_GL_CALL(
        "glTextureSubImage2D({}, 0, 0, 0, {}, {}, {}, GL_UNSIGNED_BYTE, "
        "{})",
        m_Texture, m_Proprieties.Size.x, m_Proprieties.Size.y, format,
        (const void*)m_Proprieties.Data->GetData());
    glTextureSubImage2D(m_Texture, 0, 0, 0, m_Proprieties.Size.x,
                        m_Proprieties.Size.y, format, GL_UNSIGNED_BYTE, data);

    if (IsMipmap(m_Proprieties.MinificationFilter)) {
        BE_LOG_GL_CALL("glGenerateTextureMipmap({})", m_Texture);
        glGenerateTextureMipmap(m_Texture);
    }
}

}  // namespace BillyEngine