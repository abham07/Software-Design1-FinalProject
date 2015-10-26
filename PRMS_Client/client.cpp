/***********************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: All client-side socket functions
************************************************/

#include "stdafx.h"
#include "client.h"

using namespace std;

WSADATA wsaData;
SOCKET m_socket;
SOCKET m_backup;
sockaddr_in con;
SOCKET AcceptSocket;

// Client constructor
Client::Client()
{
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");

	// Create a socket
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	m_backup = m_socket;
}

// Client destructor
Client::~Client() { WSACleanup(); }

// Accept IP and port to connect client to server; else send error
int Client::connectServer(char *ip, int port)
{
	// Connect to a server.
	con.sin_family = AF_INET;
	con.sin_addr.s_addr = inet_addr(ip);
	con.sin_port = htons(port);

	if (connect(m_socket, (SOCKADDR*)&con, sizeof(con)) == SOCKET_ERROR)
	{
		printf("Failed to connect.\n");
		WSACleanup();
		return 1;
	}
}

// Shut client socket down (close)
void Client::closeConnection()
{
	closesocket(m_socket);
	m_socket = m_backup;
}

// Send data to server
int Client::sendData(char *sendbuf)
{
	return send(m_socket, sendbuf, strlen(sendbuf), 0);
}

// Receive data from server
int Client::recvData(char *recvbuf, int size)
{
	int sz = recv(m_socket, recvbuf, size, 0);
	recvbuf[sz] = '\0';
	return sz;
}

// Receives a file from server
void Client::fileReceive(char *filename)
{
	char rec[50] = "";

	recv(m_socket, filename, 32, 0);
	send(m_socket, "OK", strlen("OK"), 0);

	FILE *fw = fopen(filename, "wb");

	int recs = recv(m_socket, rec, 32, 0);
	send(m_socket, "OK", strlen("OK"), 0);

	rec[recs] = '\0';
	int size = atoi(rec);

	while (size > 0)
	{
		char buffer[1030];

		if (size >= 1024)
		{
			recv(m_socket, buffer, 1024, 0);
			send(m_socket, "OK", strlen("OK"), 0);
			fwrite(buffer, 1024, 1, fw);
		}
		else
		{
			recv(m_socket, buffer, size, 0);
			send(m_socket, "OK", strlen("OK"), 0);
			buffer[size] = '\0';
			fwrite(buffer, size, 1, fw);
		}

		size -= 1024;
	}

	fclose(fw);
}

// Sends a file to server
void Client::fileSend(char *fpath)
{
	// Extract only filename from given path.
	//char filename[50];
	//int i = strlen(fpath);
	//for (; i>0; i--)if (fpath[i - 1] == '\\')break;
	//for (int j = 0; i <= (int)strlen(fpath); i++)filename[j++] = fpath[i];
	////////////////////////////////////////

	ifstream myFile(fpath, ios::in | ios::binary | ios::ate);
	int size = (int)myFile.tellg();
	myFile.close();

	char filesize[10]; _itoa(size, filesize, 10);

	//send(m_socket, filename, strlen(filename), 0);
	send(m_socket, fpath, strlen(fpath), 0);
	char rec[32] = ""; recv(m_socket, rec, 32, 0);

	send(m_socket, filesize, strlen(filesize), 0);
	recv(m_socket, rec, 32, 0);

	FILE *fr = fopen(fpath, "rb");

	while (size > 0)
	{
		char buffer[1030];

		if (size >= 1024)
		{
			fread(buffer, 1024, 1, fr);
			send(m_socket, buffer, 1024, 0);
			recv(m_socket, rec, 32, 0);
		}
		else
		{
			fread(buffer, size, 1, fr);
			buffer[size] = '\0';
			send(m_socket, buffer, size, 0);
			recv(m_socket, rec, 32, 0);
		}

		size -= 1024;
	}

	fclose(fr);
}
