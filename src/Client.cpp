#include "../inc/Define.hpp"

Client::Client() : registerStatus(false), clntSockFd(0), isOperator(false), nickName(""), userName(""), hostName("127.0.0.1"), realName("") {}

Client::Client(int newFd) : registerStatus(false), clntSockFd(newFd), isOperator(false), nickName(""), userName(""), hostName("127.0.0.1"), realName("") {}
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
		this->hostName = obj.hostName;
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

std::string Client::getNickName() const 
{
	return this->nickName;
}

std::string Client::getUserName() const
{
	return this->userName;
}

std::string Client::getHostName() const
{
	return this->hostName;
}

std::string Client::getRealName() const
{
	return this->realName;
}

void Client::setNickName(std::string name)
{
	this->nickName = name;
}

void Client::setUserName(std::string name) 
{
	this->userName = name;
}

void Client::setHostName(std::string name)
{
	this->hostName = name;
}

void Client::setRealName(std::string name)
{
	this->realName = name;
}