#include "k1ee/file.h"

#include <cassert>

int main()
{
	auto ret = k1ee::read_all_bytes(R"(./data/test_data.dat)");

	assert(ret.size() == 264);
}