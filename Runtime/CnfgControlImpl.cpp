#include <stdio.h>
#include <wintypes.h>
#include "CnfgControlImpl.h"
#include "AccessManager.h"
#include "properties.h"





CnfgControlImpl::CnfgControlImpl()
{
	TransactionType [0] = '\0';
	opEvent = new CnfgOperationEventImpl;
	if( loadPropertyFile("cakeys.txt") != 0 )
		loadProperties();
}

CnfgControlImpl::~CnfgControlImpl(void)
{
}



// Interface Method ***************************************************************
// Purpose: Retreives a data value from the Registry.
// Parameters:
//   iCategory - one of the following predifined categories:
//			CNFG_APPLICATION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\ApplicationInfo' key
//          CNFG_TERMINAL    - points to the 'HKLM\Software\SCS\SmartPOS\TerminalInfo' key
//          CNFG_RUNTIME     - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\Runtime' key
//          CNFG_TRANSACTION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\TransactionInfo' key
//          CNFG_CLC         - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\CLCModule' key
//          CNFG_CUSTOM      - points to the 'HKLM\<User_Defined_Key>' key
//
//   Value_Name - a null terminated character string containing a name of the value
//                to be read from the registry
//   subKey - a null terminated character string containing a subkey where the
//            value is located. iCategory is concatinated with a subKey. The subKey
//            must not have a trailing '\' character. The subKey can be NULL, or 
//            it can be omitted since it has a default value of NULL.
// Returns:
//    SUCCESS - if operation succeeds (use CnfgOperationEvent object to retreive
//				the actual value)
//    EVT_ERROR - if operation failed (use CnfgOperationEvent object to get more
//				details about the error.
// ***********************************************************************************
int CnfgControlImpl::getValue(const int iCategory, const char* Value_Name,
							  const char* subKey)
{
	DWORD dwType; // Keeps a datatype of the value returned from a registry
	LPBYTE lpData = NULL; // Keeps data returned from a registry
	DWORD dwSize; // Keeps the size in bytes of the data in lpData
	
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();

	// Cast the OperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a registry key where the targeted value is stored
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}


	// Read value from registry
	res = getValueFromRegistry (pKey, Value_Name, &lpData, &dwType, &dwSize, pEvent);
	if (res != SUCCESS)
	{
		delete [] pKey;
		return res;
	}
		
	res = packOperationEvent (lpData, dwSize, dwType, pEvent);
		
	// Release resources
	if (lpData)
		delete []lpData;
	delete []pKey;
	return res;
}


int CnfgControlImpl::getValueString(const int iCategory, const char* Value_Name,
							  const char* subKey)
{
	DWORD dwType; // Keeps a datatype of the value returned from a registry
	LPBYTE lpData = NULL; // Keeps data returned from a registry
	DWORD dwSize; // Keeps the size in bytes of the data in lpData
	
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();

	// Cast the OperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a registry key where the targeted value is stored
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}


	// Read value from registry
	res = getValueFromRegistryStr (pKey, Value_Name, &lpData, &dwType, &dwSize, pEvent);
	if (res != SUCCESS)
	{
		delete [] pKey;
		return res;
	}
		
	res = packOperationEvent (lpData, dwSize, dwType, pEvent);
		
	// Release resources
	if (lpData)
		delete []lpData;
	delete []pKey;
	return res;
}


// Interface Method ***************************************************************
// Purpose: sets a data value of type long (or integer) to the Registry.
// Parameters:
//   iCategory - one of the following predifined categories:
//			CNFG_APPLICATION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\ApplicationInfo' key
//          CNFG_TERMINAL    - points to the 'HKLM\Software\SCS\SmartPOS\TerminalInfo' key
//          CNFG_RUNTIME     - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\Runtime' key
//          CNFG_TRANSACTION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\TransactionInfo' key
//          CNFG_CLC         - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\CLCModule' key
//          CNFG_CUSTOM      - points to the 'HKLM\<User_Defined_Key>' key
//
//   Value_Name - a null terminated character string containing a name of the value
//                to be set to the registry
//   longValue - a value to be stored in the Registry under Value_Name
//   create - a flag controlling the creation of a new value in case if Value_Name
//            doesn't exist in a registry:
//			  true - value will be created
//            false - value will not be created
//   subKey - a null terminated character string containing a subkey where the
//            value is located. iCategory is concatinated with a subKey. The subKey
//            must not have a trailing '\' character. The subKey can be NULL, or 
//            it can be omitted since it has a default value of NULL.
// Returns:
//    SUCCESS - if operation succeeds 
//    EVT_ERROR - if operation failed (use CnfgOperationEvent object to get more
//				details about the error.
// ***********************************************************************************
int CnfgControlImpl::setValueLong(const int iCategory, const char* Value_Name, 
		const long longValue, bool create, const char* subKey)
{
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();

	// Cast theOperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a key to retreive the value
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}

	LPBYTE lpData; // Keeps data to be written to a registry
	DWORD dwSize;  // Keeps the size in bytes of the data in lpData
	DWORD dwType;  // Keeps a datatype of the value to be written to a registry

    res = setLongToByteArray (longValue,
		     				  &lpData, 
                              &dwSize, 
                              &dwType);
	if (res != SUCCESS)
	{
		delete [] pKey;
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}

	res = setValueToRegistry(pKey,  // A registry key where the value to be written is stored
							 Value_Name, // A Value name to be updated 
							 lpData,     // A data to be written to the Value_Name value
							 dwType,    
							 dwSize,   
							 pEvent,
							 create);
	delete [] pKey;
	delete [] lpData;
	return res;
}

