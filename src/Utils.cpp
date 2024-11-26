#include "../inc/Define.hpp"

int	Utils::getMaxFd(const std::vector<Client>& clients, int servSock)
{
	if (clients.size() == 0)
		return servSock;
	int	max = clients[0].getFd();
	for (std::vector<Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (max < it->getFd())
			max = it->getFd();
	}
	return max;
}