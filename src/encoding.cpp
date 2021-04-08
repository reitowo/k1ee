#include "k1ee/encoding.h"

std::string k1ee::encoding_convert(std::string bytes, uint32_t from, uint32_t to)
{
	return encoding_convert(bytes.c_str(), bytes.size(), from, to);
}

std::string k1ee::encoding_convert(const char* bytes, size_t bytes_len, uint32_t from, uint32_t to)
{
	int from_size = MultiByteToWideChar(from, 0, bytes, bytes_len, nullptr, 0);
	wchar_t* from_bytes = new wchar_t[from_size];
	int ret = MultiByteToWideChar(from, 0, bytes, bytes_len, from_bytes, from_size);
	int to_size = WideCharToMultiByte(to, 0, from_bytes, from_size, nullptr, 0, nullptr, nullptr);
	char* to_bytes = new char[to_size];
	ret = WideCharToMultiByte(to, 0, from_bytes, from_size, to_bytes, to_size, nullptr, nullptr);
	std::string str(to_bytes, to_size);
	delete[] to_bytes;
	delete[] from_bytes;
	return str;
}

void k1ee::set_utf8_console()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
}
 
