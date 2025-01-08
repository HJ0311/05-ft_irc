#include "../inc/Define.hpp"

std::string Request::execPrivmsg(int senderFd, const Server &server)
{
	if (args.size() < 2)
		return "ERROR: PRIVMSG requires a target and a message.\n";

	const std::string	&target = args[0]; // 대상 (채널명 또는 사용자 닉네임)
	const std::string	&message = args[1]; // 메시지

	Client *senderClient = server.clients.at(senderFd); // Sender Client
	if (!senderClient)
		return "ERROR: Sender not found.\n";

	std::string	senderNickname = senderClient->getNickName();
	std::string	senderUsername = senderClient->getUserName();
	std::string	senderHostname = senderClient->getHostName();

	std::string outgoingMessage = ":" + senderNickname + "!" + senderUsername + "@" + senderHostname +
								  " PRIVMSG " + target + " :" + message + "\r\n";

	if (target[0] == '#')//messages to a channel
	{
		Channel *targetChannel = server.allChannels.at(target);
		if (!targetChannel)
			return (Utils::RPL_403);

		const std::map<int, Client*> &channelClients = targetChannel->getClients();
		for (std::map<int, Client*>::const_iterator it = channelClients.begin(); it != channelClients.end(); ++it)
		{
			int clientFd = it->first;
			if (clientFd != senderFd)
				send(clientFd, outgoingMessage.c_str(), outgoingMessage.size(), 0); // 직접 전송, 하나의 fd로 보내는 게 아니어서
		}
		return (""); // 채널 전송은 직접 처리했으므로 빈 문자열 반환
	}
	else//messages to a client
	{
		for (std::map<int, Client*>::const_iterator it = server.clients.begin(); it != server.clients.end(); ++it)
		{
			Client *client = it->second;
			if (client->getNickName() == target)
				return (outgoingMessage); // 대상 유저에게 전송할 메시지 반환
		}
		return (Utils::RPL_401); // 대상 유저 없음
	}
}
//404 - 사용자가 채널에 메시지를 보낼 권한이 없음.

// PASS <password> : 로컬 네트워크에 연결

// KILL <nickname> <nickname> ...: 네트워크에서 강제로 연결 해제

// MODE <options>
// -i: 초대 전용 채널 설정/제거
// -t: 채널 운영자에게 TOPIC 명령의 제한 설정/제거
// -k: 채널의 키 설정/제거(비밀번호)
// -o: 채널 운영자 권한 지급/압수
// -l: 채널에 대한 사용자의 제한 설정/제거

// NICK <nickname>: 닉네임 설정

// USER <username> <unused> <unused> <realname> : 서버에 자신을 등록