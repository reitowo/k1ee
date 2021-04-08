#include "k1ee/encoding.h"
#include <iostream>
#include <cassert>

int main()
{
	std::string std_string = "UTF8字符串"; 
	std::u8string u8_string = k1ee::basic_string_cast<char8_t>(std_string); 
}