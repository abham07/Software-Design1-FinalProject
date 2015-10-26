// CREATED BY: ABAD HAMEED

#pragma once

#include "client.h"
#include "SendFile.h"

class PRMS_Client
{
public:
	PRMS_Client();

	bool auth;

	void runClient(char *ip);
	void userCredentials(char *name, char *pwd);
	void invokeFunction(char *funcName);
	void searchDatabase(char *DocName, char *DocType, char *Subject, char *Year, char *Author);
	void sortDatabase(char *SortParam);
	void userValidate();
	void recvFile();
};
