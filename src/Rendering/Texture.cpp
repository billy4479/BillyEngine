#include "Texture.hpp"

#include <glad/gl.h>
#include <stb_image.h>

#include <filesystem>

#include "Core/Logger.hpp"

namespace BillyEngine {
AssetType Texture::GetAssetType() const { return AssetType::Texture; }

Texture::~Texture() {
    if (m_Data != nullptr) stbi_image_free((void*)m_Data);
}

void Texture::Bind(u32 slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}

template <typename T>
static constexpr u32 GetGLValue(T v) {
    if constexpr (std::is_same_v<T, Texture::Filtering>) {
        switch (v) {
            case Texture::Filtering::Linear:
                return GL_LINEAR;
            case Texture::Filtering::Nearest:
                return GL_NEAREST;
        }
    } else if constexpr (std::is_same_v<T, Texture::Wrapping>) {
        switch (v) {
            case Texture::Wrapping::Repeat:
                return GL_REPEAT;
            case Texture::Wrapping::MirroredRepeat:
                return GL_MIRRORED_REPEAT;
            case Texture::Wrapping::ClampToBorder:
                return GL_CLAMP_TO_BORDER;
            case Texture::Wrapping::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
        }
    } else if constexpr (std::is_same_v<T, Texture::MipmapFiltering>) {
        switch (v) {
            case Texture::MipmapFiltering::LinearLinear:
                return GL_LINEAR_MIPMAP_LINEAR;
            case Texture::MipmapFiltering::LinearNearest:
                return GL_LINEAR_MIPMAP_NEAREST;
            case Texture::MipmapFiltering::NearestLinear:
                return GL_NEAREST_MIPMAP_LINEAR;
            case Texture::MipmapFiltering::NearestNearest:
                return GL_NEAREST_MIPMAP_NEAREST;
        }
    }
    VERIFY_NOT_REACHED();
}

template <>
Ref<Texture> Texture::Load<false, std::filesystem::path>(
    std::filesystem::path path, i32 channels, const Proprieties& props) {
    glm::ivec2 size;
    Proprieties p = props;

    stbi_set_flip_vertically_on_load(1);
    const auto* data =
        stbi_load(path.c_str(), &size.x, &size.y, &p.Channels, 0);
    if (data == nullptr) {
        Logger::Core()->error("Error while loading texture at {}",
                              path.string());
        return nullptr;
    }

    auto result = Ref<Texture>(new Texture(data, size, channels, p));
    if (!props.KeepOnCPU) stbi_image_free((void*)data);
    return result;
}

template <>
Ref<Texture> Texture::Load<true, const u8*>(const u8* data, glm::ivec2 size,
                                            i32 channels,
                                            const Proprieties& props) {
    return Ref<Texture>(new Texture(data, size, channels, props));
}

Texture::Texture(const u8* data, glm::ivec2 size, i32 channels,
                 const Proprieties& props)
    : m_Size(size) {
    if (props.KeepOnCPU) m_Data = data;

    switch (channels) {
        case 4:
            m_Format = GL_RGBA;
            m_InternalFormat = GL_RGBA8;
            break;
        case 3:
            m_Format = GL_RGB;
            m_InternalFormat = GL_RGB8;
            break;
        default:
            VERIFY_NOT_REACHED();
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
    BE_LOG_GL_CALL("glGenTextures(1, {})", m_Texture);

    BE_LOG_GL_CALL("glTextureStorage2D({}, 1, {}, {}, {})", m_Texture,
                   m_InternalFormat, m_Size.x, m_Size.y);
    glTextureStorage2D(m_Texture, 1, m_InternalFormat, m_Size.x, m_Size.y);

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_MAG_FILTER, {})",
                   m_Texture, props.Filtering);
    glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER,
                        GetGLValue(props.Filtering));

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_MIN_FILTER, {})",
                   m_Texture, props.MipmapFiltering);
    glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER,
                        GetGLValue(props.MipmapFiltering));

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_WRAP_T, {})", m_Texture,
                   props.Wrapping);
    glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T,
                        GetGLValue(props.Wrapping));

    BE_LOG_GL_CALL("glTextureParameteri({}, GL_TEXTURE_WRAP_S, {})", m_Texture,
                   props.Wrapping);
    glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S,
                        GetGLValue(props.Wrapping));

    BE_LOG_GL_CALL(
        "glTextureSubImage2D({}, 0, 0, 0, {}, {}, {}, GL_UNSIGNED_BYTE, {})",
        m_Texture, m_Size.x, m_Size.y, m_Format, (const void*)data);
    glTextureSubImage2D(m_Texture, 0, 0, 0, m_Size.x, m_Size.y, m_Format,
                        GL_UNSIGNED_BYTE, data);

    BE_LOG_GL_CALL("glGenerateTextureMipmap({})", m_Texture);
    glGenerateTextureMipmap(m_Texture);
}

}  // namespace BillyEngine