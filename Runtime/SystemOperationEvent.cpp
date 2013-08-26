#include <string.h>
#include "SystemOperationEvent.h"

SystemOperationEvent::SystemOperationEvent(void)
{
	date.CC = 0;
	date.DD = 0;
	date.HH = 0;
	date.MM = 0;
	date.MN = 0;
	date.SS = 0;
	date.WD = 0;
	date.YY = 0;
}

SystemOperationEvent::~SystemOperationEvent(void)
{
}

DateStruct SystemOperationEvent::getDate(void)
{
	return date;
}

void SystemOperationEvent::setDate(const DateStruct &new_date)
{
	date.CC = new_date.CC;
	date.DD = new_date.DD;
	date.HH = new_date.HH;
	date.MM = new_date.MM;
	date.MN = new_date.MN;
	date.SS = new_date.SS;
	date.WD = new_date.WD;
	date.YY = new_date.YY;
	
	// This function should always go at the end of any function that successfully
	// sets the value
	set_value();
}

int SystemOperationEvent::setText(const byte *byteText, UNINT size)
{
	int res;
	if (size == 0)
	{
		res = this->setByteString (0, size);
	}
	else if (byteText[size - 1] == '\0')
	{
		res = this->setByteString (byteText, size);
	}
	else
	{
		res = this->setByteString (byteText, size + 1);
		if (res == SUCCESS)
			this->byteValue[size] = '\0';
	}
	return res;
}

int SystemOperationEvent::getText(char *buff, UNINT *buff_size)
{
	if (!IsValueSet() || valueType != OPEVENT_BINARY)
	{
		return ERR_OPEVNT__VALUE_IS_NOT_SET;
	}

	if (!buff)
		return ERR_BAD_ARGUMENT;

	if (this->length == 0)
	{
		*buff_size = 0;
		return SUCCESS;
	}

	int validStr;
	if (this->byteValue [this->length - 1] == '\0')
		validStr = 0;
	else
		validStr = 1;
	
	if ((int)*buff_size < this->length + validStr)
	{
		*buff_size = this->length + validStr;
		return ERR_BUFFER_OVERFLOW;
	}

	strncpy(buff, (char*)(this->byteValue), length + validStr);
	if (validStr == 1)
		buff[length] = '\0';
	*buff_size = length + validStr;
	return SUCCESS;
}
