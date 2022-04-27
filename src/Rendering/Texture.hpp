#pragma once

#include <glm/ext/vector_int2.hpp>
#include <type_traits>

#include "Assets/Asset.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

class Image;

class Texture {
   public:
    enum class WrappingMode {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder,
    };

    enum class Filtering {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear,
    };

    enum class TexFormat {
        RGBA,
        RGB,

        // TODO: add stuff like depth buffer if needed in the future
    };

    struct Proprieties {
        glm::ivec2 Size{32, 32};
        TexFormat Format;

        WrappingMode Wrapping = WrappingMode::Repeat;
        Filtering MagnificationFilter = Filtering::Linear;
        Filtering MinificationFilter = Filtering::LinearMipmapLinear;

        // TODO: It might be interesting in the future but it creates too many
        // ownership problems for now
        // bool KeepOnCPU = false;

        Ref<Image> Data{nullptr};

        static Texture::Proprieties FromImage(Ref<Image>);
    };

    static Ref<Texture> Create(const Proprieties&);

    void Bind(u32 slot = 0) const;
    void SetData(const u8*);

    ~Texture();

   private:
    const Proprieties m_Proprieties;
    // const u8* m_Data{nullptr};
    u32 m_Texture{};

    Texture(const Proprieties&);
};  // namespace BillyEngine

}  // namespace BillyEngine