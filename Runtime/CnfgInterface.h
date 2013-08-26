// CnfgControl Service
// CnfgControl Interface Declaration.
// Used to obtain/store Application specific and Terminal data from/to 
// the terminal.

#ifndef CNFGINTERFACE_H
#define CNFGINTERFACE_H

#include "custom_types.h"
#include "ServiceInterface.h"

//Define data types
#define CNFG_NONE     0 // No defined data type
#define CNFG_BINARY   1 // Binary data in any form
#define CNFG_DWORD    2 // A 32-bit number
#define CNFG_SZ       3 // A null-terminated string
#define CNFG_MULTI_SZ 4 // An array of null-terminated strings, terminated by two null characters
#define CNFG_ENUM_KEYS 5 // Double array that keeps a list of key names

//Define data categories
#define CNFG_APPLICATION 1
#define CNFG_TERMINAL    2
#define CNFG_RUNTIME     3
#define CNFG_TRANSACTION 4
#define CNFG_CLC         5
#define CNFG_SERVICE     6
#define CNFG_POSAPPL     7

#define CNFG_CUSTOM      99

//Errors
#define ERR_REG_INAVLID_KEY         0x8D000001
#define ERR_REG_UNRECOGNIZED_TYPE   0x8D000002
#define ERR_REG_KEY_OPEN_FAILED     0x8D000003
#define ERR_REG_VALUE_READ_FAILED   0x8D000004
#define ERR_REG_VALUE_NOT_FOUND     0x8D000005
#define ERR_REG_VALUE_WRITE_FAILED  0x8D000006
#define ERR_REG_VALUE_DELETE_FAILED 0x8D000007
#define ERR_REG_QUERY_KEY_INFO      0x8D000008

class CnfgInterface : public ServiceInterface
{
public:
	CnfgInterface();
	virtual ~CnfgInterface(void);
	// Returns a value from a configuration store
	//virtual int initialize(const char* appName) = 0;
	virtual int getValue(const int iCategory, const char* Value_Name, 
		const char* subKey = 0) = 0;
	
	virtual int setValueLong(const int iCategory, const char* Value_Name, 
		const long longValue, bool create, const char* subKey = 0) = 0;
	virtual int setValueString(const int iCategory, const char* Value_Name, 
		const char* stringValue, bool create, const char* subKey = 0) = 0;
	virtual int setValueByteString(const int iCategory, const char* Value_Name, 
		const byte* binaryValue, const int size, bool create, 
		const char* subKey = 0) = 0;

	virtual int deleteValue(const int iCategory, const char* Value_Name,
		const char* subKey = 0) = 0;

	virtual int createValue(const int iCategory, const char* Value_Name, 
		const int type, const char* subKey = 0) = 0;

	virtual int enumKeys(const int iCategory, const char* Key_Name, 
		const char* subKey = 0) = 0;
	virtual int enumValues(const int iCategory, const char* Value_Name, 
		const char* subKey = 0) = 0;

	virtual int setTransactionType (const char *TransType) = 0;
};

#endif

