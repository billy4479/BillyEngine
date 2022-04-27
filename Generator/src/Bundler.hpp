#pragma once

#include <filesystem>

bool Bundle(std::filesystem::path src, std::filesystem::path base);
bool GenerateTypes(std::filesystem::path base);
