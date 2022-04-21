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
#include <string_view>

namespace BillyEngine {
namespace EngineResources {)";

    for (int i = 1; i < argc; i++) {
        auto name = std::filesystem::path(argv[i]);
        std::cerr << "Bundling " << name.filename() << std::endl;

        std::ifstream current;
        current.open(name);
        if (!current.is_open()) return 1;

        std::cout << "\n\nstatic constexpr ";
        const auto& n = name.filename().replace_extension().string();
        const auto& ext = name.extension().string();

        if (ext == ".txt" || ext == ".glsl") {
            std::cout << "std::string_view " << n << " = R\"("
                      << current.rdbuf() << ")\";";
        } else {
            current.seekg(0, std::ios::end);
            std::cout << "std::array<unsigned char, " << current.tellg() << "> "
                      << n << " = {";
            current.seekg(0, std::ios::beg);

            char c;
            while (current.get(c))
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