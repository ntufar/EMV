#include "C_APDU.h"
#include <string.h>

C_APDU::C_APDU()
: APDU(APDU_TYPE_COMMAND)
{
}

C_APDU::~C_APDU(void)
{
	resetApdu();
}

void C_APDU::resetApdu()
{
	APDU::resetApdu();
}

// Parse and set APDU from a byte array
int C_APDU::setApdu (const byte *arr, int Len)
{
	resetApdu();
	int sz = 0;
	if (Len < 4)
		return APDU_INVALID_FORMAT;

	byte *tmp;
	
	tmp = new byte [Len];
	if (!tmp)
		return ERR_MEMORY_ALLOC;

	memcpy (tmp, arr, Len);
	
	
	if (Len == 4)
		apduType = setApduClass(APDU_TYPE_CLASS1); 
	else if (Len == 5)
	{
		apduIndexInfo.Le = 4;
		apduType = setApduClass(APDU_TYPE_CLASS2);
	}
	else
	{
		sz = (tmp [4] & 0x000000ff);
		if (sz + 5 == Len)
		{
			apduIndexInfo.Lc = 4;
			apduIndexInfo.Data = Data_Indx;
			apduType = setApduClass(APDU_TYPE_CLASS3);
		}
		else if (sz + 6 == Len)
		{
			apduIndexInfo.Lc = 4;
			apduIndexInfo.Data = Data_Indx;
			apduIndexInfo.Le = sz + Data_Indx;
			apduType = setApduClass(APDU_TYPE_CLASS4);
		}
		else
		{
			delete [] tmp;
			return APDU_INVALID_FORMAT;
		}
	}
	apduHeader = tmp;
	apduLen = Len;
	dataLen = sz;
	setDefaults (&apduIndexInfo);
	return SUCCESS;
}

// Parse APDU from a byte array
int C_APDU::parseApdu (const byte *arr, int Len, int *apdu_type, 
					   apdu_struct *apdu_info)
{
	// Initialize return parameters to -1
	*apdu_type = 0;
	resetIndxInfo(apdu_info);
	
	int sz = 0;
	if (Len < 4)
		return APDU_INVALID_FORMAT;	
	
	if (Len == 4)
		*apdu_type = setApduClass(APDU_TYPE_CLASS1); 
	else if (Len == 5)
	{
		*apdu_type = setApduClass(APDU_TYPE_CLASS2);
	}
	else
	{
		sz = (arr [4] & 0x000000ff);
		if (sz + 5 == Len)
		{
			apdu_info->Lc = 4;
			apdu_info->Data = Data_Indx;
			*apdu_type = setApduClass(APDU_TYPE_CLASS3);
		}
		else if (sz + 6 == Len)
		{
			apdu_info->Lc = 4;
			apdu_info->Data = Data_Indx;
			apdu_info->Le = sz + apdu_info->Data;
			*apdu_type = setApduClass(APDU_TYPE_CLASS4);
		}
		else
		{
			return APDU_INVALID_FORMAT;
		}
	}
	setDefaults (apdu_info);
	return SUCCESS;
}

// Sets an APDU header based on the parameters passed. 
//  If parameter lc or le are to be skipped, set them to a negative number.
//  To skip a data parameter, set it to 0. If lc is negative, data must set to 0.
//  If lc > 0, then data must point to a valid byte array of size lc.
int C_APDU::setApdu(byte cla, byte ins, byte p1, byte p2, int lc, 
					const byte* data, int le)
{
	if (lc < 0 && le < 0)
		return setApdu_class1(cla, ins, p1, p2);
	else if (lc < 0 && le >= 0)
		return setApdu_class2(cla, ins, p1, p2, (byte)le);
	else if (lc > 0 && data && le < 0)
		return setApdu_class3(cla, ins, p1, p2, (byte)lc, data);
	else if (lc > 0 && data && le >= 0)
		return setApdu_class4(cla, ins, p1, p2, (byte)lc, data, (byte)le);
	else
		return ERR_BAD_ARGUMENT;

	return SUCCESS;
}

int C_APDU::setApdu_class1(byte cla, byte ins, byte p1, byte p2)
{
	resetApdu();
	byte *tmp = new byte [4];
	if (!tmp)
		return ERR_MEMORY_ALLOC;
	tmp[CLA_Indx] = cla;
	tmp[INS_Indx] = ins;
	tmp[P1_Indx] = p1;
	tmp[P2_Indx] = p2;

	apduHeader = tmp;
	apduLen = 4;
	apduType = setApduClass(APDU_TYPE_CLASS1);
	setDefaults(&apduIndexInfo);
	return SUCCESS;
}

