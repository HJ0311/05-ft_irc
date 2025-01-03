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
	std::string MSG_451 = ":irc.local 451 * JOIN :You have to authenticate!\r\n";
	std::string MSG_461 = ":irc.local 461 * PASS :Not enough parameters.\r\n";
	std::string MSG_462 = ":irc.local 462 * :You may not register.\r\n";
	std::string MSG_464 = ":irc.local 464 * :Incorrect password.\r\n";
	// std::string	welcomeMsg();
	// std::string authenticateMsg();
	// std::string notEnoughParams();
	// std::string alreadyRegistered();
}

// std::string	Utils::welcomeMsg()
// {
// 	std::string	welcome = YELLOW;
// 	welcome.append("Hello! You need to login so you can start chatting!\n");
// 	return welcome;
// }
