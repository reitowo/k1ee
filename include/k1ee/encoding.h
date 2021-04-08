#pragma once

#include "k1ee/exception.h"

#include <Windows.h>
#include <stringapiset.h>
#include <string>

namespace k1ee
{
	std::string encoding_convert(std::string bytes, uint32_t from, uint32_t to);
	std::string encoding_convert(const char* bytes, size_t bytes_len, uint32_t from, uint32_t to);

	template <typename ToStrType, typename FromStrType>
	std::basic_string<ToStrType, std::char_traits<ToStrType>, std::allocator<ToStrType>>
	basic_string_cast(std::basic_string<FromStrType, std::char_traits<FromStrType>, std::allocator<FromStrType>> str)
	{
		size_t from_size = str.size() * sizeof(FromStrType);
		size_t remain_check = from_size % sizeof(ToStrType);
		size_t to_size = from_size / sizeof(ToStrType) + (remain_check == 0 ? 0 : 1);
		return std::basic_string<ToStrType>(reinterpret_cast<const ToStrType*>(str.c_str()), to_size);
	}

	void set_utf8_console();
}
