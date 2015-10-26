/***********************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: All server-side socket functions
************************************************/

#include "stdafx.h"
#include "server.h"

using namespace std;

WSADATA wsaData;
SOCKET m_socket;
SOCKET m_backup;
sockaddr_in con;
SOCKET AcceptSocket;

// Server constructor
Server::Server()
{
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		printf("Error at WSAStartup(): %d\n", iResult);
		return;
	}
	
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

// Bind server to port and listen for client connections
void Server::startServer(int port)
{
	// Connect to a server
	con.sin_family = AF_INET;
	con.sin_addr.s_addr = inet_addr("0.0.0.0");
	con.sin_port = htons(port);

	if (bind(m_socket, (SOCKADDR*)&con, sizeof(con)) == SOCKET_ERROR)
	{
		printf("Failed to connect with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return;
	}
	
	// Listen on the socket
	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Error listening on socket with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return;
	}
}

// Shut server socket down (close)
void Server::closeConnection()
{
	closesocket(m_socket);
	m_socket = m_backup;
}

// Accept client connection when found
void Server::waitForClient()
{
	AcceptSocket = SOCKET_ERROR;
	while (AcceptSocket == SOCKET_ERROR)
	{
		AcceptSocket = accept(m_backup, NULL, NULL);
	}
	m_socket = AcceptSocket;
}

// Send data to client
int Server::sendData(char *sendbuf)
{
	return send(m_socket, sendbuf, strlen(sendbuf), 0);
}

// Receive data from client
int Server::recvData(char *recvbuf, int size)
{
	int sz = recv(m_socket, recvbuf, size, 0);
	recvbuf[sz] = '\0';
	return sz;
}

// Receives a file from client
void Server::fileReceive(char *filename)
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

// Sends a file to client
void Server::fileSend(char *fpath)
{
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
