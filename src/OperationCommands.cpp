#include "../inc/Define.hpp"

std::string Request::execPass(const Server &server, bool &registerStatus) {
	if (registerStatus) 
		return Utils::RPL_462;

	if (server.getPassword() != this->args[0]) 
		return Utils::RPL_464;

	registerStatus = true;
	return ("");
}

bool Request::validateNick(const std::string &nick) {
	
	char special[] = {'-', '[', ']', '^', '{', '}'};

	if (!isalpha(nick[0]) || nick.length() > 9)
		return false;
	for (std::string::const_iterator it = nick.begin(); it != nick.end(); ++it) {
		char *p = std::find(special, special + 5, *it);
        if (!isalnum(*it) && (p == special + 5)) {
			return false;
        }
    }
	return true;
}

std::string Request::execNick(Client *client, std::map<int, Client*> clients) {
	//TODO 자원 부족으로 닉네임, 유저네임 설정할 수 없을 때 ERR_UNAVAILRESOURCE (437)
	//TODO 닉네임 변경을 막아놓았을 때 ERR_RESTRICTED (484)

	if (this->args.size() == 0)
		return (Utils::RPL_431);//ERR_NONICKNAMEGIVEN 

	if (this->args[0] == client->getNickName()) //이미 나의 닉네임일때
		return ("");

	if (!validateNick(this->args[0]))
		return(Utils::RPL_432);

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (this->args[0] == it->second->getNickName())
			return (Utils::RPL_433);//ERR_NICKNAMEINUSE
    }
	
	std::string result = "";
	if (client->getUserName() != "")//서버 연결 시 인증과정에서의 NICK이 아닐 때는 변경에 대한 성공 메세지를 보내야 함.
		result = ":" + client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " NICK :" + this->args[0];
	client->setNickName(this->args[0]);
	return (result);
}

std::string Request::execUser(Client *client, std::map<int, Client*> clients) {
	if (this->args.size() != 4)
		return Utils::RPL_461;

	if (client->getUserName() != "")
		return Utils::RPL_462;
	
	client->setUserName(this->args[0]);

	std::stringstream RPL_CONNECTION_SUCCESS;
    RPL_CONNECTION_SUCCESS << ":irc.local 001 " << client->getNickName() << " :Welcome to the Localnet IRC Network jungslee!root@127.0.0.1\r\n"
                           << ":irc.local 002 " << client->getNickName() << " :Your host is irc.local, running version V1\r\n"
                           << ":irc.local 003 " << client->getNickName() << " :This server was created " << Utils::getTime() + "\r\n";
	return (RPL_CONNECTION_SUCCESS.str());
}
std::string Request::execPrivmsg(Client *sender, const Server &server)
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
			return (Utils::RPL_403);

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

// USER <username> <unused> <unused> <realname> : 서버에 자신을 등록
