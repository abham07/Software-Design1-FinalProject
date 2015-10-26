/**************************************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Calls functions to boot up server and waits to
			   connect to client
***************************************************************/

#include "stdafx.h"
#include "server.h"
#include "RunServer.h"

using namespace std;

void runServer(Server server)
{
	int flag = 0;
	
	// Start Server
	server.startServer(27015);
	cout << "Server Status: RUNNING\n\n";

	while (flag != 1)
	{
		// Wait until a client connects
		server.waitForClient();
		printf("Client Status: CONNECTED\n\n");
		flag = 1;

		// Disconnect client
		//w.closeConnection();
	}
}
