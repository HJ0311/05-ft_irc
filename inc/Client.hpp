#pragma once

#include "Define.hpp"

class Client
{
	public:
		Client(int fd, int port);
		~Client();

		int	getFd() const;
		int	getPort() const;
		std::string	getNickName() const;
		std::string	getHostName() const;
		std::string	getServerName() const;
		std::string	getUserName() const;
	private:
		Client();
		Client(const Client& obj);
		Client&	operator=(const Client& obj);

		char	ip[INET_ADDRSTRLEN];
		int	fd;
		int	port;
		bool	isRegistered;
		std::string	nickName;
		std::string	hostName;
		std::string	serverName;
		std::string	userName;
};