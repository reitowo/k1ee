#pragma once
 
#include <vector>
#include <cstdint>
#include <filesystem>

namespace k1ee
{
std::vector<uint8_t> read_all_bytes(const std::filesystem::path& path);
void write_all_bytes(const std::filesystem::path& path, const uint8_t* data, size_t size);
}
