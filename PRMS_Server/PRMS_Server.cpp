/********************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Runs all functions based on
*			   client-side input
*********************************************/

// PRMS_Server.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "server.h"
#include "RunServer.h"
#include "CreateAccount.h"
#include "UserValidate.h"
#include "SendFile.h"
#include "RecvFile.h"
#include "Search.h"
#include "Sort.h"
#include "GetData.h"
#include "SendToFile.h"

using namespace std;

////////////////////////////////////////////////////
Server server;
vector <Data> Container, SortContainer, SearchContainer;
Data Datatemp;
////////////////////////////////////////////////////

void _tmain(int argc, char *argv[])
{
	cout << "********* SERVER LOG ********* \n\n";

	////////////////////////////////////////////////////
	// BOOT SERVER
	runServer(server);
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	// TEST LOGIN
	userValidate(server);
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	// TEST CREATE ACCOUNT
	createAccount(server);
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	char rec[100] = "";
	server.recvData(rec, 32);
	server.sendData("OK");

	Container = Getdata();

	// SEARCH DATABASE
	if (strcmp(rec, "Search") == 0)
	{
		// found data stored into vector
		SearchContainer = Search(server, Container);
		// accepts container and filename and sends vector data to file
		sendToFile(SearchContainer, "DataFound.csv");

		// This loop is used to display the search results in the server console
		/*for (size_t i = 0; i < SearchContainer.size(); i++)
		{
			cout << SearchContainer[i].DocName << ", " << SearchContainer[i].DocType << ", " << SearchContainer[i].Subject
				<< ", " << SearchContainer[i].Year << ", " << SearchContainer[i].Author << "\n";
		}
		cout << endl;*/

		cout << "**SEARCHED DATA READY TO SEND TO CLIENT**\n";
		sendFile(server, "DataFound.csv");
	}
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	//char rec[100] = "";
	server.recvData(rec, 32);
	server.sendData("OK");

	// SORT DATABASE
	if (strcmp(rec, "Sort") == 0)
	{
		// found data stored into vector
		SortContainer = Sort(server, Container);
		// accepts container and filename and sends vector data to file
		sendToFile(SortContainer, "SortedData.csv");

		cout << "**SORTED DATA READY TO SEND TO CLIENT**\n";
		sendFile(server, "SortedData.csv");
	}
	////////////////////////////////////////////////////
	system("pause");
}
