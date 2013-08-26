// CLC module Interface
// Defines the Operation Event implementation
#ifndef CLCOPERATIONEVENTIMPL_H
#define CLCOPERATIONEVENTIMPL_H


#include "CLCOperationEvent.h"

class CLCOperationEventImpl :
	public CLCOperationEvent
{
public:
	CLCOperationEventImpl(void);
	virtual ~CLCOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

