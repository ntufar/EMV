/*
scr_command.h
This class is used to format and send commands to the ICC. Response received
from the card are located in R_APDU class, which is used to get the status 
code returned by the card and data (if data is expected).
*/
#ifndef SCR_COMMAND_H
#define SCR_COMMAND_H

#include "../Utility/utility.h"
#include "../Runtime/SCRControlImpl.h"
#include "../Runtime/SCROperationEventImpl.h"
#include "emv_constants.h"

// Define commands here
#define CMD_READ_RECORD             0xb2
#define CMD_SELECT                  0xa4
#define CMD_GET_PROCCESSING_OPTIONS 0xa8
#define CMD_GETDATA                 0xca
#define CMD_VERIFY                  0x20
#define CMD_GENERATE_AC             0xae
#define CMD_EXTERNAL_AUTHENTICATE   0x82
#define CMD_SCRIPT                  0x08
#define CMD_INTERNAL_AUTHENTICATE   0x88
#define CMD_GET_CHALLENGE           0x84

class scr_command
{
public:
	scr_command(void);
	scr_command(SCRControlImpl* scr);

	void setReader(SCRControlImpl* scr);
	int setCommand (byte InstructionID, 
					byte P1, 
					byte P2, 
					int Lc, 
					const byte* Data, 
					int Le);

	int setReadRecord (byte recordNum, byte sfi);
	int setSelect (byte *data, int data_len, bool by_name, bool first);
	int setGetProcessingOptions (byte *pdol, int len);
	int setGetData (short dataTag);
	int setVerifyPlaintext (const byte pin_block[], byte block_size);
	int setVerifyEnciphered (const byte pin_block[], byte block_size);
	int setGenerateAC (const byte *data, UNINT data_len, 
					   CRYPTOGRAM_TYPE cryptogram, bool combinedDDA_AC);
	int setExternalAuthenticate (const byte *data, UNINT data_len);
	int setInternalAuthenticate (const byte *data, UNINT data_len);
	int setGetChallenge();
	int setScript (const byte *data, UNINT data_len);

	int run (R_APDU *rapdu, long TransactionToken);
	int setP1 (byte val);
	int setP2 (byte val);
	int setINS (byte val);
	int setCLA (byte val);
	int setLe (byte val);
	int setData (byte *val, int len);

	virtual ~scr_command(void);

private:
	SCRControlImpl *SCR;
	C_APDU capdu;
};

#endif

