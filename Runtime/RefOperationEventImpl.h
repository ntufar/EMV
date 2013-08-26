#ifndef REFOPERATIONEVENTIMPL_H
#define REFOPERATIONEVENTIMPL_H

#include "RefOperationEvent.h"

class RefOperationEventImpl :
	public RefOperationEvent
{
public:
	RefOperationEventImpl(void);
	virtual ~RefOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

