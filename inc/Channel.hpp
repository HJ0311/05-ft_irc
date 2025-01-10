#pragma once

#include "Define.hpp"
#include <set>

class Channel
{
	private:
		std::map<int, Client*>	clients;//현재 채널에 소속된 유저들 목록
		std::set<std::string>	operators;
		std::string	name; // 채널 이름
		std::string	topic; // 채널 주제
		std::string	key; // 채널 비밀번호
		int	clientCnt; // 채널에 접속 중인 유저 수

		bool	isPrivate;
		bool	isInviteOnly;
		time_t	creationTime;

		Channel();
	public:
		Channel(const std::string& name);
		Channel(const std::string& name, const std::string& topic, const std::string& key);
		Channel(const Channel& obj);
		Channel&	operator=(const Channel& obj);
		~Channel();

		void	addClient(Client* user); // 유저를 채널에 추가
		void	removeClient(const std::string& nickname); // 채널에서 제거
		bool	isClientInChannel(const std::string& nickname); // 특정 유저가 채널에 있는지 확인//중복인 건데 필요한지

		void	addOperator(const std::string& nickname); // 운영자를 추가
		void	removeOperator(const std::string& nickname); // 운영자를 제거
		bool	isOperator(const std::string& nickname); // 얘가 운영자인지 확인

		void	setTopic(const std::string& newTopic, const std::string& nickname);
		void	setPassword(const std::string& password);
		void	setInviteOnly(bool inviteOnly);

		void	inviteClient(Client* inviter, const std::string& invitee);

		size_t	getClientCount() const;

		const std::string&	getName() const;
		const std::string&	getTopic() const;
		const std::string&	getKey() const;
		const std::map<int, Client*>&	getClients() const;
		const bool&	getIsInviteOnly() const;
};
