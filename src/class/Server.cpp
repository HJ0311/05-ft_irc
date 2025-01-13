#include "../../inc/Define.hpp"

Server::Server() : maxClientCnt(0),  onlineClient(0), password(""), servSockFd(-1), pfds(), clients(), allChannels() {}

Server::Server(int maxClientCnt, const std::string& port, const std::string& password) : maxClientCnt(maxClientCnt), onlineClient(0), password(password), servSockFd(-1), pfds(), clients(), allChannels()
{
	try
	{
		if (stoi(port) < 0 || stoi(port) > 65535)
			throw (std::string) "Invalid port";
		this->pfds = new struct pollfd[this->maxClientCnt];
		initSocket(port);
		this->onlineClient++;
		this->pfds[0].fd = this->servSockFd;
		this->pfds[0].events = POLLIN;
	}
	catch(const std::string& e)
	{
		std::cout << RED << e << RESET << std::endl;
		exit(1);
	}
}

Server::~Server()
{
	if (this->pfds)
		delete [] this->pfds;
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
		delete it->second;
	//TODO 여기에 Channel도 다 delete해줘야 할 듯
	this->clients.clear();
}


Server::Server(const Server& obj)
{
	*this = obj;
}

Server&	Server::operator=(const Server& obj)
{
	if (this != &obj)
	{
		this->maxClientCnt = obj.maxClientCnt;
		this->onlineClient = obj.onlineClient;
		this->password = obj.password;
		this->servSockFd = obj.servSockFd;
		this->pfds = obj.pfds;
		this->clients = obj.clients;
		this->allChannels = obj.allChannels;
	}
	return *this;
}


// =================================================================================================================
// member function
// =================================================================================================================


void	Server::initSocket(const std::string& port)
{
	int	yes = 1;
	struct addrinfo	hint, *servinfo;
	int	status;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET; // IPv4 주소 체계
	hint.ai_socktype = SOCK_STREAM; // TCP 소켓 타입 지정
	hint.ai_protocol = getprotobyname("TCP")->p_proto; // 소켓에서 사용할 프토로콜 지정, TCP 라는 프로토콜의 정보 반환

	status = getaddrinfo("0.0.0.0", port.c_str(), &hint, &servinfo); // 실질적인 주소의 정보 servinfo에 저장
	if (status != 0) // error
		throw std::runtime_error("Unable to retrieve address information");
	
	struct addrinfo	*tmp;
	for (tmp = servinfo; tmp != NULL; tmp = tmp->ai_next) // servinfo에 있는 주소들 중 사용 가능한 주소를 찾는다
	{
		this->servSockFd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (this->servSockFd < 0)
			continue;
		if (fcntl(this->servSockFd, F_SETFL, O_NONBLOCK) < 0)
			throw std::runtime_error("Fcntl error");
		setsockopt(this->servSockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

		if (bind(this->servSockFd, tmp->ai_addr, tmp->ai_addrlen) < 0)
		{
			close(this->servSockFd);
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo); // 소켓의 fd는 addrinfo와 독립적이므로 쓸모 없어진 주소 정보는 해제

	if (tmp == NULL)
		throw std::runtime_error("Bind error");
	if (listen(this->servSockFd, this->maxClientCnt) < 0)
		throw std::runtime_error("Listen error");
}

void	Server::startServer()
{
	while (true)
	{
		int	pollCnt = poll(this->pfds, this->onlineClient, -1);
		if (pollCnt < 0)
			throw std::runtime_error("Poll() error");
		for (int i = 0; i < this->onlineClient; i++) // 온라인 중인 클라이언트 개수만큼
		{
			if (this->pfds[i].revents & POLLIN)
			{
				if (this->pfds[i].fd == this->servSockFd)
					newClient();
				else
					clientRequest(i);
			}
		}
	}
}

void	Server::newClient()
{
	struct sockaddr_storage	clientAddr; // 클라이언트의 주소 정보 저장
	socklen_t	addrLen = sizeof(clientAddr);
	int	newFd = accept(this->servSockFd, (struct sockaddr*) &clientAddr, &addrLen);
	if (newFd < 0)
		throw std::runtime_error("Accept error");
	else
	{
		addToPoll(newFd);

		if (send(newFd, ERR_NOTREGISTERED().c_str(), ERR_NOTREGISTERED().length(), 0) < 0)  
			throw std::runtime_error("send() error"); 
		// std::string welcome = Utils::welcomeRPL();
		// if (send(newFd, welcome.c_str(), welcome.length(), 0) < 0)  
		// 	throw std::runtime_error("send() error");
		// std::cout << YELLOW << "[" << Utils::getTime() << "] new connection from "
		// 		<< inet_ntoa(((struct sockaddr_in*) &clientAddr)->sin_addr) << " on socket " << newFd << RESET << std::endl;
		// addToPoll(newFd);

		/*인증 완료 전에 소켓이 연결된 메세지를 띄우는 것이 좋을까??*/
		std::cout << YELLOW << "[" << Utils::getTime() << "] new connection from "
				<< inet_ntoa(((struct sockaddr_in*) &clientAddr)->sin_addr) << " on socket " << newFd << RESET << std::endl;
	}
}

void	Server::addToPoll(int newFd)
{
	if (this->onlineClient == this->maxClientCnt)
	{
		this->maxClientCnt *= 2;
		this->pfds = (struct pollfd*)realloc(this->pfds, this->maxClientCnt);
		if (pfds == NULL)
			throw std::runtime_error("Memory allocation failed for pollfd array");
	}
	this->pfds[this->onlineClient].fd = newFd;
	this->pfds[this->onlineClient].events = POLLIN;
	this->clients.insert(std::make_pair(newFd, new Client(newFd)));
	this->onlineClient++;
}

void	Server::removeFromPoll(int i)
{
	close(this->pfds[i].fd);
	this->pfds[i] = this->pfds[this->onlineClient - 1];
	this->clients.erase(this->pfds[i].fd);
	this->onlineClient--;
}

//TODO jungslee 추가
std::string Server::getPassword() const {
	return this->password;
}

std::map<std::string, Channel*>& Server::getAllChannels()
{
	return (this->allChannels);
}
