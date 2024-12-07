#pragma once

#include "Define.hpp"

class Channel
{
	public:
		std::vector<Client>	clients; // 현재 채널에 소속된 유저들 목록
		std::string	name; // 채널 이름
		std::string	topic; // 채널 주제
		std::string	key; // 채널 비밀번호
		int	clientCnt; // 채널에 접속 중인 유저 수
		std::vector<std::string>	banned; // 밴 당한(KICK) 유저 목록
	private:
		Channel();
		Channel(const std::string& name, const std::string& topic, const std::string& key);
		Channel(const Channel& obj);
		Channel&	operator=(const Channel& obj);
		~Channel();
};