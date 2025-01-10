#include "../inc/Define.hpp"

void Server::execCommandByLine(int i, const std::string &message)
{
	size_t idx = 0;
	int	senderFd = this->pfds[i].fd;

	while (1) {//PASS password\r\nUSER user\r\n 이런식으로 여러번의 명령어가 붙어서 올 때를 고려하여 처리
		size_t preIdx = idx;
		idx = message.find("\r\n", idx);
		if (idx == std::string::npos)
			break;
		std::string line = message.substr(preIdx, idx - preIdx);
		std::string result;
		if (!this->clients.find(senderFd)->second->registerStatus) 
			result = registerHandler(line, i);
		else
			result = commandHandler(line, i);
		if (send(senderFd, result.c_str(), result.length(), 0) < 0) // 명령어를 파싱한 뒤 그 결과물을 다시 클라이언트에게 전송
			std::cerr << RED << "send() error" << RESET << std::endl;
		if (result == Utils::RPL_464 || result == Utils::RPL_461) {//TODO 여기에 연결을 끊어야 하는 경우 다 넣기
			close(this->pfds[i].fd);
			removeFromPoll(i);
			std::cerr << RED << "[" << Utils::getTime() << "] socket" << senderFd << ": disconnected" << RESET << std::endl;
			return ;
		}
		idx += 2;
	}
}

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
		execCommandByLine(i, buf);
	memset(&buf, 0, 5000);
}

std::string Server::registerHandler(const std::string& message, int i)
{//TODO 입력 타임아웃 처리?
	int	senderFd = this->pfds[i].fd;
	Request	request(parsingCommand(message));
	(void)i;

	if (request.command == "CAP")
		return ("");
	else if (request.command == "JOIN")
		return (""); // 명령어 처리 함수로 바꿀 것
    else if (request.command == "PASS")
		return (request.execPass(*this, this->clients.find(senderFd)->second->registerStatus));

	if (request.command == "NICK" || request.command == "USER") 
		return Utils::RPL_461;

	return ("");
}

std::string	Server::commandHandler(const std::string& message, int i)
{
	std::map<int, Client*>::iterator it = this->clients.find(this->pfds[i].fd);
	Request	request(parsingCommand(message));
	(void)i;
	// if (request.command.empty())
	// 	return ("Invalid Command!\n"); //없어도 되지 않을까?
	
	if (request.command == "KILL")
		return ("KILL\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "MODE")
		return ("MODE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "NICK")
		return (request.execNick(it->second, this->clients));
	else if (request.command == "JOIN")
		return (request.execJoin(it->second, *this));
	else if (request.command == "USER")
		return (request.execUser(it->second, this->clients));
	else if (request.command == "PART")
		return (request.execPart(it->second, *this));
	else if (request.command == "NAMES")
		return ("NAMES\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "LIST")
		return ("LIST\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "KICK")
		return ("KICK\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "INVITE")
		return ("INVITE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "TOPIC")
		return ("TOPIC\n"); // 명령어 처리 함수로 바꿀 것
	// else if (request.command == "NOTICE")//NOTICE는 자동 응답을 방지하는 특수한 용도로 필요, 필요한가?
	// 	return ("NOTICE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PRIVMSG")
		return (request.execPrivmsg(it->second, *this)); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PING")
		return (":irc.local PONG irc.local :irc.local\n");
	else if (request.command == "PONG")
		return ("PONG\n");
	else
		return ("Invalid Command!\n");
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
	for (std::vector<std::string>::iterator it = std::next(splitStr.begin(), 1); it != splitStr.end(); ++it)
	{
		request.args.push_back(*it);
	}
	return request;
}
