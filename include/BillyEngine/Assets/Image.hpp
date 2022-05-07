#pragma once

#include <glm/ext/vector_int2.hpp>

#include "Assets/Asset.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

class Image : public Asset {
   public:
    virtual AssetType GetAssetType() const override;

    template <bool FromMemory, typename Source>
    static Ref<Image> Load(Source, i32 wantedChannels = 0);

    virtual ~Image() override;

    const u8* GetData() const { return m_Data; }
    const glm::ivec2& GetSize() const { return m_Size; }
    i32 GetChannels() const { return m_Channels; }

   private:
    Image(const u8* data, glm::ivec2 size, i32 channels, bool needsFree);

    const u8* m_Data{nullptr};
    glm::ivec2 m_Size;
    i32 m_Channels{};
    bool m_NeedsFree{};
};

}  // namespace BillyEngine