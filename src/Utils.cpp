#include "../inc/Define.hpp"

std::string	Utils::getTime()
{
	time_t	now = time(0); // 현재 시간
	tm	*ltm = localtime(&now); // 현지 시간

	std::stringstream	ss;

		ss 	<< std::setfill('0') << std::setw(4) << (1900 + ltm->tm_year) << '-'
			<< std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << '-'
			<< std::setfill('0') << std::setw(2) << ltm->tm_mday << ' '
			<< std::setfill('0') << std::setw(2) << ltm->tm_hour << ':'
			<< std::setfill('0') << std::setw(2) << ltm->tm_min << ':'
			<< std::setfill('0') << std::setw(2) << ltm->tm_sec;
		return ss.str();
}


namespace Utils
{//TODO * -> 클라이언트로 바꿔야함 , printf 사용할 것으로 올바른 플래그 넣어주기
	// std::string SUCCESS_MSG = "%s!%s@%s %s %s";

	std::string RPL_451 = ":irc.local 451 :You have to authenticate!\r\n";
	std::string RPL_461 = ":irc.local 461 PASS :Not enough parameters.\r\n";
	std::string RPL_462 = ":irc.local 462 :You may not register.\r\n";
	std::string RPL_464 = ":irc.local 464 :Incorrect password.\r\n";
	std::string RPL_433 = ":irc.local 433 jungslee :Nickname is already in use.\r\n";
	std::string RPL_431 = ":irc.local 431 :No nickname given.\r\n";
	std::string RPL_432 = ":irc.local 432 jungslee :Erroneus nickname\r\n";

	std::string RPL_403 = ":irc.local 403 sender #nochannel :No such channel\r\n";
	std::string RPL_401 = ":irc.local 401 sender nonick :No such nick\r\n";
	std::string RPL_473 = ":irc.local 473 nick #channel :Cannot join channel (invite only)\r\n";
	std::string RPL_475 = ":irc.local 475 nick #channel :Cannot join channel (incorrect channel key)\r\n";


    // std::cout << RPL_CONNECTION_SUCCESS.str();
	// std::string RPL_CONNECTION_SUCCESS = ":irc.local 001 jungslee :Welcome to the Localnet IRC Network jungslee!root@127.0.0.1\r\n"
	// 									+ ":irc.local 002 jungslee :Your host is irc.local, running version InspIRCd-3\r\n"
	// 									+ ":irc.local 003 jungslee :This server was created 16:04:34 Jan 06 2025\r\n"
	// 									+ ":irc.local 004 jungslee irc.local InspIRCd-3 iosw biklmnopstv :bklov\r\n";
	// std::string	welcomeRPL();
	// std::string authenticateRPL();
	// std::string notEnoughParams();
	// std::string alreadyRegistered();
}

// std::string	Utils::welcomeRPL()
// {
// 	std::string	welcome = YELLOW;
// 	welcome.append("Hello! You need to login so you can start chatting!\n");
// 	return welcome;
// }
