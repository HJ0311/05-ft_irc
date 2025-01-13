#include "../../inc/Define.hpp"

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
	
	if (client->getNickName() != "")
		return (RPL_WELCOME(nick, user, host)
			+ RPL_YOURHOST(nick)
			+ RPL_CREATED(nick, Utils::getTime())
		);
	else 
		return ("");
}
