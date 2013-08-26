// CryptoControl service
// Operation Event implementation

#ifndef CRYPTOOPERATIONEVENTIMPL_H
#define CRYPTOOPERATIONEVENTIMPL_H

#include "CryptoOperationEvent.h"
//#include <Windows.h>

class CryptoOperationEventImpl :
	public CryptoOperationEvent
{
public:
	CryptoOperationEventImpl(void);
	virtual ~CryptoOperationEventImpl(void);

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

