#pragma once

#include "Define.hpp"

class Client;

namespace Utils {
    extern std::string RPL_451;
    extern std::string RPL_461;
    extern std::string RPL_462;
	extern std::string RPL_464;
	extern std::string RPL_433;
	extern std::string RPL_431;
	extern std::string RPL_432;
	extern std::stringstream RPL_CONNECTION_SUCCESS;

	extern std::string RPL_403;
	extern std::string RPL_401;

	std::string	getTime();
	std::string formatString();
}
