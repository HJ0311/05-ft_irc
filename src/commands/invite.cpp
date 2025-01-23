#include "../../inc/Define.hpp"

std::string Request::execInvite(Client *inviter, Server &server) { 

	if (args.size() < 2)
		return (ERR_NEEDMOREPARAMS("INVITE"));

	if (!server.isClientExist(this->args[0])) {
		return (ERR_NOSUCHNICK(this->args[0]));
	}
	Client *invitee = server.getClient(this->args[0]);

	if (!server.isChannelExist(this->args[1]))
		return (ERR_NOSUCHCHANNEL(this->args[1]));
	
	Channel *channel = server.getChannel(this->args[1]);

	//초대한 사람이 채널에 있는지, 운영자인지
	if (!channel->isClientInChannel(inviter->getNickName()))
		return (ERR_NOTONCHANNEL(inviter->getNickName(), this->args[1]));
	if (!channel->isOperator(inviter->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(inviter->getNickName(), this->args[1]));
	
	//초대 받은 사람이 채널에 있는지
	if (channel->isClientInChannel(invitee->getNickName()))
		return (ERR_USERONCHANNEL(inviter->getNickName(), this->args[1], this->args[0]));

	channel->inviteClient(invitee->getNickName());
	std::string message =  INVITE(inviter->getNickName(), inviter->getUserName(), inviter->getHostName(), invitee->getNickName(), this->args[1]);
	send(invitee->getClntSockFd(), message.c_str(), message.length(), 0);

	return (RPL_INVITING(inviter->getNickName(), invitee->getNickName(), this->args[1]));
}
