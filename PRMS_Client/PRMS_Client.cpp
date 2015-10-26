/**************************************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Contains all client-side functions and creates
*              RunProgram object to run the functions
***************************************************************/

// PRMS_Client.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "PRMS_Client.h"
#include "RunProgram.h"

using namespace std;

/////////////////////////////////////////////
Client client;

PRMS_Client::PRMS_Client() {}
/////////////////////////////////////////////

// Accepts IP as param to invoke function
void PRMS_Client::runClient(char *ip)
{
	// Connect To Server
	if (client.connectServer(ip, 27015) == 1)
	{
		system("pause");
		exit(1);
	}
	printf("Connected to server...\n\n");
}

// Accepts username and password as param and sends to server
void PRMS_Client::userCredentials(char *name, char *pwd)
{
	char rec[32] = "";
	client.sendData(name);
	client.recvData(rec, 32);
	client.sendData(pwd);
	client.recvData(rec, 32);
}

void PRMS_Client::invokeFunction(char *funcName)
{
	char rec[32] = "";

	client.sendData(funcName);
	client.recvData(rec, 32);
}

// Sends search params to server for implementation
void PRMS_Client::searchDatabase(char *DocName, char *DocType, char *Subject, char *Year, char *Author)
{
	char rec[32] = "";

	invokeFunction("Search");

	client.sendData(DocName);
	client.recvData(rec, 32);
	client.sendData(DocType);
	client.recvData(rec, 32);
	client.sendData(Subject);
	client.recvData(rec, 32);
	client.sendData(Year);
	client.recvData(rec, 32);
	client.sendData(Author);
	client.recvData(rec, 32);
}

// Sends sort parameter to server for implementation
void PRMS_Client::sortDatabase(char *SortParam)
{
	char rec[32] = "";

	invokeFunction("Sort");

	client.sendData(SortParam);
	client.recvData(rec, 32);
}

// Retrieves validation of input username and password
void PRMS_Client::userValidate()
{
	while (TRUE)
	{
		char rec[32] = "";
		client.recvData(rec, 32);
		client.sendData("OK");

		// BELOW ARE FOR LOGIN VALIDATION
		if (strcmp(rec, "Authorized") == 0)
		{
			printf("User Status: AUTHORIZED\n");
			auth = TRUE;
			break;
		}
		else if (strcmp(rec, "Unauthorized") == 0)
		{
			printf("User Status: NOT AUTHORIZED\n");
			auth = FALSE;
			break;
		}
		// BELOW ARE FOR CREATE ACCOUNT/USER VALIDATION
		else if (strcmp(rec, "Created") == 0)
		{
			printf("User account created\n");
			break;
		}
		else if (strcmp(rec, "Skipped") == 0)
		{
			printf("User not created\n");
			break;
		}
	}
}

void PRMS_Client::recvFile()
{
	// Work with server to receive a file
	while (TRUE)
	{
		char rec[100] = "";
		client.recvData(rec, 32);
		client.sendData("OK");

		if (strcmp(rec, "FileSend") == 0)
		{
			char fname[32] = "";
			client.fileReceive(fname);
			printf("File Received.........\n");
			break;
		}

		/*if (strcmp(rec, "EndConnection") == 0)
		break;
		printf("Connection Ended......\n");*/
	}
}

// MAIN function to test all functions
void main(int argc, char *argv[])
{
	// param for server IP
	char serverIP[32] = "";
	// params for login and create user
	char name[32] = "";
	char pwd[32] = "";
	// params for search
	char DocName[50] = "";
	char DocType[50] = "";
	char Subject[50] = "";
	char Year[50] = "";
	char Author[50] = "";
	// param for sort
	char SortParam[32] = "";

	RunProgram prog = RunProgram();
	prog.runProgram();

	////////////////////////////////////////////////////
	
	system("pause");
}