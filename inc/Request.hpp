#pragma once

#include "Define.hpp"

class Request
{
	public:
		Request();
		Request(const Request& obj);
		Request&	operator=(const Request& obj);
		~Request();
		
		std::string	command; // 명령어
		std::vector<std::string>	args; // 명령어와 함께 들어온 인자
};