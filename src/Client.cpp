#include "../inc/Define.hpp"

Client::Client() : clntSockFd(0) {}

Client::Client(int newFd) : clntSockFd(newFd) {}

Client::Client(const Client& obj)
{
	*this = obj;
}

Client&	Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->clntSockFd = obj.clntSockFd;
	}
	return *this;
}

Client::~Client() {}

// =================================================================================================================
// member function
// =================================================================================================================