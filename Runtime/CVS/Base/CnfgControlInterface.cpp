#include "CnfgControlInterface.h"

CnfgControlInterface::CnfgControlInterface():
	hDLL(NULL),
	_getValue(NULL),
	_setValueLong(NULL),
	_setValueString(NULL),
	_setValueByteString(NULL),
	_deleteValue(NULL),
	_createValue(NULL),
	_enumKeys(NULL),
	_enumValues(NULL),
	_setTransactionType(NULL)
{
}

CnfgControlInterface::CnfgControlInterface(const char *path):
	CnfgControl_Interface(path),
	hDLL(NULL),
	_getValue(NULL),
	_setValueLong(NULL),
	_setValueString(NULL),
	_setValueByteString(NULL),
	_deleteValue(NULL),
	_createValue(NULL),
	_enumKeys(NULL),
	_enumValues(NULL),
	_setTransactionType(NULL)
{
}

CnfgControlInterface::~CnfgControlInterface(void)
{
	closeService();
}


int CnfgControlInterface::openService(AccessManager* am)
{
}

void CnfgControlInterface::closeService(void)
{
}

unsigned int CnfgControlInterface::connectedServices ()
{
	if(!_connectedServices)
		return ERR_SERVICE_NOT_CONNECTED;
	
	return _connectedServices();
}


int CnfgControlInterface::getValue(const int iCategory, const char* Value_Name,
								   const char* subKey)
{
	if (!_getValue)
		return ERR_SERVICE_NOT_CONNECTED;

	return _getValue(Key, iCategory, Value_Name, subKey);
}
	
int CnfgControlInterface::setValueLong(const int iCategory, 
									   const char* Value_Name, 
									   const long longValue,
									   bool create,
									   const char* subKey)
{
	if (!_setValueLong)
		return ERR_SERVICE_NOT_CONNECTED;

	return _setValueLong (Key, iCategory, Value_Name, longValue, create, subKey);
}

int CnfgControlInterface::setValueString(const int iCategory, 
										 const char* Value_Name, 
                                         const char* stringValue,
										 bool create,
										 const char* subKey)
{
	if (!_setValueString)
		return ERR_SERVICE_NOT_CONNECTED;

	return _setValueString (Key, iCategory, Value_Name, stringValue, create, subKey);
}

int CnfgControlInterface::setValueByteString(const int iCategory,
											 const char* Value_Name, 
                                             const byte* binaryValue,
											 const int size,
											 bool create,
											 const char* subKey)
{
	if (!_setValueByteString)
		return ERR_SERVICE_NOT_CONNECTED;

	return _setValueByteString (Key, iCategory, Value_Name, binaryValue, size, 
		create, subKey);
}

int CnfgControlInterface::deleteValue(const int iCategory, 
									  const char* Value_Name,
									  const char* subKey)
{
	if (!_deleteValue)
		return ERR_SERVICE_NOT_CONNECTED;

	return _deleteValue (Key, iCategory, Value_Name, subKey);
}

int CnfgControlInterface::createValue(const int iCategory, 
									  const char* Value_Name, 
                                      const int type,
									  const char* subKey)
{
	if (!_createValue)
		return ERR_SERVICE_NOT_CONNECTED;

	return _createValue (Key, iCategory, Value_Name, type, subKey);
}

int CnfgControlInterface::enumKeys(const int iCategory, 
								   const char* Key_Name,
								   const char* subKey)
{
	if (!_enumKeys)
		return ERR_SERVICE_NOT_CONNECTED;

	return _enumKeys (Key, iCategory, Key_Name, subKey);
}

int CnfgControlInterface::enumValues(const int iCategory,
									 const char* Value_Name,
									 const char* subKey)
{
	if (!_enumValues)
		return ERR_SERVICE_NOT_CONNECTED;

	return _enumValues (Key, iCategory, Value_Name, subKey);
}

int CnfgControlInterface::setTransactionType(const char *TransType)
{
	if (!_setTransactionType)
		return ERR_SERVICE_NOT_CONNECTED;

	return _setTransactionType (Key, TransType);
}
