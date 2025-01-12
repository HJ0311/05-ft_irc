#pragma once

#include "Define.hpp"

class Client;

#define PREFIX() (std::string(":") + SERVER_NAME)

#define RPL_WELCOME(NICK, USER, HOST)       (PREFIX() + (" 001 ") + NICK + " :Welcome to the Internet Relay Network " + NICK + "!" + USER + "@" + HOST + "\r\n")
#define RPL_YOURHOST(NICK)					(PREFIX() + (" 002 ") + NICK + " :Your host is " + SERVER_NAME + ", running version V1\r\n")
#define RPL_CREATED(NICK, TIME)				(PREFIX() + (" 003 ") + NICK + " :This server was created " + TIME + "\r\n")
#define ERR_NOTREGISTERED()					(PREFIX() + (" 451 ") + " :You have to authenticate!\r\n")	
#define ERR_NEEDMOREPARAMS(COMMAND)			(PREFIX() + (" 461 ") + COMMAND + " :Not enough parameters.\r\n")
#define ERR_ALREADYREGISTERED()				(PREFIX() + (" 462 ") + " :You may not register.\r\n")
#define ERR_PASSWDMISMATCH() 				(PREFIX() + (" 464 ") + " :Incorrect password.\r\n")
#define ERR_NICKNAMEINUSE(NICK)				(PREFIX() + (" 433 ") + NICK + " :Nickname is already in use.\r\n")
#define ERR_NONICKNAMEGIVEN()				(PREFIX() + (" 431 ") + " :No nickname given.\r\n")
#define ERR_ERRONEUSNICKNAME(NICK)			(PREFIX() + (" 432 ") + NICK + " :Erroneus nickname\r\n")
#define ERR_NOSUCHCHANNEL(CHANNEL)     		(PREFIX() + (" 403 ") + CHANNEL + " :No such channel\r\n")
#define ERR_NOSUCHNICK(NICK) 				(PREFIX() + (" 401 ") + NICK + " :No such nick\r\n")
#define ERR_INVITEONLYCHAN(NICK, CHANNEL)	(PREFIX() + (" 473 ") + NICK + " " + CHANNEL + " :Cannot join channel (invite only)\r\n")
#define ERR_BADCHANNELKEY(NICK, CHANNEL)	(PREFIX() + (" 475 ") + NICK + " " + CHANNEL + " Cannot join channel (incorrect channel key)\r\n")
#define PONG()					 			(PREFIX() + " PONG " + SERVER_NAME + " :" + SERVER_NAME + "\r\n")
#define NICK(OLDNICK, USER, HOST, NEWNICK)	(std::string(":") + OLDNICK + "!" + USER + "@" + HOST + " NICK :" + NEWNICK + "\r\n")

namespace Utils {
	std::string	getTime();
}
