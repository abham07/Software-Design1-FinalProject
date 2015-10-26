/***********************************************************************
* CREATED BY: ABAD HAMEED
* DESCRIPTION: Hardcoded data synced with functions in PRMS_Server
	
	*NOTE: If a certain function call is removed here then its related 
	function in PRMS_Server must also be removed!
*************************************************************************/

#include "stdafx.h"
#include "RunProgram.h"

RunProgram::RunProgram() { }

void RunProgram::runProgram()
{
	PRMS_Client c1 = PRMS_Client();

	// Connect to server
	c1.runClient("65.39.33.83");	// <====== PLEASE CHANGE THIS IP ADDRESS TO THE SERVER IP
	
	// Login / Authenticate User Test
	c1.userCredentials("ahameed1@lakeheadu.ca", "qwerty");
	c1.userValidate();

	// Create User Test
	c1.userCredentials("hnaser@lakeheadu.ca", "hnaser");
	c1.userValidate();

	// Search Database Test
	c1.searchDatabase("A", "Article", "Exact Sciences", "2006", "Glass");
	c1.recvFile();

	// Sort Database Test
	// Usage: <Document Name>, <Document Type>, <Subject>, <Publication Year>, <Author>
	c1.sortDatabase("Document Name");
	c1.recvFile();
}