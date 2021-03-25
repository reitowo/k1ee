#include "k1ee/k1ee.h"  
#include <fstream>
#include <sstream>

void k1ee::write_all_bytes(const std::filesystem::path& path, const void* data, size_t size)
{
	using namespace std::filesystem;

	std::ofstream fout(path, std::ios::binary);

	fout.write(static_cast<const char*>(data), size);
}

std::string k1ee::read_all_texts(const std::filesystem::path& path)
{
	if(!exists(path) || is_directory(path))
		throw k1ee_runtime_error("file doesn't exist.");   
	
	const std::ifstream fin(path);

	if(fin.fail())
		throw k1ee_runtime_error("open file failed");

	std::stringstream ss;

	ss << fin.rdbuf();
	
	return ss.str();
}
