#pragma once

#include "Define.hpp"

class Channel
{
	public:
		std::vector<Client>	clients;
		std::string	name;
		std::string	topic;
		std::string	key;
	private:
		Channel();
		// Channel(const std::string& name, ...)초기값 있는 생성자 
		Channel(const Channel& obj);
		Channel&	operator=(const Channel& obj);
		~Channel();
};