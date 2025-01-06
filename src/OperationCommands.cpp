#include "../inc/Define.hpp"

std::string Request::execPass(const Server &server, bool &registerStatus) {
	if (registerStatus) 
		return Utils::RPL_462;

	if (server.getPassword() != this->args[0]) 
		return Utils::RPL_464;

	registerStatus = true;
	return ("");
}

std::string Request::execNick(const Server &server, Client *client, std::map<int, Client*> clients) {
	//args가 없을때! (파라미터가 없을때)
	//닉네임이 유효하지 않을때
	if (this->args[0] == client->getNickName()) //이미 나의 닉네임일때
		return ("");

	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (this->args[0] == it->second->getNickName())
			return (Utils::RPL_433);
    }
	
	std::string result = "";
	if (client->getUserName() != "")//서버 연결 시 인증과정에서의 NICK이 아닐 때는 변경에 대한 성공 메세지를 보내야 함.
		result = client->getNickName() + "!" + client->getUserName() + "@" + client->getHostName() + " NICK :" + this->args[0];
	client->setNickName(this->args[0]);
	return (result);
}

std::string Request::execUser(const Server &server, int i) {
	
	return ("");
}

// KILL <nickname> <nickname> ...: 네트워크에서 강제로 연결 해제

// MODE <options>
// -i: 초대 전용 채널 설정/제거
// -t: 채널 운영자에게 TOPIC 명령의 제한 설정/제거
// -k: 채널의 키 설정/제거(비밀번호)
// -o: 채널 운영자 권한 지급/압수
// -l: 채널에 대한 사용자의 제한 설정/제거

// USER <username> <unused> <unused> <realname> : 서버에 자신을 등록