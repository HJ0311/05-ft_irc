#pragma once

#include "Define.hpp"

class Client;

class Server
{
	public:
		Server(const std::string& port, const std::string& password);
		~Server();

		void	run();
		// void	handleNewConnection();
		// void	handleClientRead(const Client& client);
		// void	handgleClientWrite(const Client& client);
	private:
		Server();
		Server(const Server& obj);
		Server&	operator=(const Server& obj);

		// member attribute
		int	port;
		std::string	password;
		int	sock;
		struct sockaddr_in	servAddr; // 서버 소켓의 주소 정보를 저장
		// struct sockaddr_in	clntAddr; // 연결 요청 수락 후 클라이언트의 네트워크 주소 정보 저장

		fd_set	readFds;
		fd_set	writeFds;
		fd_set	readFdsCopy;
		fd_set	writeFdsCopy;
		socklen_t	servSockSize;

		std::vector<Client>	clients;
		// vector<Channel>	channels;
		// std::map<std::string, void (Server*)(const std::string&, Client&)>	commands;

		// member function
		void	initSocket();
};