#include "../../inc/Define.hpp"

Client::Client() : errorClose(false), registerStatus(false), clntSockFd(0), isOperator(false), nickName(""), userName(""), hostName("127.0.0.1") {}

Client::Client(int newFd) : errorClose(false), registerStatus(false), clntSockFd(newFd), isOperator(false), nickName(""), hostName("127.0.0.1") {}
//TODO hostname 어떻게 할지.
Client::Client(const Client& obj)
{
	*this = obj;
}

Client&	Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->errorClose = obj.errorClose;
		this->registerStatus = obj.registerStatus;
		this->clntSockFd = obj.clntSockFd;
		this->isOperator = obj.isOperator;
		this->nickName = obj.nickName;
		this->userName = obj.userName;
		this->joinedChannels = obj.joinedChannels;
	}
	return *this;
}

Client::~Client()
{
	for (std::set<std::string>::iterator it = joinedChannels.begin(); it != joinedChannels.end(); ++it)
	{
		std::cout << *it << "\n";
	}
}

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

const int&	Client::getClntSockFd() const
{
	return (this->clntSockFd);
}

bool &Client::getRegisterStatus()
{
	return this->registerStatus;
}

void Client::setRegisterStatus(const bool &status)
{
	this->registerStatus = status;
}

bool &Client::getErrorClose()
{
	return this->errorClose;
}

void Client::setErrorClose(const bool &status)
{
	this->errorClose = status;
}

void	Client::addChannel(const std::string& channelName)
{
	this->joinedChannels.insert(channelName);
}

void	Client::removeChannel(const std::string& channelName)
{
	this->joinedChannels.erase(channelName);
}

std::set<std::string>&	Client::getJoinedChannels()
{
	return (this->joinedChannels);
}