int CnfgControlImpl::setValueString(const int iCategory, const char* Value_Name, 
		const char* stringValue, bool create, const char* subKey)
{
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();

	// Cast theOperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a key to retreive the value
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}

	LPBYTE lpData; // Keeps data to be written to a registry
	DWORD dwSize;  // Keeps the size in bytes of the data in lpData
	DWORD dwType;  // Keeps a datatype of the value to be written to a registry

    res = setStringToByteArray (stringValue,
		     				   &lpData, 
                               &dwSize, 
                               &dwType);
	if (res != SUCCESS)
	{
		delete [] pKey;
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}

	res = setValueToRegistry(pKey,  // A registry key where the value to be written is stored
							 Value_Name, // A Value name to be updated 
							 lpData,     // A data to be written to the Value_Name value
							 dwType,    
							 dwSize,   
							 pEvent,
							 create);
	delete [] pKey;
	delete [] lpData;
	return res;
}


// Interface Method ***************************************************************
// Purpose: sets a data value of type binary string to the Registry.
// Parameters:
//   iCategory - one of the following predifined categories:
//			CNFG_APPLICATION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\ApplicationInfo' key
//          CNFG_TERMINAL    - points to the 'HKLM\Software\SCS\SmartPOS\TerminalInfo' key
//          CNFG_RUNTIME     - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\Runtime' key
//          CNFG_TRANSACTION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\TransactionInfo' key
//          CNFG_CLC         - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\CLCModule' key
//          CNFG_CUSTOM      - points to the 'HKLM\<User_Defined_Key>' key
//
//   Value_Name - a null terminated character string containing a name of the value
//                to be set to the registry
//   binaryValue - a value to be stored in the Registry under Value_Name.
//				binaryValue is an array of type byte (unsigned char).
//   size - a size of a binaryValue is in bytes (binary data can be only written
//          to a registry in bytes increments).
//   create - a flag controlling the creation of a new value in case if Value_Name
//            doesn't exist in a registry:
//			  true - value will be created
//            false - value will not be created
//   subKey - a null terminated character string containing a subkey where the
//            value is located. iCategory is concatinated with a subKey. The subKey
//            must not have a trailing '\' character. The subKey can be NULL, or 
//            it can be omitted since it has a default value of NULL.
// Returns:
//    SUCCESS - if operation succeeds 
//    EVT_ERROR - if operation failed (use CnfgOperationEvent object to get more
//				details about the error.
// ***********************************************************************************
int CnfgControlImpl::setValueByteString(const int iCategory, const char* Value_Name, 
		const byte* binaryValue, const int size, bool create, const char* subKey)
{
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();

	// Cast theOperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a key to retreive the value
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}

	LPBYTE lpData; // Keeps data to be written to a registry
	DWORD dwSize;  // Keeps the size in bytes of the data in lpData
	DWORD dwType;  // Keeps a datatype of the value to be written to a registry

    res = setBinaryStrToByteArray (binaryValue,
								   size,
		     				       &lpData, 
                                   &dwSize, 
                                   &dwType);
	if (res != SUCCESS)
	{
		delete [] pKey;
		return pEvent->setError (res, RUNTIME_EXECUTION);
	}

	res = setValueToRegistry(pKey,  // A registry key where the value to be written is stored
							 Value_Name, // A Value name to be updated 
							 lpData,     // A data to be written to the Value_Name value
							 dwType,    
							 dwSize,   
							 pEvent,
							 create);
	delete [] pKey;
	delete [] lpData;
	return res;
}

// Interface Method ***************************************************************
// Purpose: removes a specified value from the Registry.
// Parameters:
//   iCategory - one of the following predifined categories:
//			CNFG_APPLICATION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\ApplicationInfo' key
//          CNFG_TERMINAL    - points to the 'HKLM\Software\SCS\SmartPOS\TerminalInfo' key
//          CNFG_RUNTIME     - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\Runtime' key
//          CNFG_TRANSACTION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\TransactionInfo' key
//          CNFG_CLC         - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\CLCModule' key
//          CNFG_CUSTOM      - points to the 'HKLM\<User_Defined_Key>' key
//
//   Value_Name - a null terminated character string containing a name of the value
//                to be deleted
//   subKey - a null terminated character string containing a subkey where the
//            value is located. iCategory is concatinated with a subKey. The subKey
//            must not have a trailing '\' character. The subKey can be NULL, or 
//            it can be omitted since it has a default value of NULL.
// Returns:
//    SUCCESS - if operation succeeds 
//    EVT_ERROR - if operation failed (use CnfgOperationEvent object to get more
//				details about the error.
// ***********************************************************************************
int CnfgControlImpl::deleteValue(const int iCategory, const char* Value_Name, 
								 const char* subKey)
{
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;

	opEvent->begin_operation();

	// Cast theOperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a key to retreive the value
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}

	res = deleteRegValue(pKey,  // A registry key where the value to be delited is stored
						 Value_Name, // A Value name to be deleted
						 pEvent
						 );
	delete [] pKey;
	return res;
}

