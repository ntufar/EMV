#ifndef OPERATIONEVENTWITHVALUE_H
#define OPERATIONEVENTWITHVALUE_H


#include "OperationEvent.h"

//Define Operation Event data types
#define OPEVENT_NONE     0 // No defined data type
#define OPEVENT_BINARY   1 // Binary data in any form
#define OPEVENT_LONG     2 // A 32-bit number
#define OPEVENT_STRING   3 // An array of null-terminated strings, terminated by two null characters

class OperationEventWithValue :
	public OperationEvent
{
public:
	OperationEventWithValue(void);
	virtual ~OperationEventWithValue(void);

	virtual void resetEvent(bool withStop = false);

protected:
	int valueType;
	long longValue;
	char *stringValue;
	byte *byteValue;
	int length;

public:
	// Retreives a data type of the value stored by this object
	int getValueType(void);

protected:
	// Releases a dynamically allocated resource.
	// This function needs to be implemented per every new environment.
	virtual void releaseResource(void **pBuffer) = 0;
	// Dynamically allocates resource.
	// This function needs to be implemented per every new environment.
	virtual void* allocateResource(int typeSize, int bufferSize) = 0;

	virtual void releaseAllResources ();

public:
	// Sets the value of the object to be long
	int setLong(long Value);
	// Returns a long value stored in the object.
	int getLong(long* Value);
	// Sets a value of the object to string
	int setString(const char* pString);
	// Returns a pointer to the string contained in this object 
	int getString(char **Value);
	// Sets a value of this object to a byte string
	int setByteString(const byte* pString, int size);
	// Retreives a byte string stored by this object
	int getByteString(byte** Value);

	// Retreives the length of the string stored by this object
	int getLength(void);
};

#endif

