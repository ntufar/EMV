/*
C_APDU.h
Encapsulates a command APDU header as a part of communication with ICC 
(T=0 protocol).
This is class derives from the APDU class.
The class is used to build all 4 cases of the APDU headers. The header created 
by this class is sent to Terminal Transaction Layer

Reference: EMV 4.0 book 1, ch 5.4; book 3 ch 2.1
*/
#ifndef C_APDU_H
#define C_APDU_H

#include "APDU.h"

#define CLA_Indx   0
#define INS_Indx   1
#define P1_Indx    2
#define P2_Indx    3
#define Data_Indx  5

class C_APDU: public APDU
{
public:
// Constructors and destructors:
	C_APDU(void);
	virtual ~C_APDU(void);

// Members:
private:
	//----------------------------------------------------------

// Modifiers:
public:
	virtual int setApdu (const byte *arr, int Len);
	// Sets an APDU header based on the parameters passed. If parameter to be skipped, set most significant bit to 1
	int setApdu(byte cla, byte ins, byte p1, byte p2, int lc, 
					const byte* data, int le);

	// Sets an APDU class per specific APDU class
	int setApdu_class1(byte cla, byte ins, byte p1, byte p2);
	int setApdu_class2(byte cla, byte ins, byte p1, byte p2, byte le);
	int setApdu_class3(byte cla, byte ins, byte p1, byte p2, byte lc, 
		const byte *data);
	int setApdu_class4(byte cla, byte ins, byte p1, byte p2, byte lc, 
		const byte *data, byte le);

	// Update Instruction class of this object
	int updateCLA(byte cla);
	// Update Instruction code of this object
	int updateINS(byte ins);
	// Update P1 refernce parameter
	int updateP1(byte p1);
	// Update P2 parameter of this object
	int updateP2(byte p2);
	// Updates Data and Lc parameters of this APDU header
	virtual int updateData(const byte* data, byte lc);
	// Update Le parameter
	int updateLe(byte le);
private:
	virtual void resetApdu();
	static byte setApduClass(byte cls);
	static void setDefaults(apdu_struct *apdu_info);

// Accessors:
public:
	// Checks if arr is a valid apdu, and if it is, then it initializes apdu_info
	static int parseApdu (const byte *arr, int Len, int *apdu_type, 
					   apdu_struct *apdu_info);
	// Returns an instruction class of this APDU. The valus is located in the least significant byte. Returns a negative number in a case of error
	int getCLA(void);
	// Returns an instruction code of this APDU object
	int getINS(void);
	int getP1(void);
	int getP2(void);
	int getLc(void);
	int getLe(void);
};

#endif

