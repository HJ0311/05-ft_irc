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
		std::string	message(buf, strlen(buf) - 1);
		
		if (message.back() == '\r')
			message.erase(message.end() - 1);
		if (send(senderFd, message.c_str(), message.length(), 0) < 0)
			std::cerr << "send() error" << std::endl;
	}
	memset(&buf, 0, 5000);
}