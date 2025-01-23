#include "../../inc/Define.hpp"

void	Server::clientRequest(int i)
{
	char	buf[5000]; // recv는 저수준 네트워크 함수로 설계 되었으므로 char 배열이 더 효율적이다. std::stirng을 사용하면 매 수신/송신마다 오버헤드가 추가적으로 생김
	int	senderFd = this->pfds[i].fd;
	int	recvBytes = recv(senderFd, buf, sizeof(buf), 0); // 특정 클라이언트에서 서버로 보내는 데이터 받아 buf에 저장
	Client *client = this->clients.find(senderFd)->second;

	if (recvBytes <= 0)
	{
		if (recvBytes == 0)
			std::cerr << RED << "[" << Utils::getTime() << "] socket" << senderFd << ": disconnected" << RESET << std::endl;
		else
			std::cerr << RED << "recv() error" << RESET << std::endl;
		send(senderFd, ERROR(client->getUserName(), client->getHostName()).c_str(), ERROR(client->getUserName(), client->getHostName()).length(), 0);
		removeFromChannels(this->clients[senderFd]);
		close(senderFd);
		removeFromPoll(i);
	}
	else
		execCommandByLine(i, buf);
	memset(&buf, 0, 5000);
}

void Server::execCommandByLine(int i, const std::string &message)
{
	size_t idx = 0;
	int	senderFd = this->pfds[i].fd;
	Client *client = this->clients.find(senderFd)->second;

	while (1) {
		size_t preIdx = idx;
		idx = message.find("\r\n", idx);
		if (idx == std::string::npos)
			break;
		std::string line = message.substr(preIdx, idx - preIdx);
		std::string result;
		if (!client->getRegisterStatus()) 
			result = registerHandler(line, i);
		else
			result = commandHandler(line, i);
		if (send(senderFd, result.c_str(), result.length(), 0) < 0)
			std::cerr << RED << "send() error" << RESET << std::endl;
		if (client->getErrorClose()) {
			send(senderFd, ERROR(client->getUserName(), client->getHostName()).c_str(), ERROR(client->getUserName(), client->getHostName()).length(), 0);
			close(senderFd);
			removeFromPoll(i);
			std::cerr << RED << "[" << Utils::getTime() << "] socket" << senderFd << ": disconnected" << RESET << std::endl;
			return ;
		}
		idx += 2;
	}
}

Request	Server::parsingCommand(const std::string& message) const
{
	Request request;

	std::vector<std::string>	splitStr;
	std::stringstream	ss(message);
	std::string	token;
	std::string trailing = "";
	bool colonFlag = false;

	while (std::getline(ss, token, ' '))
	{
		if (token.find(':', 0) != std::string::npos)
			colonFlag = true;

		if (colonFlag)
			trailing.append(" ").append(token);
		else if (!token.empty())
			splitStr.push_back(token);
	}
	if (!trailing.empty())
		splitStr.push_back(trailing);

	if (splitStr.empty())
	{
		request.command = "";
		return request;
	}
	request.command = splitStr[0];
	for (std::vector<std::string>::iterator it = splitStr.begin() + 1; it != splitStr.end(); ++it)
	{
		request.args.push_back(*it);
	}
	return request;
}
