// Application Selection Interface
// Implements Operation Event to be used with Application Selection
#ifndef APPLSELOPERATIONEVENTIMPL_H
#define APPLSELOPERATIONEVENTIMPL_H

#include "ApplSelOperationEvent.h"

class ApplSelOperationEventImpl :
	public ApplSelOperationEvent
{
public:
	ApplSelOperationEventImpl(void);
	virtual ~ApplSelOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------

};

#endif
