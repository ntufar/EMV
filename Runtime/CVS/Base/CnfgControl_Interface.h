// CnfgControl Service
// CnfgControl Interface Declaration -- Client Side.

#ifndef CNFGCONTROL_INTERFACE_H
#define CNFGCONTROL_INTERFACE_H

#include "ServiceControl.h"
#include "EventAdder_Interface.h"
#include "CnfgInterface.h"
#include "CnfgOperationEvent.h"

// Type definition of the pointer to the interface function.
// Is used when the function is exported from a DLL

typedef int (* GETVALUE)(UINT_KEY Key, 
						 const int iCategory, 
						 const char* Value_Name, 
						 const char* subKey = 0);

typedef int (* SETVALUELONG)(UINT_KEY Key, 
							 const int iCategory, 
							 const char* Value_Name, 
							 const long longValue, 
							 bool create, 
							 const char* subKey = 0);
typedef int (* SETVALUESTRING)(UINT_KEY Key, 
							   const int iCategory, 
							   const char* Value_Name, 
							   const char* stringValue, 
							   bool create, 
							   const char* subKey = 0);
typedef int (* SETVALUEBYTESTRING)(UINT_KEY Key, 
								   const int iCategory, 
								   const char* Value_Name, 
								   const byte* binaryValue, 
								   const int size, 
								   bool create, 
								   const char* subKey = 0);
typedef int (* DELETEVALUE)(UINT_KEY Key, 
							const int iCategory, 
							const char* Value_Name, 
							const char* subKey = 0);
typedef int (* CREATEVALUE)(UINT_KEY Key, 
							const int iCategory, 
							const char* Value_Name, 
							const int type, 
							const char* subKey = 0);
typedef int (* ENUMKEYS)(UINT_KEY Key, 
						 const int iCategory, 
						 const char* Key_Name, 
						 const char* subKey = 0);
typedef int (* ENUMVALUES)(UINT_KEY Key, 
						   const int iCategory, 
						   const char* Value_Name, 
						   const char* subKey = 0);
typedef int (* SETTRANSACTIONTYPE) (UINT_KEY Key, 
						   const char *TransType);

class CnfgControl_Interface :
	public ServiceControl, 
	public EventAdder_Interface, 
	public CnfgInterface
{
public:
	CnfgControl_Interface();
	CnfgControl_Interface (const char* path);
	virtual ~CnfgControl_Interface(void);
	virtual short getInterfaceType ();
};

#endif

