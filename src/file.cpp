#include "k1ee/k1ee.h"  
#include <fstream>  

void k1ee::write_all_bytes(const std::filesystem::path& path, const void* data, size_t size)
{
	using namespace std::filesystem;

	std::ofstream fout(path, std::ios::binary);

	fout.write(static_cast<const char*>(data), size);
}
