#include "../../inc/Define.hpp"

std::string Request::execPrivmsg(Client *sender, Server &server)
{
	if (args.size() < 2)
		return "ERROR: PRIVMSG requires a target and a message.\n";

	const std::string	&target = args[0]; // 대상 (채널명 또는 사용자 닉네임)
	const std::string	&message = args[1]; // 메시지

	std::string	senderNickname = sender->getNickName();
	std::string	senderUsername = sender->getUserName();
	std::string	senderHostname = sender->getHostName();

	std::string outgoingMessage = ":" + senderNickname + "!" + senderUsername + "@" + senderHostname +
								  " PRIVMSG " + target + " :" + message + "\r\n";

	if (target[0] == '#')//messages to a channel
	{
		Channel *targetChannel = server.getAllChannels().at(target);
		if (!targetChannel)
			return (ERR_NOSUCHCHANNEL(target));

		if (targetChannel->isClientInChannel(sender->getNickName()) == 0)
			return (ERR_CANNOTSENDTOCHAN(sender->getNickName(), target));

		const std::map<int, Client*> &channelClients = targetChannel->getClients();
		for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
		{
			Client *channelClient = it->second;
			if (channelClient != sender)
				send(channelClient->getClntSockFd(), outgoingMessage.c_str(), outgoingMessage.size(), 0); // send to client
		}
		return (""); // 채널 전송은 직접 처리했으므로 빈 문자열 반환
	}
	else//messages to a client
	{
		for (std::map<int, Client*>::const_iterator it = server.clients.begin(); it != server.clients.end(); ++it)
		{
			Client *receiver = it->second;
			if (receiver->getNickName() == target)
				return (outgoingMessage); // 대상 유저에게 전송할 메시지 반환
				// send(serverClient->getFd(), outgoingMessage.c_str(), outgoingMessage.size(), 0); // 전송
			// return ""; // 메시지를 전송했으므로 빈 문자열 반환
		}
		return (ERR_NOSUCHNICK(target)); // 대상 유저 없음
	}
}
