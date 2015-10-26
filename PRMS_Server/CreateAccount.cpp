/********************************************************************
* CREATED BY: BRANDON CRISPINO + ABAD HAMEED
* DESCRIPTION: Takes in parameters (done by Abad) from client side 
*			   and creates account
*********************************************************************/

#include "stdafx.h"
#include "CreateAccount.h"

using namespace std;

// Invoked from server to receive username and password
// from client and create account
void createAccount(Server server)
{
	int flag = 0;
	char name[50] = "";
	char pwd[50] = "";

	// Receiving params
	server.recvData(name, 50);
	server.sendData("OK");
	server.recvData(pwd, 50);
	server.sendData("OK");
	
	// Saving params to a file accounts.csv
	ofstream file;
	file.open("accounts.csv", ios::app);
	
	if (file)
	{
		file << name << "," << pwd << "\n";
		file.close();
		flag = 1;
	}
	else
	{
		flag = 2;
	}

	// Returning confirmation/denial of account to client
	if (flag == 1)
	{
		cout << "New user registered ....\n\n";
		char rec[32] = "";
		server.sendData("Created");
		server.recvData(rec, 32);
	}
	else if (flag == 2)
	{
		cout << "User not registered ....\n\n";
		char rec[32] = "";
		server.sendData("Skipped");
		server.recvData(rec, 32);
	}
}
