#include "../../inc/Define.hpp"

std::string Request::execQuit(Client *client, Server &server)
{
	std::string	quitMessage = "ERROR :Closing link: (" + client->getUserName() + "@" + client->getHostName() + ") [Quit: leaving]\r\n";

	send(client->getClntSockFd(), quitMessage.c_str(), quitMessage.size(), 0);

	quitMessage = ":" + client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " QUIT :Quit: leaving\r\n";

	std::set<int> clientsToNotify;
	std::set<std::string>	channels = client->getJoinedChannels();
	for (std::set<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::map<std::string, Channel*>::iterator channelIt = server.getAllChannels().find(*it);
		Channel* channel = channelIt->second;

		const std::map<int, Client*> &channelClients = channel->getClients();
		for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
		{
			Client *channelClient = it->second;
			if (channelClient != client)
				clientsToNotify.insert(channelClient->getClntSockFd());
		}
	}

	for (std::set<int>::iterator it = clientsToNotify.begin(); it != clientsToNotify.end(); ++it)
	{
		send(*it, quitMessage.c_str(), quitMessage.size(), 0);
	}

	return ("");
}
