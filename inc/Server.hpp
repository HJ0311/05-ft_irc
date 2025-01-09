#pragma once

#include "Define.hpp"

class Client;
class Request;
class Channel;

class Server
{
	public:
		Server(int maxUserCnt, const std::string& port, const std::string& password);
		~Server();

		void	initSocket(const std::string& port);
		void	startServer();
		void	newClient();
		void	addToPoll(int newFd);
		void	removeFromPoll(int i);
		void	clientRequest(int i);
		// getter
		
		// request 처리
		// std::string	parsing(const std::string& message, int i);
		void execCommandByLine(int i, const std::string &message);
		Request	parsingCommand(const std::string& message) const;
		// command 처리
		std::string registerHandler(const std::string& message, int i);
		std::string commandHandler(const std::string& message, int i);

		std::string	commandJoin(Request request, int i);

		//TODO jungslee 추가
		std::string getPassword() const;
		std::map<int, Client*>	clients; // 현존 유저

		const std::map<std::string, Channel*>& getAllChannels() const;

	private:
		Server();
		Server(const Server& obj);
		Server&	operator=(const Server& obj);

		int	maxClientCnt; // 최대 온라인 가능 유저 수
		int	onlineClient; // 온라인 중인 유저 수
		std::string servName; //TODO 이런식으로 이름을 놓아도 되는지?
		std::string	password;
		int	servSockFd;
		struct pollfd	*pfds;
		std::map<std::string, Channel*> allChannels; // 현존 채널
};
