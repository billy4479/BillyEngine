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

    enum class Wrapping_t {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder,
    };

    enum class Filtering_t {
        Nearest,
        Linear,
    };

    enum class MipmapFiltering_t {
        NearestNearest,
        LinearNearest,
        NearestLinear,
        LinearLinear,
    };

    struct Proprieties {
        Wrapping_t Wrapping;
        Filtering_t Filtering;
        MipmapFiltering_t MipmapFiltering;
        bool KeepOnCPU;
    };

    static constexpr Proprieties DefaultProprieties = {
        .Wrapping = Wrapping_t::Repeat,
        .Filtering = Filtering_t::Linear,
        .MipmapFiltering = MipmapFiltering_t::LinearLinear,
        .KeepOnCPU = false,
    };

    template <bool FromMemory, typename Source,
              typename = std::enable_if<FromMemory>>
    static Ref<Texture> Load(Source, glm::ivec2 size, i32 channels = 4,
                             const Proprieties& = DefaultProprieties);

    template <bool FromMemory, typename Source,
              typename = std::enable_if<!FromMemory>>
    static Ref<Texture> Load(Source, const Proprieties& = DefaultProprieties);

    void Bind(u32 slot = 0) const;

   private:
    glm::ivec2 m_Size;
    u32 m_Format{}, m_InternalFormat{};
    const u8* m_Data{nullptr};
    u32 m_Texture{};

    Texture(const u8*, glm::ivec2 size, i32 channels, const Proprieties&);
};  // namespace BillyEngine

}  // namespace BillyEngine