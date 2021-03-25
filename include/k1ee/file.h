#pragma once
 
#include <vector>
#include <cstdint>
#include <filesystem>
#include <fstream>  

#include "k1ee/exception.h"  

namespace k1ee
{ 
template <typename DataType = uint8_t> requires (sizeof(DataType) == 1)
std::vector<DataType> read_all_bytes(const std::filesystem::path& path)
{  
	if(!exists(path) || is_directory(path))
		throw k1ee_runtime_error("file doesn't exist."); 

	auto size = file_size(path);
	
	std::vector<DataType> ret(size);

	std::ifstream fin(path, std::ios::binary);

	if(fin.fail())
		throw k1ee_runtime_error("open file failed");

	fin.read(reinterpret_cast<char*>(ret.data()), size);

	if(fin.fail())
		throw k1ee_runtime_error("read file failed");
	
	return ret;
}
	
void write_all_bytes(const std::filesystem::path& path, const void* data, size_t size);
	
std::string read_all_texts(const std::filesystem::path& path);
}
