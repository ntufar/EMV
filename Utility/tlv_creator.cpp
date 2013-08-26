#include "tlv_creator.h"
#include <memory>

tlv_creator::tlv_creator(void)
{
}

tlv_creator::~tlv_creator(void)
{
	ResetTlv();
}

void tlv_creator::ResetTlv ()
{
	if (data_object)
		delete data_object;
	tlv::ResetTlv ();
}

int tlv_creator::SetTlv(int iTag, int iLen, byte *btData)
{
	// Release allocated resources in case they were allocated
	ResetTlv();

	// Find a total length of the array to be allocated
	int len_total = 1;
	byte tag1 = (byte)(iTag>>8);
	byte tag2 = (byte)iTag;

	if (check_bit_key(tag1, 0x1f, 0x1f))
		len_total++; // Need an extra byte to keep a second byte of the Tag

	len_total++; // at least one byte is needed to keep the length field

	int size = 0;
	if (iLen >= 128)
	{
		size = GetNumberBytes (iLen);
		len_total += size;
	}

	// Add the data length
	len_total += iLen;

	//allocate space for a new array
	byte *bArr = new byte [len_total];
	if (!bArr)
		return ERR_MEMORY_ALLOC;

	// Initialize Tag
	int curIndx = 0;
	if (check_bit_key(tag1, 0x1f, 0x1f))
		bArr[curIndx++] = tag1;
	bArr[curIndx++] = tag2;

	// Initialize length
	if (size == 0)
		bArr[curIndx++] = (0x7f & iLen);
	else
	{
		bArr[curIndx++] = (0x80 | size);
		int tmp_len = iLen;
		for (int i = size; i > 0; i--)
		{
			bArr[curIndx + i - 1] = (byte)tmp_len;
			tmp_len >>= 8;
		}
		curIndx += size;
	}
	
	// Add Data
	if (btData && iLen > 0)
		memcpy(bArr+curIndx,btData, iLen);

	return tlv::SetTlv (bArr, len_total);
}

// Calculate how many bytes are necessary to keep an integer value
int tlv_creator::GetNumberBytes (int iVal)
{
	int size = sizeof(int);
	for (int i = 8 *(size - 1); i > 0; i -=8)
	{
		byte tmp = (byte)(iVal >> i);
		if (tmp != 0)
			break;
		size--;
	}
	return size;
}
