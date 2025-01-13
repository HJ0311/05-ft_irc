#include "../../inc/Define.hpp"

std::string Server::registerHandler(const std::string &message, int i)
{
	int	senderFd = this->pfds[i].fd;
	Request	request(parsingCommand(message));
	Client *client = this->clients.find(senderFd)->second;
	(void)i;

    if (request.command == "PASS")
		return (request.execPass(*this, client));

	if (request.command == "NICK" || request.command == "USER") {
		client->setErrorClose(true);
		return ERR_NEEDMOREPARAMS("PASS");
	}

	return ("");
}

std::string	Server::commandHandler(const std::string &message, int i)
{
	int	senderFd = this->pfds[i].fd;
	Request	request(parsingCommand(message));
	Client *client = this->clients.find(senderFd)->second;
	(void)i;
	
	if (request.command == "KILL")
		return ("KILL\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "NICK")
		return (request.execNick(client, this->clients));
	else if (request.command == "JOIN")
		return (request.execJoin(client, *this));
	else if (request.command == "USER")
		return (request.execUser(client));
	else if (request.command == "INVITE")
		return (request.execInvite(client, this->clients)); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PRIVMSG")
		return (request.execPrivmsg(client, *this)); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "WHOIS")
		return (request.execWhois());
	else if (request.command == "TOPIC")
		return ("TOPIC\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "MODE")
		return ("MODE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PART")
		return (request.execPart(client, *this));
	else if (request.command == "NAMES")
		return ("NAMES\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "LIST")
		return ("LIST\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "KICK")
		return ("KICK\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "NOTICE")
		return ("NOTICE\n"); // 명령어 처리 함수로 바꿀 것
	else if (request.command == "PING")
		return (PONG());
	else
		return ("");
	// else if (request.command == "NOTICE")//NOTICE는 자동 응답을 방지하는 특수한 용도로 필요, 필요한가?
	// 	return ("NOTICE\n"); // 명령어 처리 함수로 바꿀 것
}
