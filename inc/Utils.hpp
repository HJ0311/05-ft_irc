#pragma once

#include "Define.hpp"

class Client;

#define PREFIX() (std::string(":") + SERVER_NAME)

#define RPL_WELCOME(NICK, USER, HOST)       				(PREFIX() + (" 001 ") + NICK + " :Welcome to the Internet Relay Network " + NICK + "!" + USER + "@" + HOST + "\r\n")
#define RPL_YOURHOST(NICK)									(PREFIX() + (" 002 ") + NICK + " :Your host is " + SERVER_NAME + ", running version V1\r\n")
#define RPL_CREATED(NICK, TIME)								(PREFIX() + (" 003 ") + NICK + " :This server was created " + TIME + "\r\n")
#define RPL_MYINFO(NICK)									(PREFIX() + (" 004 ") + NICK + " " + SERVER_NAME + " V1 none itkol\r\n")
#define RPL_CHANNELMODEIS(NICK, CHANNEL, MODE, MODEPARAMS) 	(PREFIX() + (" 324 ") + NICK + " " + CHANNEL + " " + MODE + " :" + MODEPARAMS + "\r\n")
#define RPL_NOTOPIC(CHANNEL)								(PREFIX() + (" 331 ") + CHANNEL + " :No topic is set\r\n")
#define RPL_TOPIC(CHANNEL, TOPIC)							(PREFIX() + (" 332 ") + CHANNEL + " " + TOPIC + "\r\n")
#define RPL_INVITING(INVITER, INVITEE, CHANNEL)				(PREFIX() + (" 341 ") + INVITER + " " + INVITEE + " " + CHANNEL + " :" + INVITER + " is inviting " + INVITEE + " to " + CHANNEL + "\r\n")
#define RPL_ENDOFNAMES(NICK, CHANNEL)						(PREFIX() + (" 366 ") + NICK + " " + CHANNEL + " :End of /NAMES list.\r\n")
#define RPL_MOTDSTART()                    	 				(PREFIX() + (" 375 ") + ":- " + SERVER_NAME + " Message of the day - \r\n")
#define RPL_MOTD(STRING)                   	 				(PREFIX() + (" 372 ") + ":" + STRING + "\r\n")
#define RPL_ENDOFMOTD()                     				(PREFIX() + (" 376 ") + ":End of /MOTD command.\r\n")
#define ERR_NOSUCHNICK(NICK) 								(PREFIX() + (" 401 ") + NICK + " :No such nick\r\n")
#define ERR_NOSUCHCHANNEL(CHANNEL)     						(PREFIX() + (" 403 ") + CHANNEL + " :No such channel\r\n")
#define ERR_CANNOTSENDTOCHAN(NICK, CHANNEL) 				(PREFIX() + (" 404 ") + NICK + " " + CHANNEL + " :You cannot send external messages to this channel.\r\n")
#define ERR_NONICKNAMEGIVEN()								(PREFIX() + (" 431 ") + " :No nickname given.\r\n")
#define ERR_ERRONEUSNICKNAME(NICK)							(PREFIX() + (" 432 ") + NICK + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(NICK)								(PREFIX() + (" 433 ") + NICK + " :Nickname is already in use.\r\n")
#define ERR_NOTONCHANNEL(NICK, CHANNEL)						(PREFIX() + (" 442 ") + NICK + " " + CHANNEL + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(SENDNICK, CHANNEL, NICK)			(PREFIX() + (" 443 ") + SENDNICK + " " + CHANNEL + " :" + NICK + " already on " + CHANNEL + "\r\n")
#define ERR_NOTREGISTERED()									(PREFIX() + (" 451 ") + " :You have to authenticate!\r\n")	
#define ERR_NEEDMOREPARAMS(COMMAND)							(PREFIX() + (" 461 ") + COMMAND + " :Not enough parameters.\r\n")
#define ERR_ALREADYREGISTERED()								(PREFIX() + (" 462 ") + " :You may not register.\r\n")
#define ERR_PASSWDMISMATCH() 								(PREFIX() + (" 464 ") + " :Incorrect password.\r\n")
#define ERR_KEYSET(NICK, CHANNEl)							(PREFIX() + (" 467 ") + NICK + " " + CHANNEL + " :Channel key already set\r\n")									
#define ERR_CHANNELISFULL(NICK, CHANNEL) 					(PREFIX() + (" 471 ") + NICK + " " + CHANNEL + " :Cannot join channel (channel is full)\r\n")
#define ERR_UNKNOWNMODE(NICK, UNKNOWN)						(PREFIX() + (" 472 ") + NICK + " " + UNKNOWN + " :is unknown mode char to me\r\n")
#define ERR_INVITEONLYCHAN(NICK, CHANNEL)					(PREFIX() + (" 473 ") + NICK + " " + CHANNEL + " :Cannot join channel (invite only)\r\n")
#define ERR_BADCHANNELKEY(NICK, CHANNEL)					(PREFIX() + (" 475 ") + NICK + " " + CHANNEL + " :Cannot join channel (incorrect channel key)\r\n")
#define ERR_BADCHANMASK(NICK, CHANNEL)						(PREFIX() + (" 476 ") + NICK + " " + CHANNEL + " :Invalid channel name\r\n")
#define ERR_CHANOPRIVSNEEDED(NICK, CHANNEL)					(PREFIX() + (" 482 ") + NICK + " " + CHANNEL + " :You're not a channel operator\r\n")
#define ERR_INVALIDMODEPARAM(NICK, CHANNEL, MODECHAR, PARAM)	(PREFIX() + (" 696 ") + NICK + " " + CHANNEL + " " + MODECHAR + " " + PARAM + " :Invalid mode param\r\n")						

