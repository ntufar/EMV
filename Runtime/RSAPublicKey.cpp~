#include "RSAPublicKey.h"
#include <memory.h>

// Default constructor
RSAPublicKey::RSAPublicKey(void)
{
	EncodedKey = 0;
	KeyLen = 0;

	Modulus = 0;
	ModLen = 0;

	Exponent = 0;
	ExponentLen = 0;	
}

RSAPublicKey::RSAPublicKey(const byte *encodedKey, UNINT length)
{
	setKey (encodedKey, length);
}

RSAPublicKey::RSAPublicKey(const byte *modulus, UNINT mod_len,
				           const byte *exponent, UNINT exp_len)
{
	setKey (modulus, mod_len, exponent, exp_len);
}

RSAPublicKey::~RSAPublicKey(void)
{
	resetKey();
}

bool RSAPublicKey::IsKeyInitialized()
{
	return (EncodedKey)? true: false;
}

UNINT RSAPublicKey::getKeyLength()
{
	return KeyLen;
}

// Returns the lenght of the modulus excluding leading bytes which equal to 0
UNINT RSAPublicKey::getModulusLength()
{
	UNINT trueMod = ModLen;
	//Make sure leading bytes with '00' do not counted as a modulud length
	for (UNINT i = 0; i < ModLen; i++)
	{
		if (Modulus[i] != 0x00)
			return trueMod;
		trueMod--;
	}
	return trueMod;
}

// Returns the size of the buffer which keeps the value of modulus
UNINT RSAPublicKey::getModulusBufferLength()
{
	return ModLen;
}

UNINT RSAPublicKey::getExpLength()
{
	return ExponentLen;
}

UNINT RSAPublicKey::getKey(byte **key)
{
	*key = EncodedKey;
	return KeyLen;
}
UNINT RSAPublicKey::getModulus(byte **modulus)
{
	*modulus = Modulus;
	return ModLen;
}

UNINT RSAPublicKey::getExponent(byte **exponent)
{
	*exponent = Exponent;
	return ExponentLen;
}


void RSAPublicKey::resetKey()
{
	if (EncodedKey)
		delete [] EncodedKey;

	EncodedKey = 0;
	KeyLen = 0;

	Modulus = 0;
	ModLen = 0;

	Exponent = 0;
	ExponentLen = 0;
}

int RSAPublicKey::setKey (const byte *btKeyMod, const UNINT mSize,
		    const byte *btKeyExp, const UNINT eSize)
{
	if (!btKeyMod || !btKeyExp)
		return KEY_BAD_ARGUMENT;

	resetKey();

	int modSize;
	int expSize = eSize;
	int extraBt = 0;
	const int TagAndLength = 2; // Tag is one byte, and Length is at least one byte
	
	// Check for negative number
	// If it is negative, then we need to add a leading byte of 0x00
	((btKeyMod[0] & 0x80) == 0x80) ? modSize = mSize + 1: modSize = mSize;
	((btKeyExp[0] & 0x80) == 0x80) ? expSize = eSize + 1: expSize = eSize;
	
	// Find out how many bytes are needed to encode a value modSize
	int btsMod = calcLengthField (modSize);
	extraBt += btsMod;
	
	// Find out how many bytes are needed to encode a value expSize
	int btsExp = calcLengthField (expSize);
	extraBt += btsExp;

	// Calculate the size of a constucted element (n + e) of the SEQUENCE
	int constrSz = extraBt + TagAndLength + modSize + TagAndLength + expSize;
	
	// Now, find extra bytes required to code the size of the Constructed Value
	int btsCnst = calcLengthField (constrSz);
	extraBt = btsCnst;
	
	// Total size of the encoded key:
	int total = TagAndLength + constrSz + extraBt;

	// Allocate space for the encoded key array
	byte *pBt = new byte [total];
	if (!pBt)
		return KEY_MEMORY_ALLOC_ERROR;

	// Encode the key bytes
	int curIndx = 0;
	pBt[curIndx++] = SEQUENCE_TAG; // SEQUENCE{
	curIndx += codeLength (pBt + curIndx, constrSz, btsCnst);

	pBt[curIndx++] = INTEGER_TAG; // INTEGER, modulus
	curIndx += codeLength (pBt + curIndx, modSize, btsMod);
	
	if ((btKeyMod[0] & 0x80) == 0x80)
		pBt[curIndx++] = 0x00; // Add a leading '00' byte if the modulus has most significant bit '1'
	
	// Copy the modulus passed as a parameter to the encoded key array
	MEMCPY(pBt + curIndx, btKeyMod, mSize);
	Modulus = pBt + curIndx;
	ModLen = mSize;

	curIndx += mSize; // Move the current index up mSize bytes

	pBt[curIndx++] = 0x02; // INTEGER, exponent
	curIndx += codeLength (pBt + curIndx, expSize, btsExp);
	
	if ((btKeyExp[0] & 0x80) == 0x80)
		pBt[curIndx++] = 0x00; // Add leading '00' byte if the exponent has most significant bit '1'

	MEMCPY (pBt + curIndx, btKeyExp, eSize);
	Exponent = pBt + curIndx;
	ExponentLen = eSize;

	EncodedKey = pBt;
	KeyLen = total;
	return KEY_SUCCESS;
}

