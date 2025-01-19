#include "../../inc/Define.hpp"

std::string Request::execMode(Client *client, Server &server) {
	if (args.size() == 0)
		return (ERR_NEEDMOREPARAMS("MODE"));
	// (void)client;
	// (void)server;
	if (!server.isChannelExist(args[0]))
		return (ERR_NOSUCHCHANNEL(args[0]));
	
	Channel *channel = server.getChannel(args[0]);

	if (!channel->isOperator(client->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(client->getNickName(), this->args[0]));

	if (args.size() == 1)


	int sign = 0;
	//mode 옵션은 무조건 붙여서 써야하는 것으로
	for (int i = 0; i < args[0].size(); i++) {
		if (args[0][i] == "+")
			sign = 1;
		else if (args[0][i] == "-")
			sign = -1;
		else if (args[0][i] == "t")
			result = changeTopicMode(sign, *this, client, server); //파라미터ㅑ 필요
		else if (args[0][i] == "i")
			result = changeInviteMode(mode, *this, client, server); // 파라미터 불필요
		else if (args[0][i] == "k")
			result = changePasswordMode(mode, *this, client, server);// 파라미터 필요
		else if (args[0][i] == "o")
			result = changeOperatorMode(mode, *this, client, server); // 파라미터 필요
		else if (args[0][i] == "l")
			result = changeClientLimitMode(mode, *this, client, server);// 파라미터 필요
	}

	// return result;
	return "";
}


//TODO 최대 메세지 길이 제한 512byte
//TODO user name 길이 제한 