// Interface Method ***************************************************************
// Purpose: creates a new value in the Registry.
// Parameters:
//   iCategory - one of the following predifined categories:
//			CNFG_APPLICATION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\ApplicationInfo' key
//          CNFG_TERMINAL    - points to the 'HKLM\Software\SCS\SmartPOS\TerminalInfo' key
//          CNFG_RUNTIME     - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\Runtime' key
//          CNFG_TRANSACTION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\TransactionInfo' key
//          CNFG_CLC         - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\CLCModule' key
//          CNFG_CUSTOM      - points to the 'HKLM\<User_Defined_Key>' key
//
//   Value_Name - a null terminated character string containing a name of the value
//                to be created
//   type - a type of the value to be created. Can be one of the following:
//			CNFG_DWORD - for storing up to 32-bit numbers
//          CNFG_SZ    - for storing null-terminated ASCII character strings
//          CNFG_BINARY - for storing byte arrays
//   subKey - a null terminated character string containing a subkey where the
//            value is located. iCategory is concatinated with a subKey. The subKey
//            must not have a trailing '\' character. The subKey can be NULL, or 
//            it can be omitted since it has a default value of NULL.
// Returns:
//    SUCCESS - if operation succeeds 
//    EVT_ERROR - if operation failed (use CnfgOperationEvent object to get more
//				details about the error.
// ***********************************************************************************
int CnfgControlImpl::createValue(const int iCategory, const char* Value_Name, 
		const int type, const char* subKey)
{
	switch (type)
	{
	case CNFG_DWORD:
		return setValueLong(iCategory, Value_Name, 0, true, subKey);
	case CNFG_SZ:
		return setValueString(iCategory, Value_Name, "", true, subKey);
	case CNFG_BINARY:
		return setValueByteString (iCategory, Value_Name, 
			(byte*)"\0", 1, true, subKey);
	default:
		long res = checkInitialization ();
		if (res != SUCCESS)
			return res;

		opEvent->begin_operation();

		// Cast theOperationEvent object to the appropriate type
		CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) this->opEvent;
		
		//Reset event
		return pEvent->setError(ERR_REG_UNRECOGNIZED_TYPE, RUNTIME_EXECUTION);
	}
}

