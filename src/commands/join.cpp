#include "../../inc/Define.hpp"

void	joinOpt(Client *client, Channel *channel, std::string joinMessage)
{
	std::string	namesMessage = joinMessage;
	
	if (channel->getTopic() != "")
		namesMessage += RPL_TOPIC(channel->getName(), channel->getTopic());
	
	namesMessage += ":ircserv 353 " + client->getNickName() + " = " + channel->getName() + " :";

	std::map<int, Client*>	clients = channel->getClients();
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (channel->isOperator(it->second->getNickName()))
			namesMessage += "@";
		namesMessage += it->second->getNickName();
		namesMessage += " ";
	}
	namesMessage += "\r\n";
	namesMessage += RPL_ENDOFNAMES(client->getNickName(), channel->getName());

	send(client->getClntSockFd(), namesMessage.c_str(), namesMessage.length(), 0);
}

std::string Request::execJoin(Client *client, Server &server)
{
	if (args.empty())
		return (ERR_NEEDMOREPARAMS("JOIN"));

	const std::string &channelName = args[0];

	if (channelName[0] != '#' || channelName.length() > 200)
		return (ERR_BADCHANMASK(client->getNickName(), channelName));

	Channel *channel;
	if (server.getAllChannels().find(channelName) == server.getAllChannels().end())// 채널이 존재하지 않으면
	{
		channel = new Channel(channelName);
		server.getAllChannels()[channelName] = channel;
		channel->addOperator(client->getNickName());//channel operator에 현 client 넣기
	}
	else
		channel = server.getAllChannels().at(channelName);

	if (channel->isClientInChannel(client->getNickName()))
		return ("");

	if (channel->getChannelModes().at("i")) {
		if (!channel->isInvited(client->getNickName()))
			return (ERR_INVITEONLYCHAN(client->getNickName(), channelName));
		channel->removeInvitee(client->getNickName());
	}

	if (channel->getChannelModes().at("k"))
	{
		const std::string &enteredKey = args[1];
		if (enteredKey != channel->getKey())
			return (ERR_BADCHANNELKEY(client->getNickName(), channelName));
	}

	if (channel->isFull())
		return (ERR_CHANNELISFULL(client->getNickName(), channelName));

	channel->addClient(client);
	client->addChannel(channelName);

	std::string	joinMessage = ":" + client->getNickName() + "!" + client->getUserName() + "@"
							  + client->getHostName() + " JOIN :" + channelName + "\r\n";
	joinOpt(client, channel, joinMessage);
	// send(client->getClntSockFd(), joinMessage.c_str(), joinMessage.length(), 0);


	const std::map<int, Client*> &channelClients = channel->getClients();
	for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
	{
		int clientFd = it->first;
		if (clientFd != client->getClntSockFd())
			send(clientFd, joinMessage.c_str(), joinMessage.length(), 0);
	}

	return ("");
}
