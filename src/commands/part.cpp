#include "../../inc/Define.hpp"

std::string Request::execPart(Client *client, Server &server)
{
	if (args.empty())
		return ("ERROR: PART requires a channel name.\n");

	const std::string &channelName = args[0];

	Channel *channel;
	if (server.getAllChannels().find(channelName) == server.getAllChannels().end())
		return (ERR_NOSUCHCHANNEL(channelName));
//127.000.000.001.37504-127.000.000.001.06667: PART #1st
//127.000.000.001.06667-127.000.000.001.37504: :irc.local 403 nick #1st :No such channel

	if (channel->isClientInChannel(client->getNickName()) == 0)
		return (ERR_NOMOTD(client->getNickName(), channelName));
//127.000.000.001.37504-127.000.000.001.06667: PART #3rd
//127.000.000.001.06667-127.000.000.001.37504: :irc.local 442 nick #3rd :You're not on that channel

	channel->removeClient(client->getNickName());
	if (channel->getClientCount() == 0)
	{
		std::map<std::string, Channel*>::iterator	it = server.getAllChannels().find(channel->getName());
		delete it->second;
		server.getAllChannels().erase(it);
	}

	return (":" + client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " PART :" + channelName + "\r\n");
//127.000.000.001.37504-127.000.000.001.06667: PART #1st
//127.000.000.001.06667-127.000.000.001.37504: :nick!root@127.0.0.1 PART :#1st
//해당 channel에서 client를 빼면서 channel에 참여자가 0명이면 채널을 닫는다.
}