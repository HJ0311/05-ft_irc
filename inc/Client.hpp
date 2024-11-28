#pragma once

#include "Define.hpp"

class Client
{
	public:
		Client(int newFd);
		~Client();

	private:
		Client();
		Client(const Client& obj);
		Client&	operator=(const Client& obj);

		int	clntSockFd;
};