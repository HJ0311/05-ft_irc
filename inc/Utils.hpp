#pragma once

#include "Define.hpp"

class Client;

namespace Utils
{
	extern std::string RPL_403;
	extern std::string RPL_401;

	std::string	getTime();
	std::string	welcomeMsg();
}