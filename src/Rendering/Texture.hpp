#pragma once

#include <glm/ext/vector_int2.hpp>
#include <type_traits>

#include "Assets/Asset.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

class Texture final : public Asset {
   public:
    virtual AssetType GetAssetType() const override;
    virtual ~Texture() override;

    enum class Wrapping {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder,
    };

    enum class Filtering {
        Nearest,
        Linear,
    };

    enum class MipmapFiltering {
        NearestNearest,
        LinearNearest,
        NearestLinear,
        LinearLinear,
    };

    struct Proprieties {
        Wrapping Wrapping;
        Filtering Filtering;
        MipmapFiltering MipmapFiltering;
        bool KeepOnCPU;
        i32 Channels;
    };

    static constexpr Proprieties DefaultProprieties = {
        .Wrapping = Wrapping::Repeat,
        .Filtering = Filtering::Linear,
        .MipmapFiltering = MipmapFiltering::LinearLinear,
        .KeepOnCPU = false,
    };

    template <bool FromMemory, typename Source,
              typename = std::enable_if<FromMemory>>
    static Ref<Texture> Load(Source, glm::ivec2 size, i32 channels = 4,
                             const Proprieties& = DefaultProprieties);

    template <bool FromMemory, typename Source,
              typename = std::enable_if<!FromMemory>>
    static Ref<Texture> Load(Source, i32 channels = 4,
                             const Proprieties& = DefaultProprieties);

    void Bind(u32 slot = 0) const;

   private:
    glm::ivec2 m_Size;
    u32 m_Format{}, m_InternalFormat{};
    const u8* m_Data{nullptr};
    u32 m_Texture{};

    Texture(const u8*, glm::ivec2 size, i32 channels, const Proprieties&);
};  // namespace BillyEngine

}  // namespace BillyEngine