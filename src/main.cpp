#include "../inc/Define.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc != 3)
		throw (std::string)"Usage: ./ircserv <port> <password>";
		
		Server	*server = new Server(argv[1], argv[2]);
		server->run();
		delete server;
	}
	catch(const std::string& e)
	{
		std::cout << RED << e << RESET << std::endl;
	}
	return 0;
}