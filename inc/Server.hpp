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
		// 사용자가 아직 로컬 서버에 로그인 되어 있지 않을 경우 경고문을 띄우는 함수
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