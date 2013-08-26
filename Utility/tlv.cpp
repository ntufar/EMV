#include "tlv.h"
#include <memory.h>

tlv::tlv(void)
{
	tag_indx = 0;
	tag_len = 0;
	tag_val = 0;

	length_indx = 0;
	length_len = 0;
	length_val = 0;

	value_indx = 0;

	data_object = 0;
	do_len = 0;
}

tlv::~tlv(void)
{
	ResetTlv();
}

void tlv::ResetTlv ()
{
	tag_indx = 0;
	tag_len = 0;
	tag_val = 0;

	length_indx = 0;
	length_len = 0;
	length_val = 0;

	value_indx = 0;

	data_object = 0;
	do_len = 0;
}

bool tlv::IsInitialized()
{
	return (do_len > 0);
}

int tlv::SetTlv(byte *bHeader, int len)
{
	if (!bHeader || len <= 0)
		return ERR_BAD_ARGUMENT;

	ResetTlv();

	unsigned int curIndx = 0;
	int res;

	// Parse the tag
	if ((res = parseTag (bHeader, &tag_val, &tag_len)) != SUCCESS)
		return res;
	
	curIndx += tag_len; 
	tag_indx = 0;

	// Length parsing
	length_indx = curIndx;
	if (check_bit_key(bHeader[curIndx], 0x80, 0x80))
	{
		// The rest of the bits of the current byte represent a number of bytes
		//  of the length field. EMV spec limit the size of the length field to 
		//  a maximum of 3 bytes (1 byte designate a size of the length field in 
		//  bytes, and the following 1 or two bytes designate the length itself
		int lenFld = bHeader[curIndx] & 0x7f;
		if (lenFld > 2)
		{
			ResetTlv();
			return TLV_INVALID_LENGTH_VALUE;
		}
		length_val = 0;
		curIndx++;
		unsigned int i;
		for (i = curIndx; i < curIndx + lenFld; i++)
		{
			length_val <<= 8;
			length_val |= bHeader[i];
		}
		length_len = lenFld + 1;
		curIndx = i;
	}
	else
	{
		// The rest of the bits of the current byte contain the length of the value field
		length_val = bHeader[curIndx] & 0x7f;
		curIndx++;
		length_len = 1;
	}

	if (length_val != 0)
	{
		// Value Field
		value_indx = curIndx;
		//check the size of the inputa array and a parsed size
		if (curIndx + (unsigned int)length_val > (unsigned int)len)
		{
			ResetTlv();
			return TLV_INVALID_LENGTH_VALUE;
		}
	}

	data_object = bHeader;
	do_len = tag_len + length_len + length_val;
	
	return SUCCESS;
}

int tlv::parseTag (const byte *header, int *tag_val, int *tag_len)
{
	*tag_val = 0;
	*tag_len = 0;
	
	if (check_bit_key(header[0], 0x1F, 0x1F))
	{
		// The tag value is coded in subsequent byte
		*tag_val = header[0];
		*tag_val <<= 8;
		if (check_bit_key(header[1], 0x80, 0x80))
			return TLV_INVALID_TAG_VALUE;
		*tag_val |= (header[1] & 0x7F);
		*tag_len = 2;
	}
	else
	{
		*tag_val = header[0];
		*tag_len = 1;
	}
	return SUCCESS;
}


bool tlv::IsUniversal()
{
	if (IsInitialized())
		if (check_bit_key(data_object[tag_indx], CLASS_MASK, UNIVERSAL_CLASS))
			return true;
	return false;
}

bool tlv::IsApplication()
{
	if (IsInitialized())
		if (check_bit_key(data_object[tag_indx], CLASS_MASK, APPLICATION_CLASS))
			return true;
	return false;
}

bool tlv::IsContext()
{
	if (IsInitialized())
		if (check_bit_key(data_object[tag_indx], CLASS_MASK, CONTEXT_CLASS))
			return true;
	return false;
}

bool tlv::IsPrivate()
{
	if (IsInitialized())
		if (check_bit_key(data_object[tag_indx], CLASS_MASK, PRIVATE_CLASS))
			return true;
	return false;
}

bool tlv::IsPrimitive()
{
	if (IsInitialized())
		if (check_bit_key(data_object[tag_indx], TYPE_MASK, PRIMITIVE_TYPE))
			return true;
	return false;
}


byte tlv::GetClass()
{
	if (IsInitialized())
		return get_bit (data_object[tag_indx], CLASS_MASK);
	else return 0xFF;
}

byte tlv::GetType()
{
	if (IsInitialized())
		return get_bit (data_object[tag_indx], TYPE_MASK);
	else return 0xFF;
}


int tlv::GetTagIndx()
{
	return tag_indx;
}

int tlv::GetTagLen()
{
	return tag_len;
}

int tlv::GetTagVal()
{
	int tag = 0;
	for (int i = 0; i < tag_len; i++)
	{
		tag <<= 8;
		tag |= data_object[tag_indx + i];
	}
	return tag;
}

int tlv::GetTagNum()
{
	return tag_val;
}

int tlv::GetLengthIndx()
{
	return length_indx;
}

int tlv::GetLengthLen()
{
	return length_len;
}

int tlv::GetLengthVal()
{
	return length_val;
}


int tlv::GetValueIndx()
{
	return value_indx;
}


byte *tlv::GetValue()
{
	if (length_val == 0)
		return 0;
	else
		return data_object + value_indx;
}

byte *tlv::CopyValue()
{
	if (length_val == 0)
		return 0;
	else
	{
		byte *val = new byte [length_val];
		if (val)
			memcpy (val, data_object + value_indx, length_val);
		return val;
	}
}

byte *tlv::GetDataObject()
{
	return data_object;
}

byte *tlv::CopyDataObject()
{
	if (do_len <= 0)
		return 0;
	else
	{
		byte *val = new byte [do_len];
		if (val)
			memcpy (val, data_object, do_len);
		return val;
	}
}

int tlv::GetDataObjectLen()
{
	return do_len;
}

int tlv::findDataStartPoint (const byte *header, int len)
{
	if (len <= 0)
		return 0;

	int i = 0;
	if (header[0] == 0x00)
	{
		for (i = 0; i < len; i++)
		{
			if (header[i] != 0x00)
				break;
		}
	}
	else if (header[0] == 0xFF)
	{
		for (i = 0; i < len; i++)
		{
			if (header[i] != 0xFF)
				break;
		}
	}
	return i;
}
