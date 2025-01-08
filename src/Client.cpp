#include "../inc/Define.hpp"

Client::Client() : clntSockFd(0), isRegistered(false), isOperator(false), nickName(""), userName(""), realName("") {}

Client::Client(int newFd) : clntSockFd(newFd), isRegistered(false), isOperator(false), nickName(""), userName(""), realName("") {}

Client::Client(const Client& obj)
{
	*this = obj;
}

Client&	Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->clntSockFd = obj.clntSockFd;
		this->isRegistered = obj.isRegistered;
		this->isOperator = obj.isOperator;
		this->nickName = obj.nickName;
		this->userName = obj.userName;
		this->realName = obj.realName;
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
