#include "../../inc/Define.hpp"

std::string Request::execTopic(Client *client, Server &server) { 
	if (this->args.size() < 1)
		return (ERR_NEEDMOREPARAMS("TOPIC"));
	
	if (!server.isChannelExist(this->args[0]))
		return (ERR_NOSUCHCHANNEL(this->args[0]));
	
	Channel *channel = server.getChannel(this->args[0]);

	if (!channel->isClientInChannel(client->getNickName()))
		return (ERR_NOTONCHANNEL(client->getNickName(), this->args[0]));

	if (!channel->isOperator(client->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(client->getNickName(), this->args[0]));
	
	if (this->args.size() == 2) {
		channel->setTopic(this->args[1]);
		channel->broadcastMessage(TOPIC(client->getNickName(), client->getUserName(), client->getHostName(), this->args[0], this->args[1]));
		// std::map<int, Client*> clients = channel->getClients();
		// for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
		// {
		// 	std::string message = TOPIC(client->getNickName(), client->getUserName(), client->getHostName(), this->args[0], this->args[1]);
		// 	send(it->second->getClntSockFd(), message.c_str(), message.length(), 0);
		// }	
		return ("");
	}

	if (channel->getTopic() == "")
		return (RPL_NOTOPIC(this->args[0]));
	
	return (RPL_TOPIC(this->args[0], channel->getTopic()));
}