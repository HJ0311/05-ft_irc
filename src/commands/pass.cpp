#include "../../inc/Define.hpp"

std::string Request::execPass(const Server &server, Client *client) {

	if (this->args.size() < 1)
		return ERR_NEEDMOREPARAMS("PASS");

	if (client->getRegisterStatus()) 
		return ERR_ALREADYREGISTERED();

	if (server.getPassword() != this->args[0]){
		client->setErrorClose(true);
		return ERR_PASSWDMISMATCH();
	}

	client->setRegisterStatus(true);
	return ("");
}
