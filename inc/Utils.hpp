#pragma once

#include "Define.hpp"

class Client;

namespace Utils
{
	int	getMaxFd(const std::vector<Client>& clients, int servSock);
	void	clearBuffer(char* buff, int size);
}