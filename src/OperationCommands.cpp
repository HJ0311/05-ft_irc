#include "../inc/Define.hpp"

void Request::handlePass(Server server) {
	std::cout << "command ::::: " << this->command << std::endl;
	std::cout << "here???" << std::endl;
	std::cout << "server password ::::: " << server.getPassword() << std::endl;
	std::cout << "here???" << std::endl;
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