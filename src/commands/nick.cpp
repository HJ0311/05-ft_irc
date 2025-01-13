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

std::string Request::execNick(Client *client, std::map<int, Client*>& clients) {
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

	std::string nick = client->getNickName();
	std::string user = client->getUserName();
	std::string host = client->getHostName();

	if (client->getNickName() != "")//서버 연결 시 인증과정에서의 NICK이 아닐 때는 변경에 대한 성공 메세지를 보내야 함.
		result = NICK(nick, user, host, this->args[0]);
	else if (client->getUserName() != "")
			result =  RPL_WELCOME(nick, user, host)
						+ RPL_YOURHOST(nick)
						+ RPL_CREATED(nick, Utils::getTime());

	client->setNickName(this->args[0]);
	return (result);
}