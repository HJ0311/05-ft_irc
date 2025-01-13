#include "../../inc/Define.hpp"

Request::Request() : command(""), args() {}

Request::Request(const Request& obj)
{
	*this = obj;
}

Request&	Request::operator=(const Request& obj)
{
	if (this != &obj)
	{
		this->command = obj.command;
		this->args = obj.args;
	}
	return *this;
}

Request::~Request() {}