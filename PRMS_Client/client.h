// CREATED BY: ABAD HAMEED

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Client
{
public:
	Client();
	~Client();

	int connectServer(char*, int);
	void closeConnection();
	int sendData(char*);
	int recvData(char*, int);
	void fileReceive(char*);
	void fileSend(char*);
};
