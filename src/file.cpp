#include "k1ee/file.h"  
#include <fstream>

#include "k1ee/exception.h"

std::vector<uint8_t> k1ee::read_all_bytes(const std::filesystem::path& path)
{
	using namespace std::filesystem;
	
	if(!exists(path) || is_directory(path))
		throw k1ee::k1ee_runtime_error("file doesn't exist."); 

	auto size = file_size(path);
	
	std::vector<uint8_t> ret(size);

	std::ifstream fin(path, std::ios::binary);

	if(fin.fail())
		throw k1ee::k1ee_runtime_error("open file failed");

	fin.read(reinterpret_cast<char*>(ret.data()), size);

	if(fin.fail())
		throw k1ee::k1ee_runtime_error("read file failed");
	
	return ret;
}
