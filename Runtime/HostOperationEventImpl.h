// HostControl Service
// operation Event implementation

#ifndef HOSTOPERATIONEVENTIMPL_H
#define HOSTOPERATIONEVENTIMPL_H

#include "HostOperationEvent.h"

class HostOperationEventImpl :
	public HostOperationEvent
{
public:
	HostOperationEventImpl(void);
	virtual ~HostOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

