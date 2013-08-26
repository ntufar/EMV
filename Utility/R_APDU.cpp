#include "R_APDU.h"

R_APDU::R_APDU()
: APDU (APDU_TYPE_RESPONSE)
{
}

R_APDU::~R_APDU(void)
{
	APDU::resetApdu ();
}

// Returns a Status Byte 1 (SW1)
int R_APDU::getSW1(void)
{
	return getApduItem (apduIndexInfo.SW1);
}

// Returns a second status byte (SW2)
int R_APDU::getSW2(void)
{
	return getApduItem (apduIndexInfo.SW2);
}

int R_APDU::setApdu (const byte *arr, int Len)
{
	resetApdu();
	if (Len < 2)
		return APDU_INVALID_FORMAT;

	byte *tmp;
	
	tmp = new byte [Len];
	if (!tmp)
		return ERR_MEMORY_ALLOC;

	memcpy (tmp, arr, Len);
	

	if (Len == 2)
	{
		apduIndexInfo.SW1 = 0;
		apduIndexInfo.SW2 = 1;
	}
	else
	{
		apduIndexInfo.SW1 = Len - 2;
		apduIndexInfo.SW2 = Len - 1;
		apduIndexInfo.Data = 0;
	}
	apduHeader = tmp;
	apduLen = Len;
	dataLen = Len - 2;
	return SUCCESS;
}

int R_APDU::setApdu (const byte *arr, int Len, byte sw1, byte sw2)
{
	resetApdu();

	int size = 2;
	if (arr && Len > 0)
		size += Len;

	byte *tmp = new byte [size];
	if (!tmp)
		return ERR_MEMORY_ALLOC;
	if (arr && Len > 0)
	{
		memcpy (tmp, arr, Len);
		apduIndexInfo.Data = 0;
	}
	
	apduIndexInfo.SW1 = size - 2;
	apduIndexInfo.SW2 = size -1;
	tmp [apduIndexInfo.SW1] = sw1;
	tmp [apduIndexInfo.SW2] = sw2;
	
	apduHeader = tmp;
	apduLen = size;
	dataLen = size - 2;
	return SUCCESS;
}

// Parse APDU from a byte array
int R_APDU::parseApdu (const byte *arr, int Len, int *apdu_type, 
					   apdu_struct *apdu_info)
{
	// Initialize return parameters to -1
	*apdu_type = 0;
	resetIndxInfo(apdu_info);

	if (Len < 2)
		return APDU_INVALID_FORMAT;	

	if (Len == 2)
	{
		apdu_info->SW1 = 0;
		apdu_info->SW2 = 1;
	}
	else
	{
		apdu_info->SW1 = Len - 2;
		apdu_info->SW2 = Len - 1;
		apdu_info->Data = 0;
	}
	*apdu_type = APDU_TYPE_RESPONSE;
	return SUCCESS;
}
