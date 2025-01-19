#include "../../inc/Define.hpp"

Channel::Channel(const std::string& name) : clients(), operators(), invitees(), name(name), topic(""), key(""), clientCnt(0), isPrivate(0), isInviteOnly(0), clientLimit(-1) {}

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
		this->clientCnt = obj.clientCnt;
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
	++this->clientCnt;
	clients[user->getClntSockFd()] = user;
}

void	Channel::removeClient(const std::string& nickname)
{
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second->getNickName() == nickname)
		{
			clients.erase(it);
			return ;
		}
	}
	this->clientCnt--;
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

bool	Channel::isInvited(const std::string& nickname)
{
	if (invitees.find(nickname) != invitees.end())
		return (1);
	else
		return (0);
}

void	Channel::setTopic(const std::string& newTopic)
{
	this->topic = newTopic;
}
/*
void	Channel::setPassword(const std::string& password)
{

}


void	Channel::setInviteOnly(bool inviteOnly)
{

}
*/
void	Channel::inviteClient(const std::string& invitee)
{
	invitees.insert(invitee);
}

void	Channel::removeInvitee(const std::string& nickname)
{
	invitees.erase(nickname);
}

size_t	Channel::getClientCount() const
{
	return (this->clients.size());
}

bool	Channel::isFull() const
{
	if (this->clientLimit == -1)
		return (0);
	if (this->clientLimit <= static_cast<int>(this->getClientCount()))
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

void Channel::broadcastMessage(const std::string &message)
{	
	for (std::map<int, Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
		send(it->second->getClntSockFd(), message.c_str(), message.length(), 0);
}
