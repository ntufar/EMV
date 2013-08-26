#include "scr_command.h"

scr_command::scr_command(void)
{
	SCR = NULL;
}

scr_command::scr_command(SCRControlImpl* scr)
{
	SCR = scr;
}

scr_command::~scr_command(void)
{
	SCR = NULL;
}

void scr_command::setReader(SCRControlImpl* scr)
{
	SCR = scr;
}

int scr_command::setCommand (byte InstrID, 
				byte P1, 
				byte P2, 
				int Lc, 
				const byte* Data, 
				int Le)
{
	byte cls, ins, p1, p2;
	int lc, le;
	
	switch(InstrID)
	{
	case CMD_READ_RECORD:
		cls = 0x00;
		ins = CMD_READ_RECORD;
		break;
	case CMD_SELECT:
		cls = 0x00;
		ins = CMD_SELECT;
		break;
	case CMD_GET_PROCCESSING_OPTIONS:
		cls = 0x80;
		ins = CMD_GET_PROCCESSING_OPTIONS;
		break;
	case CMD_GETDATA:
		cls = 0x80;
		ins = CMD_GETDATA;
		break;
	case CMD_VERIFY:
		cls = 0x00;
		ins = CMD_VERIFY;
		break;
	case CMD_GENERATE_AC:
		cls = 0x80;
		ins = CMD_GENERATE_AC;
		break;
	case CMD_EXTERNAL_AUTHENTICATE:
		cls = 0x00;
		ins = CMD_EXTERNAL_AUTHENTICATE;
		break;
	case CMD_INTERNAL_AUTHENTICATE:
		cls = 0x00;
		ins = CMD_INTERNAL_AUTHENTICATE;
		break;
	case CMD_GET_CHALLENGE:
		cls = 0x00;
		ins = CMD_GET_CHALLENGE;
		break;
	default:
		return ERR_CMD_INVALID_INSTRUCTION_ID;
	}

	p1 = P1;
	p2 = P2;
	lc = Lc;
	le = Le;
	return capdu.setApdu (cls, ins, p1, p2, lc, Data, le);
}

int scr_command::setReadRecord (byte recordNum, byte sfi)
{
	return setCommand(CMD_READ_RECORD, recordNum, ((sfi << 3) | 0x04), -1, 0, 0x00);
}

int scr_command::setSelect (byte *data, int data_len, bool by_name, bool first)
{
	byte p1, p2;
	(by_name)? p1 = 0x04: p1 = 0x00;
	(first)? p2 = 0x00: p2 = 0x02;

	return setCommand(CMD_SELECT, p1, p2, data_len, data, 0x00);
}

int scr_command::setGetProcessingOptions (byte *pdol, int len)
{
	return setCommand (CMD_GET_PROCCESSING_OPTIONS, 0x00, 0x00,
		len, pdol, 0x00);
}

int scr_command::setGetData (short dataTag)
{
	byte p1 = (byte)((dataTag & 0xff00) >> 8);
	byte p2 = (byte)(dataTag & 0x00ff);
	return setCommand(CMD_GETDATA, p1, p2, -1, 0, 0x00);
}

// Fields are set according to EMV book3, ch 2.5.12 (tables I - 24, and I - 25)
int scr_command::setVerifyPlaintext (const byte pin_block[], byte block_size)
{
	byte p1 = 0x00;
	byte p2 = 0x80; // see table I-25, ch 2.5.12.2, emv book 3

	return setCommand(CMD_VERIFY, p1, p2, block_size, pin_block, -1);
}

// Fields are set according to EMV book3, ch 2.5.12 (tables I - 24, and I - 25)
int scr_command::setVerifyEnciphered (const byte pin_block[], byte block_size)
{
	byte p1 = 0x00;
	byte p2 = 0x88; // see table I-25, ch 2.5.12.2, emv book 3

	return setCommand(CMD_VERIFY, p1, p2, block_size, pin_block, -1);
}

// Fields are set according to EMV book3, ch 2.6
int scr_command::setGetChallenge()
{
	byte p1 = 0x00;
	byte p2 = 0x00;
	return setCommand(CMD_GET_CHALLENGE, p1, p2, -1, 0, 0x00); 
}

