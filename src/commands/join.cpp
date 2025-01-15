#include "../../inc/Define.hpp"

std::string Request::execJoin(Client *client, Server &server)
{
	if (args.empty())
		return ("ERROR: JOIN requires a channel name.\n");

	const std::string &channelName = args[0];

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

	if (channel->getIsInviteOnly())
		return (ERR_INVITEONLYCHAN(client->getNickName(), channelName));

	if (channel->getKey() != "")
	{
		const std::string &enteredKey = args[1];
		if (enteredKey != channel->getKey())
			return (ERR_BADCHANNELKEY(client->getNickName(), channelName));
	}

	if (channel->isFull())
		return (ERR_CHANNELISFULL(client->getNickName(), channelName));
	//TODO 에러인 경우 new로 할당한 채널을 free를해ㅔ주어야 한다.

	channel->addClient(client);

	std::string	joinMessage = ":" + client->getNickName() + "!" + client->getUserName() + "@"
							  + client->getHostName() + " JOIN :" + channelName + "\r\n";

	const std::map<int, Client*> &channelClients = channel->getClients();
	for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
	{
		int clientFd = it->first;
		if (clientFd == client->getClntSockFd())
			send(clientFd, joinMessage.c_str(), joinMessage.length(), 0);
	}
	for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
	{
		int clientFd = it->first;
		if (clientFd != client->getClntSockFd())
			send(clientFd, joinMessage.c_str(), joinMessage.length(), 0);
	}

	return ("");
}
//TODO invitee를 지워주는 작업도 해야함