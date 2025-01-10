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
