#include <stb_image.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

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

int main(int argc, char** argv) {
    std::cout << R"(#include <array>
#include <glm/ext/vector_int2.hpp>
#include <string_view>

namespace BillyEngine {
namespace EngineResources {
    
template <std::size_t S>
struct Image {
    std::array<unsigned char, S> Data;
    glm::ivec2 Size;
    int Channels;
};
)";

    for (int i = 1; i < argc; i++) {
        auto name = std::filesystem::path(argv[i]);
        std::cerr << "Bundling " << name.filename() << std::endl;

        std::cout << "\n\nstatic constexpr ";
        const auto& n = name.filename().replace_extension().string();
        const auto& ext = name.extension().string();

        if (ext == ".txt" || ext == ".glsl") {
            std::ifstream f;
            f.open(name);
            if (!f.is_open()) return 1;

            std::cout << "std::string_view " << n << " = R\"(" << f.rdbuf()
                      << ")\";";
        } else if (ext == ".png" || ext == ".jpg") {
            int x, y, channels;
            const auto* data = stbi_load(name.c_str(), &x, &y, &channels, 0);
            if (data == nullptr) return 1;
            auto size = x * y * channels;

            std::cout << "Image<" << size << ">" << n << R"( = {
    .Data = std::array<unsigned char, )"
                      << size << ">{";
            for (int i = 0; i < size; i++)
                std::cout << "0x" << ToHex(data[i]) << ", ";

            std::cout << R"(},
    .Size = glm::ivec2{)"
                      << x << ", " << y << R"(},
    .Channels = )" << channels
                      << ",\n};\n";

            stbi_image_free((void*)data);

        } else {
            std::ifstream f;
            f.open(name);
            if (!f.is_open()) return 1;

            f.seekg(0, std::ios::end);
            std::cout << "std::array<unsigned char, " << f.tellg() << "> " << n
                      << " = {";
            f.seekg(0, std::ios::beg);

            char c;
            while (f.get(c))
                std::cout << "0x" << ToHex((unsigned char)c) << ", ";

            std::cout << "};";
        }
    }

    std::cout << R"(

}
}
    )";

    return 0;
}