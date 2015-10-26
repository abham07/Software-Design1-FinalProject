/********************************************************************
* CREATED BY: BRANDON CRISPINO + ABAD HAMEED
* DESCRIPTION: Sort algorithm (done by Brandon) takes in parameter
			   from client (done by Abad) and applies sort
*********************************************************************/

#include "stdafx.h"
#include "Sort.h"
#include "server.h"

using namespace std;

// Sort function invoked by server with a param vector to retreive sort param
// from client and apply the sort algorithm to get selected results
vector<Data> Sort(Server server, vector<Data> SortVec)
{
	Data Temp;
	size_t i, j;
	char SortParam[32] = "";

	// Retreiving sort param from client
	server.recvData(SortParam, 32);
	server.sendData("OK");

	// Sort by document name
	if ((strcmp(SortParam, "Document Name")) || (strcmp(SortParam, "document name")))
	{
		for (j = 0; j < SortVec.size(); j++)
		{
			for (i = 0; i < SortVec.size() - 1; i++)
			{
				if (SortVec[i + 1].DocName < SortVec[i].DocName)
				{
					Temp = SortVec[i + 1];
					SortVec[i + 1] = SortVec[i];
					SortVec[i] = Temp;
				}
			}
		}
	}
	
	// Sort by document type
	if ((strcmp(SortParam, "Document Type")) || (strcmp(SortParam, "document type")))
	{
		for (j = 0; j < SortVec.size(); j++)
		{
			for (i = 0; i < SortVec.size() - 1; i++)
			{
				if (SortVec[i + 1].DocType < SortVec[i].DocType)
				{
					Temp = SortVec[i + 1];
					SortVec[i + 1] = SortVec[i];
					SortVec[i] = Temp;
				}
			}
		}
	}
	
	// Sort by subject
	if ((strcmp(SortParam, "Subject")) || (strcmp(SortParam, "subject")))
	{
		for (j = 0; j < SortVec.size(); j++)
		{
			for (i = 0; i < SortVec.size() - 1; i++)
			{
				if (SortVec[i + 1].Subject < SortVec[i].Subject)
				{
					Temp = SortVec[i + 1];
					SortVec[i + 1] = SortVec[i];
					SortVec[i] = Temp;
				}
			}
		}
	}
	
	// Sort by publication year
	if ((strcmp(SortParam, "Publication Year")) || (strcmp(SortParam, "Year")) || (strcmp(SortParam, "year")))
	{
		for (j = 0; j < SortVec.size(); j++)
		{
			for (i = 0; i < SortVec.size() - 1; i++)
			{
				if (SortVec[i + 1].Year < SortVec[i].Year)
				{
					Temp = SortVec[i + 1];
					SortVec[i + 1] = SortVec[i];
					SortVec[i] = Temp;
				}
			}
		}
	}
	
	// Sort by author
	if ((strcmp(SortParam, "Author")) || (strcmp(SortParam, "author")))
	{
		for (j = 0; j < SortVec.size(); j++)
		{
			for (i = 0; i < SortVec.size() - 1; i++)
			{
				if (SortVec[i + 1].Author < SortVec[i].Author)
				{
					Temp = SortVec[i + 1];
					SortVec[i + 1] = SortVec[i];
					SortVec[i] = Temp;
				}
			}
		}
	}

	// Return vector of sorted results
	return SortVec;
}
