#pragma once

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <unistd.h>

#include "Client.hpp"
#include "Server.hpp"
#include "Utils.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"