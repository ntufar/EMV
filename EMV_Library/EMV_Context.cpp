#include "EMV_Context.h"
#include "../Runtime/UIControlImpl.h"


int EMV_Context::instanceCounter = 0;
int EMV_Context::TransactionToken = 0;
Context EMV_Context::EnvContext;
bool EMV_Context::OnLineCompleted = false;
byte EMV_Context::ReferralResponseCode = 0;
int EMV_Context::OnLineResult = -1;
int EMV_Context::ContextStatus = EMV_CONTEXT_NOT_INITIALIZED;
int EMV_Context::IssuerScriptSize = 0;
bool EMV_Context::ReversalNeeded = false;

EMV_Context::EMV_Context(void)
{
	instanceCounter++;
	InitStatus = EMV_DATA_NOT_INITIALIZED;
}

EMV_Context::~EMV_Context(void)
{
	instanceCounter--;
	if (instanceCounter  <= 0)
		UninitContext();
}


void EMV_Context::UninitContext()
{
	if (ContextStatus == EMV_CONTEXT_INITIALIZED)
	{
		EnvContext.unInitializeContext ();
		TransactionToken = 0;
		ReferralResponseCode = 0;
		OnLineCompleted = false;
		OnLineResult = -1;
		ContextStatus = EMV_CONTEXT_NOT_INITIALIZED;
		EMV_Context::IssuerScriptSize = 0;
		ReversalNeeded = false;
	}
}

