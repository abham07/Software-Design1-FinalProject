/********************************************************************
* CREATED BY: BRANDON CRISPINO
* DESCRIPTION: Gets all resources from data.csv and places in vector
*********************************************************************/

#include "stdafx.h"
#include "server.h"
#include "GetData.h"

using namespace std;

// Function used to read ALL resources into program and store into a vector
vector<Data> Getdata()
{
	Data temp;
	vector<Data> Tempcontain;
	ifstream myfile("data.csv");
	
	while (myfile.good())
	{
		getline(myfile, temp.DocName, ',');
		getline(myfile, temp.DocType, ',');
		getline(myfile, temp.Subject, ',');
		getline(myfile, temp.Year, ',');
		getline(myfile, temp.Author, '\n');
		Tempcontain.push_back(temp);
	}
	return Tempcontain;
}
