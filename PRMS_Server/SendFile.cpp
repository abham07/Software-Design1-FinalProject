/********************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Sends a file to client
*********************************************/

#include "stdafx.h"
#include "server.h"
#include "SendFile.h"

using namespace std;

// Work with client to send a file
void sendFile(Server server, char *filename)
{
	while (TRUE)
	{
		char rec[32] = "";
		//char str[80];

		cout << "Sending file ... \n";
		// Sending File
		server.sendData("FileSend");
		server.recvData(rec, 32);

		//strcpy(str, "C:\\test\\");
		//strcat(str, filename);
		server.fileSend(filename);
		printf("File Sent.............\n\n");

		break;

		/*Send Close Connection Signal
		w.sendData("EndConnection");
		w.recvData(rec, 32);
		printf("Connection ended......\n\n");*/
	}
}
