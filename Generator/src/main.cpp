#include <filesystem>
#include <string_view>

#include "Bundler.hpp"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc < 4) return 1;

    auto mode = std::string_view(argv[1]);

    if (mode == "bundler") {
        const auto base = fs::path(argv[2]) / "Bundled";
        fs::create_directories(base);

        for (int i = 3; i < argc; i++) {
            auto source = fs::path(argv[i]);
            auto result = Bundle(source, base);
            if (!result) return 1;
        }
    }

    return 0;
}