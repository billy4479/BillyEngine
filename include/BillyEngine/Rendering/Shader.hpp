#pragma once

#include <filesystem>
#include <string_view>

#include "Assets/Asset.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

class Shader final : public Asset {
   public:
    enum class ShaderType {
        Fragment,
        Vertex,
    };

    AssetType GetAssetType() const override;

    template <bool FromMemory, typename Source>
    static Ref<Shader> Load(Source, ShaderType);

    u32 GetID() const;

    virtual ~Shader() override;

   private:
    Shader(std::string_view source, ShaderType);

    u32 m_Shader{0};
    ShaderType m_Type;
};

}  // namespace BillyEngine