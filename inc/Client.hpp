#pragma once

#include "Define.hpp"

class Client
{
	public:
		Client(int newFd);
		Client(const Client& obj);
		Client&	operator=(const Client& obj);
		~Client();
		// getter
		int	getSockFd() const;

		const std::string&	getNickName() const;
		void	setNickName(const std::string& nickname);
		const std::string&	getUserName() const;
		void	setUserName(const std::string& username);
		const std::string&	getServerName() const;
		void	setServerName(const std::string& servername);
		bool registerStatus;
	private:
		Client();

		int	clntSockFd; // 클라이언트의 소켓 fd
		bool	isOperator; // 관리자?
		std::string	nickName;
		std::string	userName;
		// std::string hostName;
		std::string	serverName;
};