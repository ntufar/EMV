/*
R_APDU.h
Encapsulates a response APDU header as a part of communication with ICC 
(T=0 protocol).
This is class derives from the APDU class.
The class is used to receive response from the ICC through the Terminal 
Transaction Layer. The header includes the status bytes SW1 and SW2 which 
indicate the ststus (or error) of executed command. 

Reference: EMV 4.0 book 1, ch 5.4; book 3 ch 2.1
*/
#ifndef R_APDU_H
#define R_APDU_H

#include "APDU.h"

class R_APDU: public APDU
{
public:
// Constructors - Destructors:
	R_APDU(void);
	virtual ~R_APDU(void);

//Members:
private:

// Accessors:
public:
	// Returns a Status Byte 1 (SW1)
	int getSW1(void);

	// Returns a second status byte (SW2)
	int getSW2(void);

	// Checks if arr is a valid apdu, and if it is, then it initializes apdu_info
	static int parseApdu (const byte *arr, int Len, int *apdu_type, 
					   apdu_struct *apdu_info);

// Modifiers:
public:
	virtual int setApdu (const byte *arr, int Len);
	int setApdu (const byte *arr, int Len, byte sw1, byte sw2);
};

#endif

