#pragma once

#include <filesystem>
#include <string_view>

#include "Assets/Asset.hpp"
#include "Core/Types.hpp"

namespace BillyEngine {

class Shader : public Asset {
   public:
    enum class ShaderType {
        Fragment,
        Vertex,
    };

    AssetType GetAssetType() const override;
    static AssetType GetAssetTypeStatic();
    static Ref<Shader> Load(std::filesystem::path, ShaderType);
    static Ref<Shader> Load(std::string_view src, ShaderType);

    u32 GetID() const;

    ~Shader();

   private:
    Shader(std::string_view source, ShaderType);

    u32 m_Shader{0};
    ShaderType m_Type;
};

}  // namespace BillyEngine