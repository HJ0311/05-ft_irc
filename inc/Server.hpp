#pragma once

#include "Define.hpp"

class Client;

class Server
{
	public:
		Server(int maxUserCnt, const std::string& port, const std::string& password);
		~Server();

		void	initSocket(const std::string& port);
		void	startServer();
		void	newClient();
		void	addToPoll(int newFd);
		void	removeFromPoll(int i);
		void	clientRequest(int i);
	private:
		Server();
		Server(const Server& obj);
		Server&	operator=(const Server& obj);

		int	maxClientCnt;
		int	onlineClient;
		std::string	password;
		int	servSockFd;
		struct pollfd	*pfds;
		std::map<int, Client*>	clients;
};