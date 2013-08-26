#include "APDU.h"

APDU::APDU(byte apduType):
	apduHeader(0),
	apduLen(0),
	dataLen(0)
{
	this->apduType = apduType;
	resetIndxInfo (&apduIndexInfo);
}

APDU::~APDU(void)
{
	resetApdu();
}

void APDU::resetApdu()
{
	if (apduHeader)
		delete [] apduHeader;

	apduHeader = 0;
	apduLen = 0;
	dataLen = 0;
	apduType &= 0xf0;
	resetIndxInfo (&apduIndexInfo);
}

// returns tru if APDU header is initialized; false otherwise
bool APDU::IsHeader(void)
{
	return (apduHeader != 0);
}

int APDU::getApduItem (int indx)
{
	if (IsHeader() && indx >= 0 && indx <= apduLen)
		return (0x000000ff & apduHeader[indx]);
	else
		return -1;
}
int APDU::getApduType()
{
	return apduType;
}

const byte* APDU::getApdu(void)
{
	return apduHeader;
}

byte* APDU::copyApdu()
{
	if (apduHeader)
	{
		byte *cApdu = new byte [apduLen];
		if (!cApdu)
			return 0;
		memcpy(cApdu, apduHeader, apduLen);
		return cApdu;
	}
	else
		return 0;
}

const byte* APDU::getData()
{
	if (apduHeader && (dataLen > 0))
		return (apduHeader + apduIndexInfo.Data);
	else
		return 0;
}

byte* APDU::copyData()
{
	if (apduHeader && (dataLen > 0))
	{
		byte *cData = new byte [dataLen];
		if (!cData)
			return 0;
		memcpy(cData, apduHeader + apduIndexInfo.Data, dataLen);
		return cData;
	}
	else
		return 0;
}

int APDU::updateByteVal (byte Val, int indx)
{
	if (IsHeader())
	{
		if (indx < apduLen && indx >= 0)
		{
			apduHeader[indx] = Val;
			return SUCCESS;
		}
		else
			return ERR_BAD_ARGUMENT;
	}
	else
		return APDU_NOT_INITIALIZED;
}

int APDU::getApduLen()
{
	return apduLen;
}
int APDU::getDataLen()
{
	return dataLen;
}

int APDU::updateData(const byte* data, byte lc)
{
	if (!IsHeader())
		return APDU_NOT_INITIALIZED;

	if (lc <= 0)
		return ERR_BAD_ARGUMENT;

	if (dataLen == 0)
		return APDU_INCOMPATIBLE_CLASS;

	if (lc == dataLen)
	{
		memcpy (apduHeader + apduIndexInfo.Data, data, lc);
		return SUCCESS;
	}
	
	int new_size = apduLen - dataLen + lc;
	byte *tmp = new byte [new_size];
	memcpy (tmp + apduIndexInfo.Data, data, lc);
	
	if (apduIndexInfo.Data > 0)
		memcpy (tmp, apduHeader, apduIndexInfo.Data); // Copy data that preceeds Data in adpuHeader

	if (apduIndexInfo.Data + dataLen < apduLen)
		memcpy (tmp + apduIndexInfo.Data + lc, 
				apduHeader + apduIndexInfo.Data + dataLen, 
				apduLen - apduIndexInfo.Data - dataLen); // Copy data that follows Data in apduHeader

	delete [] apduHeader;
	apduHeader = tmp;
	apduLen = new_size;
	dataLen = lc;
	return SUCCESS;
}

void APDU::resetIndxInfo(apdu_struct *apdu)
{
	memset(apdu, -1, sizeof(apdu_struct));
}
