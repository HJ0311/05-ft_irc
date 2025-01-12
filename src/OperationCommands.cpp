#include "../inc/Define.hpp"

std::string Request::execPass(const Server &server, Client *client) {
	if (client->getRegisterStatus()) 
		return ERR_ALREADYREGISTERED();

	if (server.getPassword() != this->args[0]){
		client->setErrorClose(true);
		return ERR_PASSWDMISMATCH();
	}

	client->setRegisterStatus(true);
	return ("");
}

bool Request::validateNick(const std::string &nick) {
	
	char special[] = {'-', '[', ']', '^', '{', '}'};
	size_t size = sizeof(special) / sizeof(special[0]);

	if (!isalpha(nick[0]) || nick.length() > 9)
		return false;
	for (std::string::const_iterator it = nick.begin(); it != nick.end(); ++it) {
		char *p = std::find(special, special + size, *it);
        if (!isalnum(*it) && (p == special + size)) {
			return false;
        }
    }
	return true;
}

std::string Request::execNick(Client *client, std::map<int, Client*> clients) {
	std::string result = "";

	if (this->args.size() == 0)
		result = ERR_NONICKNAMEGIVEN();

	if (this->args[0] == client->getNickName())
		return ("");

	if (!validateNick(this->args[0]))
		result = ERR_ERRONEUSNICKNAME(this->args[0]);

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (this->args[0] == it->second->getNickName())
			result = ERR_NICKNAMEINUSE(this->args[0]);
    }

	if (result != "" && client->getNickName() == "") {
		client->setErrorClose(true);
		return (result);
	}
	
	if (client->getNickName() != "")//서버 연결 시 인증과정에서의 NICK이 아닐 때는 변경에 대한 성공 메세지를 보내야 함.
		result = NICK(client->getNickName(), client->getUserName(), client->getHostName(), this->args[0]);

	client->setNickName(this->args[0]);
	return (result);
}

std::string Request::execUser(Client *client) {
	if (this->args.size() != 4) {
		client->setErrorClose(true);
		return ERR_NEEDMOREPARAMS("USER");
	}

	if (client->getUserName() != "") {
		client->setErrorClose(true);
		return ERR_ALREADYREGISTERED();
	}
	
	client->setUserName(this->args[0]);

	std::string nick = client->getNickName();
	std::string user = client->getUserName();
	std::string host = client->getHostName();
	return (RPL_WELCOME(nick, user, host)
			+ RPL_YOURHOST(nick)
			+ RPL_CREATED(nick, Utils::getTime())
		);
}

std::string Request::execWhois() {
	
}

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


// PASS <password> : 로컬 네트워크에 연결

// KILL <nickname> <nickname> ...: 네트워크에서 강제로 연결 해제

// MODE <options>
// -i: 초대 전용 채널 설정/제거
// -t: 채널 운영자에게 TOPIC 명령의 제한 설정/제거
// -k: 채널의 키 설정/제거(비밀번호)
// -o: 채널 운영자 권한 지급/압수
// -l: 채널에 대한 사용자의 제한 설정/제거

// USER <username> <unused> <unused> <realname> : 서버에 자신을 등록


std::string Request::execInvite(Client *inviter, std::map<int, Client*> clients) { 

// 	if (args.size() < 2)
// 		return (ERR_NEEDMOREPARAMS("INVITE"));
	

// 	Client *invitee = NULL;
// 	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
// 		if (this->args[0] == it->second->getNickName())
// 			invitee = it;
//     }
// 	if (invitee == NULL)
// 		return (ERR_NOSUCHNICK(this->args[0]));

// 	Channel *channel;
// 	if (server.getAllChannels().find(this->args[1]) == server.getAllChannels().end())
// 	{
// 		channel = new Channel(this->args[1]);
// 		server.getAllChannels()[this->args[1]] = channel;
// 	}
// 	else
// 		channel = server.getAllChannels().at(channelName);

// 	if (channel->isClientInChannel(client->getNickName()))
// 		return ("");
// 127.000.000.001.06667-127.000.000.001.45310: :irc.local 442 jungslee #1 :You're not on that channel!
// 	if ()
	//args 개수 보고 ERR_NEEDMOREPARAMS
	//nickname이 client list 안에 없으면 ERR_NOSUCHNICK
	//Channel이 있으면 그 채널에, 없으면 새로 생성

	//invite  -ONly 채널일때?? 
		// 이 명령을 보내는 클라이언트가 자격이 있는지를 알아랴함.
}