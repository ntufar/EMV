/*
EMV_Context.h
This class is a base class to all the classes which implement
different EMV phases.
The static member of this class is a Context class. This allows all the EMV 
classes to share data objects saved in the context.
*/

#ifndef EMV_CONTEXT_H
#define EMV_CONTEXT_H

#include "../Utility/utility.h"
#include "../Runtime/SystemControlImpl.h"
#include "../Runtime/HostControlImpl.h"
#include "emv_constants.h"
#include "Context.h"
#include "dol_parser.h"


// Errors:
#define EMV_CONTEXT_ALREADY_INITIALIZED 0xAA00000A
#define EMV_CONTEXT_IS_NOT_INITIALIZED  0xAA00000B
#define EMV_CONTEXT_INVALID_LOG_TYPE    0xAA00000C
#define ERR_CONTEXT_MSG_NOT_SUPPORTED      0xAA00000D
#define ERR_CONTEXT_LOG_NOT_SUPPORTED      0xAA00000E

// Data initialization constatnts
#define EMV_DATA_NOT_INITIALIZED 0x01
#define EMV_DATA_INITIALIZED     0x02
#define EMV_DATA_ERROR           0x03

// Context initialization constants
#define EMV_CONTEXT_NOT_INITIALIZED 0x04
#define EMV_CONTEXT_INITIALIZED     0x05
#define EMV_CONTEXT_ERROR           0x06


// Supported log types (a log type value is equivalent to the value 
//  of the tag where corresponding pathname is stored in TerminalInfo
//	section of the Registry
#define EMV_LOG_REVERSAL 0x50000007
#define DEFAULT_REVERSAL_LOG ".\\reversal.log"
#define EMV_LOG_DATA_BATCH 0x50000008
#define DEFAULT_DATA_BATCH_LOG ".\\data_batch.log"
#define EMV_LOG_AUTH_MSG 0x50000009
#define DEFAULT_AUTH_MSG_LOG ".\\auth_msg.log"

#define AUTH_RQST_TAG     0x4000000A
#define RESP_TAG          0x4000000C
#define REVERSAL_TAG      0x4000000D
#define FINANC_RQST_TAG   0x4000000E
#define ADVICE_TAG        0x4000000F
#define DATA_BATCH_TAG    0x40000010

#define BATCH_FIN_REC     0x01
#define BATCH_ADV_REC     0x02

class EMV_Context
{
public:
	EMV_Context(void);
	virtual ~EMV_Context(void);

	int initContext(AccessManager *pAM, int TransactionToken);
	void UninitContext();
	static int instanceCounter;
	int AddCurTime2Hash();

	// Initialization functions
	int initAmount(byte Amount[], byte CurrencyCode[]);
	int initAmountOther(byte Amount[]);
	int initTransactionType(byte Transaction);
	ServiceControl* GetService(int ServiceType);

	// Opens a file in the append-writeOnly mode.
	// Parameters: 
	//	 LogType - the type of the log file to be opened		
	//   fd - a pointer initialized to the file descriptior of the opened file
	// Returns: 
	//   - a file identifire to be used with the add2LogFile function,
	//   - -1 if there is error (see SystemControl.h file for possible errors)
	int openLogFile(int LogType, int *fd);

	// Appends a log entry to the file. The format of log entry is:
	// <Timestamp (mm/dd/yyyy hh:mm:ss)>: value
	// Parameters:
	//	fd - File descriptor. Mmust be obtained by previous call to 
	//		the openLogFile function.
	//  log_entry - a data string to be written to the log file.
	// Returns:
	//   SUCCESS - log entry is written successfully
	//   non-zero value - an error code causing the error
	int add2LogFile(int fd, const byte *log_entry, UNINT log_sz);
	int closeLogFile(int fd);
	const char *getDfltPath(int LogType);

protected:
	int initData(int tags[], DataObject *objects[], bool hashOnly[],
				 bool mandatory[], int size);
	int updateDataObject (int tag, DataObject *dob, 
		   			      byte updateByte, byte bit_mask, bool setBit = true);
	int updateDataObject (int tag, byte updateByte, byte bit_mask, 
						  bool setBit = true);
	int setDataObject(int tag, const byte* value, int value_len,
		              const char* format, int category);
	static bool IsOnlineTerminal();
	static bool IsOfflineTerminal();
	static bool IsMerchantTerminal();
	static bool IsFinancialTerminal();
	static bool IsCardholderTerminal();

	bool IsLogEnabled(int LogType);
	bool IsValidLogType(int LogType);
	int logDataRecord (int log_type, int msg_type, byte batch_type = 0);
	int logDataRecord (int log_type, const byte *log_data, UNINT log_sz);
	int getLog_RegKey(int msg_type);
	int getOnLineData (const byte *tags, int tags_len,
					   byte **onLineData, UNINT *data_len);
	int addStamp2LogFile(int fd);

	void OutputMsg(const char* msg);

	static int TransactionToken;
	// Initialization status
	byte InitStatus;
	int initError;
	static bool OnLineCompleted;
	static byte ReferralResponseCode;
	static int OnLineResult;
	static int ContextStatus;
	static int IssuerScriptSize;
	static bool ReversalNeeded;

protected:
	static Context EnvContext; // Put it in Protected section after debug
};

#endif
