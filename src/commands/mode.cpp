#include "../../inc/Define.hpp"

std::string Request::execMode(Client *client, Server &server) {

	if (args.size() < 1)
		return (ERR_NEEDMOREPARAMS("MODE"));

	if (server.isClientExist(args[0]))
		return ("");

	//입력한 채널에 대한 유효성 검사
	if (args[0][0] != '#' || args[0].length() > 200)
		return (ERR_BADCHANMASK(client->getNickName(), args[0]));

	if (!server.isChannelExist(args[0]))
		return (ERR_NOSUCHCHANNEL(args[0]));
	
	Channel *channel = server.getChannel(args[0]);

	//따로 플래그에 대한 파라미터가 없을때 현재의 설정된 모드를 반환
	if (args.size() == 1)
		return (RPL_CHANNELMODEIS(client->getNickName(), this->args[0], channel->getMode(), prepareModeParams(channel)));

	if (!channel->isOperator(client->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(client->getNickName(), this->args[0]));

	std::string err = validateModeFlag(client, args);
	if (err != "")
		return err;
		
	std::string result = handleMode(client, args, channel);

	channel->broadcastMessage(result);
	
	return "";
}

std::string Request::handleMode(Client *client, std::vector<std::string> &args, Channel *channel)
{
	char sign = '+';
	std::string flags = args[1]; 
	int	paramIdx = 2;


	std::ostringstream changedMode;
	std::ostringstream changedParam;

	//mode 옵션은 무조건 붙여서 써야 함. (+i +o (X) +i+o (O))
	for (size_t i = 0; i < flags.size(); ++i) {
		if (flags[i] == 't')
			changeTopicMode(sign, channel, changedMode); //파라미터 불필요
		else if (flags[i] == 'i')
			changeInviteMode(sign, channel, changedMode); // 파라미터 불필요
		else if (flags[i] == 'o')
			changeOperatorMode(client, sign, args, channel, paramIdx, changedMode, changedParam); // 파라미터 필요 -> 표시 불필요
		else if (flags[i] == 'l')
			changeClientLimitMode(client, sign, args, channel, paramIdx ,changedMode, changedParam);// 파라미터 필요
		else if (flags[i] == 'k') 
			changePasswordMode(sign, args, channel, paramIdx, changedMode, changedParam); // 필요
		else
			sign = flags[i];
	}
	
	std::string result = MODE(client->getNickName(), client->getUserName(), client->getHostName(), args[0], changedMode.str(), changedParam.str());
	return result;
}

std::string Request::prepareModeParams(Channel *channel)
{
	std::ostringstream modeParams;
		
	if (channel->getChannelModes().at("k"))
		modeParams << "key(" << channel->getKey() << ") ";
	if (channel->getChannelModes().at("l"))
		modeParams << "limit(" << channel->getMaxClient() << ") ";
	
	return (modeParams.str());
}

std::string Request::validateModeFlag(Client *client, std::vector<std::string> &args) {
	
	// char available[] = {'+', '-', 't', 'i', 'k', 'o', 'l'};
	// size_t size = sizeof(available) / sizeof(available[0]);
	size_t	paramSize = 0;
	std::string flags = args[1];
	int		sign = 1;

	for (size_t i = 0; i < flags.size(); ++i){
		// char *p = std::find(available, available + size, flags[i]);
		// if (p == available + size) {
		// 	return ERR_UNKNOWNMODE(client->getNickName(), flags[i]);
		// }
		if (flags[i] == '+')
			sign = 1;
		else if (flags[i] == '-')
			sign = -1;
		else if (flags[i] == 'o')
			paramSize++;
		else if (flags[i] == 'l' || flags[i] == 'k') {
			if (sign == 1)
				paramSize++;
		}
		else
			return ERR_UNKNOWNMODE(client->getNickName(), flags[i]);
	}

	if (args.size() < paramSize + 2) {
		return ERR_NEEDMOREPARAMS("MODE");
	}

	return "";
}

void Request::changeTopicMode(const char &sign, Channel *channel, std::ostringstream &modes) {
	if (sign == '+') {
		if (channel->getChannelModes().at("t"))
			return ;
		channel->setChannelModes("t", true);
		modes << "+t";
	} else {
		if (!channel->getChannelModes().at("t"))
			return ;
		channel->setChannelModes("t", false);
		modes << "-t";
	}
}

void Request::changeInviteMode(const char &sign, Channel *channel, std::ostringstream &modes) {
	if (sign == '+') {
		if (channel->getChannelModes().at("i"))
			return ;
		channel->setChannelModes("i", true);
		modes << "+i";
	} else {
		if (!channel->getChannelModes().at("i"))
			return ;
		channel->setChannelModes("i", false);
		modes << "-i";
	}
}

void Request::changePasswordMode(const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx, std::ostringstream &modes, std::ostringstream &params) {

	if (sign == '+') {
		int i = paramIdx;
		paramIdx++;
		if (channel->getChannelModes().at("k"))
			return ;
		channel->setChannelModes("k", true);
		channel->setKey(args[i]);
		modes << "+k";
		params << "key(" << args[i] << ") ";
	} else {
		if (!channel->getChannelModes().at("k"))
			return ;
		// if (channel->getKey() != args[i]) {
		// 	send(client->getClntSockFd(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "k", args[i]).c_str(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "k", args[i]).length(), 0);
		// 	return ;
		// }
		channel->setChannelModes("k", false);
		channel->setKey("");
		modes << "-k";
		params << "key() ";
	}
}

void Request::changeOperatorMode(Client *client, const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx, std::ostringstream &modes, std::ostringstream &params) {
	int i = paramIdx;
	paramIdx++;
	if (sign == '+') {
		if (!channel->isClientInChannel(args[i])) {
			send(client->getClntSockFd(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "o", args[i]).c_str(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "o", args[i]).length(), 0);
			return ;
		}
		if (channel->isOperator(args[i]))
			return ;
		channel->addOperator(args[i]);
		modes << "+o";
		params << args[i] << " ";
	} else {
		if (!channel->isOperator(args[i]))
			return ;
		channel->removeOperator(args[i]);
		params << args[i] << " ";
	}
}

void Request::changeClientLimitMode(Client *client, const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx, std::ostringstream &modes, std::ostringstream &params) {//JOIN 확인 필요
	
	if (sign == '+') {
		int i = paramIdx;
		paramIdx++;

		for (int j = 0; j <static_cast<int>(args[i].size()); ++j) {
			if (!isdigit(args[i][j])) {
				send(client->getClntSockFd(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "l", args[i]).c_str(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "l", args[i]).length(), 0);
				return ;
			}
		}
		std::istringstream iss(args[i]);
		int limit;
		iss >> limit;
		if (limit < 0 || 100 < limit) {
			send(client->getClntSockFd(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "l", args[i]).c_str(), ERR_INVALIDMODEPARAM(client->getNickName(), args[0], "l", args[i]).length(), 0);
			return ;
		}
		channel->setChannelModes("l", true);
		channel->setMaxClient(limit);
		modes << "+l";
		params << "limit(" << limit << ") ";
	} else {
		if (!channel->getChannelModes().at("l"))
			return ;
		channel->setChannelModes("l", false);
		channel->setMaxClient(-1);
		modes << "-l";
		params << "limit() ";
	}
}
