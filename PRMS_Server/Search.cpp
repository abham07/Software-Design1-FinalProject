/**************************************************************
* CREATED BY: BRANDON CRISPINO
* DESCRIPTION: Search algorithm takes in parameters from
			   client (done by Abad) and applies search
***************************************************************/

#include "stdafx.h"
#include "Search.h"

using namespace std;

// Search function invoked by server with a param vector to retreive all search params 
// from client and apply the search algorithm to get selected results
vector<Data> Search(Server server, vector<Data>Searchdata)
{
	vector<Data> Searchresult;

	char DocName[50] = "";
	char DocType[50] = "";
	char Subject[50] = "";
	char Year[50] = "";
	char Author[50] = "";

	// Retreiving all search params from client
	server.recvData(DocName, 50);
	server.sendData("OK");
	server.recvData(DocType, 50);
	server.sendData("OK");
	server.recvData(Subject, 50);
	server.sendData("OK");
	server.recvData(Year, 50);
	server.sendData("OK");
	server.recvData(Author, 50);
	server.sendData("OK");	
	
	if ((strcmp(DocName,"")) && (strcmp(Author, "")))
	{
		for (size_t i = 0; i < Searchdata.size(); i++)
		{
			if (Searchdata[i].Subject == Subject && Searchdata[i].DocType == DocType && Searchdata[i].Year == Year)
			{
				Searchresult.push_back(Searchdata[i]);
			}
		}
	}
	
	else if ((strcmp(DocName, "")) && !(strcmp(Author, "")))
	{
		for (size_t i = 0; i < Searchdata.size(); i++)
		{
			if (Searchdata[i].Author == Author && Searchdata[i].Subject == Subject && Searchdata[i].DocType == DocType && Searchdata[i].Year == Year)
			{
				Searchresult.push_back(Searchdata[i]);
			}
		}
	}
	
	else if (!(strcmp(DocName, "")) && (strcmp(Author, "")))
	{
		for (size_t i = 0; i < Searchdata.size(); i++)
		{
			if (Searchdata[i].DocName.find(DocName) != string::npos && Searchdata[i].Subject == Subject && Searchdata[i].DocType == DocType && Searchdata[i].Year == Year)
			{
				Searchresult.push_back(Searchdata[i]);
			}

		}
	}
	
	else
	{
		for (size_t i = 0; i < Searchdata.size(); i++)
		{
			if (Searchdata[i].DocName.find(DocName) != string::npos && Searchdata[i].Author == Author && Searchdata[i].Subject == Subject && Searchdata[i].DocType == DocType && Searchdata[i].Year == Year)
			{
				Searchresult.push_back(Searchdata[i]);
			}

		}
	}

	// Return vector of search results
	return Searchresult;
}
