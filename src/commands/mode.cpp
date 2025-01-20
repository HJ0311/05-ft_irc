#include "../../inc/Define.hpp"

std::string Request::execMode(Client *client, Server &server) {
	if (args.size() < 1)
		return (ERR_NEEDMOREPARAMS("MODE"));

	if (!server.isChannelExist(args[0]))
		return (ERR_NOSUCHCHANNEL(args[0]));
	
	Channel *channel = server.getChannel(args[0]);

	if (!channel->isOperator(client->getNickName()))
		return (ERR_CHANOPRIVSNEEDED(client->getNickName(), this->args[0]));

	if (args.size() == 1)
		return (RPL_CHANNELMODEIS(client->getNickName(), this->args[0], channel->getMode(), prepareModeParams(channel)));

	std::string err = validateModeFlag(client, args);
	if (err != "")
		return err;
		
	handleMode(args, channel);

	channel->broadcastMessage(MODE(client->getNickName(), client->getUserName(), client->getHostName(), args[0], args[1], prepareNowParams(args)));
	return "";
	// return MODE(client->getNickName(), client->getUserName(), client->getHostName(), client->getNi)
	// :root!root@127.0.0.1 MODE root :+i;//TODO 여기 고쳐주기
}

void Request::handleMode(std::vector<std::string> &args, Channel *channel)
{
	char sign = '+';
	std::string flags = args[1]; 
	int	paramIdx = 2;

	//mode 옵션은 무조건 붙여서 써야하는 것으로
	for (size_t i = 0; i < flags.size(); i++) {
		if (flags[i] == 't')
			changeTopicMode(sign, channel); //파라미터 불필요
		else if (flags[i] == 'i')
			changeInviteMode(sign, channel); // 파라미터 불필요
		else if (flags[i] == 'o')
			changeOperatorMode(sign, args, channel, paramIdx); // 파라미터 필요 -> 표시 불필요
		else if (flags[i] == 'l')
			changeClientLimitMode(sign, args, channel, paramIdx);// 파라미터 필요
		else if (flags[i] == 'k') 
			changePasswordMode(sign, args, channel, paramIdx); // 필요
		else
			sign = flags[i];
	}
}

std::string Request::prepareNowParams(std::vector<std::string> &args) {
	std::ostringstream params;

	for (size_t i = 2; i < args.size(); ++i) {
		params << args[i] << " ";
	}
	return params.str();
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
	
	char available[] = {'+', '-', 't', 'i', 'k', 'o', 'l'};
	size_t size = sizeof(available) / sizeof(available[0]);
	size_t	paramSize = 0;
	std::string flags = args[1];

	for (size_t i = 0; i < flags.size(); ++i){
		char *p = std::find(available, available + size, flags[i]);
		if (p == available + size) {
			return ERR_UNKNOWNMODE(client->getNickName(), flags[i]);
		}
		if (flags[i] == 'o' || flags[i] == 'l' || flags[i] == 'k')
			paramSize++;
	}

	if (args.size() != paramSize + 2)
		return ERR_NEEDMOREPARAMS("MODE");

	return "";
}

void Request::changeTopicMode(const char &sign, Channel *channel) {
	if (sign == '+') {
		if (channel->getChannelModes().at("t"))
			return ;
		channel->setChannelModes("t", true);
	} else {
		if (!channel->getChannelModes().at("t"))
			return ;
		channel->setChannelModes("t", false);
	}
}

void Request::changeInviteMode(const char &sign, Channel *channel) {//TODO join 확인 해야함
	if (sign == '+') {
		if (channel->getChannelModes().at("i"))
			return ;
		channel->setChannelModes("i", true);
	} else {
		if (!channel->getChannelModes().at("i"))
			return ;
		channel->setChannelModes("i", false);
	}
}

void Request::changePasswordMode(const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx) { //TODO join 확인
	int i = paramIdx;
	paramIdx++;
	if (sign == '+') {
		if (channel->getChannelModes().at("k"))
			return ;
		channel->setChannelModes("k", true);
		channel->setKey(args[i]);
	} else {
		if (!channel->getChannelModes().at("t"))
			return ;
		channel->setChannelModes("k", false);
		channel->setKey("");
	}
}

void Request::changeOperatorMode(const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx) {
	int i = paramIdx;
	paramIdx++;
	if (sign == '+') {
		if (channel->isOperator(args[i]))
			return ;
		channel->addOperator(args[i]);
	} else {
		if (!channel->isOperator(args[i]))
			return ;
		channel->removeOperator(args[i]);
	}
}

void Request::changeClientLimitMode(const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx) {//JOIN 확인 필요
	int i = paramIdx;
	paramIdx++;

	std::istringstream iss(args[i]);
	int limit;
	iss >> limit;
	if (sign == '+') {
		if (channel->getChannelModes().at("l"))
			return ;
		channel->setChannelModes("l", true);
		channel->setMaxClient(limit);
	} else {
		if (!channel->getChannelModes().at("l"))
			return ;
		channel->setChannelModes("l", false);
		channel->setMaxClient(-1);
	}
}

//TODO 최대 메세지 길이 제한 512byte
//TODO user name 길이 제한 