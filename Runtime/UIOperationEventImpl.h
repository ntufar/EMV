// UIControl Service
// UI operation Event implementation

#ifndef UIOPERATIONEVENTIMPL_H
#define UIOPERATIONEVENTIMPL_H


#include "UIOperationEvent.h"

class UIOperationEventImpl :
	public UIOperationEvent
{
public:
	UIOperationEventImpl(void);
	virtual ~UIOperationEventImpl(void);

protected:
//--------------------------------------------------------------
	// Releases a dynamically allocated resource.
	virtual void releaseResource(void **pBuffer);
	// Dynamically allocates resource.
	virtual void* allocateResource(int typeSize, int bufferSize);
// -------------------------------------------------------------
};

#endif

