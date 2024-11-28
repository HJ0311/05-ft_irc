#include "../inc/Define.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc != 3)
		throw (std::string)"Usage: ./ircserv <port> <password>";
		
		Server	srv(10, argv[1], argv[2]);
		srv.startServer();
	}
	catch(const std::string& e)
	{
		std::cout << RED << e << RESET << std::endl;
	}
	return 0;
}