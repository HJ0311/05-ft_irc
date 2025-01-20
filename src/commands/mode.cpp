#include "../../inc/Define.hpp"

std::string Request::prepareModeParams(Channel *channel)
{
	std::ostringstream modeParams;
		
	if (channel->getIsPrivate())
		modeParams << "key(" << channel->getKey() << ") ";
	if (channel->getClientLimit() >= 0)
		modeParams << "limit(" << channel->getClientLimit() << ") ";
	
	return (modeParams.str());
}

std::string Request::execMode(Client *client, Server &server) {
	if (args.size() == 0)
		return (ERR_NEEDMOREPARAMS("MODE"));

	if (!server.isChannelExist(args[0]))
		return (ERR_NOSUCHCHANNEL(args[0]));
	
	Channel *channel = server.getChannel(args[0]);

	if (!channel->isOperator(client->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(client->getNickName(), this->args[0]));

	if (args.size() == 1)
		return (RPL_CHANNELMODEIS(client->getNickName(), this->args[0], channel->getMode(), prepareModeParams(channel)));

	int sign = 0;
	//mode 옵션은 무조건 붙여서 써야하는 것으로
	for (int i = 0; i < args[0].size(); i++) {
		if (args[0][i] == '+')
			sign = 1;
		else if (args[0][i] == '-')
			sign = -1;
		else if (args[0][i] == "t")
			changeTopicMode(sign, *this, channel); //파라미터 불필요
		else if (args[0][i] == "i")
			changeInviteMode(sign, *this, channel); // 파라미터 불필요
		else if (args[0][i] == "k")
			changePasswordMode(sign, *this, channel);// 파라미터 필요
		else if (args[0][i] == "o")
			changeOperatorMode(sign, *this, channel); // 파라미터 필요 -> 표시 불필요
		else if (args[0][i] == "l")
			changeClientLimitMode(sign, *this, channel);// 파라미터 필요
	}
	// return result;
	// return "";
}


//TODO 최대 메세지 길이 제한 512byte
//TODO user name 길이 제한 