int scr_command::setGenerateAC (const byte *data, UNINT data_len, 
					            CRYPTOGRAM_TYPE cryptogram, bool combinedDDA_AC)
{
	byte p1 = 0x00;
	byte p2 = 0x00;
	byte lc = data_len;
	byte le = 0x00;
	switch (cryptogram)
	{
	case AAC:
		p1 = 0x00;
		break;
	case TC:
		p1 = 0x40;
		break;
	case ARQC:
		p1 = 0x80;
		break;
	default:
		return ERR_CMD_INVALID_CRYPTOGRAM_TYPE;
	}

	if (combinedDDA_AC)
		set_bit(p1, 0x10); // Setting 5th bit according to Bulletin #9 (see www.emvco.com)
	return setCommand(CMD_GENERATE_AC, p1, p2, lc , data, le);
}

int scr_command::setExternalAuthenticate (const byte *data, UNINT data_len)
{
	byte p1 = 0x00;
	byte p2 = 0x00;

	return setCommand(CMD_EXTERNAL_AUTHENTICATE, p1, p2, data_len, data, -1);
}

int scr_command::setInternalAuthenticate (const byte *data, UNINT data_len)
{
	byte p1 = 0x00;
	byte p2 = 0x00;

	return setCommand(CMD_INTERNAL_AUTHENTICATE, p1, p2, data_len, data, 0x00);
}

int scr_command::setScript (const byte *data, UNINT data_len)
{
	UNINT indx = 0;
	byte cls;
	byte ins;
	byte p1;
	byte p2;
	int lc;
	int le;

	// Initialize cls
	if (indx > data_len - 1)
		return ERR_CMD_INVALID_SCRIPT_COMMAND;
	else
		cls = data[indx++];

	// Initialize ins
	if (indx > data_len - 1)
		return ERR_CMD_INVALID_SCRIPT_COMMAND;
	else
		ins = data[indx++];

	// Initialize P1
	if (indx > data_len - 1)
		return ERR_CMD_INVALID_SCRIPT_COMMAND;
	else
		p1 = data[indx++];

	// Initialize P2
	if (indx > data_len - 1)
		return ERR_CMD_INVALID_SCRIPT_COMMAND;
	else
		p2 = data[indx++];

	// Initialize Lc
	if (indx > data_len - 1)
		return ERR_CMD_INVALID_SCRIPT_COMMAND;
	else
		lc = 0x000000ff & data[indx++];

	// Initialize Data
	if (indx > data_len - 1)
		return ERR_CMD_INVALID_SCRIPT_COMMAND;
	
	const byte *command_data = data + indx;

	indx += lc;

	// Initialize Le
	if (indx <= data_len - 1)
		le = 0x000000ff & data[indx];
	else
		le = -1;

	return capdu.setApdu (cls, ins, p1, p2, lc, command_data, le);
}

int scr_command::setP1 (byte val)
{
	return capdu.updateP1(val);
}
int scr_command::setP2 (byte val)
{
	return capdu.updateP2(val);
}
int scr_command::setCLA (byte val)
{
	return capdu.updateCLA(val);
}
int scr_command::setINS (byte val)
{
	return capdu.updateINS(val);
}
int scr_command::setLe (byte val)
{
	return capdu.updateLe(val);
}
int scr_command::setData (byte *val, int len)
{
	return capdu.updateData(val, len);
}

int scr_command::run (R_APDU *rapdu, long TransactionToken)
{
	if (!SCR)
		return ERR_CMD_READER_ISNOT_INITIALIZED;

	if (!capdu.IsHeader ())
		return ERR_CMD_COMMAND_ISNOT_INITIALIZED;

	if (!SCR->IsInitialized ())
		return ERR_CMD_READER_ISNOT_INITIALIZED;

	SCROperationEventImpl opEvent;
	int res;

	SCR->removeEvent ();
	if ((res = SCR->addOperationEvent (&opEvent)) != SUCCESS)
		return res;

	res = SCR->SendCommand (capdu.getApdu (), capdu.getApduLen (), 
		TransactionToken);
	SCR->removeEvent ();
	if (res != SCR_SUCCESS)
	{
		return opEvent.getError ();
	}
	byte *dataArr;
	int len;
	
	res = opEvent.getByteString (&dataArr);
	if (res != SUCCESS)
		return res;
	len = opEvent.getLength ();

	res = rapdu->setApdu (dataArr, len);
	if (res != SUCCESS)
		return res;
	return SUCCESS;
}
