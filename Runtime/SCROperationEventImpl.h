// SCRControl Service
// Operation Event implementation.

#ifndef SCROPERATIONEVENTIMPL_H
#define SCROPERATIONEVENTIMPL_H

#include "SCROperationEvent.h"

class SCROperationEventImpl :
	public SCROperationEvent
{
public:
	SCROperationEventImpl(void);
	virtual ~SCROperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

