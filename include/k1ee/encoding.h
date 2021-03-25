#pragma once 

#include "k1ee/exception.h"  

#include <Windows.h>
#include <stringapiset.h>
#include <string>

namespace k1ee
{
	std::string encoding_convert(std::string bytes, uint32_t from, uint32_t to);
}
