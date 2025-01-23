#include "../../inc/Define.hpp"

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

std::string Request::execNick(Client *client, Server &server) {
	std::string result = "";

	if (this->args.size() == 0)
		result = ERR_NONICKNAMEGIVEN();
	else if (this->args[0] == client->getNickName())
		return ("");
	else if (!validateNick(this->args[0]))
		result = ERR_ERRONEUSNICKNAME(this->args[0]);
	else if (server.isClientExist(this->args[0]))
		result = ERR_NICKNAMEINUSE(this->args[0]);

	if (result != "") {
		if (client->getNickName() == "")
			client->setErrorClose(true);
		return (result);
	}

	std::string nick = client->getNickName();
	std::string user = client->getUserName();
	std::string host = client->getHostName();

	if (client->getNickName() != "")
		result = NICK(nick, user, host, this->args[0]);
	else if (client->getUserName() != "")
			result =  RPL_WELCOME(nick, user, host)
						+ RPL_YOURHOST(nick)
						+ RPL_CREATED(nick, Utils::getTime())
						+ RPL_MYINFO(nick)
						+ START_IRC();

	client->setNickName(this->args[0]);

	std::set<std::string>	channels = client->getJoinedChannels();//닉네임 변경 시 오퍼레이터set에서도 업데이트
	for (std::set<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::map<std::string, Channel*>::iterator channelIt = server.getAllChannels().find(*it);
		Channel* channel = channelIt->second;

		if (channel->isOperator(nick))
		{
			channel->removeOperator(nick);
			channel->addOperator(this->args[0]);
		}
	}

	return (result);
}
