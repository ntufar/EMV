// This class represents a single tlv-coded object.
// The object is parsed according to Basic Encoding Rules (BER) format
// specified by ASN.1 specification (TLV format).
// The class has methods to get all the properties of the TLV coded data object,
// such as tag value, class type, primitive/constucted type, length, value, etc.
// This class is part of Utility library of the SmartPOS project.
#ifndef TLV_H
#define TLV_H

#include "../Runtime/custom_types.h"
#include "../Runtime/errors.h"

#define CLASS_MASK        0xC0
#define UNIVERSAL_CLASS   0x00
#define APPLICATION_CLASS 0x40
#define CONTEXT_CLASS     0x80
#define PRIVATE_CLASS     0xC0

#define TYPE_MASK         0x20
#define PRIMITIVE_TYPE    0x00
#define CONSTRUCTED_TYPE  0x20

typedef struct DO_Element
{
	int  *pTags;
	byte *pLength;
	int num_elements;
} DOL_ELEMENT;

// ERRORS

#define TLV_INVALID_TAG_VALUE    0xfffe0002
#define TLV_INVALID_LENGTH_VALUE 0xfffe0003
#define TLV_NO_DATA              0xfffe0004

class tlv
{
public:
	tlv(void);
	virtual ~tlv(void);

public:
	//Accessors
	bool IsInitialized();
	bool IsUniversal();
	bool IsApplication();
	bool IsContext();
	bool IsPrivate();
	bool IsPrimitive();

	//Modifiers
	virtual int SetTlv(byte *bHeader, int len);
	virtual void ResetTlv ();
	
	byte GetClass();
	byte GetType();

	int GetTagIndx();
	int GetTagLen(); // Returns the length of the Tag field in bytes
	int GetTagVal(); // Gets the value of the tag as it is, not parsed
	int GetTagNum(); // Get only the tag value (excluding class and form bits)

	int GetLengthIndx();
	int GetLengthLen(); // Returns the length of the Length field in bytes
	int GetLengthVal(); // Returns a value contained in a Lenght field of TLV object. This value represents the size of the Value field in bytes.

	int GetValueIndx();
	byte *GetValue(); // Returns a pointer to a Value field of TLV object
	byte *CopyValue(); // Allocates a new buffer, and copies there the value of the TLV object (the buffer needs to be deallocated by a caller)

	byte *GetDataObject(); // Returns a pointer to the Data Object (including tag, length, value)
	byte *CopyDataObject(); // Allocates a new buffer and copies this Data Object into it (a buffer needs to be deallocated by a caller)
	int GetDataObjectLen(); // Returns the total length of the Data Object including length of the tag, length, and value

	// This function parses the byte array into a TLV object
	static int parseTag (const byte *header, int *tag_val, int *tag_len);

	static int findDataStartPoint (const byte *header, int len);
protected:
	// Members
	int tag_indx;
	int tag_len;
	int tag_val;

	int length_indx;
	int length_len;
	int length_val;

	int value_indx;

	byte *data_object;
	int do_len;
};

#endif
