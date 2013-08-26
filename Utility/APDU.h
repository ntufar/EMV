/*
APDU.h
Encapsulates an APDU header of Application Layer protocol as a part of communi-
cation with the ICC. this header is sent to Terminal Transport Layer.
This is a base class for command APDU (C_APDU) and response APDU (R_APDU)
classes.

Reference: EMV 4.0 book 1, ch 5.4; book 3 ch 2.1
*/
#ifndef APDU_H
#define APDU_H

#include <memory>

#include "../Runtime/custom_types.h"
#include "../Runtime/errors.h"

#define APDU_NOT_INITIALIZED    0xffff0001
#define APDU_INCOMPATIBLE_CLASS 0xffff0002
#define APDU_INVALID_FORMAT     0xffff0003

#define APDU_TYPE_COMMAND  0x10
#define APDU_TYPE_RESPONSE 0x20
#define APDU_TYPE_CLASS1   0x01
#define APDU_TYPE_CLASS2   0x02
#define APDU_TYPE_CLASS3   0x03
#define APDU_TYPE_CLASS4   0x04

typedef struct
{
	int CLA; // Index to Class of instruction;
	int INS; // Index to Instruction code
	int P1;  // Index to Instruction parameter 1
	int P2;  // Index to Instruction parameter 2
	int Data;      // Index to Data
	int Lc;        // Index to a Number of bytes present in command data field
	int Le;        // Index to a Maximum number of data bytes expected in data field of response
	int SW1;       // Index to a status byte 1 (valid only in a response header)
	int SW2;       // Index to a status byte 2 (valid only in a response header)
} apdu_struct;


class APDU
{
public:
	APDU(byte apduType);
	virtual ~APDU(void);

// Accessors:
	const byte* getApdu();
	const byte* getData();
	byte* copyApdu();
	byte* copyData();
	int getApduLen();
	int getApduType ();
	int getDataLen();
	// returns true if APDU header is initialized; false otherwise
	bool IsHeader(void);
protected:
	int getApduItem (int indx);

// Modifiers:
public:
	virtual int setApdu (const byte *arr, int Len) = 0;
	
protected:
	virtual void resetApdu();
	virtual int updateData(const byte* data, byte lc);
	int updateByteVal (byte Val, int indx);
	static void resetIndxInfo(apdu_struct *apdu);

// Members:
protected:
	byte *apduHeader;
	// Header Structure
	apdu_struct apduIndexInfo;

	// A number of elements in apduHeader array
	int apduLen;
	// String of data bytes sent in command
	int dataLen;
	int apduType;
};

#endif
