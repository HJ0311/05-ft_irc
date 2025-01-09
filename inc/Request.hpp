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
		
		bool validateNick(const std::string &nick);

		std::string execPass(const Server &server, bool &registerStatus);
		std::string execNick(Client *client, std::map<int, Client*> clients);
		std::string execUser(Client *client, std::map<int, Client*> clients);

		std::string execPrivmsg(Client *sender, const Server &server);
};
