// This class implements the format of the public key as it defined by PKCS #1,
//  and detailed in ASN.1 and BER specifications.
// PKCS #1 defines a public key as RSAPublicKey SEQUENCE element:
// RSAPublicKey:: SEQUENCE 
//{
//		modulus INTEGER, //n
//      publicExponent INTEGER // e
//{
// SEQUENCE has a tag 0x30, following the size of the sequence, or the size
//  of the length (in bytes) of the size of the sequence (which is noted by the most
//  significant bit set to 1).
// INTEGER has a tag 0x02, following the size of the integer (in bytes), or the size 
//  of the length (in bytes) of the size of the integer

#ifndef RSAPUBLICKEY_H
#define RSAPUBLICKEY_H

#include "custom_types.h"

// Define some constatnts
#define SEQUENCE_TAG 0x30
#define INTEGER_TAG  0x02

// Define status and error codes
#define KEY_SUCCESS 0
#define KEY_BAD_ARGUMENT -1;
#define KEY_MEMORY_ALLOC_ERROR -2;
#define KEY_INVALID_FORMAT -3;


class RSAPublicKey
{
public:
	RSAPublicKey(void);
	RSAPublicKey(const byte *encodedKey, UNINT length);
	RSAPublicKey(const byte *modulus, UNINT mod_len,
				 const byte *exponent, UNINT exp_len);

	~RSAPublicKey(void);
	
	int setKey (const byte *encodedKey, UNINT length);
	int setKey (const byte *modulus, UNINT mod_len,
				const byte *exponent, UNINT exp_len);
	
	bool IsKeyInitialized();

	UNINT getKeyLength();
	UNINT getModulusBufferLength();
	UNINT getModulusLength();
	UNINT getExpLength();

	UNINT getKey(byte **key);
	UNINT getModulus(byte **modulus);
	UNINT getExponent(byte **exponent);

//private:
	byte *EncodedKey;
	UNINT KeyLen;

	byte *Modulus;
	UNINT ModLen;

	byte *Exponent;
	UNINT ExponentLen;

private:
	int parseValue(byte *pArr, UNINT length, UNINT *indx, int tag,
			   UNINT *ValLen, byte **Val);
	int codeLength (byte *pBt, int size, int bytesPerSize);
	int calcLengthField (const int ciSize);

	void MEMCPY (byte *dest, const byte *src, UNINT size);
// ***
public:
// ***
	void resetKey();
// ***
	static int counter;
// ***
};

#endif
