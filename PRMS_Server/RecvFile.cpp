/********************************************
* CREATED BY: ABAD HAMEED      
* DESCRIPTION: responsible to receive a file
*********************************************/

#include "stdafx.h"
#include "server.h"
#include "RecvFile.h"

void recvFile(Server server)
{
	// Work with client to receive a file
	while (TRUE)
	{
		char rec[32] = "";
		server.recvData(rec, 32);
		server.sendData("OK");

		if (strcmp(rec, "FileSend") == 0)
		{
			char fname[32] = "";
			server.fileReceive(fname);
			printf("File Received.........\n");
			break;
		}
	}
}
