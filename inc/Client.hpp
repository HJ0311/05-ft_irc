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

		std::string getNickName() const;
		std::string getUserName() const;
		std::string getHostName() const;
		std::string getRealName() const;
		
		void setNickName(std::string name);
		void setUserName(std::string name);
		void setRealName(std::string name);
		void setHostName(std::string name);

		bool registerStatus;
	private:
		Client();

		int	clntSockFd; // 클라이언트의 소켓 fd
		bool	isOperator; // 관리자?
		std::string	nickName;
		std::string	userName;
		std::string hostName;
		std::string	realName;
};