int C_APDU::setApdu_class2(byte cla, byte ins, byte p1, byte p2, byte le)
{
	resetApdu();
	byte *tmp = new byte [5];
	if (!tmp)
		return ERR_MEMORY_ALLOC;
	tmp[CLA_Indx] = cla;
	tmp[INS_Indx] = ins;
	tmp[P1_Indx] = p1;
	tmp[P2_Indx] = p2;
	tmp[4] = le;
	setDefaults(&apduIndexInfo);
	apduIndexInfo.Le = 4;

	apduHeader = tmp;
	apduLen = 5;
	apduType = setApduClass(APDU_TYPE_CLASS2);
	return SUCCESS;
}

int C_APDU::setApdu_class3(byte cla, byte ins, byte p1, byte p2, byte lc, 
						   const byte *data)
{
	resetApdu();
	int Len = (0x000000FF & lc);
	byte *tmp = new byte [5 + Len];
	if (!tmp)
		return ERR_MEMORY_ALLOC;
	tmp[CLA_Indx] = cla;
	tmp[INS_Indx] = ins;
	tmp[P1_Indx] = p1;
	tmp[P2_Indx] = p2;
	tmp[4] = lc;
	dataLen = Len;
	setDefaults(&apduIndexInfo);
	apduIndexInfo.Lc = 4;
	apduIndexInfo.Data = Data_Indx;
	
	memcpy (tmp + Data_Indx, data, dataLen);

	apduHeader = tmp;
	apduLen = dataLen + apduIndexInfo.Data;
	apduType = setApduClass(APDU_TYPE_CLASS3);
	return SUCCESS;
}

int C_APDU::setApdu_class4(byte cla, byte ins, byte p1, byte p2, byte lc, 
						   const byte *data, byte le)
{
	resetApdu();
	int Len = (0x000000FF & lc);
	byte *tmp = new byte [6 + Len];
	if (!tmp)
		return ERR_MEMORY_ALLOC;
	tmp[CLA_Indx] = cla;
	tmp[INS_Indx] = ins;
	tmp[P1_Indx] = p1;
	tmp[P2_Indx] = p2;
	tmp[4] = lc;
	dataLen = Len;
	setDefaults(&apduIndexInfo);
	apduIndexInfo.Lc = 4;
	apduIndexInfo.Data = Data_Indx;
	memcpy (tmp + apduIndexInfo.Data, data, dataLen);
	apduIndexInfo.Le = apduIndexInfo.Data + dataLen;
	tmp[apduIndexInfo.Le] = le;

	apduHeader = tmp;
	apduLen = dataLen + 6;
	apduType = setApduClass(APDU_TYPE_CLASS4);
	return SUCCESS;
}


void C_APDU::setDefaults(apdu_struct *apdu_info)
{
	apdu_info->CLA = CLA_Indx;
	apdu_info->INS = INS_Indx;
	apdu_info->P1 = P1_Indx;
	apdu_info->P2 = P2_Indx;
}

// Returns an instruction class of this APDU. The valus is located in the least significant byte. Returns a negative number in a case of error
int C_APDU::getCLA(void)
{
	return getApduItem (apduIndexInfo.CLA);
}

// Returns an instruction code of this APDU object
int C_APDU::getINS(void)
{
	return getApduItem (apduIndexInfo.INS);
}


int C_APDU::getP1(void)
{
	return getApduItem (apduIndexInfo.P1);
}

int C_APDU::getP2(void)
{
	return getApduItem (apduIndexInfo.P2);
}

int C_APDU::getLc(void)
{
	return getApduItem (apduIndexInfo.Lc);
}

int C_APDU::getLe(void)
{
	return getApduItem (apduIndexInfo.Le);
}

// Update Instruction class of this object
int C_APDU::updateCLA(byte cla)
{
	return updateByteVal (cla, apduIndexInfo.CLA);
}

int C_APDU::updateINS(byte ins)
{
	return updateByteVal (ins, apduIndexInfo.INS);
}

int C_APDU::updateP1(byte p1)
{
	return updateByteVal (p1, apduIndexInfo.P1);
}

int C_APDU::updateP2(byte p2)
{
	return updateByteVal (p2, apduIndexInfo.P2);
}

int C_APDU::updateData(const byte* data, byte lc)
{
	int res = APDU::updateData (data, lc);
	if (res == SUCCESS)
	{	
		apduHeader[apduIndexInfo.Lc] = dataLen;
		if (apduIndexInfo.Le != -1)
			apduIndexInfo.Le = apduIndexInfo.Data + dataLen;
	}
	return res;
	
}

int C_APDU::updateLe(byte le)
{
	return updateByteVal (le, apduIndexInfo.Le);
}

byte C_APDU::setApduClass(byte val)
{
	return (APDU_TYPE_COMMAND | val);
}
