#include "../inc/Define.hpp"

void	Server::clientRequest(int i)
{
	char	buf[5000]; // recv는 저수준 네트워크 함수로 설계 되었으므로 char 배열이 더 효율적이다. std::stirng을 사용하면 매 수신/송신마다 오버헤드가 추가적으로 생김
	int	senderFd = this->pfds[i].fd;
	int	recvBytes = recv(senderFd, buf, sizeof(buf), 0); // 특정 클라이언트에서 서버로 보내는 데이터 받아 buf에 저장

	if (recvBytes <= 0)
	{
		if (recvBytes == 0)
			std::cerr << RED << "[" << Utils::getTime() << "] socket" << senderFd << ": disconnected" << RESET << std::endl;
		else
			std::cerr << RED << "recv() error" << RESET << std::endl;
		close(senderFd);
		removeFromPoll(i);
	}
	else
	{
		// command 처리
		// std::string	result = parsing(buf);
		// if (send(senderFd, result.c_str(), result.length(), 0) < 0) // 명령어를 파싱한 뒤 그 결과물을 다시 클라이언트에게 전송
		// 	std::cerr << RED << "send() error" << RESET << std::endl;
	}
	memset(&buf, 0, 5000);
}