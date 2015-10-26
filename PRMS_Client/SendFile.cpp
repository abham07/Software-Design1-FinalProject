/***************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Sends a file to server
****************************************/

#include "stdafx.h"
#include "client.h"
#include "SendFile.h"

using namespace std;

// Work with server to send a file
void sendFile(Client client, char *filename)
{
	while (TRUE)
	{
		char rec[32] = "";
		//char str[80];

		cout << "Sending file ... \n";
		// Sending File
		client.sendData("FileSend");
		client.recvData(rec, 32);

		//strcpy(str, "C:\\test\\");
		//strcat(str, filename);
		client.fileSend(filename);
		printf("File Sent.............\n\n");

		break;
	}
}
