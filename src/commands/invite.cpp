#include "../../inc/Define.hpp"

std::string Request::execInvite(Client *inviter, Server &server) { 

	std::map<int, Client*>& clients = server.getAllClients();
	std::map<std::string, Channel*>& channels = server.getAllChannels();

	if (args.size() < 2)
		return (ERR_NEEDMOREPARAMS("INVITE"));
	
	Client *invitee = NULL;
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (this->args[0] == it->second->getNickName())
			invitee = it->second;
    }
	if (invitee == NULL)
		return (ERR_NOSUCHNICK(this->args[0]));

	Channel *channel;
	if (server.getAllChannels().find(this->args[1]) == server.getAllChannels().end())
	{
		channel = new Channel(this->args[1]);
		channels[this->args[1]] = channel;
	}
	else
		channel = channels.at(this->args[1]);

	// if (!channel->isClientInChannel(inviter->getNickName()))
	// 	return ("");
	return ("");
// 127.000.000.001.06667-127.000.000.001.45310: :irc.local 442 jungslee #1 :You're not on that channel!
	// if ()
	//args 개수 보고 ERR_NEEDMOREPARAMS
	//nickname이 client list 안에 없으면 ERR_NOSUCHNICK
	//Channel이 있으면 그 채널에, 없으면 새로 생성

	//invite  -ONly 채널일때?? 
		// 이 명령을 보내는 클라이언트가 자격이 있는지를 알아랴함.
}