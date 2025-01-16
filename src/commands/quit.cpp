#include "../../inc/Define.hpp"

std::string Request::execQuit(Client *client, Server &server)
{
	std::string	quitMessage = ":" + client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " QUIT :Quit: leaving\r\n";

	std::set<std::string>	channels = client->getJoinedChannels();
	for (std::set<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::map<std::string, Channel*>::iterator channelIt = server.getAllChannels().find(*it);
		Channel* channel = channelIt->second;

		channel->removeClient(client->getNickName());
		if (channel->getClientCount() == 0)
		{
			delete channel;
			server.getAllChannels().erase(channelIt);
		}
	}

	//server.clients에서 delete 해야하는지?
	//kill의 경우 벌어지는 일?
	//겹치는 게 있는 경우 참여 채널에서 클라이언트 지우면서 채널 참여자 0이면 채널 지우는 걸 소멸자로 옮긴다

	return (quitMessage);
}
