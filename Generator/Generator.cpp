#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

template <typename T>
requires std::integral<T>
static std::string ToHex(T n) {
    // https://stackoverflow.com/a/33447587/13166735

    constexpr auto stringLength = sizeof(T) << 1;
    constexpr char digits[] = "0123456789ABCDEF";
    std::string result(stringLength, '0');
    for (size_t i = 0, j = (stringLength - 1) * 4; i < stringLength;
         ++i, j -= 4)
        result[i] = digits[(n >> j) & 0x0f];
    return result;
};

int main(int argc, char** argv) {
    if (argc < 4) return 1;

    std::ofstream outFile;
    outFile.open(argv[1]);
    if (!outFile.is_open()) return 1;

    for (int i = 2; i < argc; i += 2) {
        std::ifstream current;
        auto name = std::filesystem::path(argv[i]);
        const auto type = std::string_view(argv[i + 1]);
        current.open(name);
        if (!current.is_open()) return 1;

        outFile << "static constexpr ";
        name = name.filename().replace_extension();

        if (type == "text") {
            outFile << "std::string_view " << name.string() << " = R\"("
                    << current.rdbuf() << ")\";\n";
        } else if (type == "binary" || type == "") {
            outFile << "std::array " << name.string()
                    << " = {std::to_array<unsigned char>({";

            char c;
            while (current.get(c))
                outFile << "0x" << ToHex((unsigned char)c) << ", ";

            outFile << "})};";
        } else {
            return 1;
        }
    }

    return 0;
}