#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <filesystem>

namespace k1ee
{
std::vector<uint8_t> read_all_bytes(const std::filesystem::path& path);
}
