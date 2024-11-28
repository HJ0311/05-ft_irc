#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Client.hpp"
#include "Server.hpp"
#include "Utils.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"