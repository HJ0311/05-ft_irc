#include "../inc/Define.hpp"

void	Server::clientRequest(int i)
{
	char	buf[5000]; // recv는 저수준 네트워크 함수로 설계 되었으므로 char 배열이 더 효율적이다. std::stirng을 사용하면 매 수신/송신마다 오버헤드가 추가적으로 생김
	int	senderFd = this->pfds[i].fd;
	int	recvBytes = recv(senderFd, buf, sizeof(buf), 0); // 특정 클라이언트에서 서버로 보내는 데이터 받아 buf에 저장

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
		std::string	result = parsing(buf, i);
		if (send(senderFd, result.c_str(), result.length(), 0) < 0) // 명령어를 파싱한 뒤 그 결과물을 다시 클라이언트에게 전송
			std::cerr << RED << "send() error" << RESET << std::endl;
	}
	memset(&buf, 0, 5000);
}

std::string	Server::parsing(const std::string& message, int i)
{
	Request	request(splitCommand(message));

	if (request.command.empty())
		return ("Invalid Command!\n");

	if (request.command == "PASS")
		return ("PASS\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "KILL")
		return ("KILL\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "MODE")
		return ("MODE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "NICK")
		return ("NICK\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PART")
		return ("PART\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "NANES")
		return ("NAMES\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "LIST")
		return ("LIST\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "KICK")
		return ("KICK\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "JOIN")
		return (commandJoin(request, i)); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "INVITE")
		return ("INVITE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "TOPIC")
		return ("TOPIC\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "NOTICE")
		return ("NOTICE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PRIVMSG")
		return ("PRIVMSG\n"); // 명령어 처리 함수로 바꿀 것
	else
		return ("Invalid Command!\n");
}

Request	Server::splitCommand(const std::string& message) const
{
	Request	request;

	std::vector<std::string>	splitStr;
	std::stringstream	ss(message);
	std::string	token;

	while (std::getline(ss, token, ' '))
	{
		if (!token.empty())
			splitStr.push_back(token);
	}
	if (splitStr.empty())
	{
		request.command = "";
		return request;
	}
	request.command = splitStr[0];
	if (request.command.back() == '\n')
		request.command.pop_back();
	for (std::vector<std::string>::iterator it = std::next(splitStr.begin(), 1); it != splitStr.end(); ++it)
	{
		if (it->back() == '\n')
			it->pop_back();
		request.args.push_back(*it);
	}
	return (request);
}