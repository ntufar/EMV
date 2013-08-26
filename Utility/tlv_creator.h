// This class creates a TLV-coded value from Tag, Length, and Value fields passed to it
// in SetTlv function. This class derives from the tlv class.
// This class is part of Utility library of the SmartPOS project.

#ifndef TLV_CREATOR_H
#define TLV_CREATOR_H

#include "tlv.h"

class tlv_creator :
	public tlv
{
public:
	tlv_creator(void);
	virtual ~tlv_creator(void);
	
	virtual void ResetTlv ();
	// Create a TLV-coded value
	int SetTlv(int iTag, int iLen, byte *btData);
	// Returns a number of bytes required to code iVal
	static int GetNumberBytes (int iVal);
};

#endif

