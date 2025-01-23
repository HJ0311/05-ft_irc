#include "../../inc/Define.hpp"

std::string Request::execMode(Client *client, Server &server) {

	if (args.size() < 1)
		return (ERR_NEEDMOREPARAMS("MODE"));

	if (server.isClientExist(args[0]))
		return ("");

	if (args[0][0] != '#' || args[0].length() > 200)
		return (ERR_BADCHANMASK(client->getNickName(), args[0]));

	if (!server.isChannelExist(args[0]))
		return (ERR_NOSUCHCHANNEL(args[0]));
	
	Channel *channel = server.getChannel(args[0]);

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

	//mode 옵션은 무조건 붙여서 써야하는 것으로
	for (size_t i = 0; i < flags.size(); ++i) {
		if (flags[i] == 't')
			changeTopicMode(sign, channel, changedMode); //파라미터 불필요
		else if (flags[i] == 'i')
			changeInviteMode(sign, channel, changedMode); // 파라미터 불필요
		else if (flags[i] == 'o')
			changeOperatorMode(sign, args, channel, paramIdx, changedMode, changedParam); // 파라미터 필요 -> 표시 불필요
		else if (flags[i] == 'l')
			changeClientLimitMode(sign, args, channel, paramIdx ,changedMode, changedParam);// 파라미터 필요
		else if (flags[i] == 'k') 
			changePasswordMode(sign, args, channel, paramIdx, changedMode, changedParam); // 필요
		else
			sign = flags[i];
	}
	
	std::string result = MODE(client->getNickName(), client->getUserName(), client->getHostName(), args[0], changedMode.str(), changedParam.str());
	return result;
	// getChangedMode(changedMode, changedParam, earlyLimit, earlyModes, channel);
}

// void Request::getChangedMode(std::ostringstream &modes, std::ostringstream &params, const int &earlyLimit, std::map<std::string, bool> early, Channel *channel) {
	
// 	std::map<std::string, bool> after = channel->getChannelModes();

// 	if (early.at("i") != after.at("i")) {
// 		if (after.at("i") == false)
// 			modes << "-i";
// 		else
// 			modes << "+i";
// 	}

// 	if (early.at("t") != after.at("t")) {
// 		if (after.at("t") == false)
// 			modes << "-t";
// 		else
// 			modes << "+t";
// 	}

// 	if (early.at("k") != after.at("k")) {
// 		if (after.at("k") == false)
// 			modes << "-k";
// 		else
// 			modes << "+k";
// 		params << "key(" << channel->getKey() << ") ";
// 	}

// 	if (earlyLimit != channel->getMaxClient()) {
// 		modes << "+l";
// 		params << "limit(" << channel->getMaxClient() << ") ";
// 	}

// }

// void Request::getChangedOperator(std::ostringstream &modes, std::ostringstream &params, Channel *channel, std::vector<std::string> &args) {

// 	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
// 		if (channel->isClientInChannel(args[]))
// 	}
// 	while (it1 != early.end() && it2 != after.end() && *it1 == *it2) {
// 		++it1;
// 		++it2;
// 	}

// 	while (it1 != early.end()) {
// 		modes << "-o";
// 		params << *it1 << " ";
// 		++it1;
// 	}
// 	while (it2 != after.end()) {
// 		modes << "+o";
// 		params << *it2 << " ";
// 		++it2;
// 	}
// }

// std::string Request::prepareNowParams(std::vector<std::string> &args) {
// 	std::ostringstream params;

// 	for (size_t i = 2; i < args.size(); ++i) {
// 		params << args[i] << " ";
// 	}
// 	return params.str();
// }

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
	int i = paramIdx;
	paramIdx++;
	if (sign == '+') {
		if (channel->getChannelModes().at("k"))
			return ;
		channel->setChannelModes("k", true);
		channel->setKey(args[i]);
		modes << "+k";
		params << "key(" << args[i] << ") ";
	} else {
		if (!channel->getChannelModes().at("k"))
			return ;
		if (channel->getKey() != args[i])
			return ;
		channel->setChannelModes("k", false);
		channel->setKey("");
		modes << "-k";
		params << "key() ";
	}
}

void Request::changeOperatorMode(const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx, std::ostringstream &modes, std::ostringstream &params) {
	int i = paramIdx;
	paramIdx++;
	if (sign == '+') {
		if (!channel->isClientInChannel(args[i]))
			return ;
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

void Request::changeClientLimitMode(const char &sign, std::vector<std::string> &args, Channel *channel, int &paramIdx, std::ostringstream &modes, std::ostringstream &params) {//JOIN 확인 필요
	int i = paramIdx;
	paramIdx++;

	std::istringstream iss(args[i]);
	int limit;
	iss >> limit;
	if (sign == '+') {
		channel->setChannelModes("l", true);
		channel->setMaxClient(limit);
		modes << "+l";
		params << "limit(" << args[i] << ") ";
	} else {
		if (!channel->getChannelModes().at("l"))
			return ;
		channel->setChannelModes("l", false);
		channel->setMaxClient(-1);
		modes << "-l";
		params << "limit() ";
	}
}