// Calculates the number of bytes needed to encode the value ciSize
int RSAPublicKey::calcLengthField (const int ciSize)
{
	int iBytes = 0;
	if (ciSize >= 128)
	{
		int mod = ciSize;
		for (; mod != 0; mod >>= 8, iBytes++);
	}
	return iBytes;
}

// Enode the length field of the tagged element according to 
//  Basic Encoding Rules (BER):
// if 0 <= length <= 127
//    length_in_bits:: 0XXX XXXX
// if length > 127
//	  length_in_bits:: 1LLL LLLL
// 
// where,
// XXX XXXX is a length of the element (e.g. an integer) that follows;
// LLL LLLL is number of bytes that needed to encode the value of the length.
// RETURNS: the number of bytes (bytes) that it took to encode the length
int RSAPublicKey::codeLength (byte *pBt, int size, int bytesPerSize)
{
	if (size <= 127)
	{	
		// a length is in a range from 0 to 127
		pBt[0] = size;
		return 1;
	}
	else
	{
		// a length is > 127
		pBt[0] = bytesPerSize | 0x80; // set a most significant bit to '1' to show that the rest of the bits in this bytes denotes the length of the lenght value 
		for (int i = 0; i < bytesPerSize; i++)
		{
			pBt[bytesPerSize - i] = size;
			size >>= 8;
		}
		return bytesPerSize + 1;
	}
}

int RSAPublicKey::setKey (const byte *encodedKey, UNINT length)
{
	UNINT offset = 0;
	// Check a sequence tag
	if (encodedKey[offset] != SEQUENCE_TAG)
		return KEY_INVALID_FORMAT;

	// Allocate a new space to hold the key
	EncodedKey = new byte [length];
	if (!EncodedKey)
		return KEY_MEMORY_ALLOC_ERROR;

	// copy key
	MEMCPY(EncodedKey, encodedKey, length);
	KeyLen = length;

	int res;
	UNINT seqSize;
	byte *val = 0;
	if ((res = parseValue(EncodedKey, length, &offset, SEQUENCE_TAG,
			   &seqSize, &val)) != KEY_SUCCESS)
	{
		resetKey();
		return res;
	}

	offset = 0;
	if ((res = parseValue(val, seqSize, &offset, INTEGER_TAG,
			   &ModLen, &Modulus)) != KEY_SUCCESS)
	{
		resetKey();
		return res;
	}
	
	if ((res = parseValue(val, seqSize, &offset, INTEGER_TAG,
			   &ExponentLen, &Exponent)) != KEY_SUCCESS)
	{
		resetKey();
		return res;
	}
	return KEY_SUCCESS;
}

int RSAPublicKey::parseValue(byte *pArr, UNINT length, UNINT *indx, int tag,
			   UNINT *ValLen, byte **Val)
{
	UNINT offset = *indx;
	if (pArr[offset++] != tag)
		return KEY_INVALID_FORMAT;

	if ((pArr[offset] & 0x80) == 0x80)
	{
		// Length is coded in the following (pArr[offset] & 0x7F) bytes
		UNINT len = (pArr[offset] & 0x7f);
		//Length is incoded in the next len bytes
		int size = 0;
		offset++;

		for (UNINT i = 0; i < len; i++)
		{
			size <<= 8;
			size |= (pArr[offset++] & 0x000000FF);
		}
		if (offset + size > length)
			return KEY_INVALID_FORMAT;
		*Val = pArr +offset;
		*ValLen = size;
		*indx = offset + size; 
	}
	else
	{
		// A length is coded in 7 least significant bits of the current octat
		int size = (pArr[offset] & 0x0000007f);
		if (offset + size + 1 > length)
			return KEY_INVALID_FORMAT;
		*Val = pArr + offset + 1;
		*ValLen = size;
		*indx = offset + size + 1;
	}

	return KEY_SUCCESS;
}

void RSAPublicKey::MEMCPY (byte *dest, const byte *src, UNINT size)
{
	for (UNINT i = 0; i < size; i++)
		dest[i] = src[i];
}
