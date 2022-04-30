#include "Bundler.hpp"

#include <fmt/core.h>
#include <stb_image.h>

#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

template <typename T>
#if __cplusplus >= 202002L
requires std::integral<T>
#endif
static std::string ToHex(T n) {
    // https://stackoverflow.com/a/33447587/13166735

    constexpr auto stringLength = sizeof(T) << 1;
    constexpr char digits[] = "0123456789ABCDEF";
    std::string result(stringLength, '0');
    for (size_t i = 0, j = (stringLength - 1) * 4; i < stringLength;
         ++i, j -= 4)
        result[i] = digits[(n >> j) & 0x0f];
    return result;
}

// https://stackoverflow.com/a/3418285/13166735
static void replaceAll(std::string& str, const std::string& from,
                       const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();  // In case 'to' contains 'from', like
                                   // replacing 'x' with 'yx'
    }
}

static bool EmitText(fs::path src, fs::path dest, std::string_view name);
static bool EmitImage(fs::path src, fs::path dest, std::string_view name);
static bool EmitBinary(fs::path src, fs::path dest, std::string_view name);

bool Bundle(fs::path src, fs::path base) {
    std::string name = src.filename().string();
    replaceAll(name, ".", "_");
    auto dest = base / (name + ".hpp");
    auto ext = src.extension();

    if (ext == ".txt" || ext == ".glsl") return EmitText(src, dest, name);
    if (ext == ".png" || ext == ".jpg") return EmitImage(src, dest, name);

    return EmitBinary(src, dest, name);
}

static bool EmitText(fs::path src, fs::path dest, std::string_view name) {
    std::ofstream out;
    out.open(dest);
    if (!out.is_open()) return false;

    std::ifstream in;
    in.open(src);
    if (!in.is_open()) return false;

    std::stringstream data;
    data << in.rdbuf();

    static constexpr std::string_view formatTemplate = R"(#pragma once

#include <string_view>

namespace BillyEngine {{
namespace EngineResources {{

static constexpr std::string_view {} = {};

}}
}}
)";
    out << fmt::format(formatTemplate, name,
                       fmt::format("R\"({})\"", data.str()));
    return true;
}

static bool EmitImage(fs::path src, fs::path dest, std::string_view name) {
    std::ofstream out;
    out.open(dest);
    if (!out.is_open()) return false;

    int x, y, channels;
    const auto* data = stbi_load(src.string().c_str(), &x, &y, &channels, 0);
    if (data == nullptr) return 1;
    auto size = x * y * channels;

    std::stringstream ss;
    for (int i = 0; i < size; i++) ss << "0x" << ToHex(data[i]) << ", ";

    static constexpr std::string_view formatTemplate = R"(#pragma once

#include "Types.hpp"

namespace {{

static constexpr unsigned char {}_data[] = {{ {} }};

}}

namespace BillyEngine {{
namespace EngineResources {{

static constexpr DecodedImage {} = {{
    .Data = {}_data,
    .Size = {{ {}, {} }},
    .Channels = {},
    .SizeInBytes = {},
}};

}}
}}
)";

    out << fmt::format(formatTemplate, name, ss.str(), name, name, x, y,
                       channels, size);
    stbi_image_free((void*)data);
    return true;
}

static bool EmitBinary(fs::path src, fs::path dest, std::string_view name) {
    std::ofstream out;
    out.open(dest);
    if (!out.is_open()) return false;

    std::ifstream in;
    in.open(src);
    if (!in.is_open()) return false;

    std::stringstream ss;
    char c;
    while (in.get(c)) ss << "0x" << ToHex((unsigned char)c) << ", ";

    static constexpr std::string_view formatTemplate = R"(#pragma once

#include <array>

namespace BillyEngine {{
namespace EngineResources {{

std::array<unsigned char, {}> {} =  {{ {} }},

}}
}}
)";
    out << fmt::format(formatTemplate, in.tellg(), name, ss.str());
    return true;
}

bool GenerateTypes(fs::path base) {
    static constexpr std::string_view imageType = R"(#pragma once

#include <array>
#include <glm/ext/vector_int2.hpp>

namespace BillyEngine {
namespace EngineResources {

struct DecodedImage {
    const unsigned char* Data;
    glm::ivec2 Size;
    int Channels;
    std::size_t SizeInBytes;
};

}
}
    )";

    std::ofstream out;
    out.open(base / "Types.hpp");
    if (!out.is_open()) return false;

    out << imageType;

    return true;
}
