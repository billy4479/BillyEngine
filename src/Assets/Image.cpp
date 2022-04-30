#include "Assets/Image.hpp"

#include <stb_image.h>

#include <Generated/Bundled/Types.hpp>
#include <filesystem>

#include "Core/Logger.hpp"

namespace BillyEngine {

AssetType Image::GetAssetType() const { return AssetType::Image; }

Image::~Image() {
    if (m_NeedsFree) delete[] m_Data;
}

template <>
Ref<Image> Image::Load<false>(std::filesystem::path path, i32 wantedChannels) {
    glm::ivec2 size;
    i32 channels;

    const u8* data =
        stbi_load(path.string().c_str(), &size.x, &size.y, &channels, wantedChannels);

    return Ref<Image>(new Image(data, size, channels, true));
}

// I have to do this weird hack with the pointer instead of the reference
// because of the compiler thinking he needs to take the variable by value,
// since it doesn't have the full signature in the header, causing linking
// errors
template <>
Ref<Image> Image::Load<true>(const EngineResources::DecodedImage* image,
                             i32 channels) {
    (void)channels;
    return Ref<Image>(
        new Image(image->Data, image->Size, image->Channels, false));
}

Image::Image(const u8* data, glm::ivec2 size, i32 channels, bool needsFree)
    : m_Data(data),
      m_Size(size),
      m_Channels(channels),
      m_NeedsFree(needsFree) {}

}  // namespace BillyEngine
