#include "../../inc/Define.hpp"

std::string Request::execKick(Client *client, Server &server) { 
	//TODO BADCHANMASK...
	if (args.size() < 2)
		return (ERR_NEEDMOREPARAMS("KICK"));
	
	if (!server.isChannelExist(this->args[0]))
		return (ERR_NOSUCHCHANNEL(this->args[0]));
	
	Channel *channel = server.getChannel(this->args[0]);

	if (!channel->isOperator(client->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(client->getNickName(), this->args[0]));

	if (!channel->isClientInChannel(this->args[1]))
		return (ERR_NOTONCHANNEL(this->args[1], this->args[0]));
	
	if (client->getNickName() == this->args[1])
		return ("");

	channel->broadcastMessage(KICK(client->getNickName(), client->getUserName(), client->getHostName(), this->args[0], this->args[1], content));
	
	channel->removeClient(this->args[1]);
	if (channel->isOperator(this->args[1]))
		channel->removeOperator(this->args[1]);

	std::string content = "";
	if (args.size() == 3)
		content = this->args[2];

	return ("");
}

//자기자신을 킥하는 경우??