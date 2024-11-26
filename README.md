# **ft_irc**

#### Internet Relay Chat

실시간 인터넷 채팅

#### Summary: This project is about creating your own IRC server. You will use an actual IRC client to connect to your server and test it. Internet is ruled by solid standards protocols that allow connected computers to interact with each other. It's always a good thing to know.

요약: 이 프로젝트는 IRC 서버를 만드는 것에 대한 내용을 다루고 있다. 실제 IRC 클라이언트와 연결되는 서버를 만들고 테스트해야 한다. 인터넷은 연결된 컴퓨터들이 서로 상호작용할 수 있도록 하는 견고한 표준 프로토콜의 규칙을 따른다. 아는 것이 힘이다.

##### Version: 8

버전: 8

<br>

| Chapter | Contents                                              | page |
| :-----: | :-----------------------------------------------------| :--: |
|    1    | [**Introduction**](#Chapter-1)                        |  2   |
|    2    | [**General rules**](#Chapter-2)                       |  3   |
|    3    | [**Mandatory Part**](#Chapter-3)                      |  4   |
|    4    | [**Bonus Part**](#Chapter-4)       |  7   |

<br>

# **Chapter 1**

## Introduction

##### **Internet Relay Chat** or IRC is a text-based communication protocol on the Internet.

인터넷 실시간 채팅 혹은 IRC는 인터넷의 텍스트 기반 통신 프로토콜이다.

##### It offers real-time messaging that can be either public or private.

공개 또는 비공개 실시간 메세지를 제공한다.

##### Users can exchange direct messages and join group channels.

사용자들은 다이렉트 메세지를 주고받고 그룹 채널에 가입할 수 있다.

##### IRC clients connect to IRC servers in order to join channels.

IRC 클라이언트는 채널에 가입하기 위해 IRC 서버에 연결해야 한다.

##### IRC servers are connected together to form a network.

IRC 서버는 서로 연결되어 네트워크를 형성한다.

# **Chapter 2**

## General rules

- ##### Your program should not crash in any circumstances (even whan it runs out of memory), and should not quit unexpectedly.

- 프로그램은 어떤 상황에서도 충돌나지 않아야 하며, (메모리 영역을 벗어났다거나) 예상치 못하게 종료되어선 안 된다.

	##### If it happens, your project wil be considered non-functional and your grade will be 0.

	그런 상황이 발생한다면, 프로젝트는 기능하지 않는다고 판단되어 0점을 받게 될 것이다.

- ##### You have to turn in a **Makefile** which will compile your source files. It must not relink.

- 소스 파일을 컴파일 하는 Makefile을 제출해라. 리링크 되어선 안 된다.

- ##### Your **Makefile** must at least contain the rules: **$(NAME), all, clean, fclean, and re.**

- Makefile은 반드시 다음과 같은 규칙을 포함해야 한다: $(NAME), all, clean, fclean, re.

- ##### Compile your code with **c++** and the flags **-Wall -Wextra -Werror**

- c++로 컴파일하고 -Wall -Wextra -Werror 플래그를 사용해라.

- ##### Your code must comply with the **c++ 98 standard**. Then, it should still compile if you add the flag **-std=c++98**.

- c++98 표준으로 컴파일해라. -std=c++98 플래그를 추가해라.

- ##### Try to always develop using the most **c++** features you can (for example, choose **<cstring>** over **<string.h>**).

- 항상 c++의 특징을 잘 반영하여 개발해라(예를 들어, <string.h> 보다 <cstring>을 선택하는 등의).

	##### You are allowed to use **C** functions, but always prefer their **C++** versions if possible.

	c 함수를 쓰는 것이 허용되긴 하나, c++ 버전으로 쓰는 것을 권장한다.

- ##### Any external library and **Boost** libraries are forbidden.

- Boost 라이브러리나 외부 라이브러리는 금지된다.

<br>

# **Chapter 3**

## **Mandatory Part**

| **프로그램 이름**          | ircserv                    |
| :------------------------: | :----------------------:   |
|  **제출해야 하는 파일들**  | Makefile, *.{h, hpp}, *.cpp, *.tpp, *.ipp, 선택적 구성 파일 |
|       **Makefile**         | NAME, all, clean, fclean, re |
| **인자** | port: 수신 포트 <br> password: 연결 비밀번호 |
| **외부 함수** | c++98의 모든 함수. socket, close, setsockopt, getsockname, getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo, bind, connect, listen, accept, htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa, send, recv, signal, sigaction, lseek, fstat, fcntl, poll(또는 equivalent)|
| **Libft 권한** | 불가능 |
| **설명** | C++98로 쓰여진 IRC 서버|

##### You have to develop and IRC server in C++ 98.

C++98 버전으로 쓰인 IRC 서버를 개발해라.

##### You **mustn't** develop a client.

client는 개발하지 말아라.

##### You **mustn't** handle server-to-server communication.

서버 간의 통신을 다루지 말아라.

##### Your executable will be run as follows: **./ircserv <port> <password>**

결과물은 다음과 같이 작동한다: ./ircserv <port> <password>

- ##### port: The port number on which your IRC server will be listening to for incoming IRC connections.

- port: 들어오는 IRC 연결을 수신할 IRC 서버의 포트 번호.

- ##### password: The connection password. It will be needed by and IRC client that tries to connect to your server.

- password: 연결 비밀번호. IRC 클라이언트가 서버에 연결을 시도할 때 필요하다.

> ⚠️
>
> ##### Even it poll() is mentionned in the subject and the evaluation scale, you can use any equivalent such as select(), kqueue(), or epoll().
>
> 과제와 평가지에 poll()이 언급되어 있다고 하더라도 select(), kqueue(), 또는 epoll() 등의 대체 함수를 사용할 수 있다.

### **1.Requirements**

- ##### The server must be capable of handling multiple clients at the same time and never hang.

- 서버는 여러 클라이언트를 동시에 처리할 수 있어야 하며 절대 끊겨선 안 된다.

- ##### Forking is not allowed. All I/O operations must be **non-blocking**.

- fork는 금지된다. 논블로킹으로 입출력이 처리되어야 한다.

- ##### Only **1** poll() (or equivalent) can be used for handling all these operations (read, wrtie, but also listen, and so forth)

- 다른 동작들을 처리하기 위해 반드시 하나의 poll()(또는 대체 함수)만 사용할 수 있다.(읽기, 쓰기, 연결 요청, 기타 등등)

> ⚠️
>
> ##### Because you have to use non-blocking file descriptors, it is possible to use read/recv or write/send functions with no poll() (or equivalent), and your server wouldn't be blocking. But it would consume more system resources. Thus, if you try to read/recv or write/send in any file descriptor without using poll() (or equivalent), your grade will be 0.
>
> 논 블로킹 파일 디스크립터를 사용해야 하므로, read/recv 또는 write/send 함수를 poll() (또는 대체 함수) 없이 사용할 수 있으며 서버는 블로킹되지 않는다. 하지만 더 많은 시스템 리소스가 소모된다. 그러므로, 어떤 파일 디스크립터든 poll() (또는 대체 함수) 없이 read/recv 또는 write/send 작업을 하려고 하면 0점을 받게 된다.

- ##### Several IRC clients exist. You have to choose one of them as a **reference**. Your reference client will be used during the evaluation process.

몇 가지의 IRC 클라이언트가 존재한다. 그 중 하나를 참고할 수 있다. 참고 클라이언트는 평가 도중 사용될 것이다.

- ##### Your reference client must be able to connect to your server without encountering any error.

참고 클라이언트는 반드시 에러 없이 서버에 연결이 가능해야 한다.

- ##### Communication between client and server has to be done via **TCP/IP** (v4 or v6).

- 클라이언트와 서버 간의 통신은 TCP/IP로 이루어져야 한다(v4 또는 v6).

- ##### Using your reference client with your server must be similar to using it with any official IRC server. However, your only have to implement the following features:

- 참고 클라이언트를 서버와 함께 사용하는 것은 공식적인 IRC 서버를 사용하는 것과 비슷한 결과를 내야 한다. 하지만, 다음과 같은 기능만 구현하면 된다.

	- ##### You must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.

	- 참고 클라이언트를 사용하여 인증을 할 수 있어야 하고, 닉네임, 사용자명을 설정할 수 있어야 하고, 채널에 참가할 수 있어야 하고 비밀 메세지를 보낼 수 있어야 한다.

	- ##### All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.

	- 한 클라이언트에서 채널로 전송되는 모든 메세지는 채널에 참가한 다른 모든 클라이언트에게도 전달되어야 한다.

	- ##### You must have **operators** and regular users.

	- 운영자와 일반 사용자가 있어야 한다.

	- ##### Then, you have to implement the commands that are specific to **channel operators**:
	
	- 채널 운영자만 사용할 수 있는 명령어를 구현해야 한다.

		- ##### KICK - Eject a client from the channel

		- KICK - 클라이언트를 채널에서 강퇴한다

		- ##### INVITE - invite a client to a channel

		- INVITE - 클라이언트를 채널에 초대한다.

		- ##### TOPIC - Change or view the channel topic

		- TOPIC - 채널의 주제를 변경 또는 보여준다.

		- ##### MODE - Change the channel's mode:

		- MODE - 채널의 모드를 변경한다.

			- ##### i: Set/remove Invite-only channel

			- i: 초대 전용 채널 설정/제거

			- ##### t: Set/remove the restrictions of the TOPIC command to channel operators

			- t: 채널 운영자에게 TOPIC 명령의 제한 설정/제거
			
			- ##### k: Set/remove the channel key (password)

			- k: 채널의 키 설정/제거(비밀번호)

			- ##### o: Give/take channel operator privilege

			- o: 채널 운영자 권한 지급/압수

			- ##### l: Set/remove the user limit to channel

			- l: 채널에 대한 사용자의 제한 설정/제거

- ##### Of course, you are expected to write a clean code.

- 물론, 코드는 깔끔하게 작성해야 한다.

### **2. For MacOs only**

> ⚠️
>
> ##### Since MacOs doesn't implement write() the same way as other Unix OSes, you are allowed to use fcntl(). You must use file descriptors in non-blocking mode in order to get a behavior similar to the one of other Unix Oses.
>
> MacOs는 다른 유닉스 OS들처럼 write()를 구현하지 않으므로 fcntl()를 사용할 수 있다. 다른 유닉스 OS들과 비슷한 동작을 하도록 구현하려면 파일 디스크립터를 논 블로킹 모드로 사용해야 한다.

> ⚠️
>
> ##### However, you are allowed to use fcntl() only as follows: fcntl(fd, F_SETFL, O_NONBLOCK); Any other flag is forbidden.
>
>  하지만, 오직 fcntl(fd, F_SETFL, O_NONBLOCK) 일 때만 fcntl() 함수를 사용할 수 있다. 다른 플래그는 금지된다.

### **3. Test example**

##### Verify absolutely every possible error and issue (receiving partial data, low bandwidth, and so forth).

가능한 모든 에러와 이슈(부분 데이터 수신, 낮은 대역폭, 기타 등등)을 확인한다.

##### To ensure that your server correctly processes everything that you send to it, the following simple test using **nc** can be done:

서버가 보내는 모든 것을 올바르게 수행하는 것을 확인하기 위해 nc를 사용하여 다음과 같은 간단한 테스트를 진행할 수 있다:

<img width="316" alt="스크린샷 2024-11-26 오후 6 07 40" src="https://github.com/user-attachments/assets/7aca2272-cd42-49b9-972f-a4b2b2acdb3a">

##### Use **ctrl+D** to send the command in several parts: 'com', than 'man', than 'd\n'.

ctrl+D를 사용하여 여러 부분으로 명령어를 보낸다: 'com', 'man', 'd\n'

##### In order to process a command, you have to first aggregate the received packet in order to rebuild it.

명령을 처리하려면, 재구성하기 위해 먼저 수신된 패킷을 집계해야 한다.

# **Chapter 4**

## **Bonus Part**

##### Here are the extra features you can add to your IRC server so it looks even more like and actual IRC server:

더욱 실제 IRC 서버처럼 보이게 하기 위해 IRC 서버에 추가할 몇 가지 추가적인 특징이 있다:

- ##### Handle file transfer.

- 파일 전송 처리.

- ##### A bot.

- 봇.

> ⚠️
>
> ##### The bonus part will only be assessed if the mandatory part is PERFECT. Perfect means the mandatory part has been integrally done and works without malfunctioning. If you have not passed ALL the mandatory requirements, your bonus part will not be evaluated at all.
>
> 보너스 부분은 필수 부분이 완벽한 경우에만 평가된다. 완벽하다는 것은 필수 부분이 완전하며 오작동 없이 잘 작동함을 의미한다. 만약 모든 필수 요구사항을 통과하지 못했다면 보너스는 전혀 평가받을 수 없다.
