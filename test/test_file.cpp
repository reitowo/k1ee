#include "k1ee/file.h"

#include <cassert>

int main()
{
	const auto* path = R"(./data/test_data.dat)";
	
	auto ret = k1ee::read_all_bytes(path);

	if(ret.size() != 264)
		return 1;

	k1ee::write_all_bytes(path, ret.data(), ret.size());
}