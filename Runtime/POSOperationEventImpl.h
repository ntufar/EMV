// POSControl Service
// Operation Event implementation

#ifndef POSOPERATIONEVENTIMPL_H
#define POSOPERATIONEVENTIMPL_H

#include "POSOperationEvent.h"

class POSOperationEventImpl :
	public POSOperationEvent
{
public:
	POSOperationEventImpl(void);
	virtual ~POSOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------

};

#endif

