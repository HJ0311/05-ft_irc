#include "../../inc/Define.hpp"

Channel::Channel(const std::string& name) : clients(), operators(), invitees(), name(name), topic(""), key(""), isPrivate(0), isInviteOnly(0), clientLimit(-1) {}

// Channel::Channel(const std::string& name, const std::string& topic, const std::string& key): clients(), operators(), name(name), topic(topic), key(key) isPrivate(0), isInviteOnly(0), clientLimit(-1){}

Channel::Channel(const Channel& obj)
{
	*this = obj;
}

Channel&	Channel::operator=(const Channel& obj)
{
	if (this != &obj)
	{
		this->clients = obj.clients;
		this->operators = obj.operators;
		this->invitees = obj.invitees;
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

void	Channel::addClient(Client* user)
{
	clients[user->getClntSockFd()] = user;
}

void	Channel::removeClient(const std::string& nickname)
{
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second->getNickName() == nickname)
		{
			clients.erase(it);
			break;
		}
	}
}

bool	Channel::isClientInChannel(const std::string& nickname)
{
	for (std::map<int, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second->getNickName() == nickname)
			return (1);
	}
	return (0);
}

void	Channel::addOperator(const std::string& nickname)
{
	operators.insert(nickname);
}

void	Channel::removeOperator(const std::string& nickname)
{
	operators.erase(nickname);
}

bool	Channel::isOperator(const std::string& nickname)
{
	if (operators.find(nickname) != operators.end())
		return (1);
	else
		return (0);
}

/*
void	Channel::setTopic(const std::string& newTopic, const std::string& nickname)
{

}

void	Channel::setPassword(const std::string& password)
{

}


void	Channel::setInviteOnly(bool inviteOnly)
{

}

void	Channel::inviteClient(Client* inviter, const std::string& inviteeNickname)
{

}
*/

size_t	Channel::getClientCount() const
{
	return (this->clients.size());
}

bool	Channel::isFull() const
{
	if (this->clientLimit == -1)
		return (0);
	if (this->clientLimit <= this->getClientCount())
		return (1);
	else
		return (0);
}

const std::string&	Channel::getName() const
{
	return (this->name);
}

const std::string&	Channel::getTopic() const
{
	return (this->topic);
}

const std::string&	Channel::getKey() const
{
	return (this->key);
}

const std::map<int, Client*>& Channel::getClients() const
{
	return (this->clients);
}

const bool&	Channel::getIsInviteOnly() const
{
	return (this->isInviteOnly);
}
