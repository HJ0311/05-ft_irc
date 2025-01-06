#pragma once

#include "Define.hpp"

class Request
{
	public:
		Request(const Request& obj);
		~Request();
		
		std::string	command; // 명령어
		std::vector<std::string>	args; // 명령어와 함께 들어온 인자

		Request();
		Request&	operator=(const Request& obj);
		
		std::string execPass(const Server &server, bool &registerStatus);
		std::string execNick(const Server &server, Client *client, std::map<int, Client*> clients);
		std::string execUser(const Server &server, int i);
};