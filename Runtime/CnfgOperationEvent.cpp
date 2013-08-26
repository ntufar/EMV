#include <string.h>
#include "CnfgOperationEvent.h"
#include <stdio.h>
CnfgOperationEvent::CnfgOperationEvent(void) : 
	stringArray(NULL)
{
}

CnfgOperationEvent::~CnfgOperationEvent(void)
{
}

int CnfgOperationEvent::setStringArray(char **pArray, int numElements, 
									   int maxLen)
{
	if (getValueType() != CNFG_ENUM_KEYS)
		releaseAllResources();
	valueType = CNFG_ENUM_KEYS;
	if (numElements <= 0 || pArray == NULL)
	{
		length = 0;
		stringArray = NULL;
		set_value();
		return setSuccess();
	}
	
	stringArray = (char**) allocateResource (sizeof (char*), numElements);
	if (!stringArray)
	{
		valueType = CNFG_NONE;
		length = -1;
		return setError(ERR_MEMORY_ALLOC, SETTING_OPERATION_EVENT);
	}

	for (int i = 0; i < numElements; i++)
	{
		stringArray[i] = (char*) allocateResource (sizeof (char), 
												(int)strlen(pArray[i]) + 1);
		if (!stringArray[i])
		{
			// Release previously allocated memory
			for (int j = i - 1; j >= 0; j--)
				releaseResource((void**)&stringArray[j]);
			releaseResource ((void**)&stringArray);
			stringArray = NULL;
			length = -1;
			valueType = CNFG_NONE;
			return setError(ERR_MEMORY_ALLOC, SETTING_OPERATION_EVENT);
		}
		strcpy (stringArray[i], pArray[i]);
	}
	length = numElements;
	set_value();
	return setSuccess();
}

int CnfgOperationEvent::getStringArray(char ***string)
{
	// Check if the value is set
	if (!IsValueSet())
		return ERR_OPEVNT__VALUE_IS_NOT_SET;

	if (getValueType() != CNFG_ENUM_KEYS)
		return ERR_UNEXPECTED_TYPE;

	if (string == NULL)
		return ERR_BAD_ARGUMENT;

	*string = stringArray;
	return SUCCESS;
}

void CnfgOperationEvent::releaseAllResources()
{
	if (stringArray)
	{
		if (length > 0)
		{
			for (int i = 0; i < length; i++)
				releaseResource((void**)&stringArray[i]);
			releaseResource((void**)(&stringArray));
		}
	}
	length = -1;
	stringArray = 0;
	OperationEventWithValue::releaseAllResources();
}
