#include "../inc/Define.hpp"

Channel::Channel() : clients(), name(""), topic(""), key("") {}

Channel::Channel(const std::string& name, const std::string& topic, const std::string& key): clients(), name(name), topic(topic), key(key) {}

Channel::Channel(const Channel& obj)
{
	*this = obj;
}

Channel&	Channel::operator=(const Channel& obj)
{
	if (this != &obj)
	{
		this->clients = obj.clients;
		this->name = obj.name;
		this->topic = obj.topic;
		this->key = obj.key;
	}
	return *this;
}

Channel::~Channel() {}

// =================================================================================================================
// member function
// =================================================================================================================
