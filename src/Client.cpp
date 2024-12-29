#include "../inc/Define.hpp"

Client::Client() : clntSockFd(0), isRegistered(false), isOperator(false), authenticated(false), nickName(""), userName(""), realName("") {}

Client::Client(int newFd) : clntSockFd(newFd), isRegistered(false), isOperator(false), authenticated(false), nickName(""), userName(""), realName("") {}

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
		this->authenticated = obj.authenticated;
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

bool Client::isAuthenticated() const
{
	return this->authenticated;
}