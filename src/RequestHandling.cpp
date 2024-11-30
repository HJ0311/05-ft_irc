#include "../inc/Define.hpp"

void	Server::clientRequest(int i)
{
	char	buf[5000];
	int	senderFd = this->pfds[i].fd;
	int	recvBytes = recv(senderFd, buf, sizeof(buf), 0);

	if (recvBytes <= 0)
	{
		if (recvBytes == 0)
			std::cerr << RED << "[" << Utils::getTime() << "] socket" << senderFd << ": disconnected" << RESET << std::endl;
		else
			std::cerr << RED << "recv() error" << RESET << std::endl;
		close(senderFd);
		removeFromPoll(i);
	}
	else
	{
		// command 처리
	}
	memset(&buf, 0, 5000);
}