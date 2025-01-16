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
#include <cctype>
#include <algorithm>
#include <set>

#include "Client.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "Channel.hpp"
#include "Request.hpp"

#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"

#define CLEAR_SCREEN "\033[2J"    // 화면 전체 지우기
#define CURSOR_HOME "\033[H"      // 커서를 화면 맨 위로 이동
#define CURSOR_HIDE "\033[?25l"   // 커서 숨기기
#define CURSOR_SHOW "\033[?25h"   // 커서 보이기