int EMV_Context::initContext(AccessManager *pAM, int TransactionToken)
{
	int res;
	if (ContextStatus == EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_ALREADY_INITIALIZED;

	EnvContext.unInitializeContext();
	if ((res = EnvContext.initializeContext (pAM)) != SUCCESS)
	{
		ContextStatus = EMV_CONTEXT_ERROR;
		return res;
	}

	EMV_Context::TransactionToken = TransactionToken;
	// Initialize hash with some data
	// Add Current Time to registry (tag 0x9A)
	AddCurTime2Hash();
	ReferralResponseCode = 0;
	OnLineCompleted = false;
	OnLineResult = -1;
	ContextStatus = EMV_CONTEXT_INITIALIZED;
	ReversalNeeded = false;
	
	return SUCCESS;
}

// Initialization functions

// initAmount initializes 3 data elements: Amount Authorized,
//	Transaction Currency Code, and Transaction Currency Exponent
int EMV_Context::initAmount(byte Amount[], byte CurrencyCode[])
{
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;

	int res;
	// Write amount to the Amount Authorized data element (tag 0x9f02)
	DataObject dob_Amount;
	dob_Amount.set (Amount, 6, CNFG_TRANSACTION, "n");
	if ((res = EnvContext.setTagValue (0x9F02, &dob_Amount, IO_CREATE)) != SUCCESS)
		return res;

	// Write Currency code to the Transaction Currency Code data element (tag 0x5f2a)
	byte currency [2];
	memcpy (currency, CurrencyCode, 2);
	currency[0] &= 0x0f;
	dob_Amount.set (currency, 2, CNFG_TRANSACTION, "n");
	if ((res = EnvContext.setTagValue (0x5f2a, &dob_Amount, IO_CREATE)) != SUCCESS)
		return res;

	// Write Transaction Currency Exponent (tag 0x5f36)
	dob_Amount.Data [0] = (CurrencyCode[0] & 0xf0) >> 4;
	dob_Amount.len = 1;
	strcpy (dob_Amount.Format, "n");
	return EnvContext.setTagValue (0x5f36, &dob_Amount, IO_CREATE);

}

// Initializes 'Amount,Other' data element
int EMV_Context::initAmountOther(byte Amount[])
{
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;

	// Write amount to the 'Amount, Other' data element (tag 0x9f03)
	DataObject dob_Amount;
	dob_Amount.set (Amount, 6, CNFG_TRANSACTION, "n");
	return EnvContext.setTagValue (0x9F03, &dob_Amount, IO_CREATE);
}

// initializes 'Transaction Type' data element (tag 0x9C)
int EMV_Context::initTransactionType(byte TransactionType)
{
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;

	int res;

	// Write amount to the 'Amount, Other' data element (tag 0x9f03)
	DataObject dob_Trans;
	dob_Trans.set (&TransactionType, 1, CNFG_TRANSACTION, "n");
	if ((res = EnvContext.setTagValue (0x9C, &dob_Trans, IO_CREATE)) != SUCCESS)
		return res;

	char asciTransType [3];
	asciTransType [0] = getHexChar (TransactionType >> 4);
	asciTransType [1] = getHexChar (0x0f & TransactionType);
	asciTransType [2] = '\0';

	CnfgControlImpl *CNFG = (CnfgControlImpl*)EnvContext.GetService(CNTXT_CNFG);
	CNFG->setTransactionType(asciTransType);

	DataObject dob_TransInfo;
	return EnvContext.getTagValue(CNFG_TRANSACTION, 0x60000001, &dob_TransInfo);
}

int EMV_Context::AddCurTime2Hash()
{
	SystemControlImpl syst;
/*	
	= 
		(SystemControlInterface*)EnvContext.GetService (CNTXT_SYSTEM);
	if (!syst)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;
	if (!syst->opened ())
		return EMV_CONTEXT_IS_NOT_INITIALIZED;
*/
	DateStruct curDate;
	int res = syst.retreiveDateEx(&curDate);
	if (res == SUCCESS)
	{
		byte byteDate [3];
		// Set Date
		DateStruct2EMVDate(byteDate, curDate);
		DataObject dob_curDate;
		dob_curDate.set (byteDate, 3, CNFG_TRANSACTION, "n");
		EnvContext.setTagValue (0x9a, &dob_curDate, IO_CREATE | IO_UPDATE);
		// Set Time
		DateStruct2EMVTime(byteDate, curDate);
		DataObject dob_curTime;
		dob_curTime.set (byteDate, 3, CNFG_TRANSACTION, "n");
		EnvContext.setTagValue (0x9f21, &dob_curTime, IO_CREATE | IO_UPDATE);
	}
	
	return res;
}

int EMV_Context::initData(int tags[], DataObject *objects[], bool hashOnly[],
						  bool mandatory[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if ((initError = EnvContext.getTagValue (tags[i], objects[i], 
			hashOnly[i])) != SUCCESS)
		{
			if (mandatory[i])
			{
				InitStatus = EMV_DATA_ERROR;
				return EMV_MISSING_MANDATORY_DATA;
			}
		}
	}
	InitStatus = EMV_DATA_INITIALIZED;
	return SUCCESS;
}

int EMV_Context::updateDataObject (int tag, DataObject *dob, 
								   byte updateByte, byte bit_mask,
								   bool setBit)
{
	if ((updateByte - 1) < 0 || (updateByte - 1) > dob->len)
		return ERR_BAD_ARGUMENT;
	if (setBit)
		set_bit(dob->Data [updateByte - 1], bit_mask);
	else
		reset_bit(dob->Data [updateByte - 1], bit_mask);
	return EnvContext.setTagValue (tag, dob, IO_UPDATE);
}

int EMV_Context::updateDataObject (int tag,  
								   byte updateByte, byte bit_mask,
								   bool setBit)
{
	DataObject dob;
	int res;
	// Read Data Object from the context
	res = EnvContext.getTagValue(tag, &dob, false); // if not in the context, then read from the registry
	if (res == SUCCESS)
	{
		if ((updateByte - 1) < 0 || (updateByte - 1) > dob.len)
			res = ERR_BAD_ARGUMENT;
		else
		{
			if (setBit)
				set_bit(dob.Data [updateByte - 1], bit_mask);
			else
				reset_bit(dob.Data [updateByte - 1], bit_mask);

			res = EnvContext.setTagValue (tag, &dob, IO_UPDATE);
		}
	}
	return res;
}

int EMV_Context::setDataObject(int tag, const byte* value, int value_len,
							   const char* format, int category)
{
    int res;
	DataObject dob;
	res = dob.set ((byte*)value, value_len, category, format);
	if (res == SUCCESS)
		res = EnvContext.setTagValue(tag, &dob, IO_CREATE | IO_UPDATE);
	return res;
}

ServiceControl* EMV_Context::GetService(int ServiceType)
{
	return EnvContext.GetService(ServiceType);
}

bool EMV_Context::IsOnlineTerminal()
{
	int res;
	DataObject dob_termType;

	// Get Terminal Type from the hash
	res = EnvContext.getTagValue(0x9f35, &dob_termType, false);
	if (res == SUCCESS)
	{
		// The 'Offline only' terminal has its 4 least significant bits
		// either 0011, or 0110 (see EMV book 4, Annex A1.
		if ((dob_termType.Data [0] & 0x0f) != 0x03 &&
			(dob_termType.Data [0] & 0x0f) != 0x06)
			return true; // online terminal
	} 
	return false; // offline terminal
}

bool EMV_Context::IsOfflineTerminal()
{
	int res;
	DataObject dob_termType;

	// Get Terminal Type from the hash
	res = EnvContext.getTagValue(0x9f35, &dob_termType, false);
	if (res == SUCCESS)
	{
		// The 'Online only' terminal has its 4 least significant bits
		// either 0001, or 0100 (see EMV book 4, Annex A1.
		if ((dob_termType.Data [0] & 0x0f) != 0x01 &&
			(dob_termType.Data [0] & 0x0f) != 0x04)
			return true; // offline terminal
	} 
	return false; // online terminal
}

bool EMV_Context::IsMerchantTerminal()
{
	int res;
	DataObject dob_termType;

	// Get Terminal Type from the hash
	res = EnvContext.getTagValue(0x9f35, &dob_termType, false);
	if (res == SUCCESS)
	{
		// The 'Merchant-controlled' terminal has its 4 most significant bits = 2
		if ((dob_termType.Data [0] & 0xf0) == 0x20)
			return true; // Merchant-controlled terminal
	} 
	return false; // online terminal
}
bool EMV_Context::IsFinancialTerminal()
{
	int res;
	DataObject dob_termType;

	// Get Terminal Type from the hash
	res = EnvContext.getTagValue(0x9f35, &dob_termType, false);
	if (res == SUCCESS)
	{
		// The 'Financial-controlled' terminal has its 4 most significant bits = 1
		if ((dob_termType.Data [0] & 0xf0) == 0x10)
			return true; // Financial-controlled terminal
	} 
	return false; // online terminal
}
bool EMV_Context::IsCardholderTerminal()
{
	int res;
	DataObject dob_termType;

	// Get Terminal Type from the hash
	res = EnvContext.getTagValue(0x9f35, &dob_termType, false);
	if (res == SUCCESS)
	{
		// The 'Cardholder-controlled' terminal has its 4 most significant bits = 3
		if ((dob_termType.Data [0] & 0xf0) == 0x30)
			return true; // carholder-controlled terminal
	} 
	return false; // online terminal
}

void EMV_Context::OutputMsg(const char* msg)
{
	//#ifdef _DEBUG
/*		UIControlImpl *pui = (UIControlImpl*)EnvContext.GetService(CNTXT_UI);
		if (!pui || !pui->opened())
			return;
		pui->writeStatus (msg);*/
	//#endif
	printf("EMV_Context::OutputMsg(): %s\n",msg);
}

int EMV_Context::openLogFile(int LogType, int *fd)
{
	if (!IsValidLogType(LogType))
		return EMV_CONTEXT_INVALID_LOG_TYPE;
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;
	
	SystemControlImpl syst;
	// = (SystemControlInterface*)GetService (CNTXT_SYSTEM);
	//if (!syst)
		//return EMV_CONTEXT_IS_NOT_INITIALIZED;

	int res;
	
	// Get a pathname of the file for requested LogType
	DataObject dob;
	res = EnvContext.getTagValue (CNFG_TERMINAL, LogType, &dob);
	if (res != SUCCESS || dob.len <= 0)
	{
		return syst.openFile (getDfltPath(LogType),
								   SCS_FILE_APPEND | SCS_FILE_CREATE |
								   SCS_FILE_WRONLY, fd);
	}
	// Tag value is successfully retrieved
	if (dob.Data [dob.len - 1] != '\0')
	{
		char *tmp = new char [dob.len + 1];
		memcpy (tmp, dob.Data, dob.len);
		dob.Data [dob.len] = '\0';
		res = syst.openFile (tmp,
							  SCS_FILE_APPEND | SCS_FILE_CREATE |
							  SCS_FILE_WRONLY, fd);
		delete [] tmp;
		return res;
	}
	else
	{
		return syst.openFile ((char*)dob.Data,
							  SCS_FILE_APPEND | SCS_FILE_CREATE |
							  SCS_FILE_WRONLY, fd);
	}
}

int EMV_Context::add2LogFile(int fd, const byte *log_entry, UNINT log_sz)
{
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;
	
	SystemControlImpl syst; // = (SystemControlInterface*)GetService (CNTXT_SYSTEM);
	//if (!syst)
	//	return EMV_CONTEXT_IS_NOT_INITIALIZED;

	addStamp2LogFile(fd);
	
	int res = SUCCESS;
	char *buff = HexByte2AsciiStr(log_entry, log_sz);
	if (buff)
	{
		// Write data
		res = syst.writeFile (fd, buff, (UNINT)strlen(buff), SCS_FILE_LN_MODE);
		delete [] buff;
	}
	return res;
}

int EMV_Context::addStamp2LogFile(int fd)
{
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;
	
	SystemControlImpl syst; // = (SystemControlInterface*)GetService (CNTXT_SYSTEM);
	//if (!syst)
	//	return EMV_CONTEXT_IS_NOT_INITIALIZED;

	int res;

	// Get Current Time
	DateStruct date;
	res = syst.retreiveDateEx(&date);
	if (res != SUCCESS)
		memset(&date, 0, sizeof(DateStruct));
	
	// Convert DateStruct to ASCII string
	char asci_date [20];
	sprintf(asci_date, "%02d/%02d/%02d%02d %02d:%02d:%02d", date.MN, date.DD,
									date.CC, date.YY, date.HH, date.MM, 
									date.SS);

	// Get Transaction Sequence number (tag '9F41')
	DataObject dob;
	char seq_num [17]; // maximum is 16 digits (8 numeric bytes)
	seq_num[0] = '\0';
	res = EnvContext.getTagValue (CNFG_TERMINAL, 0x9f41, &dob);
	if (res != SUCCESS)
		strcpy (seq_num, "0");
	else
	{
		// Convert numeric format to ASCII string
		int i = 0;
		// Do not output leading 0's
		for (; (i < dob.len && i < 17); i++)
		{
			if (dob.Data [i] != 0)
				break;
		}
		for (; (i < dob.len && i < 17); i++)
			sprintf (seq_num, "%s%02X", seq_num, dob.Data [i]);
	}
	int indx = 0;
	if (seq_num[0] == '\0')
	{
		strcpy (seq_num, "0");
		indx = 0;
	}
	else
	{
		if (seq_num[0] == '0')
			indx++; // ignore leading '0'
	}
	char *out_str = new char [strlen(asci_date) + strlen (seq_num) + 6];
	if (!out_str)
		return ERR_MEMORY_ALLOC;

	// Format log entry stamp
	sprintf (out_str, "%s (%s): ", asci_date, seq_num + indx);

	// Write log entry stamp
	res = syst.writeFile (fd, out_str, (UNINT)strlen(out_str), 0);
	delete [] out_str;
	return res;
}

int EMV_Context::closeLogFile (int fd)
{
	if (ContextStatus != EMV_CONTEXT_INITIALIZED)
		return EMV_CONTEXT_IS_NOT_INITIALIZED;
	
	SystemControlImpl syst;// = (SystemControlInterface*)GetService (CNTXT_SYSTEM);
	//if (!syst)
	//	return EMV_CONTEXT_IS_NOT_INITIALIZED;

	return syst.closeFile (fd);
}

bool EMV_Context::IsValidLogType(int LogType)
{
	switch (LogType)
	{
	case EMV_LOG_REVERSAL: return true;
	case EMV_LOG_DATA_BATCH: return true;
	case EMV_LOG_AUTH_MSG: return true;
	// add new log types here
	default: return false;
	}
}

const char *EMV_Context::getDfltPath(int LogType)
{
	switch (LogType)
	{
	case EMV_LOG_REVERSAL: return DEFAULT_REVERSAL_LOG;
	case EMV_LOG_DATA_BATCH: return DEFAULT_DATA_BATCH_LOG;
	case EMV_LOG_AUTH_MSG: return DEFAULT_AUTH_MSG_LOG;
	// add new log types here
	default: return 0;
	}
}

bool EMV_Context::IsLogEnabled(int LogType)
{
	int res;
	DataObject dob;
	res = EnvContext.getTagValue (0x5000000A, &dob, false);
	if (res != SUCCESS || dob.len == 0)
	{
		// Consider log as disabled
		return false;
	}

	switch (LogType)
	{
	case EMV_LOG_REVERSAL: return check_bit(dob.Data [0], 0x02);
	case EMV_LOG_DATA_BATCH: return check_bit(dob.Data [0], 0x01);
	case EMV_LOG_AUTH_MSG: return check_bit(dob.Data [0], 0x04);
	// add new log types here
	default: return false;
	}
}

int EMV_Context::logDataRecord (int log_type, int msg_type, 
								byte batch_type)
{
	int res;
	DataObject dob;
	
	SystemControlImpl syst; //= (SystemControlInterface*)GetService (CNTXT_SYSTEM);
	//if (!syst)
	//	return EMV_CONTEXT_IS_NOT_INITIALIZED;

	// Check if Log is enabled
	if (!IsLogEnabled(log_type))
	{
		// Log is disabled, do nothing else
		return SUCCESS;
	}

	// Get Tags of the data object required in the reversal message
	int reg_key = getLog_RegKey(msg_type);
	if (reg_key == 0)
		return ERR_CONTEXT_MSG_NOT_SUPPORTED;

	res = EnvContext.getTagValue (reg_key, &dob, false);
	if (res != SUCCESS)
		return res;
	if (dob.len <= 0)
		return DATA_INCOMPATIBLE_SIZE;

	// Create a byte array containing a concatinated list of TLV-coded
	// data object participated in the reversal message
	byte *rev_data = 0;
	UNINT rev_len = 0;
	res = getOnLineData(dob.Data, dob.len, &rev_data, &rev_len);
	if (res != SUCCESS)
		return res;

	// Open a log file
	int fd;
	res = openLogFile (log_type, &fd);
	if (res != SUCCESS)
	{
		//printf ("Error opening a log file (%x)\n", res);
		return res;
	}
	
	// Add stamp
	addStamp2LogFile(fd);

	if (batch_type == BATCH_FIN_REC)
	{
		// Financial Record
		res = syst.writeFile (fd, "01", 2, 0);
	}
	else if (batch_type == BATCH_ADV_REC)
	{
		// Offline Advice
		res = syst.writeFile (fd, "02", 2, 0);
	}
	char *buff = HexByte2AsciiStr(rev_data, rev_len);
	if (buff)
	{
		res = syst.writeFile (fd, buff, (UNINT)strlen(buff), SCS_FILE_LN_MODE);
		delete [] buff;
	}
		
	// close the log file
	closeLogFile (fd);

	return SUCCESS;
}

int EMV_Context::logDataRecord (int log_type, 
								const byte *log_data, UNINT log_sz)
{
	int res;
	DataObject dob;

	// Check if Log is enabled
	if (!IsLogEnabled(log_type))
	{
		// Log is disabled, do nothing else
		return SUCCESS;
	}

	// Open a log file
	int fd;
	res = openLogFile (log_type, &fd);
	if (res != SUCCESS)
	{
		//printf ("Error opening a log file (%x)\n", res);
		return res;
	}
	
	// Add an entry to the reversal log file
	res = add2LogFile (fd, log_data, log_sz);
	
	// close the log file
	closeLogFile (fd);

	return SUCCESS;
}

int EMV_Context::getLog_RegKey(int msg_type)
{
	switch (msg_type)
	{
	case MSG_AUTHORIZATION_REQUEST: return AUTH_RQST_TAG;
	case MSG_FINANCIAL_REQUEST: return FINANC_RQST_TAG;
	case MSG_ONLINE_ADVICE: return ADVICE_TAG;
	case MSG_REVERSAL: return REVERSAL_TAG;
	case MSG_DATA_BATCH: return DATA_BATCH_TAG;
	// add new log types here
	default: return 0;
	}
}

int EMV_Context::getOnLineData (const byte *tags, int tags_len,
					            byte **onLineData, UNINT *data_len)
{
	int res;


	// Parse Data Object List and create a concatenated list of data objects required
	// for online message. Each data object in a data list is coded according to
	// BER-TLV format. Do not recalculate a dynamic data (such as unpredictable number)
	dol_parser parser(&EnvContext);
	res = parser.createTLVList(tags, tags_len, 
						   onLineData, data_len);

	//-----------------------------------------------
	// Put onLineData into registry for testing in the main
	//DataObject dob;
	//dob.set (*onLineData, *data_len, CNFG_TRANSACTION, "b");
	//EnvContext.setTagValue(0x12345678, &dob, IO_CREATE);
	// ------------------------------------------------
	return res;
}
