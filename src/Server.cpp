#include "../inc/Define.hpp"

Server::Server(const std::string& port, const std::string& password) : port(0), password(password)
{
	try
	{
		this->port = stoi(port);
		if (this->port < 0 || this->port > 65535)
			throw (std::string) "Invalid port";
		initSocket();
	}
	catch(const std::string& e)
	{
		std::cout << RED << e << RESET << std::endl;
		exit(1);
	}
}

Server::~Server() {}

Server::Server() {}

Server::Server(const Server& obj) : port(obj.port), password(obj.password)
{
	*this = obj;
}

Server&	Server::operator=(const Server& obj)
{
	if (this != &obj)
	{
		this->port = obj.port;
		this->password = obj.password;
	}
	return *this;
}

// =====================================================================================================

void	Server::initSocket()
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1)
		throw std::runtime_error("Socket creation error");
	if (fcntl(this->sock, F_SETFL, O_NONBLOCK) == -1) // 소켓 논 블로킹 모드로 설정
		throw std::runtime_error("fcntl error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(this->port);

	if (bind(sock, (struct sockaddr*) &servAddr, sizeof(servAddr)) == -1)
		throw std::runtime_error("Bind error");
	
	if (listen(sock, SOMAXCONN) == -1) // 연결 요청 대기
		throw std::runtime_error("Listen error");

}

void	Server::run()
{
	this->servSockSize = sizeof(sockaddr_in); // 소켓 함수의 호환성 유지를 위해 필요
	
	// 파일 디스크립터 집합들 초기화
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	FD_ZERO(&this->readFdsCopy);
	FD_ZERO(&this->writeFdsCopy);

	FD_SET(this->sock, &readFds); // select가 호출될 때 해당 집합의 소켓에 읽을 데이터가 있는지 확인할 수 있게 됨

	while (true)
	{
		readFdsCopy = readFds;
		writeFdsCopy = writeFds; // select를 사용하면 집합 상태가 변할 수 있으므로 복사
		if (select(Utils::getMaxFd(this->clients, this->sock) + 1, &readFdsCopy, &writeFdsCopy, NULL, 0) == -1)
			throw std::runtime_error("Select error");

		if (FD_ISSET(this->sock, &this->readFdsCopy)) // 소켓이 집합에 포함되어있는지 확인, select()이 집합을 검사한 뒤 준비된 디스크립터만 남기기 때문에 확인이 필요
		{
			std::cout << "Connected" << std::endl;
			break ;
			// handleNewConnection(); // 연결 요청 처리
			// continue;
		}
	}
}

// void	Server::handleNewConnection()
// {
// 	int	newSocket = accept(this->sock, (sockaddr*) &clntAddr, &this->servSockSize); // 연결 요청이 들어왔는지 확인하고 들어왔다면 클라이언트 정보를 저장
// 	if (newSocket == -1)
// 		throw std::runtime_error("Accept error");

// 	if (fcntl(newSocket, F_SETFL, O_NONBLOCK) == -1)
// 		throw std::runtime_error("Fcntl error");
	
// 	int port = ntohs(clntAddr.sin_port);
// 	Client	newClient(newSocket, port)

// }