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

		std::string execPass(const Server &server, Client *client);
		std::string execNick(Client *client, std::map<int, Client*> &clients);
		std::string execUser(Client *client);

		std::string execWhois();

		std::string execInvite(Client *inviter, Server &server);
		// std::string exec(Client *client, std::map<int, Client*> clients);

		std::string execPrivmsg(Client *sender, Server &server);
		std::string execJoin(Client *client, Server &server);
		std::string execPart(Client *client, Server &server);
		std::string execKick(Client *client, Server &server);
		std::string execTopic(Client *client, Server &server);
		std::string execMode(Client *client, Server &server);
};

