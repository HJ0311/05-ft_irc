#include "../inc/Define.hpp"

Client::Client() : registerStatus(false), clntSockFd(0), isOperator(false), nickName(""), userName(""), realName("") {}

Client::Client(int newFd) : registerStatus(false), clntSockFd(newFd), isOperator(false), nickName(""), userName(""), realName("") {}

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