// Interface Method ***************************************************************
// Purpose: Retreives a list of all subkeys names for a specified key.
// Parameters:
//   iCategory - one of the following predifined categories:
//			CNFG_APPLICATION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\ApplicationInfo' key
//          CNFG_TERMINAL    - points to the 'HKLM\Software\SCS\SmartPOS\TerminalInfo' key
//          CNFG_RUNTIME     - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\Runtime' key
//          CNFG_TRANSACTION - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\TransactionInfo' key
//          CNFG_CLC         - points to the 'HKLM\Software\SCS\SmartPOS\<ApplicationName>\CLCModule' key
//          CNFG_CUSTOM      - points to the 'HKLM\<User_Defined_Key>' key
//
//   Key_Name - a null terminated character string containing a name of the key for
//                which subkeys are to be searched
//   subKey - a null terminated character string containing a subkey where the
//            value is located. iCategory is concatinated with a subKey. The subKey
//            must not have a trailing '\' character. The subKey can be NULL, or 
//            it can be omitted since it has a default value of NULL.
// Returns:
//    SUCCESS - if operation succeeds (use CnfgOperation Event to retreive the 
//              actual data). 
//    EVT_ERROR - if operation failed (use CnfgOperationEvent object to get more
//				details about the error.
// ***********************************************************************************
int CnfgControlImpl::enumKeys(const int iCategory, const char* Key_Name, 
							  const char* subKey)
{
	long res = checkInitialization ();
	if (res != SUCCESS)
		return res;
	
//	if(Key_Name == NULL)
//		return 0;

	opEvent->begin_operation();

	// Cast theOperationEvent object to the appropriate type
	CnfgOperationEventImpl *pEvent = (CnfgOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();

	// Build a key
	/*
	char *pKey = buildKey(iCategory, subKey);
	if (!pKey)
	{
		return pEvent->setError (ERR_REG_INAVLID_KEY, RUNTIME_EXECUTION);
	}
	
	*/
	char *pKey = "";
	res = enumRegKeys(pKey,  
					  Key_Name, 
					  pEvent
					  );
	//delete [] pKey;
	
	return res;
}

int CnfgControlImpl::enumValues(const int iCategory, const char* Value_Name, 
								const char* subKey)
{
	return ERR_INTERFACE_NOT_IMPLEMENTED;
}


// *******************************************************************
//
// ***********  U T I L I T I E S   F U N C T I O N S    *************
//
// *******************************************************************

// BuildKey
// Purpose: Builds a string representing a registry key to be opened.
//      A registry key is based on the category ID passed to the function.
//      The following categories are currently supported:
//         CNFG_APPLICATION
//         CNFG_TERMINAL
//         CNFG_RUNTIME 
//         CNFG_TRANSACTION
//         CNFG_CLC
//         CNFG_CUSTOM
char* CnfgControlImpl::buildKey(int iCategory, const char* subKey)
{
	// Get a pointer to the AccessManager
	AccessManager *pAM = this->getAccessManager();
	char *str;
	char *str2;

	switch (iCategory)
	{
	case CNFG_APPLICATION:
		return buildString (APPLICATIONS_KEY, pAM->Application_Root, 
			APPLICATIONINFO, subKey);
	case CNFG_TERMINAL:
		return buildString (TEREMINAL_KEY, subKey);
	case CNFG_RUNTIME:
		return buildString (APPLICATIONS_KEY, pAM->Application_Root, 
			RUNTIME, subKey);
	case CNFG_TRANSACTION:
		if (TransactionType[0] == '\0')
			return buildString (TRANSACTIONINFO, subKey);
		else
		{
			str = buildString(TRANSACTIONINFO, TransactionType);
			str2 = buildString (str, subKey);
			delete [] str;
			return str2;
		}
	case CNFG_CLC:
		return buildString (APPLICATIONS_KEY, pAM->Application_Root, 
			CLCMODULE, subKey);
	case CNFG_POSAPPL:
		return buildString (APPLICATIONS_KEY, subKey);
	case CNFG_CUSTOM:
		return buildString (subKey);
	default:
		return NULL;
	}
}

// BuildString
// Purpose: Concatinates the strings specified by the parameters to this function.
//        The character '\' is inserted between concatinated strings.
//        The function concatinates strings up until the first NULL parameter.
//        The function dynamically allocates the space for a new string, therefore
//         the caller must deallocate the memory space allocated here.
char * CnfgControlImpl::buildString(const char* String1, 
									const char* String2,
									const char* String3,
									const char* String4,
									const char* String5) 
{
	if (!String1)
		return NULL;

	int size;
	int slashSz = (int)strlen(SLASH);
	char *pStr;
	size = (int)strlen (String1);
	if (String2)
	{
		size += ((int)strlen(String2) + slashSz);
		if (String3)
		{
			size += ((int)strlen(String3) + slashSz);
			if (String4)
			{
				size += ((int)strlen(String4) + slashSz);
				if (String5)
					size += ((int)strlen(String5) + slashSz);
			}
		}
	}
	
	pStr = new char [size + 1];

	if (!pStr)
		return NULL;
	
	strcpy (pStr, String1);
	if (String2)
	{
		strcat (pStr, SLASH);
		strcat (pStr, String2);
		if (String3)
		{
			strcat (pStr, SLASH);
			strcat (pStr, String3);
			if (String4)
			{
				strcat (pStr, SLASH);
				strcat (pStr, String4);	
				if (String5)
				{
					strcat (pStr, SLASH);
					strcat (pStr, String5);
				}
			}
		}
	}
	
	return pStr;
}


//getValueFromRegistry
// Purpose: Retreives a specified value from the registry. Data id returned in a form
//   of a BYTE array (parameter lpData). Also, the function returns data type
//   of the retreived data (dwType), and the size of the data (dwSize).
//   In a case of the error, the function sets the error code in 
//   CnfgOperationEventImpl object.
// Returns SUCCESS on the success and EVT_ERROR in a case of the error.
int CnfgControlImpl::getValueFromRegistry (const char *pKey, 
										   const char *Value_Name, 
										   LPBYTE *lpData, 
										   DWORD *dwType, 
										   DWORD *dwSize,
										   CnfgOperationEventImpl * pEvent)
{
	char buf[1024];
	char *pbuf = buf;

	*lpData = new BYTE [1024];
	getProperty(Value_Name, pbuf);
	*dwType = (DWORD)CNFG_BINARY;
	*dwSize = strlen(pbuf);
	strncpy((char*)*lpData, pbuf, *dwSize);
	
	return SUCCESS;
}



int CnfgControlImpl::getValueFromRegistryStr (const char *pKey, 
										   const char *Value_Name, 
										   LPBYTE *lpData, 
										   DWORD *dwType, 
										   DWORD *dwSize,
										   CnfgOperationEventImpl * pEvent)
{
	char buf[1024];
	char *pbuf = buf;

	*lpData = new BYTE [1024];
	getProperty(Value_Name, pbuf);
	*dwType = (DWORD)CNFG_SZ;
	*dwSize = strlen(pbuf);
	strncpy((char*)*lpData, pbuf, *dwSize + 1);
	
	return SUCCESS;
}


// setValueToRegistry
// Purpose: Sets the data (lpData) for the Registry value specified by Value_Name.
//    If specified value doesn't exist, and create flag is set to true, then the
//    Registry value will be created. Otherwise the function returns the error.
int CnfgControlImpl::setValueToRegistry (const char *pKey, 
										 const char *Value_Name, 
										 const LPBYTE lpData, 
										 DWORD dwType, 
										 DWORD dwSize,
										 CnfgOperationEventImpl *pEvent,
										 bool create)
{
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	HKEY hKey;
	long res;

	// Open the root registry key. In our case it is HKEY_LOCAL_MACHINE
	res = RegOpenKeyEx(
		ROOT,         // handle to open key
		pKey,         // subkey name
        0,            // reserved
        KEY_SET_VALUE | KEY_READ,     // security access mask
        &hKey          // handle to open key
		);
	if (res != ERROR_SUCCESS)
	{
		return pEvent->setError (ERR_REG_KEY_OPEN_FAILED, RUNTIME_EXECUTION);
	}

	if (!create)
	{
		if (!ValueExists(hKey, Value_Name, dwType))
		{	
			RegCloseKey(hKey);
			return pEvent->setError (ERR_REG_VALUE_NOT_FOUND, RUNTIME_EXECUTION);
		}
	}	

	// Set the value of a registry key
	res = RegSetValueEx(
		hKey,          // handle to key
		Value_Name,    // value name
        0,             // reserved
        dwType,        // value type
        lpData,        // value data
        dwSize         // size of value data
	);

	if (res != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return pEvent->setError (ERR_REG_VALUE_WRITE_FAILED, RUNTIME_EXECUTION);
	}

	RegCloseKey(hKey);
*/
	return pEvent->setSuccess();
}

// deleteRegValue
// Purpose: removes the specified value (Value_Name) from the registry.
int CnfgControlImpl::deleteRegValue(const char *pKey, const char *Value_Name,
									CnfgOperationEventImpl *pEvent)
{
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	HKEY hKey;
	long res;

	// Open the root registry key. In our case it is HKEY_LOCAL_MACHINE
	res = RegOpenKeyEx(
		ROOT,         // handle to open key
		pKey,         // subkey name
        0,            // reserved
        KEY_WRITE,    // security access mask
        &hKey         // handle to open key
		);
	if (res != ERROR_SUCCESS)
	{
		return pEvent->setError (ERR_REG_KEY_OPEN_FAILED,RUNTIME_EXECUTION);
	}
	res = RegDeleteValue(
						hKey,            // handle to key
					    Value_Name   // value name
						);
	if (res != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return pEvent->setError (ERR_REG_VALUE_DELETE_FAILED,RUNTIME_EXECUTION);
	}
	RegCloseKey(hKey);
*/
	return pEvent->setSuccess(); 
}

// packOperationEvent
// Purpose: Based on the data type (dwType) of the data, stores the data inside 
// the OperationEvent object.
int CnfgControlImpl::packOperationEvent (const LPBYTE lpData, 
										  DWORD dwSize, 
										  DWORD dwType, 
										  CnfgOperationEventImpl *pEvent)
{
	long lValue;
	// Set OperationEvent
	switch (dwType)
	{
/*	case REG_DWORD:
		lValue = 0;
		for (int i = dwSize-1; i >= 0, i < sizeof(long); i--)
		{
			lValue <<= 8;
			lValue = lValue | lpData[i];
		}
		return pEvent->setLong(lValue);
		break;
	case REG_DWORD_BIG_ENDIAN:
		lValue = 0;
		for (unsigned int i = 0; i < dwSize, i < sizeof(long); i++)
		{
			lValue <<= 8;
			lValue = lValue | lpData[i];
		}
		return pEvent->setLong(lValue);
		break;
	*/
	case CNFG_SZ:
		return pEvent->setString ((const char*) lpData);
		break;
	case CNFG_BINARY://REG_BINARY:
		return pEvent->setByteString (lpData, dwSize);
		break;
	default:
		return pEvent->setError (ERR_REG_UNRECOGNIZED_TYPE, RUNTIME_EXECUTION);
		break;
	}
}

// setLongToByteArray
// Purpose: Converts a long value (lValue) to a BYTE array of size 4 (The registry
//     stores long or int values in DWORD format, which has 32 bits (4 bytes)).
int CnfgControlImpl::setLongToByteArray (long lValue,
										  LPBYTE *lpData, 
										  DWORD *dwSize, 
									      DWORD *dwType)
{
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	BYTE *btArr = new BYTE [4];
	if (!btArr)
		return ERR_MEMORY_ALLOC;	

	*dwSize = 4;
	*dwType = REG_DWORD;

	for (unsigned int i = 0; i < *dwSize; i++)
	{
		btArr[i] = (BYTE)(lValue & 0x000000ff);
		lValue >>= 8;
	}
	*lpData = btArr;
*/
	return SUCCESS;
}
	

// checkInitialization
// Purpose: Checks if the OperationEvent object is added to the service, and if 
//   the application name is initialized. 
// Returns SUCCESS if everything is initialized.
long CnfgControlImpl::checkInitialization ()
{
	// Check if the OperationEvent has been added to this object
	if (!this->opEvent )
		return ERR_EVT_NO_EVNT_OBJECT;

	if (opEvent->operation_running())
		return ERR_OPEVNT__ALREADY_RUNNING;
	
	// Check if the Application Name has been added (call to the initialize() 
	// must be made before calling this function)
/*	
	if (!this->getAccessManager ())
	{
		return opEvent->setError (ERR_AM_NOT_INITIALIZED, RUNTIME_EXECUTION);
	}
*/	
	return SUCCESS;
}


// ValueExists
// Purpose: Checks if the value with the name specified by Value_Name exists in a registry
// under the key hKey. The type of the value in registry must be the same as
// the type specified by the parameter dwType.
// Returns TRUE if the value exists and FALSE otherwise.
bool CnfgControlImpl::ValueExists(HKEY hKey, const char *Value_Name, DWORD dwType)
{
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	// Check if the value exists
	DWORD type;
	DWORD size;
	long res = RegQueryValueEx(
		hKey,           // handle to key
		Value_Name,    // value name
		0,             // reserved
		&type,       // type buffer
		NULL,        // data buffer
        &size        // size of data buffer
	);
	if (res != ERROR_SUCCESS || type != dwType)
	{
		return false;
	}
*/
	return true;
}

// setStringToByteArray
// Purpose: Sets a null-terminated ASCII string to a BYTE array.
int CnfgControlImpl::setStringToByteArray (const char* stringValue,
		     				   LPBYTE *lpData, 
                               DWORD *dwSize, 
                               DWORD *dwType)
{
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	DWORD size = (DWORD)strlen (stringValue) + 1;
	BYTE *btArr = new BYTE [size];
	if (!btArr)
	{
		return ERR_MEMORY_ALLOC;	
	}
	strcpy ((char*)btArr, stringValue);
	*dwSize = size;
	*dwType = REG_SZ;
	*lpData = btArr;
	return SUCCESS;
*/
}

// setBinaryStrToByteArray
// Purpose: Sets a binary string (binaryValue) to a BYTE array (lpData).
//  Memory is allocated dynamically for lpData and must be released by a caller of
//  this function.
int CnfgControlImpl::setBinaryStrToByteArray (const byte *binaryValue,
										     int size,
		     							     LPBYTE *lpData, 
										     DWORD *dwSize, 
                                             DWORD *dwType)
{
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	BYTE *btArr = new BYTE [size];
	if (!btArr)
	{
		return ERR_MEMORY_ALLOC;	
	}
	memcpy (btArr, binaryValue, size);
	*dwSize = size;
	*dwType = REG_BINARY;
	*lpData = btArr;
	return SUCCESS;
*/
}


// enumRegKeys
// Purpose: Enumerates all subkeys of the registry key Key_Name.
//   This function also populates an OperationEvent object with the result.
int CnfgControlImpl::enumRegKeys(const char *pKey,  
			const char *Key_Name, 
		    CnfgOperationEventImpl *pEvent)
{
	long res;
	DWORD dwMaxSubKeyLen = 2048;

	char *subKey = 0;
	long count = 0;
	
    	PROPERTY *prev_ptr;

	if(Key_Name == NULL){
		return ERR_REG_INAVLID_KEY;
	}
												
	prev_ptr= node;						//bring to the top
    	while (prev_ptr != NULL) {			//while more elements in the list
							//found the property?
		if (strncmp(prev_ptr->property, Key_Name, strlen(Key_Name)) == 0)
			count++;
	        prev_ptr= prev_ptr->next;		//take me to the next node
    	}
	char **pKeyArr = new char* [count];
	count = 0;

	prev_ptr= node;						//bring to the top
    	while (prev_ptr != NULL) {			//while more elements in the list
							//found the property?
		if (strncmp(prev_ptr->property, Key_Name, strlen(Key_Name)) == 0){
			pKeyArr[count] = new char [dwMaxSubKeyLen + 1];
			strcpy(pKeyArr[count], prev_ptr->property);
			count++;
		}
	        prev_ptr= prev_ptr->next;		//take me to the next node
	}
	res = pEvent->setStringArray(pKeyArr, count, dwMaxSubKeyLen + 1);
	pEvent->setSuccess();
	
	for (unsigned int i = 0; i < count; i++)
		delete [] pKeyArr[i];
	delete [] pKeyArr;
	
	return SUCCESS;
}

int CnfgControlImpl::setTransactionType (const char *TransType)
{
	strncpy(TransactionType, TransType, 2);
	TransactionType[2] = '\0';
	return SUCCESS;
}




char fline[MAXDATASIZE];				//call me hog but I do real work

int propertyCount =0;					//property count

/*----------------------------------------------------------------------------
 * Entry point of the the utility application. 
 * Sequence of doing the operations should be:
   - Load the file
   - Load the properties from the file
   - work with the properties/property values 
   - cleanup the list at the end of the work.
 * IN >> None
 * OUT<< None
 */
/*
int main(int argc, char *argv[])
{
										//file name can include the path like e.g.
										//"c:/demo/properties/file.properties"
    char * filename="c:/demo/prop1/Debug/file.properties";	

    char searchValue[MAXVALUESIZE] = {""};

	loadPropertyFile(filename);			//open the pandora's box
	loadProperties();					//load the props from the file
	listProperties ();					//list all the properties ya got
										//get me the property count
	printf("\n\nProperty Count        : %d\n", getPropertyCount());
										//get me a property value
	getProperty("property2", &searchValue[0]);
	printf("\nValue for property2   : %s\n", searchValue);
										//get me a property value
	getProperty("myproperty2", &searchValue[0]);
	printf("\nValue for myproperty2   : %s\n", searchValue);

	cleanup ();							//please return my resources

}
*/

/*----------------------------------------------------------------------------
 * Loads the properties from the properties file
 * IN >> None
 * OUT<< None
 */
void loadProperties()
{
	char property[MAXPROPSIZE]={""};	//hog user memory		
	char value[MAXVALUESIZE]={""};		//hog more memory
	int index=-1;						//index for the delimiter
	int lineNumber=1;					//line count in properties file
										
										//read each line of text from prop file
    while(fgets(fline, MAXDATASIZE, fp) != NULL)
    {
	   if (ISDEBUG) printf("loadProperties() : fline = [%s]\n", fline);
										//does the delimiter exist in the line?		
	   index = searchString (DELIMITER, fline, 0);
	   if (ISDEBUG) printf("loadProperties() : index = [%d]\n", index);
	   if (index<=0) {					//no delimiter, move to next line
	       if (ISDEBUG) 
			   printf("loadProperties() : Unusable line %d\n",lineNumber);
		   continue;	
	   } else {							//found delimiter
										//get the property name
		 strncpy(property,&fline[0],index);
		 trim(property);				//remove leading and trailing spaces
										//next, get the property value
		 strncpy(&value[0],&fline[index + DELIMITERSIZE],(strlen(fline)-(index+DELIMITERSIZE)));
		 trim(value);					//remove leading and trailing spaces
	   }
       if (ISDEBUG) printf("loadProperties() : property = [%s]\n", property);
       if (ISDEBUG) printf("loadProperties() : value = [%s]\n", value);
	   addProperty(property, value);	//add the property to the list	
	   strncpy(property,"",index);		//clear the memory hog
	   strncpy(&value[0],"",(strlen(fline)-index));	
	   lineNumber++;					//increment line number count
    }
}

/*----------------------------------------------------------------------------
 * Loads the properties file
 * IN >> filename (Name of the properties file)
 * OUT<< None
 */
int loadPropertyFile( char * filename )
{
    if(fp != NULL)
    	return 0;			//Already opened
	
    if(!(fp = fopen(filename, "r"))) {	//try to open the file in read mode
        printf("Error: Could not open file: %s\n", filename);
        exit(1);						//unable to open the file
    }
    
    return 1;
}

/*----------------------------------------------------------------------------
 * Add the property read from the file to the internal data structure
 * IN >> property  (Property name) 
 * IN >> value     (Corresponding value of the property)
 * OUT<< None
 */
void addProperty (char* property, char* value) 
{
    PROPERTY *new_node;					//node handle
										//make room for daddy
    new_node= (PROPERTY *)malloc (sizeof (PROPERTY));
										//couldn't make room for daddy
    if (new_node == NULL) {				
        printf ("Out of memory!\n");	
        exit (-1);						//boom!	Get me outta here.
    }
	if (ISDEBUG) 
		printf ("\naddProperty(): Added new property: %s = %s", property,value);
										//set the property name in the node
	new_node->property = strdup(property);
	new_node->value=strdup(value);		//set the property value in the node

    new_node->next= node;				//my tail points to the node now
    node= new_node;						//set it up	
	propertyCount++;					//another one bites the dust
}    

/*----------------------------------------------------------------------------
 * Returns the count of properties currently loaded in the list
 * IN >> None
 * OUT<< int count (The count of properties currently present in memory)
 */
int getPropertyCount()
{
	return propertyCount;				//return the properties count so far
}

/*----------------------------------------------------------------------------
 * Cleans up the data structures created to read the properties
 * [DO NOT FORGET TO CLEANUP AT THE END OF THE APPLICATION TO AVOID
 *  EATING UP YOUR MEMORY]
 * IN >> None
 * OUT<< None
 */
void cleanup (void)
{
    PROPERTY *del_ptr;					//my pointer	
    while (node != NULL) {				//while im still going
       del_ptr= node;					//bring me to the head
       node= node->next;				//point to the next node
       free(del_ptr);					//free the node
    }
	if (ISDEBUG) 
		printf ("\n\ncleanup(): Done freeing up memory from the list. \n");
}

/*----------------------------------------------------------------------------
 * Get the value of a property (from the list) 
 * IN >> property  (Property name) 
 * OUT>> value     (Returns value of the corresponding property)
 */
void getProperty (const char* property, char* value)
{
    PROPERTY *prev_ptr;					//can't do without me	
											
    if (node == NULL) {					//No properties have been loaded
        if (ISDEBUG) 
			printf ("No properties have been loaded yet.\n");
        return;
    }
											
    prev_ptr= node;						//bring to the top
    while (prev_ptr != NULL) {			//while more elements in the list
										//found the property?
		if (strcmp(prev_ptr->property, property) == 0) {
			if (ISDEBUG) 
				printf ("getProperty(): value = %s \n",prev_ptr->value);
										//get the value for the property then
			strcpy(value,prev_ptr->value);
			if (ISDEBUG) 
				printf ("getProperty(): Property %s = %s \n",property,value);
            return;
        }									
        prev_ptr= prev_ptr->next;		//take me to the next node
    }
    if (ISDEBUG) 
		printf ("\nProperty [%s] not found.\n", property);
}

/*----------------------------------------------------------------------------
 * Displays the properties read from the properties file (debug function)
 * IN >> None
 * OUT<< None
 */
void listProperties (void)
{
    PROPERTY *tmp_ptr;					//can't do without me	
    if (ISDEBUG) printf ("\nAll properties in property file:");
    tmp_ptr= node;						//bring me to the head
    while (tmp_ptr != NULL) {			//while not reached my tail
										//print property, value
		printf ("\n%s : %s ",tmp_ptr->property, tmp_ptr->value);
        tmp_ptr= tmp_ptr->next;			//move me to the next node
    }
}

/*----------------------------------------------------------------------------
 * Cleans up the data structures created to read the properties
 * IN >> search    (The string that is to be searched)
 * IN >> string    (The source string)
 * IN >> offset    (Offset on where to begin the search in 'string')
 * OUT<< int index (Index on where 'search' was found in 'string')
 */
int searchString (const char *search, const char *string, int offset)
{
    int stlen=strlen(string);			//source string length
    int srlen=strlen(search);			//search string length
    int counter=0;						//Main string counter
    int sublcv=0;						//Search String counter
    int start=-1;						//Substring index indicator

    if(srlen>stlen) {
        return(-2);						//Think daddy is a fool?
    }
										//step through the string
    for(counter=offset;counter<=(stlen-srlen); counter++) {
										//found, then move ahead!
        if(string[counter]==search[sublcv]) {
            while(sublcv<=srlen)  {		//string comparison
										//do the characters correspond
                if(search[sublcv]==string[sublcv+counter]) {
                    sublcv++;			//check next if correct
                } else {
                    sublcv=srlen+1;		//over step the counter
                }
                if(sublcv==srlen)  {	//all of the string was searche through
                    start=counter;		//current counter is start pos of substr
										//end the loop
                    counter=(stlen-srlen)+1; 
                }
            }
        }
        sublcv=0;						//reset sub lcv;
    }
    return(start);						//index of substring, -1 not found
}

/*----------------------------------------------------------------------------
 * Get the value of a property (from the list) 
 * IN >> daddy	   (String to be trimmed) 
 * OUT>> char *    (Trimmed input string)
 */
static char *trim( char *daddy)
{
	char *input, *output;
	if (daddy) {						//if daddy exists
		for (input = output = daddy; *input; ) {
										//trim the leading spaces first
			while (*input && (isspace (*input)))
				input++;				//next char
			if (*input && (output != daddy))
				*(output++) = ' ';		
										//trim the trailing spaces
			while (*input && (!isspace (*input)))
				*(output++) = *(input++);
		}								//give me an end point or im lost
			*output=0;
	}
	return (daddy);
}
/*==========================================================================*/





































/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************* JUNKYARD  ************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/


/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	DWORD size = (DWORD)strlen (stringValue) + 1;
	HKEY hKey;
	long res;

	char *subKey = 0;
	if (pKey)
	{
		if (Key_Name)
			subKey = buildString(pKey, Key_Name);
		else
			subKey = buildString(pKey);
	}
	if (!subKey)
		return ERR_REG_VALUE_NOT_FOUND;

	// Open the root registry key. In our case it is HKEY_LOCAL_MACHINE
	res = RegOpenKeyEx(
		ROOT,         // handle to open key
		subKey,         // subkey name
        0,            // reserved
        KEY_READ,     // security access mask
        &hKey          // handle to open key
		);

	delete [] subKey;

	if (res != ERROR_SUCCESS)
	{
		return pEvent->setError(ERR_REG_KEY_OPEN_FAILED, RUNTIME_EXECUTION);
	}

	//Get Registry Key information
	DWORD dwSubKeys;
	DWORD dwMaxSubKeyLen;        // longest subkey name
    DWORD dwValues;              // number of value entries
    DWORD dwMaxValueNameLen;     // longest value name
    DWORD dwMaxValueLen;         // longest value data

	res = RegQueryInfoKey(
				hKey,             // handle to key
                NULL,             // class buffer (currently not defined by API)
				NULL,             // size of class buffer
                NULL,             // reserved
				&dwSubKeys,       // number of subkeys
                &dwMaxSubKeyLen,        // longest subkey name
                NULL,                   // longest class string
                &dwValues,              // number of value entries
                &dwMaxValueNameLen,     // longest value name
                &dwMaxValueLen,         // longest value data
                NULL, // descriptor length
                NULL     // last write time
				);
	if (res != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return pEvent->setError(ERR_REG_QUERY_KEY_INFO, RUNTIME_EXECUTION);
	}
	if (dwSubKeys <= 0)
	{
		RegCloseKey(hKey);
		pEvent->setStringArray(NULL, 0, 0);
		pEvent->setSuccess();
	}

	// Allocate the space to hold the key names

	char **pKeyArr = new char* [dwSubKeys];
	if (!pKeyArr)
	{
		RegCloseKey(hKey);
		return pEvent->setError(ERR_MEMORY_ALLOC, RUNTIME_EXECUTION);
	}

	for (unsigned int i = 0; i < dwSubKeys; i++)
	{
		pKeyArr[i] = new char [dwMaxSubKeyLen + 1];
		if (!pKeyArr[i])
		{
			for (int j = i - 1; j >= 0; j--)
				delete [] pKeyArr[j];
			delete [] pKeyArr;
			RegCloseKey(hKey);
			return pEvent->setError(ERR_MEMORY_ALLOC, RUNTIME_EXECUTION);
		}
	}

	DWORD dwSize;
	FILETIME LastWriteTime;
	i = 0;
	for (int j = dwSubKeys; j > 0; j--)
	{
		dwSize = dwMaxSubKeyLen + 1;
		res = RegEnumKeyEx(
				hKey,           // handle to key to enumerate
				i,              // subkey index
                pKeyArr[i],     // subkey name
                &dwSize,        // size of subkey buffer
				NULL,           // reserved
				NULL,           // class string buffer
                NULL,           // size of class string buffer
                &LastWriteTime  // last write time
				);

		if (res == ERROR_SUCCESS)
		{
			i++;
		}
		else if (res == ERROR_NO_MORE_ITEMS)
			break;
	}
	res = pEvent->setStringArray(pKeyArr, i, dwMaxSubKeyLen + 1);
	
	RegCloseKey(hKey);
	
	for (unsigned int i = 0; i < dwSubKeys; i++)
		delete [] pKeyArr[i];
	delete [] pKeyArr;
	return res;
*/
