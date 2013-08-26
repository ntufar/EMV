/*
IssuerScriptProcessing.h
Implements the "Issuer-to-Card Processing" phase of EMV Transaction.
Reference: EMV 4.0 book 3, ch 6.10; VIS 1.4.0, ch 14.

Note: Parces the script and executes the commands
*/
#ifndef ISSUERSCRIPTPROCESSING_H
#define ISSUERSCRIPTPROCESSING_H

#include "EMV_Context.h"
#include "../Utility/utility.h"
#include "scr_command.h"

#include <list>

typedef list<byte*> ISR_LIST;

enum SCS_SCRIPT_TYPE {SCS_BEFORE_GENERATE_AC = 0x71, SCS_AFTER_GENERATE_AC};

// Constants:
#define MAX_ISSUER_SCRIPT_SIZE 128

// Errors
#define ERR_FAILED_SCRIPT_PROCESSING 0xA6000001
#define ERR_INVALID_SCRIPT_LENGTH    0xA6000002

using namespace std;

class IssuerScriptProcessing :
	public EMV_Context
{
public:
	IssuerScriptProcessing(void);
	virtual ~IssuerScriptProcessing(void);

	// Processes all the scripts of the type scriptType (0x71, or 0x72)
	int processScript (SCS_SCRIPT_TYPE scriptType);

	// Parses a single script to a list of commands to be executed, and calls
	// execCommand for each command in a list.
	int parseScript(byte *data, UNINT data_len, byte *isr);

	// Parses and executes a single script command
	int execCommand (const byte *data, UNINT data_len);

private:
	void resetList();

private:
	ISR_LIST IssuerScriptResultList;
};

#endif

