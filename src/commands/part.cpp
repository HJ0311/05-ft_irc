#include "../../inc/Define.hpp"

std::string Request::execPart(Client *client, Server &server)
{
	if (args.empty())
		return ("ERROR: PART requires a channel name.\n");

	const std::string&	channelName = args[0];

	Channel	*channel;
	std::map<std::string, Channel*>::iterator it = server.getAllChannels().find(channelName);
	if (it == server.getAllChannels().end())
		return (ERR_NOSUCHCHANNEL(channelName));

	channel = it->second;
	if (channel->isClientInChannel(client->getNickName()) == 0)
		return (ERR_NOMOTD(client->getNickName(), channelName));

	std::string	partMessage = ":" + client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " PART :" + channelName + "\r\n";

	send(client->getClntSockFd(), partMessage.c_str(), partMessage.length(), 0);

	const std::map<int, Client*> &channelClients = channel->getClients();
	for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
	{
		int clientFd = it->first;
		if (clientFd != client->getClntSockFd())
			send(clientFd, partMessage.c_str(), partMessage.length(), 0);
	}

	channel->removeClient(client->getNickName());
	if (channel->getClientCount() == 0)
	{
		std::map<std::string, Channel*>::iterator	it = server.getAllChannels().find(channelName);
		delete it->second;
		server.getAllChannels().erase(it);
	}
	client->removeChannel(channelName);

	return ("");
}
