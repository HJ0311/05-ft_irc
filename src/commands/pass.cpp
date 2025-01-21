#include "../../inc/Define.hpp"

std::string Request::execPass(const Server &server, Client *client) {

	if (client->getRegisterStatus()) 
		return ERR_ALREADYREGISTERED();

	if (this->args.size() < 1) {
		client->setErrorClose(true);
		std::cout << "errorClose 2" << std::endl;

		return ERR_NEEDMOREPARAMS("PASS");
	}

	if (server.getPassword() != this->args[0]){
		std::cout << "errorClose 3" << std::endl;
		client->setErrorClose(true);
		return ERR_PASSWDMISMATCH();
	}

	client->setRegisterStatus(true);
	return ("");
}
