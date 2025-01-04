#include "../inc/Define.hpp"

std::string Request::execPass(const Server &server, bool &registerStatus) {
	// std::cout << "Pass command" << std::endl;
	if (this->args.size() == 0) {
		std::cout << "not enough params" << std::endl;
		return Utils::MSG_461;
	}//RFC문서에는 있는데,...irssi를 사용하면. 이게 나올 일이 없다. 462도 마찬가지

	if (registerStatus) {
		return Utils::MSG_462;
	}//이것도 나올 일이 없음

	if (server.getPassword() != this->args[0]) { //TODO 지금 끝에 \r가 포함되어있다.
		return Utils::MSG_464;
	}
	registerStatus = true;
	return ("");
}

std::string Request::execNick(const Server &server, int i) {
	std::cout << "command ::::: " << this->command << std::endl;
	return ("");
}

std::string Request::execUser(const Server &server, int i) {
	std::cout << "command ::::: " << this->command << std::endl;
	return ("");
}

// PASS <password> : 로컬 네트워크에 연결

// KILL <nickname> <nickname> ...: 네트워크에서 강제로 연결 해제

// MODE <options>
// -i: 초대 전용 채널 설정/제거
// -t: 채널 운영자에게 TOPIC 명령의 제한 설정/제거
// -k: 채널의 키 설정/제거(비밀번호)
// -o: 채널 운영자 권한 지급/압수
// -l: 채널에 대한 사용자의 제한 설정/제거

// NICK <nickname>: 닉네임 설정

// USER <username> <unused> <unused> <realname> : 서버에 자신을 등록