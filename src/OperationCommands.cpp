#include "../inc/Define.hpp"

std::string Request::execPass(const Server &server, bool &registerStatus) {
	if (registerStatus) 
		return Utils::RPL_462;

	if (server.getPassword() != this->args[0]) 
		return Utils::RPL_464;

	registerStatus = true;
	return ("");
}

std::string Request::execNick(Client *client, std::map<int, Client*> clients) {
	//TODO 유효성 검사 (printable 검사..?)ERR_ERRONEUSNICKNAME (432)
	//TODO 자원 부족으로 닉네임, 유저네임 설정할 수 없을 때 ERR_UNAVAILRESOURCE (437)
	//TODO 닉네임 변경을 막아놓았을 때 ERR_RESTRICTED (484)

	if (this->args.size() == 0)
		return (Utils::RPL_431);//ERR_NONICKNAMEGIVEN 

	if (this->args[0] == client->getNickName()) //이미 나의 닉네임일때
		return ("");

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (this->args[0] == it->second->getNickName())
			return (Utils::RPL_433);//ERR_NICKNAMEINUSE
    }
	
	std::string result = "";
	if (client->getUserName() != "")//서버 연결 시 인증과정에서의 NICK이 아닐 때는 변경에 대한 성공 메세지를 보내야 함.
		result = client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " NICK :" + this->args[0];
	client->setNickName(this->args[0]);
	return (result);
}

std::string Request::execUser(Client *client, std::map<int, Client*> clients) {
	if (this->args.size() != 4)
		return Utils::RPL_461;

	if (client->getUserName() != "")
		return Utils::RPL_462;
	
	client->setUserName(this->args[0]);
	client->setRealName(this->args[3]);

	std::stringstream RPL_CONNECTION_SUCCESS;
    RPL_CONNECTION_SUCCESS << ":irc.local 001 jungslee :Welcome to the Localnet IRC Network jungslee!root@127.0.0.1\r\n"
                           << ":irc.local 002 jungslee :Your host is irc.local, running version V1\n"
                           << ":irc.local 003 jungslee :This server was created 16:04:34 Jan 06 2025\r\n";
	return (RPL_CONNECTION_SUCCESS.str());
}

// KILL <nickname> <nickname> ...: 네트워크에서 강제로 연결 해제

// MODE <options>
// -i: 초대 전용 채널 설정/제거
// -t: 채널 운영자에게 TOPIC 명령의 제한 설정/제거
// -k: 채널의 키 설정/제거(비밀번호)
// -o: 채널 운영자 권한 지급/압수
// -l: 채널에 대한 사용자의 제한 설정/제거

// USER <username> <unused> <unused> <realname> : 서버에 자신을 등록