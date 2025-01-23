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
	
	if (request.command == "NICK")
		return (request.execNick(client, *this));
	else if (request.command == "JOIN")
		return (request.execJoin(client, *this));
	else if (request.command == "USER")
		return (request.execUser(client));
	else if (request.command == "INVITE")
		return (request.execInvite(client, *this));
	else if (request.command == "PRIVMSG")
		return (request.execPrivmsg(client, *this));
	else if (request.command == "TOPIC")
		return (request.execTopic(client, *this));
	else if (request.command == "MODE")
		return (request.execMode(client, *this));
	else if (request.command == "PART")
		return (request.execPart(client, *this));
	else if (request.command == "KICK")
		return (request.execKick(client, *this));
	else if (request.command == "PING")
		return (PONG());
	else if (request.command == "QUIT")
		return (request.execQuit(client, *this));
	else
		return ("");
}
