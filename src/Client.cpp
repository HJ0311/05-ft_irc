#include "../inc/Define.hpp"

Client::Client() : registerStatus(false), clntSockFd(0), isOperator(false), nickName(""), userName(""), serverName("127.0.0.1") {}

Client::Client(int newFd) : registerStatus(false), clntSockFd(newFd), isOperator(false), nickName(""), userName(""), serverName("127.0.0.1") {}
//TODO hostname 어떻게 할지.
Client::Client(const Client& obj)
{
	*this = obj;
}

Client&	Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->registerStatus = obj.registerStatus;
		this->clntSockFd = obj.clntSockFd;
		this->isOperator = obj.isOperator;
		this->nickName = obj.nickName;
		this->userName = obj.userName;
	}
	return *this;
}

Client::~Client() {}

// =================================================================================================================
// member function
// =================================================================================================================

int	Client::getSockFd() const
{
	return this->clntSockFd;
}

const std::string&	Client::getNickName() const
{
	return (this->nickName);
}

void	Client::setNickName(const std::string& nickname)
{
	this->nickName = nickname;
}

const std::string&	Client::getUserName() const
{
	return (this->userName);
}

void	Client::setUserName(const std::string& username)
{
	this->userName = username;
}

const std::string&	Client::getHostName() const
{
	return (this->hostName);
}

void	Client::setHostName(const std::string& hostname)
{
	this->hostName = hostname;
}
