#include <stdio.h>
#include <string.h>
#include "UIOperationEvent.h"

UIOperationEvent::UIOperationEvent(void) : 
	valueType(0),
	stringValue(0),
	length (-1)
{
	intButton = -1;
	intIndex = -1;
	intData = -1;
}

UIOperationEvent::~UIOperationEvent(void)
{
}

void UIOperationEvent::resetEvent(bool withStop)
{
	releaseAllResources();
	OperationEvent::resetEvent(withStop);
}

void UIOperationEvent::releaseAllResources()
{
	if (stringValue)
	{
		releaseResource((void**)&stringValue);
		length = -1;
	}
}

// Sets the long value of the object
int UIOperationEvent::setButton(int iValue)
{
	intButton = iValue;
	set_value();
	return setSuccess();
}

int UIOperationEvent::setIndex(int iValue)
{
	intIndex = iValue;
	set_value();
	return setSuccess();
}

// Sets the long value of the object
int UIOperationEvent::setData(int iValue)
{
	intData = iValue;
	set_value();
	return setSuccess();
}

// Returns a long value stored in the object.
int UIOperationEvent::getButton(int* piValue)
{
	// Check if the value is set
	if (!IsValueSet())
		return ERR_OPEVNT__VALUE_IS_NOT_SET;

	if (!piValue)
		return ERR_BAD_ARGUMENT;

	*piValue = intButton;
	return SUCCESS;
}

// Returns a long value stored in the object.
int UIOperationEvent::getData(int* piValue)
{
	// Check if the value is set
	if (!IsValueSet())
		return ERR_OPEVNT__VALUE_IS_NOT_SET;

	if (!piValue)
		return ERR_BAD_ARGUMENT;

	*piValue = intData;
	return SUCCESS;
}
int UIOperationEvent::getIndex(int* piValue)
{
	// Check if the value is set
	if (!IsValueSet())
		return ERR_OPEVNT__VALUE_IS_NOT_SET;

	if (!piValue)
		return ERR_BAD_ARGUMENT;

	*piValue = intIndex;
	return SUCCESS;
}

// Sets a value of the object to string
int UIOperationEvent::setString(const char* pString)
{
	if (stringValue)
		releaseAllResources();
	stringValue = (char*) allocateResource (sizeof (char), (int)strlen(pString) + 1);
	if (!stringValue)
	{
		valueType = UI_STRING;
		return setError(ERR_MEMORY_ALLOC, SETTING_OPERATION_EVENT);
	}
	strcpy (stringValue, pString);
	length = (int)strlen(stringValue);
	set_value();
	return setSuccess();
}


// Returns a pointer to the string kontained in this object 
int UIOperationEvent::getString(char **string)
{
	// Check if the value is set
	if (!IsValueSet())
		return ERR_OPEVNT__VALUE_IS_NOT_SET;

	if (string == NULL)
		return ERR_BAD_ARGUMENT;

	*string = stringValue;
	return SUCCESS;
}

// Retreives the length of the string stored by this object
int UIOperationEvent::getLength(void)
{
	return length;
}
