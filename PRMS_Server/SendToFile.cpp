/********************************************
* CREATED BY: BRANDON CRISPINO
* DESCRIPTION: Takes a vector of data and
			   creates a .csv file with it
*********************************************/

#include "stdafx.h"
#include "SendToFile.h"
#include "server.h"

using namespace std;

// Function accepts a vector and filename with extension and outputs all
// vector data into specified file
void sendToFile(vector<Data> filecontainer, string filename)
{
	ofstream myfile;
	
	//clears file of any data
	myfile.open(filename, ifstream::out | ifstream::trunc);
	myfile.close();
	myfile.open(filename, ios::app);
	for (size_t i = 0; i < filecontainer.size(); i++){
		myfile << filecontainer[i].DocName << "," << filecontainer[i].DocType << "," << filecontainer[i].Subject 
			<< "," << filecontainer[i].Year << "," << filecontainer[i].Author << "\n";
	}
	myfile.close();
	printf("Found data stored to file ....\n\n");
}
