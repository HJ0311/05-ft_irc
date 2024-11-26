#include "../inc/Define.hpp"

Client::Client() : ip("\0"), fd(-1), port(-1), isRegistered(false) {}

Client::Client(int fd, int port) : ip("\0"), fd(fd), port(port), isRegistered(false) {}

Client::Client(const Client& obj)
{
	*this = obj;
}

Client&	Client::operator=(const Client& obj)
{
	if (this != &obj)
	{
		this->port = obj.port;
		this->fd = obj.fd;
		this->isRegistered = obj.isRegistered;
		this->nickName = obj.nickName;
		this->hostName = obj.hostName;
		this->serverName = obj.serverName;
		this->userName = obj.userName;
		strcpy(this->ip, obj.ip);
	}
	return *this;
}

Client::~Client() {}

int	Client::getFd() const
{
	return this->fd;
}

int	Client::getPort() const
{
	return this->port;
}

std::string	Client::getNickName() const
{
	return this->nickName;
}

std::string	Client::getHostName() const
{
	return this->hostName;
}

std::string	Client::getServerName() const
{
	return this->serverName;
}

std::string	Client::getUserName() const
{
	return this->userName;
}