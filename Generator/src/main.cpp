#include <filesystem>
#include <string_view>

#include "Bundler.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    auto mode = std::string_view(argv[1]);

    if (mode == "bundler") {
        if (argc < 4) return 1;
        const auto base = fs::path(argv[2]) / "Bundled";
        fs::create_directories(base);

        for (int i = 3; i < argc; i++) {
            auto source = fs::path(argv[i]);
            auto result = Bundle(source, base);
            if (!result) return 1;
        }
    } else if (mode == "bundler-types") {
        if (argc < 3) return 1;
        const auto base = fs::path(argv[2]) / "Bundled";
        fs::create_directories(base);

        auto result = GenerateTypes(base);
        if (!result) return 1;
    }

    return 0;
}