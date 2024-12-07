// PART <channel> <channel> ...: 하나 이상의 채널에서 퇴장

// NAMES <channel>: 지정된 채널에 있는 사용자 목록 표시

// LIST : 접속 가능한 채널 표시

// KICK <nickname> <nickname> ...: 채널에서 한 명 이상의 사용자 추방

// JOIN <channel>: 해당 채널이 없으면 생성, 있으면 참가

// INVITE <nick> <channel> : 초대 메세지 보내기

// TOPIC <channel> <Topic> : Topic 설정
// TOPIC <channel> : Topic 보여주기

#include "../inc/Define.hpp"

std::string	Server::commandJoin(Request request, int i)
{
	(void)request;
	(void)i;
	
	std::string	chatroom;
    // chatroom.append(CLEAR_SCREEN);
	// chatroom.append(CURSOR_HOME);
	chatroom.append("+===========================+\n");
	chatroom.append("|         Chatroom          |\n");
	chatroom.append("+===========================+\n");

	if (send(this->clients[i]->getSockFd(), chatroom.c_str(), chatroom.length(), 0) < 0)
		throw std::runtime_error("send() error");
	return ("");
}