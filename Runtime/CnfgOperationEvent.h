// CnfgControl service
// Defines the Operation Event interface to be used with CnfgControl.

#ifndef CNFGOPERATIONEVENT_H
#define CNFGOPERATIONEVENT_H

#include "OperationEventWithValue.h"
#include "custom_types.h"
#include "CnfgInterface.h"

class CnfgOperationEvent :
	public OperationEventWithValue
{
public:
	CnfgOperationEvent(void);
	virtual ~CnfgOperationEvent(void);

protected:
	char **stringArray;

public:
	// Sets a value of this object to double char Array
	int setStringArray(char **pArray, int numElements, 
									   int maxLen);
	// retreives a double char array saved in this object
	int getStringArray (char ***pArray);

	virtual void releaseAllResources ();
};

#endif

