#pragma once

#include "Define.hpp"

class Client
{
	public:
		Client(int newFd);
		Client(const Client& obj);
		Client&	operator=(const Client& obj);
		~Client();

		std::string	recvBuffer; // 클라이언트별로 데이터를 저장할 버퍼

		int	getSockFd() const;

		const std::string&	getNickName() const;
		void	setNickName(const std::string& nickname);
		const std::string&	getUserName() const;
		void	setUserName(const std::string& username);
		const std::string&	getHostName() const;
		void	setHostName(const std::string& hostname);
		bool &getRegisterStatus();
		void 	setRegisterStatus(const bool &status);
		bool &getErrorClose();
		void setErrorClose(const bool &status);
		const int&	getClntSockFd() const;
		
		void	addChannel(const std::string& channelName);
		void	removeChannel(const std::string& channelName);
		std::set<std::string>&	getJoinedChannels();
	private:
		Client();

		bool 	errorClose;
		bool 	registerStatus;
		int		clntSockFd;

		std::string	nickName;
		std::string	userName;
		std::string	hostName;
		std::set<std::string>	joinedChannels;
};
