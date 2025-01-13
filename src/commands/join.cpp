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
		return ("");//여기서 초반에 채널 생성하면. 만든 client가 채널에 참여하고 있는 사람으로 추가되어야할 것 같다.

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
//Join 에러를 반환하는 경우를 먼저 걸러내고 new 로 채널을 생성해야할 것 같다.
//send는 이 안에서 하지 않아도 된다! 해당 string을 리턴하면 됨