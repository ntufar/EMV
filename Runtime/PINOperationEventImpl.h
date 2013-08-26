// PINControl Service
// Operation Event implementation.

#ifndef PINOPERATIONEVENTIMPL_H
#define PINOPERATIONEVENTIMPL_H

#include "PINOperationEvent.h"

class PINOperationEventImpl :
	public PINOperationEvent
{
public:
	PINOperationEventImpl(void);
	virtual ~PINOperationEventImpl(void);
	// Functions declared in the EventAdder class
protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

