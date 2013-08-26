#ifndef SYSTEMOPERATIONEVENTWITHVALUE_H
#define SYSTEMOPERATIONEVENTWITHVALUE_H

#include "SystemOperationEvent.h"

class SystemOperationEventImpl :
	public SystemOperationEvent
{
public:
	SystemOperationEventImpl(void);
	virtual ~SystemOperationEventImpl(void);

	protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

