/**************************************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Validates received username and password
			   with those accounts registered in accounts.csv
***************************************************************/

#include "stdafx.h"
#include "server.h"
#include "UserValidate.h"

using namespace std;

// Invoked by server to retreive username and password from client and verify 
// if they valid/registered users 
void userValidate(Server server)
{
	size_t pos1, pos2;
	string line;
	
	int flag = 0;
	char name[50] = "";
	char pwd[50] = "";

	// Retreiving user params from client
	server.recvData(name, 50);
	server.sendData("OK");
	server.recvData(pwd, 50);
	server.sendData("OK");

	// Verifying if retreived params exist in registered accounts
	cout << "Validating user credentials... \n";
	ifstream file("accounts.csv");

	if (!file)
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}

	while (!file.eof())
	{
		getline(file, line);
		pos1 = line.find(name);
		pos2 = line.find(pwd);

		// string::npos is returned if string is not found
		if (pos1 != string::npos && pos2 != string::npos)
		{
			flag = 1;
		}
		else if (pos1 != string::npos && pos2 == string::npos)
		{
			flag = 2;
		}
		else if (pos1 == string::npos && pos2 != string::npos)
		{
			flag = 2;
		}
	}

	file.close();

	// Returning confirmation/denial of user login
	if (flag == 1)
	{
		cout << "User authorized!\n\n";
		char rec[32] = "";
		server.sendData("Authorized");
		server.recvData(rec, 32);
	}
	else if (flag == 2)
	{
		cout << "User not authorized!\n\n";
		char rec[32] = "";
		server.sendData("Unauthorized");
		server.recvData(rec, 32);
	}
}