#define PONG()					 							(PREFIX() + " PONG " + ":" + SERVER_NAME + "\r\n")
#define NICK(OLDNICK, USER, HOST, NEWNICK)					(std::string(":") + OLDNICK + "!" + USER + "@" + HOST + " NICK :" + NEWNICK + "\r\n")
#define KILL(NICK)											(PREFIX() + " KILL " + NICK + " :Connection killed by server.\r\n")
#define ERROR(USER, HOST)									(PREFIX() + " ERROR " + ": Closing Link (" + USER + "@" + HOST + ")\r\n")
#define INVITE(NICK, USER, HOST, INVITEE, CHANNEL)  		(std::string(":") + NICK + "!" + USER + "@" + HOST + " INVITE " + INVITEE + " " + ":" + CHANNEL + "\r\n")
#define TOPIC(NICK, USER, HOST, CHANNEL, NEWTOPIC)			(std::string(":") + NICK + "!" + USER + "@" + HOST + " TOPIC " + CHANNEL + " " + NEWTOPIC + "\r\n")
#define KICK(NICK, USER, HOST, CHANNEL, KICKED, CONTENT)	(std::string(":") + NICK + "!" + USER + "@" + HOST + " KICK " + CHANNEL + " " + KICKED + " " + CONTENT + "\r\n") 
#define MODE(NICK, USER, HOST, CHANNEL, MODE, MODEPARAMS)	(std::string(":") + NICK + "!" + USER + "@" + HOST + " MODE " + CHANNEL + " " + MODE + " :" + MODEPARAMS + "\r\n")

#define START_IRC()                         				(RPL_MOTDSTART() \
																+ RPL_MOTD("   __      __     ____       __         ____       _____                   ____       ") \
																+ RPL_MOTD("  /\\ \\  __/\\ \\   /\\  _`\\    /\\ \\       /\\  _`\\    /\\  __`\\     /'\\_/`\\    /\\  _`\\     ") \
																+ RPL_MOTD("  \\ \\ \\/\\ \\ \\ \\  \\ \\ \\L\\_\\  \\ \\ \\      \\ \\ \\/\\_\\  \\ \\ \\/\\ \\   /\\      \\   \\ \\ \\L\\_\\   ") \
																+ RPL_MOTD("   \\ \\ \\ \\ \\ \\ \\  \\ \\  _\\L   \\ \\ \\  __  \\ \\ \\/_/_  \\ \\ \\ \\ \\  \\ \\ \\__\\ \\   \\ \\  _\\L   ") \
																+ RPL_MOTD("    \\ \\ \\_/ \\_\\ \\  \\ \\ \\L\\ \\  \\ \\ \\L\\ \\  \\ \\ \\L\\ \\  \\ \\ \\_\\ \\  \\ \\ \\_/\\ \\   \\ \\ \\L\\ \\ ") \
																+ RPL_MOTD("     \\ `\\___x___/   \\ \\____/   \\ \\____/   \\ \\____/   \\ \\_____\\  \\ \\_\\\\ \\_\\   \\ \\____/ ") \
																+ RPL_MOTD("      '\\/__//__/     \\/___/     \\/___/     \\/___/     \\/_____/   \\/_/ \\/_/    \\/___/  ") \
																+ RPL_ENDOFMOTD())

namespace Utils {
	std::string	getTime();
}
