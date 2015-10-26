// CREATED BY: ABAD HAMEED

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define DEFAULT_PORT 27015

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

class Server
{
public:
	Server();

	void startServer(int);
	void closeConnection();
	void waitForClient();
	int sendData(char*);
	int recvData(char*, int);
	void fileReceive(char*);
	void fileSend(char*);
};
