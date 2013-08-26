// CnfgControl Service
// CnfgControl Interface Implementation -- Client Side.

#ifndef CNFGCONTROLINTERFACE_H
#define CNFGCONTROLINTERFACE_H

#include "CnfgControl_Interface.h"
#include "CnfgControlImpl.h"
#include "CnfgOperationEventImpl.h"
#include <stdio.h>
#include "patch.h"

class CnfgControlInterface :
	public CnfgControl_Interface,
	public CnfgControlImpl
{
public:
	CnfgControlInterface();
	CnfgControlInterface(const char* path);
	virtual ~CnfgControlInterface(void);

	virtual unsigned int connectedServices ();

	// Interface functions
	virtual int getValue(const int iCategory, const char* Value_Name,
		const char* subKey = NULL);
	
	virtual int setValueLong(const int iCategory, const char* Value_Name, 
		const long longValue, bool create, const char* subKey = 0);
	virtual int setValueString(const int iCategory, const char* Value_Name, 
		const char* stringValue, bool create, const char* subKey = 0);
	virtual int setValueByteString(const int iCategory, const char* Value_Name, 
		const byte* binaryValue, const int size, bool create, 
		const char* subKey = 0);
	virtual int deleteValue(const int iCategory, const char* Value_Name,
		const char* subKey = 0);
	virtual int createValue(const int iCategory, const char* Value_Name, 
		const int type, const char* subKey = 0);
	virtual int enumKeys(const int iCategory, const char* Key_Name,
		const char* subKey = 0);
	virtual int enumValues(const int iCategory, const char* Value_Name,
		const char* subKey = 0);
	virtual int setTransactionType (const char *TransType);
	

protected:
	virtual int openService(AccessManager* am);
	virtual void closeService(void);

private:
	HINSTANCE hDLL;               // Handle to DLL
	//Interface functions
	GETVALUE _getValue;
	SETVALUELONG _setValueLong;
	SETVALUESTRING _setValueString;
	SETVALUEBYTESTRING _setValueByteString;
	DELETEVALUE _deleteValue;
	CREATEVALUE _createValue;
    ENUMKEYS _enumKeys;
	ENUMVALUES _enumValues;
	SETTRANSACTIONTYPE _setTransactionType;

};

#endif

