#pragma once

#include <stdexcept>

namespace k1ee
{
class k1ee_runtime_error : public std::runtime_error
{
public:
	k1ee_runtime_error(const std::string& error) : std::runtime_error("[k1ee] " + error)
	{
		
	}

	k1ee_runtime_error(const char * error) : std::runtime_error("[k1ee] " + std::string(error))
	{
		
	} 
};
}